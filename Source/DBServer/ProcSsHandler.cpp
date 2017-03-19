#include "DBServer_PCH.h"
#include "ProcSsHandler.h"



ProcSsHandler::ProcSsHandler(void)
{
}


ProcSsHandler::~ProcSsHandler(void)
{
}

void ProcSsHandler::ReqAccountLogin(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize)
{


}

/*
 *	创建角色
 */
void ProcSsHandler::ReqRoleCreate(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize)
{

	
}

void ProcSsHandler::ReqLoadUser(zSession* pBaseSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSRqLoadUser* packet = static_cast<const S::SSRqLoadUser*>(pMsg);

	static char wheres[100];
	memset(wheres, 0, sizeof(wheres));
	sprintf(wheres, "`id`=%llu", packet->uid);

	BUFFER_CMD(S::SSRtLoadUser, send, MAX_USERDATASIZE);
	int ret = dbmem::Memory::data.getDB()->ExecSelectLimit("USER", S::user_columns, wheres, NULL, (unsigned char*)&send->base);
	if (ret == 1)
	{
		H::logger->info("[%s]加载角色数据",zUtility::Utf8ToGBK(send->base.name));
		send->sessid = packet->sessid;
		send->fepsid = packet->fepsid;
		pBaseSession->sendMsg(send, sizeof(S::SSRtLoadUser) + send->getSize());
	}
}

void ProcSsHandler::ReqSaveUser(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize)
{
	const S::SSRqSaveUser* packet = static_cast<const S::SSRqSaveUser*>(pMsg);

	static char wheres[100];
	memset(wheres, 0, sizeof(wheres));
	sprintf(wheres, "`id`=%llu",packet->base.id);
	int ret = dbmem::Memory::data.getDB()->ExecUpdate("USER", S::user_columns, (const char*)&packet->base, wheres);
	if (ret == 0)
	{
		H::logger->info("保存档案成功!");
	}
	else
	{
		H::logger->error("保存档案失败!");
	}
}

void ProcSsHandler::ReqSaveMixItemNumber(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize)
{


}

//------------------------------db回调----------------------------------------

void ProcSsHandler::QueryCharacterList(ClientSession* pClientSession,int64 nAccountID/* = 0 */, int64 nCharacterID/* = 0*/)
{

}

void ProcSsHandler::DbRoleCreate(void* pSession,const void* pData)
{


}