#ifndef _DP_SERVER_PROC_HANDLER_H_
#define _DP_SERVER_PROC_HANDLER_H_

#include "Single.h"
#include "BaseProcHandler.h"

class ProcDpHandler : public BaseProcHandler, public Single<ProcDpHandler>
{
public:
	ProcDpHandler();
	~ProcDpHandler();


	/*--------------------------------------------
	 *  @brief  : 
	 *  @input	: 
	 *  @return :	
	 *-------------------------------------------*/
	void RqGlobalInfo(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);


	/*--------------------------------------------
	 *  @brief  :	
	 *  @input	: 
	 *  @return :	
	 *-------------------------------------------*/
	void RtSelectRoleResult(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	void NtLoadSortLists(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

};

#endif



