#ifndef __FOR_SERVER_MSG_HANDLER_H_
#define __FOR_SERVER_MSG_HANDLER_H_

#include "Config.h"
#include "BaseSingle.h"
#include "BaseMsgHandler.h"

class ForServerMsgHandler : public BaseMsgHandler, public BaseSingle<ForServerMsgHandler>
{
public:
	ForServerMsgHandler();
	~ForServerMsgHandler();


	// 有客户端连接回调 
	virtual void OnNetMsgEnter(NetSocket& rSocket);

	// 有客户端消息收到 
	virtual void OnNetMsg(NetSocket& rSocket, NetMsgSS* pHead,int32 nSize);

	// 有客户端断开回调(此时socket已经回收)  
	virtual void OnNetMsgExit(NetSocket& rSocket);

	// 请求登录 
	void ReqLogined(BaseSession* pSessioin, const NetMsgSS* pHead,int32 nSize);

	// 收到ping请求信息 
	void ReqPingToS(BaseSession* pSession, const NetMsgSS* pMsg,int32 nSize);
};


#endif // !



