#ifndef _CMSG_CONN_HPP_
#define _CMSG_CONN_HPP_
#include "SrvEngine.h"
#include "Single.h"

class CMsgConn : public Single<CMsgConn>
{
public:
	CMsgConn();
	~CMsgConn();

	void HandleHandshakeResponse(const PbMsgWebSS* pMsg);
	void HandleMsg(const PbMsgWebSS* pMsg);

private: //登陆消息

	void HandleLoginMsg(const PbMsgWebSS* pMsg);

	void HandleLoginPlayerResp(const PbMsgWebSS* pMsg);
	void HandleCreateRoomResp(const PbMsgWebSS* pMsg);
	void HandleEnterRoomResp(const PbMsgWebSS* pMsg);
	void HandleRoomReadyNotify(const PbMsgWebSS* pMsg);
	void HandleInnRoomInfoNotify(const PbMsgWebSS* pMsg);
	void HandleSyncRoleInfResp(const PbMsgWebSS* pMsg);
	void HandleAskStartGameResp(const PbMsgWebSS* pMsg);
	void HandleStartRoundResp(const PbMsgWebSS* pMsg);
	void HandleDealTileNotify(const PbMsgWebSS* pMsg);
	void HandleDiscardTileResp(const PbMsgWebSS* pMsg);
	void HandleGameResultNotify(const PbMsgWebSS* pMsg);
	void HandleTotalResultNotify(const PbMsgWebSS* pMsg);
	void HandleResponseResp(const PbMsgWebSS* pMsg);
	void HandleNotifyPlayerEvent(const PbMsgWebSS* pMsg);
	void HandlePrepareRoundNotify(const PbMsgWebSS* pMsg);
	void HandleDismissRoomNotify(const PbMsgWebSS* pMsg);
	void HandleDismissRoomResp(const PbMsgWebSS* pMsg);

	void HandleRobotReconnected(const PbMsgWebSS* pMsg);
	void HandleRobotStartRoundResp(const PbMsgWebSS* pMsg);
	void HandleRobotDiscardTingNotify(const PbMsgWebSS* pMsg);

	void HandleAskSanZhuang(const PbMsgWebSS* pMsg);
	void HandleHuanSanNotify(const PbMsgWebSS* pMsg);
	void HandleAskDingQue(const PbMsgWebSS* pMsg);
	
	void HandleReconnectSyncCard(const PbMsgWebSS* pMsg);

private:
	
	void HandleRoomMsg(const PbMsgWebSS* pMsg); //房间消息
	void HandleMajiangMsg(const PbMsgWebSS* pMsg);//麻将消息
	
};



#endif // !_CMSG_CONN_HPP_
