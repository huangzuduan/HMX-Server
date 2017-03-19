#include "DBServer_PCH.h"
#include "ProcWorldHandler.h"

#include "Collection.h"
#include "Memory.h"
#include "sorlists.pb.h"


ProcWorldHandler::ProcWorldHandler()
{

}

ProcWorldHandler::~ProcWorldHandler()
{

}

void ProcWorldHandler::ReqLogin(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize)
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

void ProcWorldHandler::ReqNotifyServerInfo(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize)
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

void ProcWorldHandler::ReqNotifySceneInfo(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize)
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

void ProcWorldHandler::ReqQueryEventInfo(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize)
{
	// 检查event_info表中的事件，取出后，设置为已经执行 
}


void ProcWorldHandler::ReqSelectRole(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize)
{

	//const W2DSelectRole* packet = static_cast<const W2DSelectRole*>(pMsg);
	
	///* 加载道具数据 */
	//LoadUserTable<StItemSlotsTable>(packet->nCharID, packet->nSessionID, Memory::getMe().GetItemslotsMem(), NULL);

	///* 加载个人聊天数据 */
	//LoadUserTable<StChatMsgTable>(packet->nCharID, packet->nSessionID, Memory::getMe().GetChatMsgMem(), NULL);

	///* 加载角色数据 */
	//LoadUserTable<DUser>(packet->nCharID, packet->nSessionID, Memory::getMe().GetCharacterMem(), boost::bind(&ProcWorldHandler::CallBackSelectRole, ProcWorldHandler::Instance(), _1, _2));


}

void ProcWorldHandler::ReqLoadSortLists(zSession* pBaseSession, const NetMsgSS* pMsg, int32 nSize)
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

void ProcWorldHandler::ReqSaveSortLists(zSession* pBaseSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void ProcWorldHandler::CallBackSelectRole(int32 nCSID, DUser* pUserMem)
{

	/*ClientSession* pCSession = ClientSessionMgr::getMe().getSession(nCSID);
	if (NULL == pCSession)
	{
		ASSERT(pCSession);
		return;
	}

	D2WSelectRoleResult sMsg;
	sMsg.nResult = D2WSelectRoleResult::E_SELECT_SUCCESS;
	sMsg.sUserData.LoadData(*pUserMem);
	pCSession->SendMsgToWs(&sMsg, sMsg.GetLength());
	return;*/
}


