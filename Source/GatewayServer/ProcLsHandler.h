#ifndef _LOGIN_SERVER_PROC_HANDLER_H_
#define _LOGIN_SERVER_PROC_HANDLER_H_

#include "Single.h"
#include "SrvEngine.h"

class zSession;
struct NetMsgSS;

class ProcLsHandler : public Single<ProcLsHandler>
{
public:
	ProcLsHandler();
	~ProcLsHandler();

	void RqLoadList(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);

};




#endif

