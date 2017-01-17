#ifndef _PROC_CLIENT_HANDLER_H_
#define _PROC_CLIENT_HANDLER_H_

#include "BaseDefine.h"
#include "Single.h"

class zSession;
struct NetMsgSS;


class ProcFepHandler : public Single<ProcFepHandler>
{
public:
	ProcFepHandler(void);
	~ProcFepHandler(void);

	void RqPlayerExit(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void ReqChatWorld(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);
	void RqClientIsReady(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);
	void ReqChangeScene(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void ReqItemMovePosition(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// 
	void ReqQuestAccept(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);
	
	// 移动 
	void ReqPositionMove(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void ReqShoppingBuyItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void ReqShoppingSellItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void ReqUseItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// 频道
	void rqChanneCmd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);


	/* 单聊 */
	void RqChatToOne(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	/* 群聊 */
	void RqChatToTeam(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	/* 讨论组 */
	void RqChatToDiscuss(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	/* 世界聊 */
	void RqChatToWorld(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// 社会关系
	void rqRelationList(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void rqRelationAdd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void rqRelationRemove(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
};


#endif




