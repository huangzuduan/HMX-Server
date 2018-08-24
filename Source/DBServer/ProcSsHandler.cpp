#include "ProcSsHandler.h"
#include "SrvIncludes.h"
#include "base/hmx_data.pb.h"
#include "maj/msg_mail.pb.h"
#include "MysqlProtobufHelper.h"
#include "GameService.h"
#include "CZhanJiRecord.hpp"
#include "CZhanJiRecordMgr.hpp"
#include "ProcWorldHandler.h"

struct stOtherRoleInfo
{
	std::string nick;
	std::string actor_addr;
};

ProcSsHandler::ProcSsHandler(void)
{
}

ProcSsHandler::~ProcSsHandler(void)
{
}

void ProcSsHandler::onQueryPlayerRequest(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::QueryPlayerRequest proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);

	fogs::proto::msg::QueryPlayerResponse sendProto;
	std::stringstream dataSql;
	dataSql << "select * from `tb_role` where id = " << proto.uid();
	int32_t nRet = doQueryProto(*GameService::Instance()->GetDataRef(), dataSql.str(), *sendProto.mutable_role_info());
	sendProto.set_result(nRet == 0 ? 0:1);
	sendProto.set_room_id(proto.room_id());
	pSession->sendMsgProto(::comdef::msg_ss,::msg_maj::QueryPlayerResponseID, pMsg->clientSessID,pMsg->fepServerID,sendProto);
}

void ProcSsHandler::onSavePlayerDataReq(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::SavePlayerRequest proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);

	msg_maj::Role m_proData;
	m_proData.CopyFrom(proto.role_info());
	std::stringstream smData;

	MYSQL* mysqlRef = GameService::Instance()->GetDataRef()->getMysqlRef();

	smData << "replace into tb_role(id, account, nickname, level, logo_icon, title, diamond, coin, sexual, room_card, total_games, win_games, con_games, "
		<< "his_max_score,his_max_con, week_max_score, top_wins_ymd, top_wins_total, top_score_ymd, top_score_total, blocktime, today_play_num, login_time, ip, data) values("
		<< m_proData.id() << ", "
		<< ::db::StringMysqlString(mysqlRef, m_proData.account()) << ", "
		<< ::db::StringMysqlString(mysqlRef, m_proData.nickname()) << ", "
		<< m_proData.level() << ", "
		<< ::db::StringMysqlString(mysqlRef, m_proData.logo_icon()) << ", "
		<< m_proData.title() << ", "
		<< m_proData.diamond() << ", "
		<< m_proData.coin() << ", "
		<< m_proData.sexual() << ", "
		<< m_proData.room_card() << ", "
		<< m_proData.total_games() << ", "
		<< m_proData.win_games() << ", "
		<< m_proData.con_games() << ", "
		<< m_proData.his_max_score() << ", "
		<< m_proData.his_max_con() << ", "
		<< m_proData.week_max_score() << ", "
		<< m_proData.top_wins_ymd() << ", "
		<< m_proData.top_wins_total() << ", "
		<< m_proData.top_score_ymd() << ", "
		<< m_proData.top_score_total() << ", "
		<< m_proData.blocktime() << ", "
		<< m_proData.today_play_num() << ", "
		<< m_proData.login_time() << ", "
		<< m_proData.ip() << ", "
		<< ::db::ProtoMysqlString(mysqlRef, m_proData.data()) << ")";
	doQuery(*GameService::Instance()->GetDataRef(), smData.str());

}

void ProcSsHandler::onZhanjiAddRecordRequest(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::ZhanjiRecordAdd proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CZhanJiRecordMgr::getMe().AddRecord(proto.record_id(), proto.inn_record(), proto.inn_replay(), proto.room_id(), &proto.room_info(), &proto.role_info(), proto.start_time());
}

void ProcSsHandler::onZhanjiFinishRequest(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::ZhanJiFinish proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CZhanJiRecordMgr::getMe().FinishRecord(proto.record_id());
}

void ProcSsHandler::onZhanjiQueryList(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::ZhanjiQueryList proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	if (proto.req().type() == ::msg_maj::total_list)
	{
		fogs::proto::msg::ZhanjiQueryResp sendProto;
		sendProto.set_char_id(proto.char_id());
		::msg_maj::HistoryListResp* resp = sendProto.mutable_resp();
		resp->set_type(proto.req().type());
		std::vector<CZhanJiRecord*> vecEntry;
		if (CZhanJiRecordMgr::getMe().GetByUID(vecEntry, proto.char_id()))
		{
			int32_t nCount = 0;
			std::vector<CZhanJiRecord*>::iterator it = vecEntry.begin();
			for (; it != vecEntry.end(); ++it)
			{
				if (proto.req().start_index() == 0 || (*it)->GetRecordID() < proto.req().start_index())
				{
					if ((*it)->GetIsFinished())
					{
						Recond2ProtoC((*it)->GetHistoryRecordS(), *(resp->add_record_list()));
						if (++nCount >= 4)
							break;
					}
				}
			}
		}
		pSession->sendMsgProto(::comdef::msg_ss, ::msg_maj::ZhanjiQueryListResponseID, pMsg->clientSessID,pMsg->fepServerID, sendProto);
	}
}

