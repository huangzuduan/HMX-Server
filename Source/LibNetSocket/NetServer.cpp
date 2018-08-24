#include "NetServer.h"
#include "NetSocket.h"

NetServer::NetServer(int32_t nMaxConnected):m_nMaxConnected(nMaxConnected),m_cAcceptor(*this)
{
	static int32_t s_nIncreaseNetServerID = 0;
	m_nServerID = ++s_nIncreaseNetServerID;

	for (int32_t i = 0; i < nMaxConnected && i < MAX_SOCKETS; i++)
	{
		m_vecSocket.push_back(new NetSocket(*this));
	}
}


NetServer::~NetServer()
{
	for (int32_t i = 0; i < m_nMaxConnected; i++)
	{
		NetSocket* pSocket = m_vecSocket[i];
		if (pSocket)
		{
			delete pSocket;
			pSocket = NULL;
		}
	}
	m_setWaitAccept.clear();
}

int32_t NetServer::SocketID()
{
	return m_nServerID;
}

void NetServer::SetTimeout(int32_t nTimeout)
{
	for (int32_t i = 0; i < m_nMaxConnected; i++)
	{
		m_vecSocket[i]->SetTimeout(nTimeout);
	}
}

void NetServer::SetAccept(NetSocket& rSocket)
{
	m_setWaitAccept.insert(std::make_pair(rSocket.SocketID(), &rSocket));
	m_cAcceptor.async_accept(rSocket, boost::bind(&NetServer::HandleAccept, this, boost::asio::placeholders::error, &rSocket));
}


void NetServer::SetAddress(const char* pIp, uint16_t nPort)
{
	boost::system::error_code ec;
	m_cServerAddr = tcp::endpoint(address::from_string(pIp, ec), nPort);
	assert(!ec);
}

void NetServer::SetHandler(PNetServerEnterHandler pEnter, PNetServerOnMsgHandler pOnMsg, PNetServerExistHandler pExit)
{
	m_pOnEnter = pEnter;
	m_pOnMsg = pOnMsg;
	m_pOnExit = pExit;
}

void NetServer::Run()
{
	while (true)
	{
		boost::system::error_code ec;
#ifdef _DEBUG
		run(ec);
		break;
#else
		try
		{
			run(ec);
			break;
		}
		catch (std::exception& e)
		{
			printf("[ERROR]:NetServer Error Msg:%s\n", e.what());
		}
#endif
	}
}


void NetServer::Start()
{
	// Start socket use a new thread , that can loop
	boost::thread t(boost::bind(&NetServer::HandleStart, this));
	boost::this_thread::yield();		// Temporarily give up a CPU time , to other threads
	t.swap(m_cServiceThread);	// Swaps the state of the object with that of mServiceThread
}


void NetServer::HandleStart()
{
	boost::system::error_code ec;
	m_cAcceptor.open(m_cServerAddr.protocol(), ec);
	assert(!ec);
	m_cAcceptor.set_option(tcp::acceptor::reuse_address(true), ec);
	assert(!ec);
	m_cAcceptor.bind(m_cServerAddr, ec);
	if (ec)
	{
		printf("[ERROR]:bind port fail \n");
		assert(!ec);
		return;
	}
	
	m_cAcceptor.listen(socket_base::max_connections, ec);
	assert(!ec);
	for (int i = 0; i < m_nMaxConnected; ++i)
	{
		SetAccept(*m_vecSocket[i]);
	}
	boost::thread_group tg;
	for (int i = 0; i < MAX_THREAD; ++i)
	{
		tg.create_thread(boost::bind(&NetServer::Run, this));
	}
	boost::this_thread::yield();
	tg.join_all();
}

void NetServer::Stop()
{

}

void NetServer::OnUpdateAccept()
{
	boost::mutex::scoped_lock cLock(m_cClientListMutex);
	for (SocketMapIter it = m_mapHadAccepted.begin(); it != m_mapHadAccepted.end(); ++it)
	{
		(m_pOnEnter)(*it->second);
		m_mapIsUsing[it->second->SocketID()] = it->second;
	}
	m_mapHadAccepted.clear();
	cLock.unlock();
}

void NetServer::OnUpdateRecived()
{
	for (SocketMapIter it = m_mapIsUsing.begin(); it != m_mapIsUsing.end();)
	{
		NetSocket* pSocket = it->second;
		if (!pSocket)
		{
			++it;
			continue;
		}
			
		/* 处理关闭事件 */ 
		if (pSocket->GetIsClose())
		{
			if (!pSocket->GetIsCloseBegin())
			{
				pSocket->SetIsCloseBeing(true);
				(m_pOnExit)(*pSocket);
				pSocket->Disconnect();
			}
			if (pSocket->GetIsCloseFinish())
			{
				pSocket->SetLocalClose(false);
#ifdef WIN32
				Sleep(10);
#else
				usleep(10);
#endif
				m_mapIsUsing.erase(it++);
				SetAccept(*pSocket);
			}
			continue;
		}
		else
		{
			uint8_t* data = NULL;
			int32_t len = pSocket->ReadDataMsg(&data);
			if (len == -1)
			{
				pSocket->SetLocalClose(true);
				return;
			}
			if (len > 0)
			{
				(m_pOnMsg)(*pSocket, (NetMsgSS*)data, len);
				pSocket->RemoveQueueHeader();
			}
			++it;
		}
	}
}


void NetServer::OnUpdate()
{
	if (!m_mapHadAccepted.empty())
	{
		OnUpdateAccept();
	}

	if (!m_mapIsUsing.empty())
	{
		OnUpdateRecived();
	}
}

void NetServer::HandleAccept(const boost::system::error_code& rError, NetSocket* pSocket)
{
	SocketMapIter it = m_setWaitAccept.find(pSocket->SocketID());
	if (it != m_setWaitAccept.end())
	{
		m_setWaitAccept.erase(it);
	}
	if (rError)
	{
		SetAccept(*pSocket);
		return;
	}
	boost::mutex::scoped_lock lock(m_cClientListMutex);
	pSocket->Clear();
	m_mapHadAccepted[pSocket->SocketID()] = pSocket;
	pSocket->Run();
	lock.unlock();
}

NetSocket& NetServer::GetSocket(int32_t nIndex)
{
	return *m_vecSocket[nIndex];
}

size_t NetServer::ConnectedSockets()
{
	return m_mapIsUsing.size();
}

size_t NetServer::AcceptingSockets()
{
	return m_mapHadAccepted.size();
}

NetSocket* NetServer::getAcceptSocket(int64_t socketid)
{
	SocketMapIter it = m_mapHadAccepted.find(socketid);
	if (it != m_mapHadAccepted.end())
	{
		return it->second;
	}
	return NULL;
}

NetSocket* NetServer::getUsedSocket(int64_t socketid)
{
	SocketMapIter it = m_mapIsUsing.find(socketid);
	if (it != m_mapIsUsing.end())
	{
		return it->second;
	}
	return NULL;
}












