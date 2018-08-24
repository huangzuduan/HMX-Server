#ifndef _DP_SERVER_PROC_HANDLER_H_
#define _DP_SERVER_PROC_HANDLER_H_


#include "SrvEngine.h"
#include "Single.h"

class ProcDpHandler : public Single<ProcDpHandler>
{
public:
	ProcDpHandler();
	~ProcDpHandler();


	/*--------------------------------------------
	 *  @brief  : 
	 *  @input	: 
	 *  @return :	
	 *-------------------------------------------*/
	void RqGlobalInfo(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);


	/*--------------------------------------------
	 *  @brief  :	
	 *  @input	: 
	 *  @return :	
	 *-------------------------------------------*/
	void RtSelectRoleResult(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);

	void NtLoadSortLists(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

};

#endif



