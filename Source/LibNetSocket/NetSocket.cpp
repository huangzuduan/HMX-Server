#include "NetSocket.h"
#include "NetServer.h"

/*-------------------------------------------------------------------
 * @Brief : Scoket数据处理类
 * 
 * @Author:hzd 2012/04/03
 *------------------------------------------------------------------*/
NetSocket::NetSocket(io_service& rIo_service,int32 nMaxRecivedSize,int32 nMaxSendoutSize,int32 nMaxRecivedCacheSize,int32 nMaxSendoutCacheSize):tcp::socket(rIo_service)
	, m_cHeadBuffer(buffer(m_arrRecvBuffer, PACKAGE_HEADER_SIZE))
	, m_cBodyBuffer(buffer(m_arrRecvBuffer + PACKAGE_HEADER_SIZE, nMaxRecivedSize - PACKAGE_HEADER_SIZE))
	, m_cSendBuffer(buffer(m_arrSendBuffer, nMaxSendoutSize))
	, m_cTimer(rIo_service)
	, m_cCloseTimer(rIo_service)
	, m_eRecvStage(REVC_FSRS_NULL)
	, m_nBodyLen(0)
	, m_bSending(false)
	, m_nMaxRecivedSize(nMaxRecivedSize)
	, m_nMaxSendoutSize(nMaxSendoutSize)
	, m_nTimeout(0)
	, m_errorCode(-1)
	, m_bBreakUpdateIo(false)
	, m_bEnventClose(false)
{
	static int32 nSocketIncreseID = 1;
	static uint64 nSocketIncreseLongID = 1;
	m_nID = nSocketIncreseID++;
	m_nLongID = nSocketIncreseLongID++;
	m_cIBuffer.InitBuffer(nMaxRecivedCacheSize);
	m_cOBuffer.InitBuffer(nMaxSendoutCacheSize);
}

NetSocket::~NetSocket()
{

}

