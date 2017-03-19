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

	void doLoginTask(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void doPlayerExit(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void doSelectRole(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void doCreateRole(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void doDeleteRole(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void doMessageTask(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

};



#endif

