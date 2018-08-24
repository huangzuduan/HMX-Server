#ifndef _PROC_WORLD_HANDLER_H_
#define _PROC_WORLD_HANDLER_H_


#include "SrvEngine.h"
#include "Single.h"

struct NetMsgSS;


class ProcWorldHandler : public Single<ProcWorldHandler>
{
public:
	ProcWorldHandler();
	~ProcWorldHandler();
	
	void TransTerToSceneReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void TransTerToSceneResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandlerLoginScene(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void HandleQueryRankResponse(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleUpdateRankResponse(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleSendRoomCard(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleUserEditCard(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleEditRoomCard(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleSendMail(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleDeleteNotice(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleSendNotice(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleSendBlock(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleBindingAgentInfoResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleBindingAgentResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleInputInviteCodeResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleRefreshConfigResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
};


#endif

