#include "NetServer.h"
#include "NetSocket.h"

NetServer::NetServer(int32 nMaxConnected, int32 nMaxRecivedSize, int32 nMaxSendoutSize, int32 nMaxRecivedCacheSize, int32 nMaxSendoutCacheSize):m_nMaxConnected(nMaxConnected),m_cAcceptor(*this)
{
	int32 _nPreCacehTotal = 1024 * 1024 * 512; // 500M
	int32 _nMaxConnectNum = _nPreCacehTotal / (nMaxRecivedCacheSize + nMaxSendoutCacheSize);
	int32 _nMaxRecivedCacheSize = (_nPreCacehTotal - nMaxConnected * nMaxSendoutCacheSize) / nMaxConnected;
	int32 _nMaxSendoutCacheSize = (_nPreCacehTotal - nMaxConnected * nMaxRecivedCacheSize) / nMaxConnected;
	if (!(0 < nMaxConnected && nMaxConnected < _nMaxConnectNum))
	{
		printf("[ERROR]:nMaxConnectd need <= 1000 & Cache Max is 500M\n");
		ASSERT(0);
		return;
	}

	if (nMaxRecivedSize < 1 || nMaxRecivedSize > 65536 || nMaxSendoutSize < 1 || nMaxSendoutSize > 65536 ||
		nMaxRecivedCacheSize < 1 || nMaxRecivedCacheSize > _nMaxRecivedCacheSize || nMaxSendoutCacheSize < 1 || nMaxSendoutCacheSize > _nMaxSendoutCacheSize)
	{
		printf("[ERROR]:nMaxRecivedSize | nMaxSendoutSize | nMaxRecivedCacheSize | nMaxSendoutCacheSize Need < ? & > 0\n");
		ASSERT(0);
		return;
	}

	if (nMaxConnected > (sizeof(m_arrSocket) / sizeof(m_arrSocket[0])) )
	{
		printf("[ERROR]:nMaxConnected > %lld", (sizeof(m_arrSocket) / sizeof(m_arrSocket[0])));
		ASSERT(0);
		return;
	}

	static int32 s_nIncreaseNetServerID = 0;
	m_nServerID = ++s_nIncreaseNetServerID;

	for (int32 i = 0; i < nMaxConnected; i++)
	{
		m_arrSocket[i] = new NetSocket(*this, nMaxRecivedSize, nMaxSendoutSize, nMaxRecivedCacheSize, nMaxSendoutCacheSize);
		m_setAcceptSocket.insert(std::make_pair(m_arrSocket[i]->SLongID(), m_arrSocket[i]));
	}
}


NetServer::~NetServer()
{
	for (int32 i = 0; i < m_nMaxConnected; i++)
	{
		NetSocket* pSocket = m_arrSocket[i];
		if (pSocket)
		{
			delete pSocket;
			pSocket = NULL;
		}
	}
	m_setAcceptSocket.clear();
}

int32 NetServer::SID()
{
	return m_nServerID;
}

void NetServer::SetTimeout(int32 nTimeout)
{
	for (int32 i = 0; i < m_nMaxConnected; i++)
	{
		m_arrSocket[i]->SetTimeout(nTimeout);
	}
}

void NetServer::SetAccept(NetSocket& rSocket)
{
	m_cAcceptor.async_accept(rSocket, boost::bind(&NetServer::HandleAccept, this, boost::asio::placeholders::error, &rSocket));
}


void NetServer::SetAddress(const char* pIp, uint16 nPort)
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
	assert(!ec);
	m_cAcceptor.listen(socket_base::max_connections, ec);
	assert(!ec);
	for (int i = 0; i < m_nMaxConnected; ++i)
	{
		SetAccept(*m_arrSocket[i]);
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
	for (SocketMapIter it = m_mapAcceptSocket.begin(); it != m_mapAcceptSocket.end(); ++it)
	{
		(m_pOnEnter)(*it->second);
		m_mapUsedSocket[it->second->SLongID()] = it->second;
	}
	m_mapAcceptSocket.clear();
	cLock.unlock();
}

void NetServer::OnUpdateRecived()
{
	static size_t nSocketSize = 0;
	static int32 nMsgBodyLen = 0;
	static NetMsgSS* pMsg = NULL;
	
	for (SocketMapIter it = m_mapUsedSocket.begin(); it != m_mapUsedSocket.end();)
	{
		NetSocket* pSocket = it->second;
		if (!pSocket)
		{
			++it;
			continue;
		}
			
		/* Pre处理事件 */ 
		if (pSocket->HadEventClose())
		{
			(m_pOnExit)(*pSocket);
			m_mapUsedSocket.erase(it++);
			pSocket->Disconnect();
			SSleep(10); // for disconnect
			SetAccept(*pSocket);
			continue;
		}
		else
		{
			int msgStatus = pSocket->ReadMsg(&pMsg, nMsgBodyLen);
			switch (msgStatus)
			{
			case MSG_READ_INVALID: /* 断开socket，再设置为重新等待 */
			{
				pSocket->AddEventLocalClose();
			}
			break;
			case MSG_READ_OK: /* 收到正常的数据请求 */
			{

				(m_pOnMsg)(*pSocket, pMsg, nMsgBodyLen);
				pSocket->RemoveMsg(PACKAGE_HEADER_SIZE + nMsgBodyLen);
			}
			break;
			case MSG_READ_WAITTING:
			case MSG_READ_REVCING:
				break;
			}
			++it;
		}
	}
}


void NetServer::OnUpdate()
{
	if (!m_mapAcceptSocket.empty())
	{
		OnUpdateAccept();
	}

	if (!m_mapUsedSocket.empty())
	{
		OnUpdateRecived();
	}
}

void NetServer::HandleAccept(const boost::system::error_code& rError, NetSocket* pSocket)
{
	if (rError)
	{
		SetAccept(*pSocket);
		return;
	}

	boost::mutex::scoped_lock lock(m_cClientListMutex);
	pSocket->Clear();
	m_mapAcceptSocket[pSocket->SLongID()] = pSocket;
	pSocket->Run();
	lock.unlock();
}

NetSocket& NetServer::GetSocket(int32 nIndex)
{
	return *m_arrSocket[nIndex];
}

size_t NetServer::ConnectedSockets()
{
	return m_mapUsedSocket.size();
}

size_t NetServer::AcceptingSockets()
{
	return m_mapAcceptSocket.size();
}

NetSocket* NetServer::getAcceptSocket(int64 socketid)
{
	SocketMapIter it = m_mapAcceptSocket.find(socketid);
	if (it != m_mapAcceptSocket.end())
	{
		return it->second;
	}
	return NULL;
}

NetSocket* NetServer::getUsedSocket(int64 socketid)
{
	SocketMapIter it = m_mapUsedSocket.find(socketid);
	if (it != m_mapUsedSocket.end())
	{
		return it->second;
	}
	return NULL;
}












