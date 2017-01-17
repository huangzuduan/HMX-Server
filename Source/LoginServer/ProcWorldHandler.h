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

};


#endif

