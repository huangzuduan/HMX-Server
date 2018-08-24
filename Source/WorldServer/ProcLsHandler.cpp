#include "ProcLsHandler.h"
#include "GameService.h"

#include "LoginTokenMgr.h"


ProcLsHandler::ProcLsHandler()
{
}


ProcLsHandler::~ProcLsHandler()
{
}

void ProcLsHandler::RqLoadList(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{

}

void ProcLsHandler::NotifyLoginToken(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	::msg_maj::LoginToken proReq;
	if (!proReq.ParseFromArray(pMsg->data, pMsg->size))
	{
		return;
	}
	LoginTokenMgr::Instance()->AddToken(proReq);
}



