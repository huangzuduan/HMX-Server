#include "NetMsgHandler.h"
#include "SrvIncludes.h"
#include "ProcSsHandler.h"
#include "ProcWorldHandler.h"
#include "GameService.h"

NetMsgHandler::NetMsgHandler() :zMsgHandler(GameService::Instance())
{
	// ws 
#define REGISTER_WS_MESSAGE(cmd,cmdType,cls,handler)\
	{\
	RegisterMessage(cmd,cmdType, sizeof(cls), boost::bind(&ProcWorldHandler::handler, ProcWorldHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_WS_MESSAGE(::comdef::msg_ss, ::msg_maj::SendMailID, PbMsgWebSS, onSendMail);
	REGISTER_WS_MESSAGE(::comdef::msg_ss, ::msg_maj::SendRoomCardID, PbMsgWebSS, onSendRoomCard);
	REGISTER_WS_MESSAGE(::comdef::msg_ss, ::msg_maj::UserEditCardID, PbMsgWebSS, onUserEditCard);
	REGISTER_WS_MESSAGE(::comdef::msg_ss, ::msg_maj::SaveOnlinePlayerID, PbMsgWebSS, onSaveOnlinePlayer);
	REGISTER_WS_MESSAGE(::comdef::msg_ss, ::msg_maj::SaveRoomOptionReqID, PbMsgWebSS, onSaveRoomOption);
	REGISTER_WS_MESSAGE(::comdef::msg_ss, ::msg_maj::UpdateRoomOptionReqID, PbMsgWebSS, onUpdateRoomOption);
	
#undef REGISTER_WS_MESSAGE

		// ls
#define REGISTER_LS_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcLsHandler::handler, ProcLsHandler::Instance(), _1, _2, _3)); \
	}

#undef REGISTER_LS_MESSAGE

		// ss
#define REGISTER_SS_MESSAGE(cmd,cmdType,cls,handler)\
	{\
	RegisterMessage(cmd,cmdType, sizeof(cls), boost::bind(&ProcSsHandler::handler, ProcSsHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::QueryPlayerRequestID, PbMsgWebSS,onQueryPlayerRequest);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::SavePlayerDataReqID, PbMsgWebSS,onSavePlayerDataReq);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::ZhanJiRecordAddRequestID, PbMsgWebSS,onZhanjiAddRecordRequest);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::ZhanJiFinishRequestID, PbMsgWebSS,onZhanjiFinishRequest);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::ZhanjiQueryListRequestID, PbMsgWebSS,onZhanjiQueryList);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::ZhanjiQueryRoomRequestID, PbMsgWebSS, onZhanjiRoomList);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::ZhanjiQueryReplyRequestID, PbMsgWebSS,onZhanjiQueryReply);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::InnRecordAddLogRequestID, PbMsgWebSS, onInnRecordAddLogRequest);

	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::QueryMailRequestID, PbMsgWebSS,onQueryMailRequest);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::SaveMailRequestID, PbMsgWebSS,onSaveMailRequest);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::QueryMailSysLogRequestID, PbMsgWebSS, onQueryMailSysLogRequest);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::SaveMailSysLogRequestID, PbMsgWebSS, onSaveMailSysLogRequest);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::GetMaxUUIDRequestID, PbMsgWebSS,onMaxUUIDRequest);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::RechargeRoomCardID, PbMsgWebSS,onRechargeRoomCard);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::SendBlockUserID, PbMsgWebSS,onSendBlockUser);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::SendEditRoomCardID, PbMsgWebSS,onEditRoomCard);	
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::SaveMoneyLogRequestID, PbMsgWebSS, onSaveMoneyLogRequest);

	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::GetFreeConfigReqID, PbMsgWebSS, onGetRewardConfigReq);
	REGISTER_SS_MESSAGE(::comdef::msg_ss,::msg_maj::GetRewardConfigReqID, PbMsgWebSS, onGetFreeConfigReq);
	REGISTER_SS_MESSAGE(::comdef::msg_ss, ::msg_maj::GetNotifyConfigReqID, PbMsgWebSS, onGetNotifyConfigReq);
	REGISTER_SS_MESSAGE(::comdef::msg_ss, ::msg_maj::GetRoomSetConfigReqID, PbMsgWebSS, onGetRoomSetConfigReq);
	
#undef REGISTER_SS_MESSAGE


}


NetMsgHandler::~NetMsgHandler()
{ 
}


void NetMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	CommonOnNetMsgEnter(rSocket);
}

void NetMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg, int32_t nSize)
{
	CommonOnNetMsg(rSocket, pMsg, nSize);
}

void NetMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	CommonOnNetMsgExit(rSocket);
}




