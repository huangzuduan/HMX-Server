#include "ProcWorldHandler.h"
#include "SrvIncludes.h"
#include "GameService.h"
#include "MysqlProtobufHelper.h"


ProcWorldHandler::ProcWorldHandler()
{

}

ProcWorldHandler::~ProcWorldHandler()
{

}

void ProcWorldHandler::ReqLogin(zSession* pBaseSession, const PbMsgWebSS* pMsg,int32_t nSize)
{

	//if(pBaseSession->getStatus() != E_SERVER_STATUS_CONNETED)
	//{
	//	//FLOG_INFO("pBaseSession->getStatus() != EWORLD_STATUS_CONNECTED"); 
	//	return;
	//}

	//// 判断 
	//pBaseSession->setStatus(E_SERVER_STATUS_LOGINED);

	//// ok finish! 
	//// 等待其它 ls,ss的连接  

}

void ProcWorldHandler::ReqNotifyServerInfo(zSession* pBaseSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	/*const W2DNotifyServerInfo* packet = static_cast<const W2DNotifyServerInfo*>(pMsg);
	IDbBase* pDB = DbConnectsMgr::getMe().GetMainConn();

	for (int32 i = 0; i < packet->nServerNum; ++i)
	{
		memset(SQL_BUFFER,0,MAX_SQL_BUFFER);
		const NotifyServerInfo& rInfo = packet->arrServerInfo[i];
		SPRINTF(SQL_BUFFER,"REPLACE INTO `server_info` (`group_idx`,`server_idx`,`server_type`,`server_host`,`server_port`,`server_load`,`client_load`) VALUES (%d,%d,%d,'%s',%d,%d,%d);",packet->nGroupID,rInfo.nServerID,rInfo.nServerType,rInfo.arrHost,rInfo.nPort,rInfo.nServerLoad,rInfo.nClientLoad);
		SQL_BUFFER[ MAX_SQL_BUFFER - 1 ] = '\0';
		pDB->ExecSQLAsync(SQL_BUFFER,NULL);
	}*/

}

void ProcWorldHandler::ReqNotifySceneInfo(zSession* pBaseSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	//const W2DNotifySceneInfo* packet = static_cast<const W2DNotifySceneInfo*>(pMsg);
	//IDbBase* pDB = DbConnectsMgr::getMe().GetMainConn();
	//for (int32 i = 0; i < packet->nSceneNum; ++i)
	//{
	//	const NotifySceneInfo& rInfo = packet->arrSceneInfo[i];
	//	memset(SQL_BUFFER,0,MAX_SQL_BUFFER);
	//	SPRINTF(SQL_BUFFER,"REPLACE INTO `scene_info` (`server_idx`,`scene_idx`,`scene_load`) VALUES (%d,%d,%d);",rInfo.nServerID,rInfo.nSceneID,rInfo.nLoadNum);
	//	SQL_BUFFER[ MAX_SQL_BUFFER - 1 ] = '\0';
	//	pDB->ExecSQLAsync(SQL_BUFFER,NULL);
	//}
}

void ProcWorldHandler::ReqQueryEventInfo(zSession* pBaseSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	// 检查event_info表中的事件，取出后，设置为已经执行 
}


void ProcWorldHandler::ReqSelectRole(zSession* pBaseSession, const PbMsgWebSS* pMsg,int32_t nSize)
{

	//const W2DSelectRole* packet = static_cast<const W2DSelectRole*>(pMsg);
	
	///* 加载道具数据 */
	//LoadUserTable<StItemSlotsTable>(packet->nCharID, packet->nSessionID, Memory::getMe().GetItemslotsMem(), NULL);

	///* 加载个人聊天数据 */
	//LoadUserTable<StChatMsgTable>(packet->nCharID, packet->nSessionID, Memory::getMe().GetChatMsgMem(), NULL);

	///* 加载角色数据 */
	//LoadUserTable<DUser>(packet->nCharID, packet->nSessionID, Memory::getMe().GetCharacterMem(), boost::bind(&ProcWorldHandler::CallBackSelectRole, ProcWorldHandler::Instance(), _1, _2));


}

