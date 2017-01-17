#include "GameServer_PCH.h"
#include "ProcWorldHandler.h"
#include "ScenesServer.h"
#include "SceneUserMgr.h"

ProcWorldHandler::ProcWorldHandler()
{
}


ProcWorldHandler::~ProcWorldHandler()
{
}

void ProcWorldHandler::RqEnterScene(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	const W2SRqEnterScene* packet = static_cast<const W2SRqEnterScene*>(pMsg);

	zSession* dp = NetService::getMe().getSessionMgr().getDp();
	if (dp == NULL)
	{
		ASSERT(dp);
		return;
	}

	// 
	Scene* scene = SceneManager::getInstance().getSceneByID(packet->sceneid);
	if (scene == NULL)
	{

		return;
	}

	S2DLoadUser sMsgLoad;
	sMsgLoad.uid = packet->uid;
	sMsgLoad.sessid = packet->sessid;
	sMsgLoad.fepsid = packet->fepsid;
	dp->sendMsg(&sMsgLoad, sMsgLoad.GetPackLength());
}

void ProcWorldHandler::NtEnterResult(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const W2SNtEnterResult* packet = static_cast<const W2SNtEnterResult*>(pMsg);

	if (packet->nResult == W2SNtEnterResult::E_ENTER_SUCCESS)
	{
		// 成功，删除本地内存即可，无需要其他处理
		SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserByID(packet->nCharID);
		if (pUser)
		{
			NetService::getMe().getSceneUserMgr().removeUser(pUser);
			NetService::getMe().getSceneUserMgr().DestroyObj(pUser);
		}

	}
	else if (packet->nResult == W2SNtEnterResult::E_ENTER_FAIL)
	{
		// 失败，提示前端即可 
	}

}

void ProcWorldHandler::NtLoadUids(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

	BUFFER_MSG(pMsg,nSize);

	const W2SLoadUids* packet = static_cast<const W2SLoadUids*>((void*)buffmsg);

	/*zSession* dpSession = NetService::getMe().getSessionMgr().getByDb();
	if (dpSession == NULL)
	{
		Zebra::logger->error("NtLoadUids not found dbsession");
		ASSERT(dpSession);
		return;
	}

	if (packet->count)
	{
		for (int32 i = 0; i < packet->count; ++i)
		{
			int64 uid = packet->uids[i];

			SceneUser* u = NetService::getMe().getSceneUserMgr().getUserByID(uid);
			if (u == NULL)
			{
				S2DLoadUser sMsgLoad;
				sMsgLoad.sessid = packet->sessid;
				sMsgLoad.uid = uid;
				sMsgLoad.nDpServerID = dpSession->getServerID();
				sMsgLoad.nFepServerID = 0;
				sMsgLoad.nEnterType = ENTER_TYPE_OFFLINE_LOAD;
				dpSession->sendMsg(&sMsgLoad, sMsgLoad.GetPackLength());
			}
		}
	}*/

}
