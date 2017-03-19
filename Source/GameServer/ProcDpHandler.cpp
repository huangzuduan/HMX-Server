#include "GameServer_PCH.h"
#include "ProcDpHandler.h"
#include "SceneUser.h"
#include "SceneUserMgr.h"


ProcDpHandler::ProcDpHandler()
{
}


ProcDpHandler::~ProcDpHandler()
{
}

void ProcDpHandler::RtLoadUserData(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	const S::SSRtLoadUser* packet = static_cast<const S::SSRtLoadUser*>(pMsg);
	SceneUser* user = GameService::getMe().getSceneUserMgr().getUserByID(packet->base.id);
	if (!user)
	{
		user = GameService::getMe().getSceneUserMgr().CreateObj();
	}
	
	if (user == NULL)
	{
		ASSERT(0);
		return ;
	}

	if (!user->loadDB(packet, nSize))
	{
		ASSERT(0);
		H::logger->error("LoadFromDb fail!");
		GameService::getMe().getSceneUserMgr().DestroyObj(user);
	}

	user->sessid = packet->sessid;
	user->fepsid = packet->fepsid;
	user->tempid = user->sessid;

	if (!GameService::getMe().getSceneUserMgr().addUser(user))
	{
		ASSERT(0);
		H::logger->error("add User to manager fail!");
		GameService::getMe().getSceneUserMgr().DestroyObj(user);
		return;
	}

	/* 同步用户数据到场景 */
	S::SSNtSyncUserData sendGateUserData;
	sendGateUserData.base.x = user->getPos().x;
	sendGateUserData.base.y = user->getPos().y;
	sendGateUserData.base.level = user->getLevel();
	sendGateUserData.base.vip = user->getVip();
	sendGateUserData.base.countryID = user->getCountry();
	sendGateUserData.base.mapid = user->getCurrMapID();
	sendGateUserData.base.sceneid = user->getSceneID();
	sendGateUserData.base.zoneid = user->getZoneID();
	sendGateUserData.base.teamid = user->getTeamID();
	user->sendToFep(&sendGateUserData, sizeof(sendGateUserData));

	S::SSNtSyncUserScene sendUserScene;
	sendUserScene.uid = user->id;
	user->sendToFep(&sendUserScene, sizeof(sendUserScene));

	user->initDataFinish = true;

	/* 通知Client场景信息 */ 
	C::RtSceneLoadInfo sendSceneData;
	sendSceneData.mapid = user->getSceneID();
	user->sendToFep(&sendSceneData, sizeof(sendSceneData));

	H::logger->info("[INFO]:Get Character Is Ok....\n");

}


