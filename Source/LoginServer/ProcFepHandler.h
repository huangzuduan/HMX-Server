#ifndef __PROC_CLIENT_HANDLER_H_
#define __PROC_CLIENT_HANDLER_H_

#include "BaseDefine.h"
#include "Single.h"

class zSession;
struct NetMsgSS;

class ProcFepHandler : public Single<ProcFepHandler>
{
public:
	ProcFepHandler(void);
	~ProcFepHandler(void);

	void RqAccountLogin(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	void RqRoleCreate(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	void RqRandNames(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);
};

#endif

