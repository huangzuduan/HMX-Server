#include "SrvEngine.h"

zMsgHandler::zMsgHandler(zNetSerivce* pSerivce):m_pNetSerivce(pSerivce)
{
	/* common 需要用到内部协议 */
	/* 内部协议，即不分不同servertype，都去做统一的事情，如登录，返回列表，ping等等操作 */
#define REGISTER_INTERNAL_MESSAGE(cmd,cmdType,cls,handler) \
	{\
	RegisterMessage( cmd, cmdType, sizeof(cls), boost::bind(&zMsgHandler::handler, this, _1, _2, _3)); \
}

	REGISTER_INTERNAL_MESSAGE(::hmx_cmd::msg_login,::hmx_msg_login::login_req, PbMsgWebSS, recvLoginRequest);
	REGISTER_INTERNAL_MESSAGE(::hmx_cmd::msg_login,::hmx_msg_login::login_resp, PbMsgWebSS, recvLoginReponse);
	REGISTER_INTERNAL_MESSAGE(::hmx_cmd::msg_login,::hmx_msg_login::ping_req, PbMsgWebSS, recvPingRequest);
	REGISTER_INTERNAL_MESSAGE(::hmx_cmd::msg_login,::hmx_msg_login::ping_resp, PbMsgWebSS, recvPingResponse);
	REGISTER_INTERNAL_MESSAGE(::hmx_cmd::msg_login,::hmx_msg_login::srvlist_notify, PbMsgWebSS, recvSrvListNotifty);

#undef REGISTER_INTERNAL_MESSAGE
}

zMsgHandler::~zMsgHandler()
{

}

void zMsgHandler::CommonOnNetMsgEnter(NetSocket& socket)
{
	H::logger->info("连接成功！来自于:id=%d ip=%s,port=%d", socket.SocketID(), socket.GetIp().c_str(), (int32_t)socket.GetPort());
	zSession* pSession = m_pNetSerivce->SessionMgr()->get(socket.SocketID());
	if (pSession)
	{
		::hmx_msg_login::LoginReq proto;
		proto.mutable_server_info()->CopyFrom(pSession->GetDataProto());
		zServerMgr* pSrvMgr = m_pNetSerivce->SrvSerivceMgr()->GetServerMgr(m_pNetSerivce->GetServerID());
		if (pSrvMgr)
		{
			std::vector<zSerivce*> vecBroadSerives;
			pSrvMgr->GetBroadSerives(vecBroadSerives);
			for (size_t i = 0; i < vecBroadSerives.size(); ++i)
			{
				proto.add_broad_serivce_list()->CopyFrom(vecBroadSerives[i]->GetDataProto());
			}
		}
		pSession->sendMsgProto(::hmx_cmd::msg_login, ::hmx_msg_login::login_req, proto);
		H::logger->info("发送连接信息到:ip=%s port=%d", socket.GetIp().c_str(), (int32_t)socket.GetPort());
	}
	else
	{
		H::logger->info("连接信息找不到:ip=%s port=%d", socket.GetIp().c_str(), (int32_t)socket.GetPort());
		//ASSERT(0);
	}
}

void zMsgHandler::CommonOnNetMsg(NetSocket& socket, NetMsgSS* pMsg, int32_t nSize)
{
	zSession* pSession = m_pNetSerivce->SessionMgr()->get(socket.SocketID());
	if (pSession == NULL)
	{
		H::logger->error("Can not find session");
		socket.OnEventColse();
		ASSERT(0);
		return;
	}

	const MsgFunc* pMsgHandler = GetMsgHandler(pMsg->cmd,pMsg->cmdType);
	if (pMsgHandler == NULL)
	{
		H::logger->error("找不到该协议 cmd=%d,cmdType=%d,protocol=%d,大小:%d", pMsg->cmd, pMsg->cmdType, pMsg->protocol,nSize);
		//ASSERT(0);
		return;
	}

	H::logger->info("收到协议 cmd=%d,cmdType=%d,protocol=%d", pMsg->cmd, pMsg->cmdType, pMsg->protocol);

	(pMsgHandler->handlerFun)((zSession*)(pSession), (PbMsgWebSS*)pMsg, nSize);
}

