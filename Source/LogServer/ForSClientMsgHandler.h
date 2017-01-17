#ifndef _SERVER_HANDLER_H_
#define _SERVER_HANDLER_H_

#include "Config.h"
#include "BaseSingle.h"
#include "BaseMsgHandler.h"

/*
 *
 *	Detail: 处理与ws，ss,ls通信消息 
 *   
 * Copyright (c) Created by hzd 2015-4-27.All rights reserved
 *
 */

class NetSocket;
struct NetMsgSS;

class ForSClientMsgHandler : public BaseMsgHandler, public BaseSingle<ForSClientMsgHandler>
{

public:
	ForSClientMsgHandler();
	~ForSClientMsgHandler();

	// 有客户端连接回调 
	virtual void OnNetMsgEnter(NetSocket& rSocket);

	// 有客户端消息收到 
	virtual void OnNetMsg(NetSocket& rSocket, NetMsgSS* pHead,int32 nSize);

	// 有客户端断开回调(此时socket已经回收)  
	virtual void OnNetMsgExit(NetSocket& rSocket);

	// 登录结果 
	void RepLogined(BaseSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	// 同步client连接的server信息 
	void NofityClientSessionInfo(BaseSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	// 客户端退出通知 
	void NofityClientExit(BaseSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// 收到ping 返回 
	void RepPingToS(BaseSession* pSession, const NetMsgSS* pMsg,int32 nSize);

private:

	bool m_bFirstMsg;

};

#endif


