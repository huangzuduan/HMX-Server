#ifndef _PROC_DP_HANDLER_H_
#define _PROC_DP_HANDLER_H_

#include "BaseDefine.h"
#include "Single.h"

class zSession;
struct NetMsgSS;


class ProcDpHandler : public Single<ProcDpHandler>
{
public:
	ProcDpHandler();
	~ProcDpHandler();

	void RtLoadUserData(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

};


#endif

