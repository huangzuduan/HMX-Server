#ifndef _PROC_WORLD_HANDLER_H_
#define _PROC_WORLD_HANDLER_H_

#include "BaseDefine.h"
#include "Single.h"

class zSession;
struct NetMsgSS;


class ProcWorldHandler : public Single<ProcWorldHandler>
{
public:
	ProcWorldHandler();
	~ProcWorldHandler();

	void RqEnterScene(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	void NtEnterResult(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void NtLoadUids(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
};


#endif

