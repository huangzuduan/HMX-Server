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

void ProcFepHandler::doPlayerExit(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	H::logger->info("玩家离线");
	const S::SSRqPlayerExit* packet = static_cast<const S::SSRqPlayerExit*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser)
	{
		pUser->saveDB();
		GameService::getMe().getSceneUserMgr().removeUser(pUser);
		GameService::getMe().getSceneUserMgr().DestroyObj(pUser);
	}
}

void ProcFepHandler::doChatWorld(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	//const RqCharWorld* packet = static_cast<const RqCharWorld*>(pMsg);
	//ClientSession* pCSession = ClientSessMgr::getMe().getSession(packet->nSessionID);
	//ASSERT(pCSession);
	//int32 nID = pCSession->GetSessionID();
	//stringstream ss;
	//ss << nID;
	//RtRepCharWorld sMsg;
	//strcpy(sMsg.fromName,ss.str().c_str());
	//strcpy(sMsg.sayMsg,packet->arrMsg);
	//sMsg.sayLen = packet->nLength;
	//ClientSessMgr::getMe().SendToAll(&sMsg,ssizeof(msg),ESERVER_TYPE_FEP);
}

void ProcFepHandler::doClientIsReady(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	// 发送场景数据 
	const C::RqClientIsReady* packet = static_cast<const C::RqClientIsReady*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if(pUser)
	{
		// 前端已经准备好了 
		pUser->clientReady = true;

		/* User上线回调 */
		pUser->online();

		// 发送主数据 
		pUser->sendMainToMe();

		// 发送装备数据 
	
		// 发送数据完毕消息 
		C::RtSendDataFinish sendDataFinish;
		sendDataFinish.nMsgOrderID = H::timeTick->now();
		sendDataFinish.nMsgOrderID = 0; 
		pUser->sendToFep(&sendDataFinish, sizeof(sendDataFinish));

	}

}

void ProcFepHandler::doQuestAccept(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	const C::RqClientIsReady* packet = static_cast<const C::RqClientIsReady*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if(pUser)
	{


	}
}

void ProcFepHandler::doChangeScene(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	
	const C::RqChanageScene* packet = static_cast<const C::RqChanageScene*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	int32 nEnterSceneID = packet->nSceneID;
	if (nEnterSceneID == pUser->getCurrMapID())
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

void ProcFepHandler::doItemMovePosition(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C::RqItemMovePosition* packet = static_cast<const C::RqItemMovePosition*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

}

void ProcFepHandler::doPositionMove(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C::RqPositionMove* packet = static_cast<const C::RqPositionMove*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	//H::logger->info("SceneManager::loadScene type=%d,countryid=%d,mapid=%d", 1, 2, 3);

	int32 x = packet->nNewX;
	int32 y = packet->nNewY;

	//t_NpcAIDefine ai(NPC_AI_MOVETO,zPos(x, y),10,10,60);
	//pUser->AIC->setAI(ai);

}

void ProcFepHandler::doShoppingBuyItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

	const C::RqShoppingBuyItem* packet = static_cast<const C::RqShoppingBuyItem*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	int32 count = pUser->ucm.GetCounter(Counter_ITEM_SHOP);

	H::logger->debug("Counter:%u", count);

	pUser->ucm.AddDay(Counter_ITEM_SHOP, 1);

	zShopB* shopB = shopbm.get(packet->nShopID);
	if (shopB == NULL)
	{
		H::logger->error("Not found shopID:%u", packet->nShopID);
		return;
	}

	int32 nItemNum = shopB->itemNum * packet->nShopNum;

	if (!pUser->TryAddObject(shopB->itemID, nItemNum))
	{
		H::logger->debug("try add item fail");
		return;
	}

	bool ret = pUser->SubMoney(shopB->sellMoneyType, shopB->sellMoneyValue);
	if (!ret)
	{
		H::logger->debug("money isnout enough");
		return;
	}

	// 增加背包道具 
	ret = pUser->AddObject(shopB->itemID, nItemNum, true);

	if (!ret)
	{
		H::logger->debug("buy shop fail");
		return;
	}

	H::logger->debug("buy shop success");
}

void ProcFepHandler::doShoppingSellItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

	const C::RqShoppingSellItem* packet = static_cast<const C::RqShoppingSellItem*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}
	
}

void ProcFepHandler::doUseItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C::RqItemUseObject* packet = static_cast<const C::RqItemUseObject*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	pUser->UseObject(packet->nUniqueID, packet->nItemNum, true);

}

void ProcFepHandler::doChanneCmd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

/* 单聊 */
void ProcFepHandler::doChatToOne(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	//const RqChatToOne* packet = static_cast<const RqChatToOne*>(pMsg);
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
void ProcFepHandler::doChatToTeam(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

/* 讨论组 */
void ProcFepHandler::doChatToDiscuss(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

/* 世界聊 */
void ProcFepHandler::doChatToWorld(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

	const C::RqChatToWorld* packet = static_cast<const C::RqChatToWorld*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	//H::logger->info("世界聊天:%s", zUtility::Utf8ToGBK(packet->msg.data));

	//pUser->SendToWs(pMsg,nSize);

}

void ProcFepHandler::doRelationList(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C::RqRelationList* packet = static_cast<const C::RqRelationList*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	pUser->relM.sendAllRelList();

}

void ProcFepHandler::doRelationAdd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C::RqRelationAdd* packet = static_cast<const C::RqRelationAdd*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	if (pSession->sessionType == zSession::FOR_WORLD)
	{
		SceneUser* relUser = GameService::getMe().getSceneUserMgr().getUserByName(packet->name);
		if (relUser)
		{
			pUser->relM.doAddRel(relUser->id, relUser->name, packet->rel);
		}
	}
	else if(pSession->sessionType == zSession::FOR_FEP)
	{
		SceneUser* relUser = GameService::getMe().getSceneUserMgr().getUserByName(packet->name);
		if (relUser)
		{
			pUser->relM.doAddRel(relUser->id, relUser->name, packet->rel);
		}
		else 
		{
			GameService::getMe().getSessionMgr().sendToWs(pMsg, nSize);
		}
	}
}

void ProcFepHandler::doRelationRemove(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C::RqRelationRemove* packet = static_cast<const C::RqRelationRemove*>(pMsg);
	SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(packet->sessid);
	if (pUser == NULL)
	{
		ASSERT(pUser);
		return;
	}

	pUser->relM.doRemoveRel(packet->uid);
}


