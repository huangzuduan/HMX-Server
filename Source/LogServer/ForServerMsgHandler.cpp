#include "ForServerMsgHandler.h"
#include "../DyNetSocket/NetSocket.h"
#include "../DyNetSocket/NetClient.h"

#include "LogManager.h"
#include "BaseDefine.h"
#include "CommonServerOpt.h"
#include "ServerSession.h"
#include "CommonInternal.h"
#include "ServerClientCommon.h"

#include "CommonS2S.h"
#include "ProcServerHandler.h"

#include "LogManager.h"


ForServerMsgHandler::ForServerMsgHandler()
{
	// 内部协议 
#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ForServerMsgHandler::handler, this, _1, _2, _3)); \
}

	REGISTER_INTERNAL_MESSAGE(PRO_SS_REQ_LOGIN_S, SSReqLoginS, ReqLogined);	// 请求登录 
	REGISTER_INTERNAL_MESSAGE(PRO_SS_REQ_PING_S,SSReqPingToS,ReqPingToS);

#undef REGISTER_INTERNAL_MESSAGE


#define REGISTER_S2LOG_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcServerHandler::handler, ProcServerHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_S2LOG_MESSAGE(PRO_S2LOG_MSG,S2LogMsg,ReqSaveToDb);	

#undef REGISTER_S2LOG_MESSAGE

}


ForServerMsgHandler::~ForServerMsgHandler()
{
}

// 有客户端连接回调 
void ForServerMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	//---------------------------------服务组代码begin-------------------------------
	ServerCommonHandler::ForServerOnMsgEnter(rSocket,ESERVER_TYPE_LOG);
	//---------------------------------服务组代码end-------------------------------
}

// 有客户端消息收到
void ForServerMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32 nSize)
{
	//---------------------------------服务组代码begin-------------------------------
	ServerCommonHandler::ForServerOnMsg(*this,rSocket, pMsg,nSize);
	//---------------------------------服务组代码end-------------------------------
}

// 有客户端断开回调(此时socket已经回收) 
void ForServerMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	//---------------------------------服务组代码begin-------------------------------
	ServerCommonHandler::ForServerOnMsgExit(rSocket);
	//---------------------------------服务组代码end-------------------------------
}

void ForServerMsgHandler::ReqLogined(BaseSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	//---------------------------------服务组代码begin-------------------------------
	ServerCommonHandler::ForServerOnLogin(pSession, pMsg);
	//---------------------------------服务组代码end-------------------------------
}

// 收到ping请求信息 
void ForServerMsgHandler::ReqPingToS(BaseSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	ServerSession* pServerSession = static_cast<ServerSession*>(pSession);
	SSRepPingS sMsg;
	pServerSession->SendMsg(&sMsg,sMsg.GetPackLength());
}
