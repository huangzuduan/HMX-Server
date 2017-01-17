#ifndef _FEP_SERVER_PROC_HANDLER_H_
#define _FEP_SERVER_PROC_HANDLER_H_

#include "Single.h"
#include "BaseProcHandler.h"

class zSession;
struct NetMsgSS;

class ProcFepHandler : public BaseProcHandler, public Single<ProcFepHandler>
{
public:
	ProcFepHandler();
	~ProcFepHandler();

	void RqPlayerExit(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void RqSelectRole(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void RqCreateRole(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void RqDeleteRole(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

};



#endif

