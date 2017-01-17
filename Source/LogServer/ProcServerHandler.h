#ifndef __PROC_SERVER_HANDLER_H_
#define __PROC_SERVER_HANDLER_H_

#include "BaseDefine.h"
#include "BaseSingle.h"
#include "../DyNetMysql/DbRecordSet.h"

class BaseSession;
struct NetMsgSS;

/*
 *	业务逻辑 
 */
class ProcServerHandler : public BaseSingle<ProcServerHandler> 
{
public:
	ProcServerHandler(void);
	~ProcServerHandler(void);

	//  保存Server服的日志记录 
	void ReqSaveToDb(BaseSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	
};


#endif

