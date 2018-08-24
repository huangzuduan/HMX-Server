#include "CZhanJiRecordMgr.hpp"
#include "CZhanJiRecord.hpp"
#include "GameService.h"
#include "MysqlProtobufHelper.h"

::boost::object_pool<CZhanJiRecord> objpoolZhanJi;

void CZhanJiRecordMgr::LoadRecords()
{
	fogs::proto::msg::QueryHistoryResponse proLists;
	time_t limit_time = time(NULL) - 30 * 86400L;
	std::stringstream sql_data;
	sql_data << "select `record_id`,`room_id`,`room_info`,`role_info`,`time`,`innrecord`,`seat_total`,`inn_replay` from tb_zhanji where `time`>=" << limit_time << " order by time DESC;";
	int32_t nRet = doQueryRepeatedProto(*GameService::getMe().GetDataRef(), sql_data.str(), *proLists.mutable_record_list());

	UnSerialize(proLists);
}

void CZhanJiRecordMgr::UnSerialize(const fogs::proto::msg::QueryHistoryResponse proto)
{
	for (int i = 0; i < proto.record_list_size(); ++i)
	{
		const ::msg_maj::HistoryRecordS& recond = proto.record_list(i);
		AddRecord(recond);
	}
}

void CZhanJiRecordMgr::AddRecord(uint64_t record_id, const ::msg_maj::InnRecordS& innRecord, const ::msg_maj::InnReplayActionS& innReplay, uint32_t room_id, const ::msg_maj::RoomInfo* roomInfo, const ::msg_maj::RoleInfoListS* roleInfo, uint64_t time)
{
	CZhanJiRecord* obj = NULL;
	if (!GetByID(obj, record_id)) // 1 inn
	{
		if (NULL == roomInfo || NULL == roleInfo || 0 == room_id)
			return;
	
		::msg_maj::HistoryRecordS proto;
		proto.set_record_id(record_id);
		proto.set_room_id(room_id);
		proto.set_time(time);
		proto.mutable_room_info()->CopyFrom(*roomInfo);
		proto.mutable_role_info()->CopyFrom(*roleInfo);		
		proto.mutable_innrecord()->add_inn_list()->CopyFrom(innRecord);
		proto.mutable_inn_replay()->add_replay_list()->CopyFrom(innReplay); // 未打完回看添加在这里，保存后再转移到缓存中 

		obj = objpoolZhanJi.construct(proto);
		if (NULL == obj)
		{
			return;
		}

		if (!AddRecord(obj))
		{
			objpoolZhanJi.destroy(obj);
			return;
		}

		obj->SetIsFinished(false);

		if (obj->GetPlayer1()) AddUidRecordMap(obj->GetPlayer1(), obj);
		if (obj->GetPlayer2()) AddUidRecordMap(obj->GetPlayer2(), obj);
		if (obj->GetPlayer3()) AddUidRecordMap(obj->GetPlayer3(), obj);
		if (obj->GetPlayer4()) AddUidRecordMap(obj->GetPlayer4(), obj);

		obj->CountTotalScore();
	}
	else
	{
		if (obj) 
		{
			obj->AddInnRecord(innRecord,innReplay);
			obj->CountTotalScore();
		}
	}
}

void CZhanJiRecordMgr::AddUidRecordMap(uint64_t insertUID, CZhanJiRecord* obj)
{
	std::map<uint64_t, std::map<uint64_t, CZhanJiRecord* > >::iterator it = mapUidRecords.find(insertUID);
	if (it != mapUidRecords.end())
	{
		it->second.insert(std::make_pair(obj->GetRecordID(), obj));
	}
	else
	{
		std::map<uint64_t, CZhanJiRecord* > recordMap;
		recordMap.insert(std::make_pair(obj->GetRecordID(), obj));
		mapUidRecords.insert(std::make_pair(insertUID, recordMap));
	}
}

void CZhanJiRecordMgr::FinishRecord(uint64_t record_id)
{
	// 检查是否有记录
	CZhanJiRecord* obj = NULL;
	if (GetByID(obj, record_id) && obj) // 1 inn
	{
		obj->SetIsFinished(true);
		::msg_maj::HistoryRecordS proLists;
		proLists.CopyFrom(obj->GetHistoryRecordS());
		doInsertProto(*GameService::getMe().GetDataRef(), "tb_zhanji", proLists);
	}
}

