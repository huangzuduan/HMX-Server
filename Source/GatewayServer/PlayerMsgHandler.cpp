#include "PlayerMsgHandler.h"
#include "GameService.h"
#include "GateScene.h"
#include "GateUser.h"


// 在 fep 中 ，client的sessionID为socketID

PlayerMsgHandler::PlayerMsgHandler() :zMsgHandler(GameService::Instance())
{

	// to fep
#define REGISTER_FEP_MESSAGE(msg_idx, cls,handler)\
	{\
		RegisterMessage(msg_idx, sizeof(cls),boost::bind(&PlayerMsgHandler::handler, this, _1, _2,_3)); \
	}

//	REGISTER_FEP_MESSAGE(C::RQ_ENCRYPT, C::RqEncryptInfo,	ReqFepEncyptHandler);

#undef REGISTER_FEP_MESSAGE

	// to ls
#define REGISTER_LS_MESSAGE(msg_idx,cls)\
	{\
	RegisterMessage(msg_idx,sizeof(cls),boost::bind(&PlayerMsgHandler::ReqSendToLoginServer,this, _1, _2,_3));\
	}
	
	//REGISTER_LS_MESSAGE(C::RQ_ACCOUNT_LOGIN, C::RqAccountLogin);
	
#undef REGISTER_LS_MESSAGE

	// to ws
#define REGISTER_WS_MESSAGE(msg_idx,cls)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&PlayerMsgHandler::ReqSendToWorldServer, this, _1, _2,_3)); \
	}

	//REGISTER_WS_MESSAGE(C::RQ_SWITCH_SCENE, C::RqSwitchScene);	// 切换新场景 
	//REGISTER_WS_MESSAGE(C::RQ_Rq_SELECT_ROLE, C::RqSelectRole);		// 选择角色
	//REGISTER_WS_MESSAGE(C::RQ_CREATE_ROLE, C::RqCreateRole);
	//REGISTER_WS_MESSAGE(C::RQ_DELETE_ROLE, C::RqDeleteRole);

	//REGISTER_WS_MESSAGE(C::RQ_LOOK_MESSAGE,	C::rqLookMessage);
	//REGISTER_WS_MESSAGE(C::RQ_OPT_MESSAGE, C::rqOptMessage);

#undef REGISTER_WS_MESSAGE

	// to ss
#define REGISTER_SS_MESSAGE(msg_idx,cls)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&PlayerMsgHandler::ReqSendToSceneServer, this, _1, _2,_3)); \
	}

	//REGISTER_SS_MESSAGE(RQ_CHAT_WORLD,		RqCharWorld);
	//REGISTER_SS_MESSAGE(C::RQ_SCENE_INIT_DATA, C::RqClientIsReady);
	//REGISTER_SS_MESSAGE(C::RQ_CHANGE_SCENE, C::RqChanageScene);

	//REGISTER_SS_MESSAGE(C::RQ_ITEM_MOVE_POSITION, C::RqItemMovePosition);
	//REGISTER_SS_MESSAGE(C::RQ_POSITION_MOVE, C::RqPositionMove);
	//REGISTER_SS_MESSAGE(C::RQ_ITEM_USE_OBJECT, C::RqItemUseObject);

	//REGISTER_SS_MESSAGE(C::RQ_SHOPPING_BUY_ITME, C::RqShoppingBuyItem);
	//REGISTER_SS_MESSAGE(C::RQ_SHOPPING_SELL_ITME, C::RqShoppingSellItem);

	//REGISTER_SS_MESSAGE(C::RQ_CHAT_TO_WORLD, C::RqChatToWorld);

	//REGISTER_SS_MESSAGE(C::RQ_RELATION_LIST, C::RqRelationList);
	//REGISTER_SS_MESSAGE(C::RQ_RELATION_ADD, C::RqRelationAdd);
	//REGISTER_SS_MESSAGE(C::RQ_RELATION_REMOVE, C::RqRelationRemove);

#undef REGISTER_SS_MESSAGE

}


PlayerMsgHandler::~PlayerMsgHandler()
{
}

void PlayerMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	H::logger->info("[玩家]连接成功！来自于:id=%d ip=%s,port=%d", rSocket.SocketID(), rSocket.GetIp().c_str(), (int32_t)rSocket.GetPort());

	zSession* session = GameService::getMe().PlayerSessMgr()->get(rSocket.SocketID());
	if (session)
	{
		session->initEncrypt();
		zSession* ws = GameService::getMe().PlayerSessMgr()->getWs();
		if (ws == NULL)
		{
			H::logger->warn("[玩家]WS尚未连接，拒绝玩家连接");
			session->socket->OnEventColse();
			return;
		}

		zSession* ls = GameService::getMe().SessionMgr()->getLs();
		if (ls == NULL)
		{
			H::logger->warn("[玩家]LS尚未连接，拒绝玩家连接");
			session->socket->OnEventColse();
			return;
		}
		session->status = E_CLIENT_STATUS_CONNECTED;
	}
	else
	{
		H::logger->error("[玩家]找不到Session");
	}
}


void PlayerMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32_t nSize)
{
	zSession* session = GameService::getMe().PlayerSessMgr()->get(rSocket.SocketID());
	if(session)
	{
		// 解密处理 
		static char msgEnBuffer[65536];
		static char msgUnBuffer[65536];

		int nCHeadSize = sizeof(NetMsgC);
		int nSHeadSize = sizeof(NetMsgSS);
		memcpy(&msgEnBuffer[0], pMsg, nSize);		
		
		zEncrypt::xorCode(nSize, session->encrypt, msgEnBuffer, nSize);

		// 组装为NetMsgSS头协议，中间补两种头协议的字节差 
		memcpy(&msgUnBuffer[0], msgEnBuffer, nCHeadSize);
		memset(&msgUnBuffer[nCHeadSize], 0, nSHeadSize - nCHeadSize);
		memcpy(&msgUnBuffer[nSHeadSize], &msgEnBuffer[nCHeadSize], nSize - nCHeadSize);

		pMsg = (NetMsgSS*)&msgUnBuffer[0];

		const MsgFunc* handler = GetMsgHandler(pMsg->protocol);
		if(handler == NULL)
		{
			H::logger->error("[玩家]找不该协议:%d,大小:%d", pMsg->protocol,nSize);
			rSocket.OnEventColse();
			return;
		}
		else
		{
			H::logger->info("[玩家]收到协议:%d", pMsg->protocol);
			(handler->handlerFun)(session, (PbMsgWebSS*)pMsg ,nSize + nSHeadSize - nCHeadSize);
		}
	}
	else
	{
		H::logger->error("[玩家]找不到该连接:%lld", rSocket.SocketID());
		rSocket.OnEventColse();
	}
}

void PlayerMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	// 打印退出原因  
	H::logger->error("[玩家]连接断开:%lld", rSocket.SocketID());

	zSession* session = GameService::getMe().SessionMgr()->get(rSocket.SocketID());
	ASSERT(session);

	// 如果连接未进行验证，可以不发到WS中 
	if (session->status < E_CLIENT_STATUS_ENCRYPTED)
	{
		return;
	}
}

// 发送到 ls 
void PlayerMsgHandler::ReqSendToLoginServer(zSession* pSession, const NetMsgSS* pMsg,int32_t nSize)
{
	if(pSession->status != E_CLIENT_STATUS_NOTIFY_INITED)
	{
		H::logger->warn("[玩家]无法转发到LS,连接%lld状态未完成初始化", pSession->GetID());
		return;
	}
	zSession* ls = GameService::getMe().SessionMgr()->getLs();
	if (ls == NULL)
	{
		H::logger->warn("[玩家]无法转发到LS,找不到LS Session");
		return;
	}
	
	MSG_MAKE_PLAYER_SESSID(pSession->GetID(),GameService::getMe().GetServerID(),pMsg,nSize);
	ls->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
}

