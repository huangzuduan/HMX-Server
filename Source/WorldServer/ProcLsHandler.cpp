#include "WorldServer_PCH.h"
#include "ProcLsHandler.h"


ProcLsHandler::ProcLsHandler()
{
}


ProcLsHandler::~ProcLsHandler()
{
}

void ProcLsHandler::RqLoadList(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const L2WLoadList* packet = static_cast<const L2WLoadList*>(pMsg);
	NetService::getMe().getWorldUserMgr().sendRoleList(packet->accid,packet->fepsid,packet->sessid);
}


