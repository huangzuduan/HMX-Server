#ifndef _SERVER_MSG_HANDLER_H_
#define _SERVER_MSG_HANDLER_H_


#include "SrvEngine.h"
#include "Single.h"

struct NetMsgSS;
class NetSocket;

class NetMsgHandler : public zMsgHandler, public Single<NetMsgHandler>
{
public:
	NetMsgHandler();
	~NetMsgHandler();
	void OnNetMsgEnter(NetSocket& rSocket);
	void OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg, int32_t nSize);
	void OnNetMsgExit(NetSocket& rSocket);
};

#endif


