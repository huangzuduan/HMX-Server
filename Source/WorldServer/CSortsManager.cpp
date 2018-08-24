#include "CSortsManager.hpp"
#include "SrvEngine.h"
#include "MysqlProtobufHelper.h"
#include "GameService.h"

// 凌晨5点，所以-18000
inline time_t GetLastTurnYmd(time_t now_t = 0)
{
	time_t now = now_t == 0? time(NULL): now_t;
	now -= 18000;
	struct tm* t = localtime(&now);
	t->tm_hour = 0;
	t->tm_min = 0;
	t->tm_sec = 0;
	time_t todayStart = mktime(t);
	return todayStart;
}

CSortsManager::CSortsManager() : sortTempWins(SORT_ITEM_WINS, "胜局排行榜", SORT_CYCLE_DAY, 100)
, sortTempScore(SORT_ITEM_SCORE, "积分排行榜", SORT_CYCLE_DAY, 100)
, m_pTimer(NULL)
{
	m_lastTurnYmd = GetLastTurnYmd(); // 合适的做法是要从数据库中获得
}

CSortsManager::~CSortsManager()
{
	if (m_pTimer)
	{
		m_pTimer->cancel();
		S_SAFE_DELETE(m_pTimer);
	}
};

void CSortsManager::Init()
{
	m_pTimer = new fogs::FogsTimer(*GameService::getMe().GetIoService());
	m_pTimer->start(60 * 1000, boost::bind(&CSortsManager::Timer, this), fogs::FogsTimer::PERIODICAL_TIMER);
}

void CSortsManager::Serialize(fogs::proto::msg::QuerySaveRanks& proto)
{
	if (proto.ranktype() == msg_maj::rank_t_wins)
	{
		std::vector<SortWinsValue> listTop;
		sortTempWins.GetAllList(listTop, 100);
		for (size_t i = 0; i < listTop.size(); ++i)
		{
			SortWinsValue& item = listTop[i];
			msg_maj::WinsInfo* row = proto.add_winsinfo();
			if (row == NULL)
				continue;
			row->set_uid(item.uid);
			row->set_name(item.name);
			row->set_value(item.value);
			row->set_time(item.time);
			row->set_sort(item.sort);
			row->set_type(item.type);
			row->set_actor_addr(item.actor_addr);
		}
	}
	else if (proto.ranktype() == msg_maj::rank_t_score)
	{
		std::vector<SortScoreValue> listTop;
		sortTempScore.GetAllList(listTop, 100);
		for (int i = 0; i < listTop.size(); ++i)
		{
			SortScoreValue& item = listTop[i];
			msg_maj::ScoreInfo* row = proto.add_scoreinfo();
			if (row == NULL)
				continue;
			row->set_uid(item.uid);
			row->set_name(item.name);
			row->set_value(item.value);
			row->set_time(item.time);
			row->set_sort(item.sort);
			row->set_type(item.type);
			row->set_actor_addr(item.actor_addr);
		}
	}
}

void CSortsManager::UnSerialize(const fogs::proto::msg::QuerySaveRanks& proto)
{
	if (proto.ranktype() == msg_maj::rank_t_wins)
	{
		for (int i = 0; i < proto.winsinfo_size(); ++i)
		{
			const msg_maj::WinsInfo& row = proto.winsinfo(i);
			SortWinsKey key;
			key.uid = row.uid();
			key.name = row.name();
			key.value = row.value();
			key.time = row.time();
			key.sort = row.sort();
			key.type = row.type();
			SortWinsValue val(key);
			val.actor_addr = row.actor_addr();
			if (key.type == 0)
				sortTempWins.AddSort(key, val);
			else
				sortTempWins.AddLastSort(key, val);
		}
	}
	else if (proto.ranktype() == msg_maj::rank_t_score)
	{
		for (size_t i = 0; i < proto.scoreinfo_size(); ++i)
		{
			const msg_maj::ScoreInfo& row = proto.scoreinfo(i);
			SortScoreKey key;
			key.uid = row.uid();
			key.name = row.name();
			key.value = row.value();
			key.time = row.time();
			key.sort = row.sort();
			key.type = row.type();
			SortScoreValue val(key);
			val.actor_addr = row.actor_addr();
			if (key.type == 0)
				sortTempScore.AddSort(key, val);
			else
				sortTempScore.AddLastSort(key, val);
		}
	}
}

