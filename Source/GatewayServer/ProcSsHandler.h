#ifndef _SCENE_SERVER_MSG_HANDLER_H_
#define _SCENE_SERVER_MSG_HANDLER_H_

#include "SrvEngine.h"
#include "Single.h"

struct NetMsgSS;

class ProcSsHandler : public Single<ProcSsHandler>
{
public:
	ProcSsHandler();
	~ProcSsHandler();

	// 发起由机器人替换
	void onStartRobotReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	// 结束由机器人替换
	void onStopRobotReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void RobotReconnResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void RobotStartRoundResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void NtBroadcastMsg(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	/* 聊天信息转发 */
	void TurnChatToOne(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void UpdateUserToGate(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);


};

#endif