// 发送到 ss
void PlayerMsgHandler::ReqSendToSceneServer(zSession* pSession, const NetMsgSS* pMsg,int32_t nSize)
{
	if(pSession->status != E_CLIENT_STATUS_IN_SCENE)
	{
		H::logger->warn("[玩家]无法转发到SS,连接%lld状态未进入场景", pSession->GetID());
		return;
	}

	GateUser* gateUser = GateUserManager::getMe().getBySessID(pSession->GetID());
	if (gateUser)
	{
		zSession* ss = GameService::getMe().SessionMgr()->getSs(gateUser->GetSceneServerID());
		if (ss == NULL)
		{
			H::logger->warn("[玩家]无法转发到SS,找不到SS,serverid:%d", gateUser->GetSceneServerID());
			return;
		}
		MSG_MAKE_PLAYER_SESSID(pSession->GetID(), GameService::getMe().GetServerID(), pMsg, nSize);
		ss->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
	}
}

// 发送到 ws
void PlayerMsgHandler::ReqSendToWorldServer(zSession* pSession, const NetMsgSS* pMsg,int32_t nSize)
{
	if(pSession->status <= E_CLIENT_STATUS_ENCRYPTED)
	{
		H::logger->warn("[玩家]无法转发到WS,连接%lld状态未完成初始化", pSession->GetID());
		return;
	}
	zSession* ws = GameService::getMe().SessionMgr()->getWs();
	if (!ws)
	{
		H::logger->warn("[玩家]无法转发到WS,找不到WS Session");
		return;
	}
	MSG_MAKE_PLAYER_SESSID(pSession->GetID(), GameService::getMe().GetServerID(), pMsg, nSize);
	ws->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
}

void PlayerMsgHandler::SendToPlayer(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	static char arrUnBuffer[65536];
	static char arrEnBuffer[65536];
	int nCHeadSize = sizeof(NetMsgC);
	int nSHeadSize = sizeof(NetMsgSS);
	int nCSize = nSize - (nSHeadSize - nCHeadSize);
	memcpy(&arrUnBuffer[0], pMsg, nSize);
	memcpy(&arrEnBuffer[0], &arrUnBuffer[0], nCHeadSize);
	memcpy(&arrEnBuffer[nCHeadSize], &arrUnBuffer[nSHeadSize], nSize - nSHeadSize);
	zEncrypt::xorCode(nCSize, pSession->encrypt, arrEnBuffer, nCSize);
	pSession->socket->ParkMsg((uint8_t*)&arrEnBuffer[0], nCSize);
}

void PlayerMsgHandler::ReqFepEncyptHandler(zSession* pSession,const NetMsgSS* pMsg,int32_t nSize)
{
	//if(pSession->status == E_CLIENT_STATUS_CONNECTED )
	//{
	//	char arrRandKey[MAX_ENCRYPTSIZE + 1];
	//	bzero(arrRandKey,sizeof(arrRandKey));
	//	zEncrypt::getRandKey(arrRandKey,MAX_NAMESIZE);
	//	
	//	C::RtEncryptInfo sendEncrypt;
	//	strncpy(sendEncrypt.encryptKey, arrRandKey, MAX_ENCRYPTSIZE);
	//	SendToPlayer(pSession, &sendEncrypt, sizeof(sendEncrypt));

	//	// 要先发数据后才能改 
	//	strncpy(pSession->encrypt,arrRandKey,MAX_ENCRYPTSIZE);
	//	pSession->status = E_CLIENT_STATUS_ENCRYPTED;

	//	// 获得服务器状态是否可用 
	//	S::SSRqCheckSerivces sendCheckSerivces;
	//	sendCheckSerivces.clientSessID = pSession->GetID();
	//	zSession* wsSession = GameService::getMe().SessionMgr()->getWs();
	//	if (!wsSession)
	//	{
	//		H::logger->warn("[玩家]登录前检测各服务器状态是否可用转发失败，找不到WS Session");
	//		return;
	//	}
	//	wsSession->sendMsg(&sendCheckSerivces, sizeof(sendCheckSerivces));

	//	pSession->status = E_CLIENT_STATUS_NOTIFY_INITED;
	//}
	//else
	//{
	//	H::logger->error("[玩家]连接%lld状态未连接成功，无法获得密钥", pSession->GetID());
	//}
}


