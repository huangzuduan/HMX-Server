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
	const D2SLoadUser* packet = static_cast<const D2SLoadUser*>(pMsg);
	SceneUser* user = NetService::getMe().getSceneUserMgr().getUserByID(packet->uid);
	if (!user)
	{
		user = NetService::getMe().getSceneUserMgr().CreateObj();
	}
	
	if (user == NULL)
	{
		ASSERT(0);
		return ;
	}

	if (!user->loadFromDb(packet, nSize))
	{
		ASSERT(0);
		Zebra::logger->error("LoadFromDb fail!");
		NetService::getMe().getSceneUserMgr().DestroyObj(user);
	}

	user->sessid = packet->sessid;
	user->fepsid = packet->fepsid;
	user->tempid = user->sessid;

	if (!NetService::getMe().getSceneUserMgr().addUser(user))
	{
		ASSERT(0);
		Zebra::logger->error("add User to manager fail!");
		NetService::getMe().getSceneUserMgr().DestroyObj(user);
		return;
	}

	/* 同步用户数据到场景 */
	S2FSyncUserData sendGateUserData;
	sendGateUserData.uid = user->id;
	strncpy(sendGateUserData.name, user->name, MAX_NAME_LENGTH);
	sendGateUserData.base.x = user->getPos().x;
	sendGateUserData.base.y = user->getPos().y;
	sendGateUserData.base.level = user->getLevel();
	sendGateUserData.base.vip = user->getVip();
	sendGateUserData.base.countryID = user->getCountry();
	sendGateUserData.base.mapid = user->GetCurrMapID();
	sendGateUserData.base.sceneid = user->GetSceneID();
	sendGateUserData.base.zoneid = user->GetZoneID();
	sendGateUserData.base.teamid = user->GetTeamID();
	user->SendToFep(&sendGateUserData, sendGateUserData.GetPackLength());

	S2FSyncUserScene sendUserScene;
	sendUserScene.uid = user->id;
	user->SendToFep(&sendUserScene,sendUserScene.GetPackLength());

	user->initDataFinish = true;

	/* 通知Client场景信息 */ 
	S2CSceneLoadInfo sendSceneData;
	sendSceneData.mapid = user->GetSceneID();
	user->SendToFep(&sendSceneData,sendSceneData.GetPackLength());

	Zebra::logger->info("[INFO]:Get Character Is Ok....\n");

}


