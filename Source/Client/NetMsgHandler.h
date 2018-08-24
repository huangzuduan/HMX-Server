#ifndef __NETMSGHANDLER_H_
#define __NETMSGHANDLER_H_


#include "NetIncludes.h"
#include "SrvEngine.h"
#include "Single.h"

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