void ProcWorldHandler::ReqLoadSortLists(zSession* pBaseSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	/*D2WLoadSortLists levelMsg;
	::protobuf::LevelTable proto;
	for (int16 j = 1; j <= 200; ++j)
	{
		StLevelSortTable* pItem = Memory::getMe().GetSortlistsMem().get(j);
		if (pItem == NULL) continue;
		::protobuf::LevelRow* row = proto.add_levels();
		row->set_sortid(pItem->sortID);
		row->set_uid(pItem->uid);
		row->set_name(pItem->name);
		row->set_level(pItem->level);
		::protobuf::LevelBinary* binData = row->mutable_bindata();
		if (binData == NULL) continue;
		binData->ParseFromArray(pItem->binData.revser, pItem->binData.datalen);
	}
	int32 byteSize = proto.ByteSize();
	proto.SerializeToArray(&levelMsg.arrByte[0], byteSize);
	levelMsg.nByteSize = byteSize;
	ServerSessMgr::getMe().GetWsSess()->SendMsg(&levelMsg, levelsizeof(msg));*/
	
}

void ProcWorldHandler::ReqSaveSortLists(zSession* pBaseSession, const PbMsgWebSS* pMsg, int32_t nSize)
{

}

void ProcWorldHandler::CallBackSelectRole(int32_t nCSID, DUser* pUserMem)
{
	/*ClientSession* pCSession = ClientSessionMgr::getMe().getSession(nCSID);
	if (NULL == pCSession)
	{
		return;
	}

	D2WSelectRoleResult sMsg;
	sMsg.nResult = D2WSelectRoleResult::E_SELECT_SUCCESS;
	sMsg.sUserData.LoadData(*pUserMem);
	pCSession->SendMsgToWs(&sMsg, sMsg.GetLength());
	return;*/
}

void ProcWorldHandler::onSendRoomCard(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::SendRoomCard proReq;
	proReq.ParseFromArray(pMsg->data, pMsg->size);
	DUMP_PROTO_MSG(proReq);

	::msg_maj::Role roleData;
	std::stringstream dataSql;
	dataSql << "select * from `tb_role` where id = " << proReq.user_id();
	int32_t nRet = doQueryProto(*GameService::Instance()->GetDataRef(), dataSql.str(), roleData);
	if (nRet == 0)
	{
		if (roleData.id() > 0)
		{
			std::stringstream roleSql;
			roleSql << "update tb_role set room_card = " << (roleData.room_card() + proReq.cards()) << " where id = " << proReq.user_id();
			doQuery(*GameService::getMe().GetDataRef(), roleSql.str());

			fogs::proto::msg::RechargeRoomCard roomcard;
			roomcard.set_user_id(proReq.user_id());
			roomcard.set_is_add(1);
			roomcard.set_order_no(proReq.order_no());
			roomcard.set_room_card(proReq.cards());
			roomcard.set_time(time(NULL));
			roomcard.set_from_uid(proReq.from_uid());

			doRecordRoomCard(roomcard);

			::fogs::proto::msg::MoneyLog moneyLog;
			zUUID zuuid;
			moneyLog.set_log_id(zuuid.generate());
			moneyLog.set_user_id(proReq.user_id());
			moneyLog.set_room_card(proReq.cards());
			moneyLog.set_room_total(roleData.room_card() + proReq.cards());
			moneyLog.set_time(time(NULL));
			moneyLog.set_log_type(::fogs::proto::msg::log_t_roomcard_add_charge);

			doRecordMoneyLog(moneyLog);
		}
		else
		{
			H::logger->error("onSendRoomCard uid error,uid:%ld,cards:%d", proReq.user_id(), proReq.cards());
		}
	}
	else
	{
		H::logger->error("onSendRoomCard sql error,uid:%ld,cards:%d", proReq.user_id(), proReq.cards());
	}
}