void ProcSsHandler::onZhanjiRoomList(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::ZhanjiQueryRoom proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	if (proto.req().type() == ::msg_maj::total_list)
	{
		fogs::proto::msg::ZhanjiQueryRoomResp sendProto;
		sendProto.set_char_id(proto.char_id());
		CZhanJiRecord* record = NULL;
		if (CZhanJiRecordMgr::Instance()->GetByUIDRecordID(record, proto.char_id(), proto.req().record_id()))
		{
			if (record->GetIsFinished())
			{
				::msg_maj::HistoryRoomResp* resp = sendProto.mutable_resp();
				resp->set_type(proto.req().type());
				Recond2ProtoCRoom(record->GetHistoryRecordS(), *resp);
				pSession->sendMsgProto(::comdef::msg_ss, ::msg_maj::ZhanjiQueryRoomResponseID, pMsg->clientSessID, pMsg->fepServerID, sendProto);
			}
		}
	}
}

void ProcSsHandler::onZhanjiInnList(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::ZhanjiQueryInnReq proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	fogs::proto::msg::ZhanjiQueryInnResp sendProto;
	sendProto.set_char_id(proto.char_id());
	CZhanJiRecord* record = NULL;
	if (CZhanJiRecordMgr::Instance()->GetByUIDRecordID(record, proto.char_id(), proto.req().record_id()))
	{
		if (record->GetIsFinished())
		{
			::msg_maj::HistoryInnResp* resp = sendProto.mutable_resp();
			Recond2ProtoCInn(record->GetHistoryRecordS(), *resp, proto.req().inn_id());
			pSession->sendMsgProto(::comdef::msg_ss, ::msg_maj::ZhanjiQueryInnResponseID, pMsg->clientSessID, pMsg->fepServerID, sendProto);
		}
	}
}

void ProcSsHandler::Recond2ProtoC(const ::msg_maj::HistoryRecordS& srcProto, ::msg_maj::HistoryRecord& distProto)
{
	distProto.set_record_id(srcProto.record_id());
	distProto.set_room_id(srcProto.room_id());
	distProto.mutable_option()->CopyFrom(srcProto.room_info().option());
	distProto.set_time(srcProto.time());

	std::map<uint32_t, stOtherRoleInfo> mapSeatName;
	const ::msg_maj::RoleInfoListS& roleInfos = srcProto.role_info();
	for (int j = 0; j < roleInfos.role_list_size(); ++j)
	{
		stOtherRoleInfo otherInfo;
		otherInfo.nick = roleInfos.role_list(j).nick();
		otherInfo.actor_addr = roleInfos.role_list(j).actor_addr();
		mapSeatName.insert(std::make_pair(roleInfos.role_list(j).seat(), otherInfo));
	}

	for (int i = 0; i < srcProto.seat_total().score_list_size(); ++i)
	{
		::msg_maj::SeatTotalScore* seatTotalInfo = distProto.add_score_list();
		if (seatTotalInfo)
		{
			const ::msg_maj::SeatTotalScoreS& seatTotalData = srcProto.seat_total().score_list(i);
			seatTotalInfo->set_seat_id(seatTotalData.seat_id());
			seatTotalInfo->set_score(seatTotalData.score());
			seatTotalInfo->set_nickname(mapSeatName[seatTotalData.seat_id()].nick);
			seatTotalInfo->set_actor_addr(mapSeatName[seatTotalData.seat_id()].actor_addr);
		}
	}
}