void CSortsManager::loadDB()
{

	{
		// 加载排行榜基本表
		fogs::proto::msg::QueryBase queryBase;
		std::stringstream sql_data;
		sql_data << "select `id`,`value` from `tb_base` where `id`=1";
		doQueryProto(*GameService::getMe().GetDataRef(), sql_data.str(), queryBase);
		m_lastTurnYmd = GetLastTurnYmd(queryBase.value());
	}

	{
		fogs::proto::msg::QuerySaveRanks proLists;
		proLists.set_ranktype(msg_maj::rank_t_wins);

		std::stringstream sql_data;
		sql_data << "select `uid`,`name`,`value`,`sort`,`time`,`type`,`actor_addr` from tb_rankwins";
		doQueryRepeatedProto(*GameService::getMe().GetDataRef(), sql_data.str(), *proLists.mutable_winsinfo());
		UnSerialize(proLists);
	}

	{
		fogs::proto::msg::QuerySaveRanks proLists;
		proLists.set_ranktype(msg_maj::rank_t_score);

		std::stringstream sql_data;
		sql_data << "select `uid`,`name`,`value`,`sort`,`time`,`type`,`actor_addr` from tb_rankscore";
		doQueryRepeatedProto(*GameService::getMe().GetDataRef(), sql_data.str(), *proLists.mutable_winsinfo());
		UnSerialize(proLists);
	}

}

void CSortsManager::SaveAllSorts()
{
	SaveWinsSort();
	SaveScoreSort();
}

void CSortsManager::SaveWinsSort()
{
	{
		std::stringstream sql_data;
		sql_data << "delete from tb_rankwins;";
		doQuery(*GameService::getMe().GetDataRef(), sql_data.str());
	}
	fogs::proto::msg::QuerySaveRanks proLists;
	proLists.set_ranktype(::msg_maj::rank_t_wins);
	Serialize(proLists);
	if (proLists.winsinfo_size() > 0)
	{
		std::stringstream smData;
		smData << "replace into tb_rankwins(uid,name,value,sort,time,type,actor_addr) values ";
		for (int i = 0; i < proLists.winsinfo_size(); ++i)
		{
			const ::msg_maj::WinsInfo& info = proLists.winsinfo(i);

			if (i == 0)
				smData << "(";
			else
				smData << ",(";

			smData << info.uid() << ","
				<< "'" << info.name() << "',"
				<< info.value() << ","
				<< info.sort() << ","
				<< info.time() << ","
				<< info.type() << ", "
				<< "'" << info.actor_addr() << "')";
		}

		int32_t nRet = doQuery(*GameService::getMe().GetDataRef(), smData.str());
		if (nRet == 0)
		{
			H::logger->info("tb_rankwins update data success!");
		}
		else
		{
			H::logger->error("tb_rankwins update data failure!");
		}
	}
}

void CSortsManager::SaveScoreSort()
{
	std::stringstream sql_data;
	sql_data << "delete from tb_rankscore;";
	doQuery(*GameService::getMe().GetDataRef(), sql_data.str());

	fogs::proto::msg::QuerySaveRanks proLists;
	Serialize(proLists);

	if (proLists.scoreinfo_size() > 0)
	{
		std::stringstream smData;
		smData << "replace into tb_rankscore(uid,name,value,sort,time,type,actor_addr) values ";
		for (int i = 0; i < proLists.scoreinfo_size(); ++i)
		{
			const ::msg_maj::ScoreInfo& info = proLists.scoreinfo(i);

			if (i == 0)
				smData << "(";
			else
				smData << ",(";

			smData << info.uid() << ","
				<< "'" << info.name() << "',"
				<< info.value() << ","
				<< info.sort() << ","
				<< info.time() << ","
				<< info.type() << ", "
				<< "'" << info.actor_addr() << "')";
		}

		int32_t nRet = doQuery(*GameService::getMe().GetDataRef(), smData.str());
		if (nRet == 0)
		{
			H::logger->info("tb_rankscore update data success!");
		}
		else
		{
			H::logger->info("tb_rankscore update data failure!");
		}
			
	}

}