void zMsgHandler::CommonOnNetMsgExit(NetSocket& socket)
{
	H::logger->info("连接断开！来自于:id=%d ip=%s,port=%d", socket.SocketID(), socket.GetIp().c_str(), (int32_t)socket.GetPort());
}

const MsgFunc* zMsgHandler::GetMsgHandler(uint32_t protocol)
{
	MsgFuncMap::iterator it = msgFuncs.find(protocol);
	if (it != msgFuncs.end())
	{
		return &(it->second);
	}
	return NULL;
}

const MsgFunc* zMsgHandler::GetMsgHandler(uint16_t cmd, uint16_t cmdType)
{
	UnProtocol unp;
	unp.cmd = cmd;
	unp.cmdType = cmdType;
	return GetMsgHandler(unp.protocol);
}

bool zMsgHandler::RegisterMessage(uint32_t msgIdx, int32_t packSize, const HandleFunc& handlerFun)
{
	if (!msgFuncs.insert(std::make_pair(msgIdx, MsgFunc(packSize, handlerFun))).second)
	{
		printf("协议重复:%u",msgIdx);
		ASSERT(0);
	}
	return true;
}

bool zMsgHandler::RegisterMessage(uint16_t cmd, uint16_t cmdType, int32_t packSize, const HandleFunc& handlerFun)
{
	UnProtocol unp;
	unp.cmd = cmd;
	unp.cmdType = cmdType;
	return RegisterMessage(unp.protocol,packSize,handlerFun);
}

void zMsgHandler::recvLoginRequest(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	::hmx_msg_login::LoginReq proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	pSession->SetRemoteDataProto(proto.server_info());
	zServerReg* addReg = m_pNetSerivce->ServerRegMgr()->add(proto.server_info());
	if (addReg == NULL)
	{
		H::logger->error("注册服务器ID重复:%d", proto.server_info().serverid());
		::hmx_msg_login::LoginResp proResp;
		proResp.set_server_id(m_pNetSerivce->GetServerID());
		proResp.set_server_type(m_pNetSerivce->GetServerType());
		proResp.set_result(::hmx_msg_login::login_r_fail);
		pSession->sendMsgProto(::hmx_cmd::msg_login,::hmx_msg_login::login_resp,proResp);
		return;
	}
	else
	{
		H::logger->info("注册服务器ID:%d,来源于:%d", proto.server_info().serverid(), pSession->GetRemoteServerID());
	}

	// 添加需要广播的服务器消息
	for (int i = 0; i < proto.broad_serivce_list_size(); ++i)
	{
		addReg->AddBroadSerivce(proto.broad_serivce_list(i));
	}

	::hmx_msg_login::LoginResp proResp;
	proResp.set_result(::hmx_msg_login::login_r_success);
	proResp.set_server_id(m_pNetSerivce->GetServerID());
	proResp.set_server_type(m_pNetSerivce->GetServerType());
	pSession->sendMsgProto(::hmx_cmd::msg_login, ::hmx_msg_login::login_resp, proResp);

	// 广播信息只能允许WorldServer
	if (m_pNetSerivce->GetServerType() == 3)
	{
		if (addReg->GetRecvSrvList())
		{
			this->GetRecvSrvListToMe(pSession);
		}
		if (addReg->GetBroadcast())
		{
			this->GetBroadcastToRecvers(addReg);
		}
	}
}

void zMsgHandler::recvLoginReponse(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	::hmx_msg_login::LoginResp proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	if (proto.result() == ::hmx_msg_login::login_r_success)
	{
		H::logger->info("新登录成功！来自于:server_id=%d server_type=%d", proto.server_id(), proto.server_type());
		NewLoginSuccessed(pSession, proto.server_id(), proto.server_type());
	}
	else
	{
		H::logger->error("登录失败");
	}
}