void ProcWorldHandler::onUserEditCard(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::UserEditCard proReq;
	proReq.ParseFromArray(pMsg->data, pMsg->size);
	DUMP_PROTO_MSG(proReq);

	::msg_maj::Role roleData;
	std::stringstream dataSql;
	dataSql << "select * from `tb_role` where id = " << proReq.user_id();
	int32_t nRet = doQueryProto(*GameService::Instance()->GetDataRef(), dataSql.str(), roleData);
	if (nRet == 0)
	{
		if (roleData.id() > 0)
		{
			std::stringstream roleSql;
			roleSql << "update tb_role set room_card = " << (roleData.room_card() + proReq.cards()) << " where id = " << proReq.user_id();
			doQuery(*GameService::getMe().GetDataRef(), roleSql.str());

			::fogs::proto::msg::MoneyLog moneyLog;
			zUUID zuuid;
			moneyLog.set_log_id(zuuid.generate());
			moneyLog.set_user_id(proReq.user_id());
			moneyLog.set_room_card(proReq.cards());
			moneyLog.set_room_total(proReq.cards());
			moneyLog.set_time(time(NULL));
			moneyLog.set_log_type(::fogs::proto::msg::log_t_roomcard_add_charge);

			doRecordMoneyLog(moneyLog);
		}
		else
		{
			H::logger->error("onUserEditCard uid error,uid:%ld,cards:%d", proReq.user_id(), proReq.cards());
		}
	}
	else
	{
		H::logger->error("onUserEditCard sql error,uid:%ld,cards:%d", proReq.user_id(), proReq.cards());
	}
}

void ProcWorldHandler::onSendMail(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::SendMailToPlayer proReq;
	proReq.ParseFromArray(pMsg->data, pMsg->size);
	DUMP_PROTO_MSG(proReq);

	for (int i = 0; i < proReq.user_ids_size(); ++i)
	{
		uint64_t uid = proReq.user_ids(i);
		::msg_maj::MailRecordS  proto;
		zUUID zuuid;
		proto.set_id(zuuid.generate32());
		proto.set_type(uid > 0 ? ::msg_maj::mail_t_system_one : ::msg_maj::mail_t_system_all);
		proto.set_from_id(0);
		proto.set_from_name("system");
		proto.set_to_id(uid);
		proto.set_to_name("");
		proto.set_title(proReq.mail_title());
		proto.set_content(proReq.mail_content());
		proto.set_room_cards(proReq.award_num());
		proto.set_mark(::msg_maj::mark_t_unread);
		proto.set_create_time(time(NULL));
		proto.set_fetch_time(0);
		doInsertProto(*GameService::getMe().GetDataRef(), "tb_mail", proto);
	}
	
}

void ProcWorldHandler::doRecordRoomCard(const ::fogs::proto::msg::RechargeRoomCard proto)
{
	std::stringstream dataSql;
	dataSql << "insert into tb_roomcard(order_no, user_id, room_card, is_add, time, from_uid) values("
		<< "'" << proto.order_no() << "', "
		<< proto.user_id() << ", "
		<< proto.room_card() << ", "
		<< proto.is_add() << ", "
		<< proto.time() <<", " 
		<< proto.from_uid() << ") ";
	int32_t nRet = doQuery(*GameService::getMe().GetLogRef(), dataSql.str());
}

void ProcWorldHandler::doRecordMoneyLog(const ::fogs::proto::msg::MoneyLog& moneyLog)
{
	std::stringstream moneyLogSql;
	moneyLogSql << "insert into tb_moneylog(log_id,log_type, user_id,room_card,room_total,time) values("
		<< moneyLog.log_id() << ", "
		<< moneyLog.log_type() << ", "
		<< moneyLog.user_id() << ", '"
		<< moneyLog.room_card() << "', "
		<< moneyLog.room_total() << ", "
		<< moneyLog.time() << ") ";

	doQuery(*GameService::getMe().GetLogRef(), moneyLogSql.str());
}

void ProcWorldHandler::onSaveOnlinePlayer(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	::fogs::proto::msg::SaveOnlinePlayer proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	std::stringstream dataSql;
	dataSql << "insert into tb_online_record(time,online_num,roomcard_num,inn_num) values("
		<< proto.time() << ", "
		<< proto.online_num() << ", "
		<< proto.roomcard_num() << ", "
		<< proto.inn_num() << ") ";

	doQuery(*GameService::getMe().GetLogRef(), dataSql.str());
}

void ProcWorldHandler::onSaveRoomOption(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	::fogs::proto::msg::RoomOptionCreate proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	doInsertProto(*GameService::getMe().GetLogRef(), "tb_roomoption", proto);
}

void ProcWorldHandler::onUpdateRoomOption(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{

	::fogs::proto::msg::RoomOptionEnd proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);

	std::stringstream dataSql;
	dataSql << "update tb_roomoption set `end_time`=" << proto.end_time() << " where `id`=" << proto.id();
	doQuery(*GameService::getMe().GetLogRef(), dataSql.str());

}

