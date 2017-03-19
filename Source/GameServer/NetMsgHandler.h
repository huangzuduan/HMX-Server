#ifndef _SERVER_MSG_HANDLER_H_
#define _SERVER_MSG_HANDLER_H_

#include "Single.h"
#include "NetConfig.h"
#include "SrvEngine.h"

class NetMsgHandler : public zMsgHandler, public Single<NetMsgHandler>
{
public:
	NetMsgHandler();
	~NetMsgHandler();
	void OnNetMsgEnter(NetSocket& rSocket);
	void OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32 nSize);
	void OnNetMsgExit(NetSocket& rSocket);

	// 由端向服务器请求登录（注册serverid）
	void doLoginRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void doLoginReponse(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// 由端向服务器Ping
	void doPingRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// 服务器列表 
	void doSrvListNotifty(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	
};

#endif


