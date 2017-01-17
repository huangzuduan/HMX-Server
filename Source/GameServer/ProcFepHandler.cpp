#include "GameServer_PCH.h"
#include "ProcFepHandler.h"
#include "SceneUser.h"
#include "SceneUserMgr.h"
#include "SceneNpcAIController.h"

ProcFepHandler::ProcFepHandler(void)
{
}


ProcFepHandler::~ProcFepHandler(void)
{
}

void ProcFepHandler::RqPlayerExit(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	Zebra::logger->info("玩家离线");
	const F2SRqPlayerExit* packet = static_cast<const F2SRqPlayerExit*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser)
	{
		pUser->SaveToDb();
		NetService::getMe().getSceneUserMgr().removeUser(pUser);
		NetService::getMe().getSceneUserMgr().DestroyObj(pUser);
	}
}

void ProcFepHandler::ReqChatWorld(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	//const C2SCharWorld* packet = static_cast<const C2SCharWorld*>(pMsg);
	//ClientSession* pCSession = ClientSessMgr::getMe().getSession(packet->nSessionID);
	//ASSERT(pCSession);
	//int32 nID = pCSession->GetSessionID();
	//stringstream ss;
	//ss << nID;
	//S2CRepCharWorld sMsg;
	//strcpy(sMsg.fromName,ss.str().c_str());
	//strcpy(sMsg.sayMsg,packet->arrMsg);
	//sMsg.sayLen = packet->nLength;
	//ClientSessMgr::getMe().SendToAll(&sMsg,sMsg.GetPackLength(),ESERVER_TYPE_FEP);
}

void ProcFepHandler::RqClientIsReady(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	// 发送场景数据 
	const C2SClientIsReady* packet = static_cast<const C2SClientIsReady*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if(pUser)
	{
		// 前端已经准备好了 
		pUser->clientReady = true;

		/* User上线回调 */
		pUser->Online();

		// 发送主数据 
		pUser->sendMainToMe();

		// 发送装备数据 
	
		// 发送数据完毕消息 
		S2CSendDataFinish sendDataFinish;
		sendDataFinish.nMsgOrderID = Zebra::timeTick->getNowTime();
		sendDataFinish.nMsgOrderID = 0; 
		pUser->SendToFep(&sendDataFinish,sendDataFinish.GetPackLength());

	}

}

void ProcFepHandler::ReqQuestAccept(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	const C2SClientIsReady* packet = static_cast<const C2SClientIsReady*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if(pUser)
	{


	}
}

void ProcFepHandler::ReqChangeScene(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	
	const C2SChanageScene* packet = static_cast<const C2SChanageScene*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	int32 nEnterSceneID = packet->nSceneID;
	if (nEnterSceneID == pUser->GetMapID())
	{
		return;
	}

	//Scene* pEnterScene = SceneMapManager::getMe().GetGeneralScene(nEnterSceneID);
	//if (pEnterScene)
	//{		
	//	return;
	//}
	//
	//SceneMapManager::getMe().DelSceneEnity(*pUser);

	//pUser->SaveToDb(SOCKET_EVENT_CODE_SAVE_CHANGE_MAP);

	return;

}

void ProcFepHandler::ReqItemMovePosition(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C2SItemMovePosition* packet = static_cast<const C2SItemMovePosition*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

}

void ProcFepHandler::ReqPositionMove(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C2SPositionMove* packet = static_cast<const C2SPositionMove*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	//Zebra::logger->info("SceneManager::loadScene type=%d,countryid=%d,mapid=%d", 1, 2, 3);

	int32 x = packet->nNewX;
	int32 y = packet->nNewY;

	//t_NpcAIDefine ai(NPC_AI_MOVETO,zPos(x, y),10,10,60);
	//pUser->AIC->setAI(ai);

}

void ProcFepHandler::ReqShoppingBuyItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

	const C2SShoppingBuyItem* packet = static_cast<const C2SShoppingBuyItem*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	int32 count = pUser->ucm.GetCounter(Counter_ITEM_SHOP);

	Zebra::logger->debug("Counter:%u", count);

	pUser->ucm.AddDay(Counter_ITEM_SHOP, 1);

	zShopB* shopB = shopbm.get(packet->nShopID);
	if (shopB == NULL)
	{
		Zebra::logger->error("Not found shopID:%u", packet->nShopID);
		return;
	}

	int32 nItemNum = shopB->itemNum * packet->nShopNum;

	if (!pUser->TryAddObject(shopB->itemID, nItemNum))
	{
		Zebra::logger->debug("try add item fail");
		return;
	}

	bool ret = pUser->SubMoney(shopB->sellMoneyType, shopB->sellMoneyValue);
	if (!ret)
	{
		Zebra::logger->debug("money isnout enough");
		return;
	}

	// 增加背包道具 
	ret = pUser->AddObject(shopB->itemID, nItemNum, true);

	if (!ret)
	{
		Zebra::logger->debug("buy shop fail");
		return;
	}

	Zebra::logger->debug("buy shop success");
}

void ProcFepHandler::ReqShoppingSellItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

	const C2SShoppingSellItem* packet = static_cast<const C2SShoppingSellItem*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}
	
}

void ProcFepHandler::ReqUseItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C2SItemUseObject* packet = static_cast<const C2SItemUseObject*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	pUser->UseObject(packet->nUniqueID, packet->nItemNum, true);

}

void ProcFepHandler::rqChanneCmd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

/* 单聊 */
void ProcFepHandler::RqChatToOne(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	//const C2SChatToOne* packet = static_cast<const C2SChatToOne*>(pMsg);
	//SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	//if (pUser == NULL)
	//{
	//	ASSERT(pUser);
	//	return;
	//}

	//pUser->ChatToOne(packet,nSize);

	/* */
}

/* 群聊 */
void ProcFepHandler::RqChatToTeam(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

/* 讨论组 */
void ProcFepHandler::RqChatToDiscuss(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

/* 世界聊 */
void ProcFepHandler::RqChatToWorld(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

	const C2SChatToWorld* packet = static_cast<const C2SChatToWorld*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	//Zebra::logger->info("世界聊天:%s", Utf8ToGBK(packet->msg.data));

	//pUser->SendToWs(pMsg,nSize);

}

void ProcFepHandler::rqRelationList(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C2SRelationList* packet = static_cast<const C2SRelationList*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	pUser->relM.sendAllRelList();

}

void ProcFepHandler::rqRelationAdd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C2SRelationAdd* packet = static_cast<const C2SRelationAdd*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	if (pSession->sessionType == zSession::FOR_WORLD)
	{
		SceneUser* relUser = NetService::getMe().getSceneUserMgr().getUserByName(packet->name);
		if (relUser)
		{
			pUser->relM.doAddRel(relUser->id, relUser->name, packet->rel);
		}
	}
	else if(pSession->sessionType == zSession::FOR_FEP)
	{
		SceneUser* relUser = NetService::getMe().getSceneUserMgr().getUserByName(packet->name);
		if (relUser)
		{
			pUser->relM.doAddRel(relUser->id, relUser->name, packet->rel);
		}
		else 
		{
			NetService::getMe().getSessionMgr().sendToWs(pMsg, nSize);
		}
	}
}

void ProcFepHandler::rqRelationRemove(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C2SRelationRemove* packet = static_cast<const C2SRelationRemove*>(pMsg);
	SceneUser* pUser = NetService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	pUser->relM.doRemoveRel(packet->uid);
}