void ProcSsHandler::Recond2ProtoCRoom(const ::msg_maj::HistoryRecordS& srcProto, ::msg_maj::HistoryRoomResp& distProto)
{
	distProto.set_record_id(srcProto.record_id());
	distProto.set_room_id(srcProto.room_id());
	distProto.mutable_option()->CopyFrom(srcProto.room_info().option());
	for (int i = 0; i < srcProto.innrecord().inn_list_size(); ++i)
	{
		::msg_maj::InnRecord* innInfo = distProto.add_inn_list();
		if (innInfo)
		{
			const ::msg_maj::InnRecordS& innData = srcProto.innrecord().inn_list(i);
			innInfo->set_inn_id(innData.inn_id());
			innInfo->set_banker_seat(innData.banker_seat());
			innInfo->set_dice(innData.dice());
			innInfo->set_close_type(innData.close_type());
			for (int j = 0; j < innData.seat_result_size(); ++j)
			{
				innInfo->add_seat_result()->CopyFrom(innData.seat_result(j));
			}
			DUMP_PROTO_MSG(*innInfo);
		}
	}

	std::map<uint32_t, stOtherRoleInfo> mapSeatName;
	const ::msg_maj::RoleInfoListS& roleInfos = srcProto.role_info();
	for (int j = 0; j < roleInfos.role_list_size(); ++j)
	{
		stOtherRoleInfo otherInfo;
		otherInfo.nick = roleInfos.role_list(j).nick();
		otherInfo.actor_addr = roleInfos.role_list(j).actor_addr();
		mapSeatName.insert(std::make_pair(roleInfos.role_list(j).seat(), otherInfo));
	}

	for (int i = 0; i < srcProto.seat_total().score_list_size(); ++i)
	{
		::msg_maj::SeatTotalScore* seatTotalInfo = distProto.add_score_list();
		if (seatTotalInfo)
		{
			const ::msg_maj::SeatTotalScoreS& seatTotalData = srcProto.seat_total().score_list(i);
			seatTotalInfo->set_seat_id(seatTotalData.seat_id());
			seatTotalInfo->set_score(seatTotalData.score());
			seatTotalInfo->set_nickname(mapSeatName[seatTotalData.seat_id()].nick);
			seatTotalInfo->set_actor_addr(mapSeatName[seatTotalData.seat_id()].actor_addr);
		}
	}
}

void ProcSsHandler::Recond2ProtoCInn(const ::msg_maj::HistoryRecordS& srcProto, ::msg_maj::HistoryInnResp& distProto, int32_t inn_id)
{
	distProto.set_record_id(srcProto.record_id());
	distProto.set_room_id(srcProto.room_id());
	distProto.mutable_option()->CopyFrom(srcProto.room_info().option());
	for (int i = 0; i < srcProto.innrecord().inn_list_size(); ++i)
	{
		const ::msg_maj::InnRecordS& innData = srcProto.innrecord().inn_list(i);
		if (innData.inn_id() == inn_id)
		{
			::msg_maj::InnRecord* innInfo = distProto.mutable_inn();
			if (innInfo)
			{
				innInfo->set_inn_id(innData.inn_id());
				innInfo->set_banker_seat(innData.banker_seat());
				innInfo->set_dice(innData.dice());
				innInfo->set_close_type(innData.close_type());
				for (int j = 0; j < innData.seat_result_size(); ++j)
				{
					innInfo->add_seat_result()->CopyFrom(innData.seat_result(j));
				}
			}
			break;
		}
	}

	std::map<uint32_t, stOtherRoleInfo> mapSeatName;
	const ::msg_maj::RoleInfoListS& roleInfos = srcProto.role_info();
	for (int j = 0; j < roleInfos.role_list_size(); ++j)
	{
		stOtherRoleInfo otherInfo;
		otherInfo.nick = roleInfos.role_list(j).nick();
		otherInfo.actor_addr = roleInfos.role_list(j).actor_addr();
		mapSeatName.insert(std::make_pair(roleInfos.role_list(j).seat(), otherInfo));
	}

	for (int i = 0; i < srcProto.seat_total().score_list_size(); ++i)
	{
		::msg_maj::SeatTotalScore* seatTotalInfo = distProto.add_score_list();
		if (seatTotalInfo)
		{
			const ::msg_maj::SeatTotalScoreS& seatTotalData = srcProto.seat_total().score_list(i);
			seatTotalInfo->set_seat_id(seatTotalData.seat_id());
			seatTotalInfo->set_score(seatTotalData.score());
			seatTotalInfo->set_nickname(mapSeatName[seatTotalData.seat_id()].nick);
			seatTotalInfo->set_actor_addr(mapSeatName[seatTotalData.seat_id()].actor_addr);
		}
	}
}

void ProcSsHandler::onZhanjiQueryReply(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::ZhanjiQueryReply proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CZhanJiRecordMgr::getMe().SendZhanjiReply(pSession, proto);
}

