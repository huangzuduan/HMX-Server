#ifndef _SCENE_SERVER_MSG_HANDLER_H_
#define _SCENE_SERVER_MSG_HANDLER_H_

#include "Single.h"

class ProcSsHandler : public Single<ProcSsHandler>
{
public:
	ProcSsHandler();
	~ProcSsHandler();

	void NtSyncUserScene(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void NtSyncUserData(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void NtBroadcastMsg(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	/* 聊天信息转发 */
	void TurnChatToOne(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);


};

#endif


