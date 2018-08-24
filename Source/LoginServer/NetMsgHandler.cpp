#include "NetMsgHandler.h"
#include "GameService.h"


NetMsgHandler::NetMsgHandler():zMsgHandler(GameService::Instance())
{
		// ss
#define REGISTER_SS_MESSAGE(cmd,cmdType,cls,handler)\
	{\
	RegisterMessage(cmd,cmdType,sizeof(cls), boost::bind(&NetMsgHandler::handler, this, _1, _2, _3)); \
	}

	REGISTER_SS_MESSAGE(::comdef::msg_ss, ::msg_maj::ServerIsBrepairingNotifyID, PbMsgWebSS, ServerBrepairingNotify);

#undef REGISTER_SS_MESSAGE

	// fep
#define REGISTER_FEP_MESSAGE(cmd,cmdType,cls,handler)\
	{\
	RegisterMessage(cmd,cmdType, sizeof(cls), boost::bind(&NetMsgHandler::handler, this, _1, _2, _3)); \
	}

	REGISTER_FEP_MESSAGE(::comdef::msg_login, ::msg_maj::login_weixin_req, PbMsgWebSS, LoginReq);
	REGISTER_FEP_MESSAGE(::comdef::msg_login, ::msg_maj::login_account_req, PbMsgWebSS, LoginReq);
	REGISTER_FEP_MESSAGE(::comdef::msg_login, ::msg_maj::prelogin_account_req, PbMsgWebSS, LoginReq);
	REGISTER_FEP_MESSAGE(::comdef::msg_login, ::msg_maj::logout_req, PbMsgWebSS, LoginReq);
	REGISTER_FEP_MESSAGE(::comdef::msg_login, ::msg_maj::login_player_req, PbMsgWebSS, LoginReq);
	REGISTER_FEP_MESSAGE(::comdef::msg_login, ::msg_maj::sdk_token_req, PbMsgWebSS, LoginReq);

#undef REGISTER_FEP_MESSAGE

}

NetMsgHandler::~NetMsgHandler()
{ 

}

void NetMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	CommonOnNetMsgEnter(rSocket);
}

void NetMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg, int32_t nSize)
{
	CommonOnNetMsg(rSocket,pMsg,nSize);
}

void NetMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	CommonOnNetMsgExit(rSocket);
}


void NetMsgHandler::LoginReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	int32_t a = 0;
}

void NetMsgHandler::ServerBrepairingNotify(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	::msg_maj::ServerBrepairingNotify proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	GameService::getMe().SetIsBrepairing(proto.status() == 1);
}



