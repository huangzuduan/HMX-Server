#ifndef _PROC_CLIENT_HANDLER_H_
#define _PROC_CLIENT_HANDLER_H_

#include "SrvEngine.h"
#include "Single.h"

struct PbMsgWebSS;

class ProcFepHandler : public Single<ProcFepHandler>
{
public:
	ProcFepHandler(void);
	~ProcFepHandler(void);

	void HandlePlayerExit(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HnadleGotoScene(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	//-------role----
	void HandleRoleReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleGpsUploadReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleUpdateReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleCardInfoReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	//-------room------
	void HandleRoomListReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleOpenRoomReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleEnterRoomReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleLeaveRoomReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleDismissRoomReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleDismissAcceptReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleKickRoleReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleEnterRoomReady(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleRoomCardPriceReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	//--------maj--------
	void HandleStartGameReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleAcceptStartReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleDisoverCardReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleDiscardTileReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandlePrepareRoundReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleResponseReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleReconnectReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleReconnectReadyReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleReconnectOtherReadyReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandlerQuickMessageReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandlerQuickSanZhangReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandlerQuickDingQueReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandlerQuickMyScoreListReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandlerQuickMyTingListReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	//--------rank------
	void HandleRankTopList(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	//--------gm------
	void HandleRemainingCardReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleAssignAllCardsReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleAssignNextCardReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleCommonReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	//--------event------
	void HandleListReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleOptReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	//-------hist--------
	void HandleHistoryReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleHistRoomReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleHistInnReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleReplayReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void Recond2ProtoC(const ::msg_maj::HistoryRecordS& srcProto, ::msg_maj::HistoryRecord& distProto);
	void Recond2ProtoCRoom(const ::msg_maj::HistoryRecordS& srcProto, ::msg_maj::HistoryRoomResp& distProto);
	void CountTotalScore(::msg_maj::HistoryRecordS& srcProto);

	void doPlayerExit(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void doChatWorld(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void doClientIsReady(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void doChangeScene(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void doItemMovePosition(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	//-------match---------
	void HandleMatchBaoMingReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleMatchOpenRoomReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleMatchSortRankReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	//-------activity------
	void HandleGetShareInfoReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleShareReportReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleRecvShareRewardReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleGetInvitationInfoReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleRecvInvitationRewardReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleGetBindingAgentInfoReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleBindingAgentReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void HandleInputInvitationCodeReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	// 
	void doQuestAccept(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	
	// 移动 
	void doPositionMove(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void doShoppingBuyItem(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void doShoppingSellItem(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void doUseItem(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	// 频道
	void doChanneCmd(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);


	/* 单聊 */
	void doChatToOne(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	/* 群聊 */
	void doChatToTeam(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	/* 讨论组 */
	void doChatToDiscuss(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	/* 世界聊 */
	void doChatToWorld(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	// 社会关系
	void doRelationList(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void doRelationAdd(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void doRelationRemove(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
};


#endif




