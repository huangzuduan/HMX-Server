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
	const S::SSRqEnterScene* packet = static_cast<const S::SSRqEnterScene*>(pMsg);

	zSession* dp = GameService::getMe().getSessionMgr().getDp();
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

	S::SSRqLoadUser sMsgLoad;
	sMsgLoad.uid = packet->uid;
	sMsgLoad.sessid = packet->sessid;
	sMsgLoad.fepsid = packet->fepsid;
	dp->sendMsg(&sMsgLoad, sizeof(sMsgLoad));
}

void ProcWorldHandler::NtEnterResult(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSRqEnterResult* packet = static_cast<const S::SSRqEnterResult*>(pMsg);

	if (packet->nResult == S::SSRqEnterResult::E_ENTER_SUCCESS)
	{
		// 成功，删除本地内存即可，无需要其他处理
		SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserByID(packet->nCharID);
		if (pUser)
		{
			GameService::getMe().getSceneUserMgr().removeUser(pUser);
			GameService::getMe().getSceneUserMgr().DestroyObj(pUser);
		}

	}
	else if (packet->nResult == S::SSRqEnterResult::E_ENTER_FAIL)
	{
		// 失败，提示前端即可 
	}

}

void ProcWorldHandler::NtLoadUids(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}
