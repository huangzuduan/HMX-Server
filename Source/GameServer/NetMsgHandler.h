#ifndef _SERVER_MSG_HANDLER_H_
#define _SERVER_MSG_HANDLER_H_

#include "SrvEngine.h"
#include "NetConfig.h"
#include "Single.h"

class NetMsgHandler : public zMsgHandler, public Single<NetMsgHandler>
{
public:
	NetMsgHandler();
	~NetMsgHandler();
	void OnNetMsgEnter(NetSocket& rSocket);
	void OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32_t nSize);
	void OnNetMsgExit(NetSocket& rSocket);

	virtual void NewLoginSuccessed(zSession* pSession, int32_t server_id, int32_t server_type);
};

#endif


