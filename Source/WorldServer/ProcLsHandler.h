#ifndef _LOGIN_SERVER_PROC_HANDLER_H_
#define _LOGIN_SERVER_PROC_HANDLER_H_

#include "SrvEngine.h"
#include "Single.h"

class ProcLsHandler : public Single<ProcLsHandler>
{
public:
	ProcLsHandler();
	~ProcLsHandler();

	void RqLoadList(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void NotifyLoginToken(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

};




#endif

