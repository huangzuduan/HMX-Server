#ifndef _PROC_WORLD_HANDLER_H_
#define _PROC_WORLD_HANDLER_H_

#include "Single.h"
#include "SrvEngine.h"

class zSession;
struct DUser;
struct PbMsgWebSS;


class ProcWorldHandler : public Single<ProcWorldHandler>
{
public:
	ProcWorldHandler();
	~ProcWorldHandler();

	void ReqLogin(zSession* pBaseSession, const PbMsgWebSS* pMsg,int32_t nSize);

	void ReqNotifyServerInfo(zSession* pBaseSession, const PbMsgWebSS* pMsg,int32_t nSize);

	void ReqNotifySceneInfo(zSession* pBaseSession, const PbMsgWebSS* pMsg,int32_t nSize);

	void ReqQueryEventInfo(zSession* pBaseSession, const PbMsgWebSS* pMsg,int32_t nSize);

	void ReqSelectRole(zSession* pBaseSession, const PbMsgWebSS* pMsg,int32_t nSize);

	void ReqLoadSortLists(zSession* pBaseSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void ReqSaveSortLists(zSession* pBaseSession, const PbMsgWebSS* pMsg, int32_t nSize);

	//////////////////////////////////////////////////////////////////////////

	void CallBackSelectRole(int32_t nCSID, DUser* pUserMem);

	void onSendRoomCard(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void onUserEditCard(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void onSendMail(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void onSaveOnlinePlayer(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void onSaveRoomOption(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void onUpdateRoomOption(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void doRecordRoomCard(const ::fogs::proto::msg::RechargeRoomCard proto);
	void doRecordMoneyLog(const ::fogs::proto::msg::MoneyLog& moneyLog);
};


#endif