void zMsgHandler::GetRecvSrvListToMe(zSession* pSession)
{
	struct MyStruct : public execEntry<zServerReg>
	{
		virtual bool exec(zServerReg* entry)
		{
			if (entry->GetBroadcast())
			{
				const std::vector< ::config::SerivceInfo>& broadSerivces = entry->GetBroadSerivces();
				if (!broadSerivces.empty())
				{
					for (size_t i = 0; i < broadSerivces.size(); ++i)
					{
						proto.add_serivce_list()->CopyFrom(broadSerivces[i]);
					}
				}
			}
			return true;
		}
		::hmx_msg_login::SerivceListResp proto;
	};

	MyStruct exec;
	m_pNetSerivce->ServerRegMgr()->execEveryServer(exec);
	if (exec.proto.serivce_list_size() > 0)
	{
		pSession->sendMsgProto(::hmx_cmd::msg_login, ::hmx_msg_login::srvlist_notify, exec.proto);
	}
}

void zMsgHandler::GetBroadcastToRecvers(zServerReg* addReg)
{
	struct MyStruct : public execEntry<zServerReg>
	{
		MyStruct(zNetSerivce* pNetSerivce, zServerReg* addReg) :m_pNetSerivce(pNetSerivce), m_addReg(addReg)
		{
		}
		virtual bool exec(zServerReg* entry)
		{
			if (entry->GetRecvSrvList())
			{
				zSession* pSession = m_pNetSerivce->SessionMgr()->getByServerID(entry->GetServerID());
				if (pSession)
				{
					const std::vector< ::config::SerivceInfo>& broadSerivces = m_addReg->GetBroadSerivces();
					if (!broadSerivces.empty())
					{
						::hmx_msg_login::SerivceListResp sendProto;
						for (size_t i = 0; i < broadSerivces.size(); ++i)
						{
							sendProto.add_serivce_list()->CopyFrom(broadSerivces[i]);
						}
						pSession->sendMsgProto(::hmx_cmd::msg_login, ::hmx_msg_login::srvlist_notify, sendProto);
					}
				}
			}
			return true;
		}
		zNetSerivce* m_pNetSerivce;
		zServerReg* m_addReg;
	};
	MyStruct exec(m_pNetSerivce, addReg);
	m_pNetSerivce->ServerRegMgr()->execEveryServer(exec);
}

void zMsgHandler::recvPingRequest(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	const PbMsgWebSS* packet = static_cast<const PbMsgWebSS*>(pMsg);
	::hmx_msg_login::PingServerClientProto proto;
	proto.ParseFromArray(packet->data, packet->size);

	std::stringstream ss;
	ss << "=====recvPingRequest, from: ";
	ss << proto.from_server_id();
	ss << ",to:";
	ss << proto.to_server_id();

	H::logger->info(ss.str().c_str());
}

void zMsgHandler::recvPingResponse(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	H::logger->info("=====recvPingResponse");
}

void zMsgHandler::recvSrvListNotifty(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	const PbMsgWebSS* packet = static_cast<const PbMsgWebSS*>(pMsg);
	::hmx_msg_login::SerivceListResp proto;
	proto.ParseFromArray(packet->data, packet->size);

	for (int i = 0; i < proto.serivce_list_size(); ++i)
	{
		const ::config::SerivceInfo& info = proto.serivce_list(i);
		if (STRNICMP(info.serivcename().c_str(), "server", 6) == 0 
			&& STRNICMP(info.serivcefun().c_str(), "forss", 5) == 0)
		{
			if (!m_pNetSerivce->doConnectServer(info))
			{
				H::logger->error("Connect Server Fail!");
				ASSERT(0);
			}
		}
	}
}




