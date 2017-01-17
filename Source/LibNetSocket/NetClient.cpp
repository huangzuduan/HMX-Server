
#include "NetClient.h"
#include "NetSocket.h"

/*-------------------------------------------------------------------
 * @Brief : Scoket客户端封装类
 *
 * @Author:hzd 2012/04/03
 *------------------------------------------------------------------*/
NetClient::NetClient(int32 RecivedSize,int32 SendoutSize,int32 RecivedCacheSize,int32 SendoutCacheSize)
{
	pSocket = new NetSocket(*this, RecivedSize, SendoutSize, RecivedCacheSize, SendoutCacheSize);
	m_connected = m_onconnected = false;
}

NetClient::~NetClient(void)
{
	if (pSocket)
	{ 
		delete pSocket;
		pSocket = NULL;
	}
}


void NetClient::Start()
{
	thread t(boost::bind(&NetClient::HandleStart, this));
	this_thread::yield();
	t.swap(m_serviceThread);
}

void NetClient::HandleStart()
{
	// Use thread group can add code to connect more servers 
	// here can SetConnect more socket connect
	SetConnect(*pSocket);

	thread_group tg;
	tg.create_thread(boost::bind(&NetClient::Run, this));
	this_thread::yield();
	tg.join_all(); // Waitting threads to complete

}

void NetClient::SetAddress(const char* ip, uint16 port)
{
	boost::system::error_code ec;
	m_serverAddr = tcp::endpoint(address::from_string(ip, ec), port);
	assert(!ec);
}

void NetClient::SetConnect(NetSocket& rSocket)
{
	rSocket.async_connect(m_serverAddr, boost::bind(&NetClient::HandleConnect, this, boost::asio::placeholders::error, &rSocket));
}


void NetClient::HandleConnect(const boost::system::error_code& error, NetSocket* pSocket)
{
	if (error)
	{
		printf("[NOTE]:Connected Fail.................ok\n");
		SetConnect(*pSocket);
		printf("[NOTE]:SetConnect Again.................ok\n");
	}
	else
	{
		/* 设置连接成功 */ 
		m_connected = true;
		m_onconnected = false;
		//printf("[NOTE]:Connected Success.................ok\n");
		pSocket->Clear();
		pSocket->Run();/* 绑定该线程读头消息，这个操作必须是该线程 */ 
		//printf("[NOTE]:Socket io event start.................ok\n");
	}
}


void NetClient::SetHandler(PNetServerEnterHandler enter, PNetServerOnMsgHandler msg, PNetServerExistHandler exit)
{
	m_pOnMsgConnected = enter;
	m_pOnMsgRecevied = msg;
	m_pOnMsgDisconnect = exit;
}

void NetClient::Run()
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
			printf("[ERROR]:NetClient Error Msg:%s\n", e.what());
		}
#endif
	}
}

void NetClient::OnUpdate()
{
	OnUpdateConnected();
	OnUpdateRecived();
}

void NetClient::OnUpdateConnected()
{
	if (!m_onconnected && m_connected)
	{
		m_onconnected = true;
		(m_pOnMsgConnected)(*pSocket);
	}
}

void NetClient::OnUpdateRecived()
{

	/* Pre处理事件 */ 
	if (pSocket->HadEventClose())
	{
		(m_pOnMsgDisconnect)(*pSocket);
		pSocket->Disconnect();
		return;
	}

	static int32 nBodyLen = 0;
	static NetMsgSS* pMsg = NULL;
	int32 nMsgResult = pSocket->ReadMsg(&pMsg, nBodyLen);
	switch (nMsgResult)
	{
	case MSG_READ_INVALID:
	{
		pSocket->AddEventLocalClose();
	}
	break;
	case MSG_READ_OK:
	{
		
		(m_pOnMsgRecevied)(*pSocket, pMsg, nBodyLen);
		pSocket->RemoveMsg(PACKAGE_HEADER_SIZE + nBodyLen);
	}
	break;
	case MSG_READ_WAITTING:
	case MSG_READ_REVCING:
		break;
	}

	/* Afer检查定义事件 */ 
}

NetSocket* NetClient::GetSocket()
{ 
	return pSocket; 
}

void NetClient::Disconnect()
{
	pSocket->OnEventColse();
}

