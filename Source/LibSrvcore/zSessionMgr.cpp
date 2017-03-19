#include "SrvEngine.h"


zSessionMgr::zSessionMgr():serverobjpool(1), clientobjpool(4), sessionobjpool(64)
{
}

zSessionMgr::~zSessionMgr()
{
}

bool zSessionMgr::getUniqeID(QWORD& tempid)
{
	return true;
}

void zSessionMgr::putUniqeID(const QWORD& tempid)
{

}

zSession* zSessionMgr::getByServerID(zSession::SessionType fun,int32 serverid)
{
	struct FindSession : public execEntry<zSession>
	{
		FindSession(zSession::SessionType _fun,int32 _serverid):fun(_fun), serverid(_serverid)
		{
			session = NULL;
		}

		virtual bool exec(zSession* entry)
		{
			if (!session && entry->sessionType == fun && entry->serverid == serverid)
			{
				session = entry;
			}
			return true;
		}
		zSession::SessionType fun;
		int32 serverid;
		zSession* session;
	};

	FindSession find(fun, serverid);
	execEveryEntry(find);
	return find.session;
}

zSession* zSessionMgr::getWs(int32 serverid)
{
	return getByServerID(zSession::FOR_WORLD, 3001);
}

zSession* zSessionMgr::getLs(int32 serverid)
{
	return getByServerID(zSession::FOR_LOGIN, 2001);
}

zSession* zSessionMgr::getFep(int32 serverid)
{
	return getByServerID(zSession::FOR_FEP, serverid);
}

zSession* zSessionMgr::getSs(int32 serverid)
{
	return getByServerID(zSession::FOR_SCENE, serverid);
}

zSession* zSessionMgr::getDp(int32 serverid)
{
	return getByServerID(zSession::FOR_DP, serverid);
}

bool zSessionMgr::sendMsg(int64 sessid,const NetMsgSS* pMsg, int32 nSize)
{
	zSession* session = get(sessid);
	if (session)
	{
		session->sendMsg(pMsg, nSize);
		return true;
	}
	return false;
}

bool zSessionMgr::sendToWs(const NetMsgSS* pMsg, int32 nSize)
{
	zSession* ws = getWs();
	if (ws)
	{
		ws->sendMsg(pMsg, nSize);
		return true;
	}
	return false;
}

bool zSessionMgr::sendToDp(const NetMsgSS* pMsg, int32 nSize)
{
	zSession* dps = getDp();
	if (dps)
	{
		dps->sendMsg(pMsg, nSize);
		return true;
	}
	return false;
}

bool zSessionMgr::sendToLs(const NetMsgSS* pMsg, int32 nSize)
{
	zSession* ls = getLs();
	if (ls)
	{
		ls->sendMsg(pMsg, nSize);
		return true;
	}
	return false;
}

bool zSessionMgr::sendToSs(int32 serverid, const NetMsgSS* pMsg, int32 nSize)
{
	zSession* ss = getByServerID(zSession::FOR_SCENE, serverid);
	if (ss)
	{
		ss->sendMsg(pMsg, nSize);
		return true;
	}
	return false;
}

bool zSessionMgr::sendToFep(int32 serverid, const NetMsgSS* pMsg, int32 nSize)
{
	zSession* fep = getByServerID(zSession::FOR_FEP, serverid);
	if (fep)
	{
		fep->sendMsg(pMsg, nSize);
		return true;
	}
	return false;
}

bool zSessionMgr::bind(int32 id, const char* ip, int16 port,int16 maxConnects,NetMsgEnter fEnter, NetMsgOn fMsg, NetMsgExit fExit)
{
	NetServer* server = serverobjpool.CreateObj(maxConnects);
	SocketMap& setAcceptSockets = server->getSetAccepts();
	SocketMap::iterator it = setAcceptSockets.begin();
	for (; it != setAcceptSockets.end(); ++it)
	{
		zSession* session = CreateObj(it->second);
		session->id = it->second->SLongID();
		if (!add(session))
		{
			DestoryObj(session);
			ASSERT(0);
			continue;
		}
		session->setServerType(zSession::SERVER_TYPE_SERVER);
		session->serivceid = id;
	}

	server->SetTimeout(SERVER_TIMEOUT);
	server->SetAddress(ip, port);
	server->SetHandler(fEnter, fMsg, fExit);
	server->Start();

	serverListAdd.push_back(server);

	H::logger->info("启动一个服务:ID=%d,IP=%s,PORT=%d", id, ip,(int32) port);

	return true;

}

zSession* zSessionMgr::connect(int32 id, const char* ip, int16 port, NetMsgEnter fEnter, NetMsgOn fMsg, NetMsgExit fExit)
{
	NetClient* client = clientobjpool.CreateObj();
	zSession* session = CreateObj(client->GetSocket());
	session->id = client->GetSocket()->SLongID();
	if (!add(session))
	{	
		DestoryObj(session);
		ASSERT(0);
		return NULL;
	}
	session->setServerType(zSession::SERVER_TYPE_CLIENT);
	session->serivceid = id;

	client->SetAddress(ip, port);
	client->SetHandler(fEnter, fMsg, fExit);
	client->Start();

	clientListAdd.push_back(client);

	H::logger->info("启动一个连接:ID=%d,IP=%s,PORT=%d", id, ip, (int32)port);

	return session;

}

void zSessionMgr::updateIO(const zTaskTimer* timer)
{
	updateServerIO(timer);
	updateClientIO(timer);
}

void zSessionMgr::updateServerIO(const zTaskTimer* timer)
{

	if (!serverListAdd.empty())
	{
		for (std::vector<NetServer*>::iterator itSrv = serverListAdd.begin(); itSrv != serverListAdd.end(); ++itSrv)
		{
			serverListUsed.push_back(*itSrv);
		}

		serverListAdd.clear();
	}

	for (std::vector<NetServer*>::iterator itSrv = serverListUsed.begin(); itSrv != serverListUsed.end(); ++itSrv)
	{
		(*itSrv)->OnUpdate();
	}
}

void zSessionMgr::updateClientIO(const zTaskTimer* timer)
{

	if (!clientListAdd.empty())
	{
		for (std::vector<NetClient*>::iterator itCli = clientListAdd.begin(); itCli != clientListAdd.end(); ++itCli)
		{
			clientListUsed.push_back(*itCli);
		}
		clientListAdd.clear();
	}

	for (std::vector<NetClient*>::iterator itCli = clientListUsed.begin(); itCli != clientListUsed.end(); ++itCli)
	{
		(*itCli)->OnUpdate();
	}
}
