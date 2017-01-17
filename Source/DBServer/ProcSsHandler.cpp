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
	const S2DLoadUser* packet = static_cast<const S2DLoadUser*>(pMsg);

	static char wheres[100];
	memset(wheres, 0, sizeof(wheres));
	sprintf(wheres, "`id`=%llu", packet->uid);

	BUFFER_CMD(D2SLoadUser, send, MAX_USERDATASIZE);
	send->uid = packet->uid;
	int ret = dbmem::Memory::data.getDB()->ExecSelectLimit("User", user_columns, wheres, NULL, (unsigned char*)&send->base);
	if (ret == 1)
	{
		Zebra::logger->info("[%s]加载角色数据",Utf8ToGBK(send->base.name));
		send->sessid = packet->sessid;
		send->fepsid = packet->fepsid;
		pBaseSession->sendMsg(send, sizeof(D2SLoadUser) + send->size * sizeof(send->data[0]));
	}

}

void ProcSsHandler::ReqSaveUser(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize)
{
	const S2DSaveUser* packet = static_cast<const S2DSaveUser*>(pMsg);

	static char wheres[100];
	memset(wheres, 0, sizeof(wheres));
	sprintf(wheres, "`id`=%llu", packet->uid);
	int ret = dbmem::Memory::data.getDB()->ExecUpdate("User", user_columns, (const char*)&packet->base, wheres);
	if (ret == 0)
	{
		Zebra::logger->info("保存档案成功!");
	}
	else
	{
		Zebra::logger->error("保存档案失败!");
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