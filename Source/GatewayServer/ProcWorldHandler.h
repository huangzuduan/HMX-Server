#ifndef _PROC_WORLD_HANDLER_H_
#define _PROC_WORLD_HANDLER_H_

#include "BaseDefine.h"
#include "Single.h"

class zSession;
struct NetMsgSS;

/*-------------------------------------------------------------------
 * @Brief :FEP作为客户端，怎不与WS逻辑处理Handler 
 * 
 * @Author:hzd 2013/04/03
 *------------------------------------------------------------------*/
class ProcWorldHandler : public Single<ProcWorldHandler>
{
public:
	ProcWorldHandler();
	~ProcWorldHandler();

	void ReqLogin(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);
};


#endif