void ProcSsHandler::onInnRecordAddLogRequest(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	::fogs::proto::msg::MatchUserInfo proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	MYSQL* mysqlRef = GameService::Instance()->GetLogRef()->getMysqlRef();
	std::stringstream smData;
	smData << "insert into tb_match_user ("
		<< "record_id, record_time, room_no, inn_id, match_id, inn_time, huway, hutype, huseat,"
		<< "u_1_id,u_1_score,u_1_total,u_1_angang,u_1_minggang,u_1_goushouggang,"
		<< "u_2_id,u_2_score,u_2_total,u_2_angang,u_2_minggang,u_2_goushouggang,"
		<< "u_3_id,u_3_score,u_3_total,u_3_angang,u_3_minggang,u_3_goushouggang,"
		<< "u_4_id,u_4_score,u_4_total,u_4_angang,u_4_minggang,u_4_goushouggang,"
		<< "hupaitiles"
		<< ") values("
		<< proto.record_id() << ", "
		<< proto.record_time() << ", "
		<< proto.room_no() << ", "
		<< proto.inn_id() << ", "
		<< proto.match_id() << ", "
		<< proto.inn_time() << ", "
		<< proto.huway() << ", "
		<< proto.hutype() << ", "
		<< proto.huseat() << ", "

		<< proto.u_1_id() << ", "
		<< proto.u_1_score() << ", "
		<< proto.u_1_total() << ", "
		<< proto.u_1_angang() << ", "
		<< proto.u_1_minggang() << ", "
		<< proto.u_1_goushouggang() << ", "

		<< proto.u_2_id() << ", "
		<< proto.u_2_score() << ", "
		<< proto.u_2_total() << ", "
		<< proto.u_2_angang() << ", "
		<< proto.u_2_minggang() << ", "
		<< proto.u_2_goushouggang() << ", "

		<< proto.u_3_id() << ", "
		<< proto.u_3_score() << ", "
		<< proto.u_3_total() << ", "
		<< proto.u_3_angang() << ", "
		<< proto.u_3_minggang() << ", "
		<< proto.u_3_goushouggang() << ", "

		<< proto.u_4_id() << ", "
		<< proto.u_4_score() << ", "
		<< proto.u_4_total() << ", "
		<< proto.u_4_angang() << ", "
		<< proto.u_4_minggang() << ", "
		<< proto.u_4_goushouggang() << ", "
		<< ::db::ProtoMysqlString(mysqlRef, proto.hupaitiles()) << ")";

	doQuery(*GameService::Instance()->GetLogRef(), smData.str());
}

void ProcSsHandler::onQueryMailRequest(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::QueryMailRequest proReq;
	proReq.ParseFromArray(pMsg->data, pMsg->size);
	if (proReq.uid() == 0) // 系统通知邮件
	{

	}
	else
	{
		fogs::proto::msg::QueryMailResponse sendProto;
		std::stringstream dataSql;
		dataSql << "select * from `tb_mail` where `to_id` = " << proReq.uid();
		doQueryRepeatedProto(*GameService::Instance()->GetDataRef(), dataSql.str(), *sendProto.mutable_record_list());
		sendProto.set_uid(proReq.uid());
		sendProto.set_last_num(0);
		pSession->sendMsgProto(::comdef::msg_ss, ::msg_maj::QueryMailResponseID, pMsg->clientSessID, pMsg->fepServerID, sendProto);
	}
}

void ProcSsHandler::onSaveMailRequest(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::SaveMailRequest proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	doReplaceProto(*GameService::getMe().GetDataRef(), "tb_mail", proto.records());
}

void ProcSsHandler::onQueryMailSysLogRequest(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::QueryMailSystemLogRequest proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);

	fogs::proto::msg::QueryMailSystemLogResponse proLists;

	time_t limit_time = time(NULL) - 14 * 86400L;
	std::stringstream sql_data;
	sql_data << "select * from tb_mailsyslog ";
	int32_t nRet = doQueryRepeatedProto(*GameService::getMe().GetDataRef(), sql_data.str(), *proLists.mutable_record_list());

	int nTotalCount = proLists.record_list_size();
	int nCount = 0;
	int nSendCount = 0;
	fogs::proto::msg::QueryMailSystemLogResponse sendLists;
	for (int i = 0; i < nTotalCount; ++i)
	{
		sendLists.add_record_list()->CopyFrom(proLists.record_list(i));
		nSendCount++;
		nCount++;
		if (nCount >= 400)
		{
			sendLists.set_uid(proto.uid());
			sendLists.set_last_num(nTotalCount - nSendCount);
			pSession->sendMsgProto(::comdef::msg_ss,::msg_maj::QueryMailSysLogResponseID, pMsg->clientSessID,pMsg->fepServerID, sendLists);
			sendLists.Clear();
			nCount = 0;
		}
	}

	if (nCount)
	{
		sendLists.set_uid(proto.uid());
		sendLists.set_last_num(nTotalCount - nSendCount);
		pSession->sendMsgProto(::comdef::msg_ss, ::msg_maj::QueryMailSysLogResponseID, pMsg->clientSessID, pMsg->fepServerID, sendLists);
		sendLists.Clear();
		nCount = 0;
	}

}

