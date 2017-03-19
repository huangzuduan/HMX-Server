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
	const S::SSRqLoadList* packet = static_cast<const S::SSRqLoadList*>(pMsg);
	GameService::getMe().getWorldUserMgr().sendRoleList(packet->accid,packet->fepsid,packet->sessid);
}


