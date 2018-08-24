#include "NetMsgHandler.h"
#include "PlayerProcHandler.h"
#include "GameService.h"
#include "Player.h"
#include "PlayerMgr.h"

NetMsgHandler::NetMsgHandler():zMsgHandler(GameService::Instance())
{
	/* common 需要用到内部协议 */
	/* 内部协议，即不分不同servertype，都去做统一的事情，如登录，返回列表，ping等等操作 */
#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler) \
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&NetMsgHandler::handler, this, _1, _2, _3)); \
	}

#undef REGISTER_INTERNAL_MESSAGE

	// from server
#define REGISTER_FEP_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&PlayerProcHandler::handler, PlayerProcHandler::Instance(), _1, _2, _3)); \
	}

#undef REGISTER_FEP_MESSAGE

}


NetMsgHandler::~NetMsgHandler()
{
}


void NetMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	H::logger->info("连接成功！来自于:id=%d ip=%s,port=%d", rSocket.SocketID(), rSocket.GetIp().c_str(), (int32_t)rSocket.GetPort());
	zSession* pSession = GameService::getMe().SessionMgr()->get(rSocket.SocketID());
	if (pSession)
	{
		Player* player = PlayerMgr::getMe().get(pSession->GetID());
		if (player)
		{
			PlayerProcHandler::SendEncrypt(player);
			H::logger->info("发送请求密钥信息到:ip=%s port=%d", rSocket.GetIp().c_str(), (int32_t)rSocket.GetPort());
		}
	}
	else
	{
		ASSERT(0);
	}
}

void NetMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg, int32_t nSize)
{
	zSession* pSession = GameService::getMe().SessionMgr()->get(rSocket.SocketID());
	if (pSession == NULL)
	{
		H::logger->error("Can not find session");
		rSocket.OnEventColse();
		return;
	}

	// 解密处理 
	static char msgEnBuffer[65536];
	static char msgUnBuffer[65536];

	int nCHeadSize = sizeof(NetMsgC);
	int nSHeadSize = sizeof(NetMsgSS);
	memcpy(&msgEnBuffer[0], pMsg, nSize);

	zEncrypt::xorCode(nSize, pSession->encrypt, msgEnBuffer, nSize);

	// 组装为NetMsgSS头协议，中间补两种头协议的字节差 
	memcpy(&msgUnBuffer[0], msgEnBuffer, nCHeadSize);
	memset(&msgUnBuffer[nCHeadSize], 0, nSHeadSize - nCHeadSize);
	memcpy(&msgUnBuffer[nSHeadSize], &msgEnBuffer[nCHeadSize], nSize - nCHeadSize);

	pMsg = (NetMsgSS*)&msgUnBuffer[0];

	const MsgFunc* pMsgHandlerInfo = GetMsgHandler(pMsg->protocol);
	if (pMsgHandlerInfo == NULL)
	{
		H::logger->error("找不到该协议:%d,大小:%d", pMsg->protocol, nSize);
		rSocket.OnEventColse();
		return;
	}

	H::logger->info("收到协议=%d", pMsg->protocol);

	(pMsgHandlerInfo->handlerFun)((zSession*)(pSession), (PbMsgWebSS*)pMsg, nSize);
}

/* 有Server断开回调(此时socket已经回收) */
void NetMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	H::logger->info("连接断开！来自于:id=%d ip=%s,port=%d", rSocket.SocketID(), rSocket.GetIp().c_str(), (int32_t)rSocket.GetPort());
}