void NetSocket::ReadHead()
{
	async_read(*this, m_cHeadBuffer,
		transfer_exactly(PACKAGE_HEADER_SIZE), 
		boost::bind(&NetSocket::RecvMsg, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	TimeoutStart();
}


void NetSocket::ReadBody()
{
	async_read(*this, m_cBodyBuffer,
		transfer_exactly(m_nBodyLen),
		boost::bind(&NetSocket::RecvMsg, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	TimeoutStart();
}

void NetSocket::Disconnect()
{
	m_cCloseTimer.cancel();
	m_cCloseTimer.expires_from_now(boost::posix_time::seconds(0));
	m_cCloseTimer.async_wait(boost::bind(&NetSocket::HandleClose, this, boost::asio::placeholders::error));
}

void NetSocket::HandleClose(const boost::system::error_code& error)
{

#ifdef WIN32

#else
	try
	{
		boost::system::error_code ec;
		shutdown(socket_base::shutdown_both, ec);
	}
	catch (...)
	{
	}
#endif // WIN32


	try
	{
		boost::asio::socket_base::linger option(true, 0);
		boost::system::error_code ec1;
		set_option(option, ec1);
		boost::system::error_code ec2;
		tcp::socket::close(ec2); /* 这个不会再收到消息回调 end */ 
	} catch(...)
	{

	}

}

EMsgRead NetSocket::ReadMsg(NetMsgSS** pMsg,int32& nSize)
{
	if (m_bBreakUpdateIo)
	{
		printf("[WARRING]:m_bBreakUpdateIo==========true\n");
		return MSG_READ_WAITTING;
	}
	if (m_cIBuffer.GetLen() < PACKAGE_HEADER_SIZE)
	{
		return MSG_READ_WAITTING;
	}
	void* buf = m_cIBuffer.GetStart();
	memcpy(&nSize,buf,PACKAGE_HEADER_SIZE);
	if (m_cIBuffer.GetLen() < nSize + PACKAGE_HEADER_SIZE)
	{
		return MSG_READ_REVCING;
	}
	*pMsg = (NetMsgSS*)((char*)buf + PACKAGE_HEADER_SIZE);
	return MSG_READ_OK;
}

void NetSocket::RemoveMsg(uint32 nLen)
{
	m_cIBuffer.RemoveBuffer(nLen);
}

void NetSocket::RecvMsg(const boost::system::error_code& ec, size_t bytes_transferred)
{
	TimeoutCancel();
	if(ec)
	{
		printf("[ERROR]:Recv error msg,%s\n",ec.message().c_str());
		AddEventLocalClose();
		m_errorCode = ESOCKET_EXIST_REMOTE;
		return;
	}

	switch(m_eRecvStage)
	{
		case REVC_FSRS_HEAD:
		{
			ASSERT(bytes_transferred == PACKAGE_HEADER_SIZE);
			memcpy(&m_nBodyLen,m_arrRecvBuffer,PACKAGE_HEADER_SIZE);
			if((uint32) m_nBodyLen < sizeof(NetMsgC) || m_nBodyLen > m_nMaxRecivedSize)
			{
			   printf("[ERROR]:Recv data length,bodylen:%d, maxLimitLength:%d\n",m_nBodyLen,m_nMaxRecivedSize);
			   AddEventLocalClose();
			   m_errorCode = ESOCKET_EXIST_PACK_LENGTH_ERROR;
			   m_nBodyLen = 0;
			   return;
			}
			bool bResult = m_cIBuffer.Write(m_arrRecvBuffer, PACKAGE_HEADER_SIZE);
			if(!bResult)
			{
				printf("[ERROR]:Write too much data to buffer\n");
				AddEventLocalClose();
				m_errorCode = ESOCKET_EXIST_WRITE_TOO_DATA;
				return;
			}
			m_eRecvStage = REVC_FSRS_BODY;
			ReadBody();
		}
			break;
		case REVC_FSRS_BODY:
		{
			bool bResult = m_cIBuffer.Write(m_arrRecvBuffer + PACKAGE_HEADER_SIZE, m_nBodyLen);
			if(!bResult)
			{
				printf("[ERROR]:Write too much data to buffer\n");
				AddEventLocalClose();
				m_errorCode = ESOCKET_EXIST_WRITE_TOO_DATA;
				return;
			}
			m_eRecvStage = REVC_FSRS_HEAD;
			ReadHead();
		}
			break;
		default:
		{
			ASSERT(0);
		}
			break;
	}
}

void NetSocket::Clear()
{
	m_bSending = false;
	m_nBodyLen = 0;
	m_eRecvStage = REVC_FSRS_NULL;
	m_cIBuffer.ClearBuffer();
	m_cOBuffer.ClearBuffer();
	m_bBreakUpdateIo = false;
	m_bEnventClose = false;
}

void NetSocket::ParkMsg(const NetMsgSS* pMsg,int32 nLength)
{
	ASSERT(nLength < 65336);
	{
		char arrLen[PACKAGE_HEADER_SIZE];
		memcpy(arrLen, &nLength, PACKAGE_HEADER_SIZE);
		m_cOBuffer.Write(arrLen, PACKAGE_HEADER_SIZE);
		m_cOBuffer.Write((char*)pMsg, nLength);
	}
}

void NetSocket::ParkMsg(const NetMsgC* pMsg, int32 nLength)
{
	char arrLen[PACKAGE_HEADER_SIZE];
	memcpy(arrLen, &nLength, PACKAGE_HEADER_SIZE);
	m_cOBuffer.Write(arrLen, PACKAGE_HEADER_SIZE);
	m_cOBuffer.Write((char*)pMsg, nLength);
}

void NetSocket::SendMsg()
{
	if(m_bSending)
		return;

	if(int nLen = m_cOBuffer.ReadRemove(&m_arrSendBuffer,m_nMaxSendoutSize))
	{
		m_bSending = true;
		async_write(*this, m_cSendBuffer, transfer_exactly(nLen), boost::bind(&NetSocket::SendMsg, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
}

void NetSocket::SendMsg(const boost::system::error_code& ec, size_t bytes_transferred)
{
	if(ec)
	{
		printf("[ERROR]:Send msg data error\n");
		AddEventLocalClose();
		m_errorCode = ESCOKET_EXIST_SEND_CONNECT_INVAILD;
		return;
	}

	if(int nLen = m_cOBuffer.ReadRemove(&m_arrSendBuffer,m_nMaxSendoutSize))
	{
		async_write(*this, m_cSendBuffer, transfer_exactly(nLen), boost::bind(&NetSocket::SendMsg, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	} else
	{
		m_bSending = false;
	}
}

void NetSocket::HandleWait(const boost::system::error_code& error)
{
	if(error)
	{
		return;
	}
	printf("[INFO]:That is timeout!\n");
	AddEventLocalClose();
	m_errorCode = ESOCKET_EXIST_TIMEOUT;
}

void NetSocket::Run()
{
	m_eRecvStage = REVC_FSRS_HEAD;
	ReadHead();
}

const string NetSocket::GetIp()
{
	return remote_endpoint().address().to_string();
}

uint16 NetSocket::GetPort()
{
	return remote_endpoint().port();
}

void NetSocket::OnEventColse()
{
	printf("[WARRING]:OnEventColse\n");
	AddEventLocalClose();
	m_errorCode = ESOCKET_EXIST_LOCAL;
}

void NetSocket::SetTimeout(int32 nTimeout)
{
	ASSERT(nTimeout > -1);
	m_nTimeout = nTimeout;
}

void NetSocket::TimeoutStart()
{
	if(m_nTimeout)
	{
		m_cTimer.cancel();
		m_cTimer.expires_from_now(boost::posix_time::seconds(m_nTimeout));
		m_cTimer.async_wait(boost::bind(&NetSocket::HandleWait, this, boost::asio::placeholders::error));
	}
}

void NetSocket::TimeoutCancel()
{
	if(m_nTimeout)
	{
		m_cTimer.cancel();
	}
}

int32 NetSocket::ErrorCode(std::string& error)
{
	switch (m_errorCode)
	{
	case ESOCKET_EXIST_NULL:
		error = "未知";
		break;
	case ESOCKET_EXIST_LOCAL:
		error = "本地主动断开";
		break;
	case ESOCKET_EXIST_REMOTE:
		error = "远程主动断开";
		break;
	case ESOCKET_EXIST_TIMEOUT:
		error = "超时";
		break;
	case ESOCKET_EXIST_PACK_LENGTH_ERROR:
		error = "数据长度错误";
		break;
	case ESOCKET_EXIST_WRITE_TOO_DATA:
		error = "写入数据过多";
		break;
	case ESCOKET_EXIST_SEND_CONNECT_INVAILD:
		error = "发时连接无效";
		break;
	default:
		error = "未知";
		break;
	}
	return m_errorCode;
}

void NetSocket::BreakUpdateIO()
{
	m_bBreakUpdateIo = true;
}

void NetSocket::UnBreakUpdateIO()
{
	m_bBreakUpdateIo = false;
}

void NetSocket::AddEventLocalClose()
{
	m_bEnventClose = true;
}

bool NetSocket::HadEventClose()
{
	bool ret = m_bEnventClose;
	m_bEnventClose = false;
	return ret;

}


