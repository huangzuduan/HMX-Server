#ifndef _FEP_SERVER_PROC_HANDLER_H_
#define _FEP_SERVER_PROC_HANDLER_H_

#include "SrvEngine.h"
#include "Single.h"

class zSession;
struct NetMsgSS;


size_t onPayResp(void *buffer, size_t size, size_t nmemb, void *parm);

class ProcWorldHandler : public Single<ProcWorldHandler>
{
public:
	ProcWorldHandler();
	~ProcWorldHandler();

	void reqWxPayOrderInfo(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
};



#endif

