#ifndef CLIENT_MSG_HANDLER_H_
#define CLIENT_MSG_HANDLER_H_

#include "Single.h"
#include "SrvEngine.h"
#include "BaseDefine.h"

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
// 玩家状态 
enum EClientStatus
{
	/*-------------------------------------------------------------------
	* @Brief : 初始化时，当Client连接成功时，初始化该Session时
	*------------------------------------------------------------------*/
	E_CLIENT_STATUS_INITED = 0,	// 

	/*-------------------------------------------------------------------
	* @Brief : 初始化完成后，设置为已经连接成功状态，
	*          这时仅能请求密钥接口
	*------------------------------------------------------------------*/
	E_CLIENT_STATUS_CONNECTED,

	/*-------------------------------------------------------------------
	* @Brief : 已经请求获得密钥成功，此时，Client是不能请求任何接口的，
	*          这时服务器正给它分配负载最低的dp,ls服务器ID
	*------------------------------------------------------------------*/
	E_CLIENT_STATUS_ENCRYPTED,	// 获得密钥成功完成 

	/*-------------------------------------------------------------------
	* @Brief : 分配ls,dp服务器id成功，此时client仅可以向ls发送帐号登录
	*
	*------------------------------------------------------------------*/
	E_CLIENT_STATUS_NOTIFY_INITED,

	/*-------------------------------------------------------------------
	* @Brief :
	*
	*------------------------------------------------------------------*/
	E_CLIENT_STATUS_LOGINED,	// 登录完成完成 
	E_CLIENT_STATUS_SELECTED,	// 选择角色完成 
	E_CLIENT_STATUS_IN_WORLD,	// 可以进行数据交互完成  
	E_CLIENT_STATUS_IN_SCENE,	// 在游戏场景中 
};


/*-------------------------------------------------------------------
 * @Brief : 接收处理客户端（用户）连接
 *			固定的客户端数据处理，其它协议在Proc中
 * 
 * @Author:hzd 2013/04/03
 *------------------------------------------------------------------*/
class PlayerMsgHandler : public zMsgHandler, public Single<PlayerMsgHandler>
{
public:
	PlayerMsgHandler();
	~PlayerMsgHandler();

	// 有客户端连接回调 
	virtual void OnNetMsgEnter(NetSocket& rSocket);

	// 有客户端消息收到 
	virtual void OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32 nSize);

	// 有客户端断开回调(此时socket已经回收)  
	virtual void OnNetMsgExit(NetSocket& rSocket);

	// 发送到 ls
	void ReqSendToLoginServer(zSession* pSession,const NetMsgSS* pMsg,int32 nSize);

	// 发送到 ss
	void ReqSendToSceneServer(zSession* pSession,const NetMsgSS* pMsg,int32 nSize);

	// 发送到 ws
	void ReqSendToWorldServer(zSession* pSession,const NetMsgSS* pMsg,int32 nSize);

	// 发送到 player 
	void SendToPlayer(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	//-----------------------------本地处理协议---------------------------------
	// fep
	void ReqFepEncyptHandler(zSession* pSession,const NetMsgSS* pMsg,int32 nSize);

	//////////////////////////////////////////////////////////////////////////
	virtual bool ForWsOnExit(NetSocket& rSocket) { return true; };
	virtual bool ForClientToServerOnMsgEnter(NetSocket& rSocket, int32 nLocalServerType) { return true; };
	virtual bool ForServerOnMsgEnter(NetSocket& rSocket, int32 nServerType) { return true; };
	virtual bool ForServerOnMsgExit(NetSocket& rSocket) { return true; };
	virtual bool ForServerOnLogin(zSession* pSession, const NetMsgSS* pMsg) { return true; };
	virtual bool ForServerTimeOutCancel(zSession* pSession) { return true; };
	virtual bool ForWsUpdateClientToFepDp(zSession* pSession, const NetMsgSS* pMsg, int32 nOnServerType) { return true; };

	virtual bool ForWsOnMsgEnter(NetSocket& rSocket, int32 nLocalServerType) { return true; };
	virtual bool ForWsOnMsg(zMsgHandler& baseMsgHandler, NetSocket& rSocket, NetMsgSS* pMsg, int32 nSize) { return true; };
	virtual bool ForWsUpdateClientToLsSs(zSession* pSession, const NetMsgSS* pMsg, int32 nOnServerType) { return true; };
	virtual bool ForServerOnMsg(zMsgHandler& baseMsgHandler, NetSocket& rSocket, NetMsgSS* pMsg, int32 nSize) { return true; };

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
	reinterpret_cast<NetMsgSS*>(&vecMsgBuffer[0])->sessid = _sessid; \
	reinterpret_cast<NetMsgSS*>(&vecMsgBuffer[0])->fepsid = _fepsid; \
}\


#endif



