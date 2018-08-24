
#include "NetClient.h"
#include "NetSocket.h"

/*-------------------------------------------------------------------
 * @Brief : Scoket客户端封装类
 *
 * @Author:hzd 2012/04/03
 *------------------------------------------------------------------*/
NetClient::NetClient()
	:m_connected(false)
	,m_onconnected(false)
{
	static int32_t g_s_nClientID = 0; m_ID = ++g_s_nClientID;
	m_pSocket = new NetSocket(*this);
}

NetClient::~NetClient(void)
{
	if (m_pSocket)
	{ 
		delete m_pSocket;
		m_pSocket = NULL;
	}
}


void NetClient::Start()
{
	boost::thread t(boost::bind(&NetClient::HandleStart, this));
	boost::this_thread::yield();
	t.swap(m_serviceThread);
}

void NetClient::HandleStart()
{
	// Use thread group can add code to connect more servers 
	// here can SetConnect more socket connect
	SetConnect();

	boost::thread_group tg;
	tg.create_thread(boost::bind(&NetClient::Run, this));
	boost::this_thread::yield();
	tg.join_all(); // Waitting threads to complete

}

void NetClient::SetAddress(const char* ip, uint16_t port)
{
	boost::system::error_code ec;
	m_serverAddr = tcp::endpoint(address::from_string(ip, ec), port);
	assert(!ec);
}

void NetClient::SetConnect()
{
	this->Clear();
	m_pSocket->async_connect(m_serverAddr, boost::bind(&NetClient::HandleConnect, this, boost::asio::placeholders::error, m_pSocket));
}


void NetClient::HandleConnect(const boost::system::error_code& error, NetSocket* _socket)
{
	if (error)
	{
		printf("[NOTE]:Connected Fail,SetConnect Again..................ok\n");
#ifdef WIN32
		Sleep(1000);
#else
		usleep(1000);
#endif
		SetConnect();
	}
	else
	{
		m_connected = true;
		m_onconnected = false;
		printf("[NOTE]:Connected Success.................ok\n");
		m_pSocket->Clear();
		m_pSocket->Run();
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
	if (m_onconnected && m_connected)
	{
		OnUpdateRecived();
	}
}

void NetClient::OnUpdateConnected()
{
	if (!m_onconnected && m_connected)
	{
		m_onconnected = true;
		(m_pOnMsgConnected)(*m_pSocket);
	}
}

void NetClient::OnUpdateRecived()
{
	/* 处理关闭事件 */
	if (m_pSocket->GetIsClose())
	{
		if (!m_pSocket->GetIsCloseBegin())
		{
			m_pSocket->SetIsCloseBeing(true);
			(m_pOnMsgDisconnect)(*m_pSocket);
			m_pSocket->Disconnect();
		}

		if (m_pSocket->GetIsCloseFinish())
		{
			m_pSocket->SetLocalClose(false);
#ifdef WIN32
			Sleep(10);
#else
			usleep(10);
#endif
			SetConnect();
		}
		return;
	}

	uint8_t* data = NULL;
	int32_t len = m_pSocket->ReadDataMsg(&data);
	if (len == -1)
	{
		m_pSocket->SetLocalClose(true);
		return;
	}
	
	if (len > 0)
	{
		(m_pOnMsgRecevied)(*m_pSocket, (NetMsgSS*)data, len);
		m_pSocket->RemoveQueueHeader();
		return;
	}
	
}

NetSocket* NetClient::GetSocket()
{ 
	return m_pSocket; 
}

void NetClient::Disconnect()
{
	m_pSocket->OnEventColse();
}

void NetClient::Clear()
{
	m_connected = m_onconnected = false;
}

