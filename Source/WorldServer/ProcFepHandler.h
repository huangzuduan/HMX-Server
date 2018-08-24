#ifndef _FEP_SERVER_PROC_HANDLER_H_
#define _FEP_SERVER_PROC_HANDLER_H_

#include "SrvEngine.h"
#include "Single.h"

class zSession;
struct NetMsgSS;


size_t onProxyGameZone(void *buffer, size_t size, size_t nmemb, void *parm);

class ProcFepHandler : public Single<ProcFepHandler>
{
public:
	ProcFepHandler();
	~ProcFepHandler();

	void HandleLoginOut(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleLoginPlayer(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void doLoginTask(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void HandlePlayerExit(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void doSelectRole(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void doCreateRole(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void doDeleteRole(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void doMessageTask(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

};



#endif