void ProcSsHandler::onSaveMailSysLogRequest(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::SaveMailSystemLogRequest proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	const ::msg_maj::MailSystemLogS& m_proData = proto.records();
	std::stringstream smData;
	smData << "replace into tb_mailsyslog(id, mail_id, uid, mark, create_time, fetch_time) values("
		<< m_proData.id() << ", "
		<< m_proData.mail_id() << ", "
		<< m_proData.uid() << ", "
		<< m_proData.mark() << ", "
		<< m_proData.create_time() << ", "
		<< m_proData.fetch_time() << ") ";
	doQuery(*GameService::getMe().GetDataRef(), smData.str());
}

void ProcSsHandler::onMaxUUIDRequest(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{

}

void ProcSsHandler::onRechargeRoomCard(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::RechargeRoomCard proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	ProcWorldHandler::getMe().doRecordRoomCard(proto);
}

void ProcSsHandler::onSendBlockUser(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::SendBlockUser proReq;
	proReq.ParseFromArray(pMsg->data, pMsg->size);
	DUMP_PROTO_MSG(proReq);
}

void ProcSsHandler::onEditRoomCard(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::EditRoomCard proReq;
	proReq.ParseFromArray(pMsg->data, pMsg->size);
	DUMP_PROTO_MSG(proReq);
}

void ProcSsHandler::onSaveMoneyLogRequest(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::SaveMoneyLogRequest proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	const ::fogs::proto::msg::MoneyLog& moneyLog = proto.moneylog();

	zUUID zuuid;
	std::stringstream smData;
	smData << "insert into tb_moneylog(log_id, log_type,user_id,room_card,room_total,time) values("
		<< zuuid.generate32() << ", "
		<< moneyLog.log_type() << ", "
		<< moneyLog.user_id() << ", "
		<< moneyLog.room_card() << ", "
		<< moneyLog.room_total() << ","
		<< moneyLog.time() << ") ";
	doQuery(*GameService::Instance()->GetLogRef(), smData.str());
}

void ProcSsHandler::onGetRewardConfigReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::GetRewardConfigResp m_proResp;
	std::string strInvitation = "select room_card from tb_invitation_activity_manager where status = 0";
	doQueryProto(*GameService::Instance()->GetConfigRef(), strInvitation, *m_proResp.mutable_invitation_reward());
	std::string strShare = "select room_card from tb_share_activity_manager where status = 0";
	doQueryProto(*GameService::Instance()->GetConfigRef(), strShare, *m_proResp.mutable_share_reward());
	pSession->sendMsgProto(::comdef::msg_ss, ::msg_maj::GetRewardConfigRespID, pMsg->clientSessID, pMsg->fepServerID, m_proResp);
}

void ProcSsHandler::onGetFreeConfigReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::GetFreeConfigResp m_proResp;
	std::string strFree = "select start_time,end_time from tb_room_card_free_activity";
	doQueryProto(*GameService::Instance()->GetConfigRef(), strFree, m_proResp);
	pSession->sendMsgProto(::comdef::msg_ss, ::msg_maj::GetFreeConfigRespID, pMsg->clientSessID, pMsg->fepServerID, m_proResp);
}

void ProcSsHandler::onGetNotifyConfigReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::GetNotifyConfigResp m_proResp;
	std::string strFree = "select id,content,begin_time,break_time,minute_time,sort_level from tb_notify_activity_manager";
	doQueryProto(*GameService::Instance()->GetConfigRef(), strFree, *m_proResp.mutable_record());
	pSession->sendMsgProto(::comdef::msg_ss, ::msg_maj::GetNotifyConfigRespID, pMsg->clientSessID, pMsg->fepServerID, m_proResp);
}

void ProcSsHandler::onGetRoomSetConfigReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::GetRoomSetConfigResp m_proResp;
	std::string strFree = "select start_robot,limit_time from tb_roomset_manager";
	doQueryProto(*GameService::Instance()->GetConfigRef(), strFree, m_proResp);
	pSession->sendMsgProto(::comdef::msg_ss, ::msg_maj::GetRoomSetConfigRespID, pMsg->clientSessID, pMsg->fepServerID, m_proResp);
}






