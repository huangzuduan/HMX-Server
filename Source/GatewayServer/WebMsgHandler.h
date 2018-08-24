#ifndef _WEB_MSG_HANDLER_H_
#define _WEB_MSG_HANDLER_H_


#include "SrvEngine.h"
#include "Single.h"

class NetSocket;
struct NetMsgSS;

/*------------------------------------------------------------------
*
* @Brief : 通用所有Server的客户端Session，只能用于记录通用的信息
*          本类不能修改用于游戏功能，只限于游戏框架修改
* @Author: hzd
* @File  : ClientSession.h
* @Date  : 2015/10/18 22:33
* @Copyright (c) 2015,hzd, All rights reserved.
*-----------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * @Brief : 接收处理客户端（用户）连接
 *			固定的客户端数据处理，其它协议在Proc中
 * 
 * @Author:hzd 2013/04/03
 *------------------------------------------------------------------*/
class WebMsgHandler : public zMsgHandler, public Single<WebMsgHandler>
{
public:
	WebMsgHandler();
	~WebMsgHandler();

	virtual void OnNetMsgEnter(NetSocket& rSocket) {};
	virtual void OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg, int32_t nSize){};
	virtual void OnNetMsgExit(NetSocket& rSocket) {};

	// 有客户端连接回调 
	virtual void OnWebMsgEnter(CWebClient* client);

	// 有客户端消息收到 
	virtual void OnWebMsg(CWebClient* client, PbMsgWebSS* pMsg,int32_t nSize);

	// 有客户端断开回调(此时socket已经回收)  
	virtual void OnWebMsgExit(CWebClient* client);

	// 发送到 local
	void ReqSendLocalServer(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	// 发送到 ls
	void ReqSendToLoginServer(zSession* pSession,const PbMsgWebSS* pMsg,int32_t nSize);

	// 发送到 ss
	void ReqSendToSceneServer(zSession* pSession,const PbMsgWebSS* pMsg,int32_t nSize);

	// 发送到 ws
	void ReqSendToWorldServer(zSession* pSession,const PbMsgWebSS* pMsg,int32_t nSize);

	// 发送到 player 
	void SendToPlayer(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	//-----------------------------本地处理协议---------------------------------

	//////////////////////////////////////////////////////////////////////////
	virtual bool ForWsOnExit(NetSocket& rSocket) { return true; };
	virtual bool ForClientToServerOnMsgEnter(NetSocket& rSocket, int32_t nLocalServerType) { return true; };
	virtual bool ForServerOnMsgEnter(NetSocket& rSocket, int32_t nServerType) { return true; };
	virtual bool ForServerOnMsgExit(NetSocket& rSocket) { return true; };
	virtual bool ForServerOnLogin(zSession* pSession, const NetMsgSS* pMsg) { return true; };
	virtual bool ForServerTimeOutCancel(zSession* pSession) { return true; };
	virtual bool ForWsUpdateClientToFepDp(zSession* pSession, const NetMsgSS* pMsg, int32_t nOnServerType) { return true; };

	virtual bool ForWsOnMsgEnter(NetSocket& rSocket, int32_t nLocalServerType) { return true; };
	virtual bool ForWsOnMsg(zMsgHandler& baseMsgHandler, NetSocket& rSocket, NetMsgSS* pMsg, int32_t nSize) { return true; };
	virtual bool ForWsUpdateClientToLsSs(zSession* pSession, const NetMsgSS* pMsg, int32_t nOnServerType) { return true; };
	virtual bool ForServerOnMsg(zMsgHandler& baseMsgHandler, NetSocket& rSocket, NetMsgSS* pMsg, int32_t nSize) { return true; };

};

/*-------------------------------------------------------------------
 * @Brief : 将客户端发来的消息转成SS通用消息（消息头插入了clientSessionID）
 * 
 * @Author:hzd 2015:10:24
 *------------------------------------------------------------------*/
#define MSG_MAKE_PLAYER_SESSID(_sessid,_fepsid,pMsg,nSize) static vector<char> vecMsgBuffer;\
{\
	vecMsgBuffer.resize(nSize); \
	memcpy(&vecMsgBuffer[0], pMsg, nSize); \
	reinterpret_cast<NetMsgSS*>(&vecMsgBuffer[0])->clientSessID = _sessid; \
	reinterpret_cast<NetMsgSS*>(&vecMsgBuffer[0])->fepServerID = _fepsid; \
}\


#endif



