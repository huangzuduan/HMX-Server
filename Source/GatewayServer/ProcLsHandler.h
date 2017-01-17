#ifndef _LOGIN_SERVER_PROC_HANDLER_H_
#define _LOGIN_SERVER_PROC_HANDLER_H_

#include "Single.h"
#include "BaseProcHandler.h"

class zSession;
struct NetMsgSS;

class ProcLsHandler : public BaseProcHandler, public Single<ProcLsHandler>
{
public:
	ProcLsHandler();
	~ProcLsHandler();

	void RqLoadList(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

};




#endif

