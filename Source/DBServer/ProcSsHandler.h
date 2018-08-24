#ifndef __PROC_SERVER_HANDLER_H_
#define __PROC_SERVER_HANDLER_H_

#include "Single.h"
#include "SrvEngine.h"

class zSession;
class ClientSession;
struct PbMsgWebSS;

/*
 *	ÒµÎñÂß¼­ 
 */
class ProcSsHandler : public Single<ProcSsHandler> 
{
public:
	ProcSsHandler(void);
	~ProcSsHandler(void);

	void onQueryPlayerRequest(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void onSavePlayerDataReq(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void onZhanjiAddRecordRequest(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void onZhanjiFinishRequest(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void onZhanjiQueryList(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void onZhanjiRoomList(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void onZhanjiInnList(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void onZhanjiQueryReply(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void Recond2ProtoC(const ::msg_maj::HistoryRecordS& srcProto, ::msg_maj::HistoryRecord& distProto);
	void Recond2ProtoCRoom(const ::msg_maj::HistoryRecordS& srcProto, ::msg_maj::HistoryRoomResp& distProto);
	void Recond2ProtoCInn(const ::msg_maj::HistoryRecordS& srcProto, ::msg_maj::HistoryInnResp& distProto, int32_t inn_id);
	void onInnRecordAddLogRequest(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void onQueryMailRequest(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void onSaveMailRequest(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void onQueryMailSysLogRequest(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void onSaveMailSysLogRequest(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void onMaxUUIDRequest(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void onRechargeRoomCard(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void onSendBlockUser(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void onEditRoomCard(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);
	void onSaveMoneyLogRequest(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void onGetRewardConfigReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void onGetFreeConfigReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void onGetNotifyConfigReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void onGetRoomSetConfigReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

private:


	
};


#endif