void CSortsManager::Update(const SortWinsKey& key, const SortWinsValue& value)
{
	sortTempWins.UpdateSort(key, value);
}

void CSortsManager::Update(const SortScoreKey& key, const SortScoreValue& value)
{
	sortTempScore.UpdateSort(key, value);
}

void  CSortsManager::Timer()
{
	time_t todayYmd = GetLastTurnYmd();
	if (todayYmd != m_lastTurnYmd) // 1分钟之内检查
	{
		m_lastTurnYmd = todayYmd;
		sortTempWins.TurnLast();
		sortTempScore.TurnLast();
		SaveAllSorts();

		std::stringstream smData;
		smData << "replace into tb_base(id,value,sort,time,type,actor_addr) values (";
		smData << "1," << m_lastTurnYmd << ")";
		doQuery(*GameService::getMe().GetDataRef(), smData.str());
	}
	else
	{
		SaveAllSorts();
	}
}

void CSortsManager::SendTopList(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	//sQueryRankRequest::
	fogs::proto::msg::QueryRankReqResp proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	fogs::proto::msg::QueryRankReqResp sendProto;
	::msg_maj::RankResp* resp = sendProto.mutable_ranklist();
	switch (proto.ranktype())
	{
	case msg_maj::rank_t_wins:
	{
		std::vector<SortWinsValue> vecSort;
		if (proto.last() == 0)
			sortTempWins.GetTopList(vecSort, 10);
		else
			sortTempWins.GetLastTopList(vecSort, 10);
		
		for (int i = 0; i < vecSort.size(); ++i)
		{
			const SortWinsValue& val = vecSort[i];
			::msg_maj::RankInfo* info = resp->add_rank();
			if (info)
			{
				info->set_uid(val.uid);
				info->set_name(val.name);
				info->set_value(val.value);
				info->set_sort(val.sort);
				info->set_actor_addr(val.actor_addr);
			}
		}
	}
	break;
	case msg_maj::rank_t_score:
	{
		std::vector<SortScoreValue> vecSort;
		if (proto.last() == 0)
			sortTempScore.GetTopList(vecSort, 10);
		else
			sortTempScore.GetLastTopList(vecSort, 10);

		for (size_t i = 0; i < vecSort.size(); ++i)
		{
			const SortScoreValue& val = vecSort[i];
			::msg_maj::RankInfo* info = resp->add_rank();
			if (info)
			{
				info->set_uid(val.uid);
				info->set_name(val.name);
				info->set_value(val.value);
				info->set_sort(val.sort);
				info->set_actor_addr(val.actor_addr);
			}
		}
	}
	break;
	default:
		break;
	}

	std::pair<int32_t, int32_t> myRankScore;
	GetMyTopList(proto.char_id(), proto.ranktype(), myRankScore);

	resp->set_sorttype(proto.ranktype());
	resp->set_last(proto.last());
	resp->set_mysort(myRankScore.first);
	resp->set_myvalue(myRankScore.second);

	sendProto.set_ranktype(proto.ranktype());
	sendProto.set_last(proto.last());
	sendProto.set_char_id(proto.char_id());
	pSession->sendMsgProto(::comdef::msg_ss, ::msg_maj::QueryRankResponseID, pMsg->clientSessID,pMsg->fepServerID, sendProto);
}

void CSortsManager::GetMyTopList(uint64_t nCharID, ::msg_maj::rank_type rankType, std::pair<int32_t, int32_t>& myRankScore)
{
	switch (rankType)
	{
		case msg_maj::rank_t_wins:
		{
			const SortWinsValue* myVal = sortTempWins.FindSortValue(nCharID);
			if (myVal)
			{
				myRankScore.first = myVal->sort;
				myRankScore.second = myVal->value;
			}
			else
			{
				myRankScore.first = 0;
				myRankScore.second = 0;
			}
			break;
		}
		case msg_maj::rank_t_score:
		{
			const SortScoreValue* myVal = sortTempScore.FindSortValue(nCharID);
			if (myVal)
			{
				myRankScore.first = myVal->sort;
				myRankScore.second = myVal->value;
			}
			else
			{
				myRankScore.first = 0;
				myRankScore.second = 0;
			}
			break;
		}
	}
}

