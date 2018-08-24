#include "NetMsgHandler.h"
#include "ProcWorldHandler.h"
#include "GameService.h"


NetMsgHandler::NetMsgHandler() :zMsgHandler(GameService::Instance())
{
	// world
#define REGISTER_WS_MESSAGE(cmd,cmdType,cls,handler)\
	{\
	RegisterMessage(cmd,cmdType, sizeof(cls), boost::bind(&ProcWorldHandler::handler, ProcWorldHandler::Instance(), _1, _2, _3)); \
	}

	//REGISTER_WS_MESSAGE(::comdef::msg_login, ::msg_maj::logout_req, PbMsgWebSS, HandleLoginOut);
	//REGISTER_WS_MESSAGE(::comdef::msg_login, ::msg_maj::login_player_req, PbMsgWebSS, HandleLoginPlayer);
	//REGISTER_WS_MESSAGE(::comdef::msg_login, ::msg_maj::notify_dis_conntion, PbMsgWebSS, HandlePlayerExit);

#undef REGISTER_WS_MESSAGE

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
	CommonOnNetMsg(rSocket, pMsg, nSize);
}

void NetMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	CommonOnNetMsgExit(rSocket);
}


