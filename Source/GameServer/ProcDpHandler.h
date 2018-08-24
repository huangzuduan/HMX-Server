#ifndef _PROC_DP_HANDLER_H_
#define _PROC_DP_HANDLER_H_


#include "SrvEngine.h"
#include "Single.h"

struct NetMsgSS;


class ProcDpHandler : public Single<ProcDpHandler>
{
public:
	ProcDpHandler();
	~ProcDpHandler();

	void HandleQueryPlayerResponse(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void HandleQueryMailResponse(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void HandleQueryMailSysLogResponse(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void HandleGetMaxUUIDResponse(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void HandleSessionAccountName(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void HandleUpdateRoomInfo(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void HandlerZhanjiQueryResp(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void HandlerZhanjiRoomResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandlerZhanjiReplyResp(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void HandleFreeConfigResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleRewardConfigResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleNotifyConfigResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleRoomSetConfigResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

};


#endif

