#ifndef _SERVER_MSG_HANDLER_H_
#define _SERVER_MSG_HANDLER_H_

#include "Single.h"
#include "SrvEngine.h"
#include "CWebCommon.hpp"

struct NetMsgSS;

class NetMsgHandler : public zMsgHandler, public Single<NetMsgHandler>
{
public:
	NetMsgHandler();
	~NetMsgHandler();
	void OnNetMsgEnter(NetSocket& rSocket);
	void OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32_t nSize);
	void OnNetMsgExit(NetSocket& rSocket);
	void sendSToPlayer(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
};

#endif


