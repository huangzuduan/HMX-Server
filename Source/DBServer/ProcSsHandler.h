#ifndef __PROC_SERVER_HANDLER_H_
#define __PROC_SERVER_HANDLER_H_

#include "Includes.h"
#include "DbRecordSet.h"

class zSession;
class ClientSession;
struct NetMsgSS;

/*
 *	业务逻辑 
 */
class ProcSsHandler : public Single<ProcSsHandler> 
{
public:
	ProcSsHandler(void);
	~ProcSsHandler(void);

	// client登录查询 
	void ReqAccountLogin(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	// 创建角色 
	void ReqRoleCreate(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	// ss 中加载角色数据 
	void ReqLoadUser(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	// ss 中保存数据 
	void ReqSaveUser(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	void ReqSaveMixItemNumber(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);


	//------------------db回调函数--------------------
public:

	// 创建角色
	static void DbRoleCreate(void* pSession,const void* pData);

	static void QueryCharacterList(ClientSession* pClientSession,int64 nAccountID = 0 , int64 nCharacterID = 0);
	
};


#endif

