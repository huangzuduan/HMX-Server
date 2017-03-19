#include "WorldServer_PCH.h"
#include "ProcDpHandler.h"
#include "WorldUserMgr.h"
#include "OfflineUserMgr.h"
#include "SceneRegMgr.h"
#include "SortsManager.h"

ProcDpHandler::ProcDpHandler()
{
}


ProcDpHandler::~ProcDpHandler()
{
}

void ProcDpHandler::RqGlobalInfo(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{

}

void ProcDpHandler::RtSelectRoleResult(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	//const D2WSelectRoleResult* packet = static_cast<const D2WSelectRoleResult*>(pMsg);

	//int64 uid = packet->data.uid;
	//ASSERT(uid);

	//WorldUser* user = NetService::getMe().getWorldUserMgr().get(uid);
	//if(user == NULL)
	//{
	//	user = NetService::getMe().getWorldUserMgr().CreateObj();
	//	user->id = uid;
	//	user->sessid = packet->sessid;
	//	strncpy(user->name, packet->data.name, MAX_NAME_LENGTH);
	//	bool b = NetService::getMe().getWorldUserMgr().add(user);
	//	if(!b) /* 创建内存失败 */ 
	//	{
	//		NetService::getMe().getWorldUserMgr().DestroyObj(user);
	//		Zebra::logger->error("LoadUserData Fail!");
	//		return;
	//	}
	//}

	//// 判断是否为相同帐号 
	//if (user && user->sessid == packet->sessid)
	//{
	//	// 找合适的SceneServer 
	//	// 如何找到最合适的权重 最合适为负载最低 当前负载值 = 本server选择数量 + 本scene中使用数量 
	//	SceneInfo* pSceneInfo = SceneManager::getMe().GetLoadLestServerID(user->sceneid);
	//	if (pSceneInfo == NULL)
	//	{
	//		ASSERT(pSceneInfo);
	//		return;
	//	}
	//	zSession* pSSession = ServerSessMgr::getMe().getBySs(pSceneInfo->nServerID);
	//	if (pSSession == NULL)
	//	{
	//		ASSERT(pSSession);
	//		return;
	//	}

	//	// 找到用户连接FepServer
	//	zSession* pFepSession = ServerSessMgr::getMe().get(packet->fepSessionID);
	//	if (pFepSession = NULL)
	//	{
	//		ASSERT(pSSession);
	//		return;
	//	}

	//	user->SceneSesion = pSSession;
	//	user->fepSession = pFepSession;

	//	//W2SRqEnterScene sMsg;
	//	//sMsg.sessid = user->sessid;
	//	//sMsg.uid = uid;
	//	//sMsg.nSceneID = user->sceneid;
	//	//sMsg.nFepServerID = pFepSession->id;
	//	//sMsg.nEnterType = ENTER_TYPE_ONLINE_FIRST;
	//	//user->sendToSs(&sMsg, ssizeof(msg));

	//	Zebra::logger->info("Send to dist scene of requst enter this %d scene", user->sceneid);

	//	return;
	//}

 //   // 踢掉老玩家,采用回调再进行处理 
	//Zebra::logger->warn("Same Character Login!,uid:%lld", uid);

	//// 发出老用客户端退出消息 
	//SSNofityClientExit sMsgExit;// todo 
	//user->sendToFep(&sMsgExit, sMsgExit.GetPackLength());

}

void ProcDpHandler::NtLoadSortLists(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	H::logger->info("RepLoadSortLists");

	const S::SSRtLoadSortLists* packet = static_cast<const S::SSRtLoadSortLists*>(pMsg);
	::protobuf::LevelTable proto;
	proto.ParseFromArray(packet->arrByte, packet->nByteSize);
	SortsManager::getMe().UnSerialize(proto);

	/* 与DP连通，加载共用数据 */
	//if (nServerType == ESERVER_TYPE_DP)
	//{
	//	W2DLoadSortLists send;
	//	zSessionMgr::getMe().GetDBSession()->SendMsg(&send, sizeof(send));
	//}

}


