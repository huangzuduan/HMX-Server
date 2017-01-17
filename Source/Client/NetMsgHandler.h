#ifndef __NETMSGHANDLER_H_
#define __NETMSGHANDLER_H_

#include "Includes.h"
#include "NetIncludes.h"
#include "Single.h"
#include "SrvEngine.h"

class NetMsgHandler : public zMsgHandler, public Single<NetMsgHandler>
{
public:
	NetMsgHandler();
	~NetMsgHandler();

	void OnNetMsgEnter(NetSocket& rSocket);
	void OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg, int32 nSize);
	void OnNetMsgExit(NetSocket& rSocket);

	void recvLoginRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void recvLoginReponse(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
};





#endif