void CZhanJiRecordMgr::SendZhanjiReply(zSession* pSession, const fogs::proto::msg::ZhanjiQueryReply& proto)
{
	CZhanJiRecord* obj = NULL;
	if (CZhanJiRecordMgr::Instance()->GetByID(obj, proto.req().record_id()))
	{
		fogs::proto::msg::ZhanjiRespReply sendProto;
		sendProto.set_char_id(proto.char_id());
		::msg_maj::ReplayResp& resp = *sendProto.mutable_resp();
		const ::msg_maj::HistoryRecordS& recordS = obj->GetHistoryRecordS();
		resp.mutable_room_info()->CopyFrom(recordS.room_info());
		for (int i = 0; i < recordS.role_info().role_list_size(); ++i)
		{
			::msg_maj::RoleInfo* roleInfo = resp.add_user_info_list();
			if (roleInfo)
			{
				const ::msg_maj::RoleInfoS& infoData = recordS.role_info().role_list(i);
				roleInfo->set_seat_id(infoData.seat());
				roleInfo->set_uid(infoData.uid());
				roleInfo->set_logo_icon(infoData.actor_addr());
				roleInfo->set_nickname(infoData.nick());
				roleInfo->set_status(1);
				roleInfo->set_score(0); // 默认值，前端无需要显示 
				roleInfo->set_sexual(0);
			}
		}

		bool bFindInn = false;
		for (int i = 0; i < recordS.innrecord().inn_list_size(); ++i)
		{
			const ::msg_maj::InnRecordS& inn = recordS.innrecord().inn_list(i);
			if (inn.inn_id() == proto.req().inn_id())
			{
				resp.set_banker_seat(inn.banker_seat());
				resp.set_dice(inn.dice());
				for (int j = 0; j < inn.seat_info_size(); ++j)
				{
					resp.add_seat_list()->CopyFrom(inn.seat_info(j));
				}
				bFindInn = true;
				break;
			}
		}

		if (false == bFindInn)
		{
			return;
		}

		const ::msg_maj::InnReplayActionListS& replayAction = recordS.inn_replay();
		for (int i = 0; i < replayAction.replay_list_size(); ++i)
		{
			if (proto.req().inn_id() == i + 1)
			{
				const ::msg_maj::InnReplayActionS* innReplayS = &replayAction.replay_list(i);
				if (!innReplayS)
				{
					return;
				}
				for (int i = 0; i < innReplayS->replay_list_size(); ++i)
				{
					resp.add_action_list()->CopyFrom(innReplayS->replay_list(i));
				}
				break;
			}
		}

		pSession->sendMsgProto(::comdef::msg_ss, ::msg_maj::ZhanjiRespReplyResponseID,sendProto);

	}
}

void CZhanJiRecordMgr::AddRecord(const ::msg_maj::HistoryRecordS& record)
{
	CZhanJiRecord* obj = objpoolZhanJi.construct(record);
	if (NULL == obj)
	{
		return;
	}

	if (!AddRecord(obj))
	{
		objpoolZhanJi.destroy(obj);
		return;
	}

	AddUidRecordMap(obj->GetPlayer1(), obj);
	AddUidRecordMap(obj->GetPlayer2(), obj);
	AddUidRecordMap(obj->GetPlayer3(), obj);
	AddUidRecordMap(obj->GetPlayer4(), obj);
}

bool CZhanJiRecordMgr::AddRecord(CZhanJiRecord *obj)
{
	return zEntryMgr< zEntryID<0> >::addEntry(obj);
}

bool CZhanJiRecordMgr::GetByID(CZhanJiRecord* &entry, uint64_t nRecordID)
{
	CZhanJiRecord* obj = (CZhanJiRecord*)zEntryMgr< zEntryID<0> >::getEntryByID(nRecordID);
	if (obj)
	{
		if (CheckAndRelease(obj))
		{
			entry = NULL;
			return false;
		}
		entry = obj;
		return true;
	}
	return false;
}

bool CZhanJiRecordMgr::GetByUID(std::vector<CZhanJiRecord*>& vecEntry, uint64_t uid)
{
	std::map<uint64_t, CZhanJiRecord*,std::greater<uint64_t> > mapSortEntryGreator;
	std::map<uint64_t, std::map<uint64_t, CZhanJiRecord* > >::const_iterator it = mapUidRecords.find(uid);
	if (it != mapUidRecords.end())
	{
		const std::map<uint64_t, CZhanJiRecord* >& idRecordMap = it->second;
		for (std::map<uint64_t, CZhanJiRecord* >::const_iterator it2 = idRecordMap.begin(); it2 != idRecordMap.end(); ++it2)
		{
			mapSortEntryGreator.insert(std::make_pair(it2->second->GetRecordTime(), it2->second));
		}
	}
	if (!mapSortEntryGreator.empty())
	{
		std::map<uint64_t, CZhanJiRecord*, std::greater<uint64_t> >::iterator it = mapSortEntryGreator.begin();
		for (; it != mapSortEntryGreator.end(); ++it)
		{
			if (CheckAndRelease(it->second))
				continue;
			vecEntry.push_back(it->second);
		}
	}
	return !mapSortEntryGreator.empty();
}

bool CZhanJiRecordMgr::GetByUIDRecordID(CZhanJiRecord* &entry, uint64_t uid, uint64_t nRecordID)
{
	std::map<uint64_t, std::map<uint64_t, CZhanJiRecord* > >::const_iterator it = mapUidRecords.find(uid);
	if (it != mapUidRecords.end())
	{
		const std::map<uint64_t, CZhanJiRecord* >& idRecordMap = it->second;
		std::map<uint64_t, CZhanJiRecord* >::const_iterator it2 = idRecordMap.find(nRecordID);
		if (it2 != idRecordMap.end())
		{
			entry = it2->second;
			return true;
		}
	}
	return false;
}

bool CZhanJiRecordMgr::CheckAndRelease(CZhanJiRecord *obj)
{
	if (obj->IsExpire())
	{
		// 去掉所有索引
		zEntryMgr< zEntryID<0> >::removeEntry(obj);

		std::vector<uint64_t> vecUids;
		vecUids.push_back(obj->GetPlayer1());
		vecUids.push_back(obj->GetPlayer2());
		vecUids.push_back(obj->GetPlayer3());
		vecUids.push_back(obj->GetPlayer4());

		for (std::vector<uint64_t>::iterator it = vecUids.begin(); it != vecUids.end(); ++it)
		{
			std::map<uint64_t, std::map<uint64_t, CZhanJiRecord* > >::iterator it2 = mapUidRecords.find(*it);
			if (it2 != mapUidRecords.end())
			{
				std::map<uint64_t, CZhanJiRecord* >::iterator it3 = it2->second.find(obj->GetRecordID());
				if (it3 != it2->second.end())
				{
					it2->second.erase(it3);
				}
			}
		}
		objpoolZhanJi.destroy(obj);
		return true;
	}
	return false;
}
