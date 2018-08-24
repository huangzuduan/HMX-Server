#include "NetSocket.h"
#include "NetServer.h"

/*-------------------------------------------------------------------
 * @Brief : Scoket数据处理类
 *
 * @Author:hzd 2012/04/03
 *------------------------------------------------------------------*/
NetSocket::NetSocket(io_service& rIo_service) :tcp::socket(rIo_service)
, m_cRecvHeadBuffer(buffer(&m_arrRecvBuffer[0], PACKAGE_HEADER_SIZE))
, m_cRecvBodyBuffer(buffer(&m_arrRecvBuffer[PACKAGE_HEADER_SIZE], PACKAGE_BODY_MAX_SIZE))
, m_cTimer(rIo_service)
, m_cCloseTimer(rIo_service)
, m_eRecvStage(REVC_FSRS_NULL)
, recvQueueHeader_(NULL)
, recvQueueLastest_(NULL)
, m_nTimeout(0)
, m_bBreakUpdateIo(false)
, m_bEnventClose(false)
, m_bEventCloseBegin(false)
, m_bEventCloseFinish(false)
{
	static uint64_t nIncreseLongID = 1LL;
	m_usSocketID = nIncreseLongID++;
}

NetSocket::~NetSocket()
{
	S_SAFE_DELETE(recvQueueHeader_);
	S_SAFE_DELETE(recvQueueLastest_);
}

void NetSocket::ReadMsg(mutable_buffers_1& _buffers,uint32_t dataLen)
{
	async_read(*this, _buffers, transfer_exactly(dataLen),
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
	SetIsCloseFinish(true);
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
	}
	catch (...)
	{

	}
}

int NetSocket::ReadDataMsg(uint8_t** data)
{
	if (m_bBreakUpdateIo)
	{
		return 0;
	}

	if (recvQueueHeader_ == NULL)
	{
		return 0;
	}

	int len = recvQueueHeader_->data_len - PACKAGE_HEADER_SIZE;
	*data = recvQueueHeader_->data_all + PACKAGE_HEADER_SIZE;
	return len;
}

void NetSocket::RemoveQueueHeader()
{
	boost::mutex::scoped_lock lock(m_writeBufferMutex);
	DataBuffer*	pBuff = recvQueueHeader_;
	if (recvQueueHeader_ == recvQueueLastest_)
	{
		recvQueueHeader_ = NULL;
		recvQueueLastest_ = NULL;
	}
	else
	{
		recvQueueHeader_ = recvQueueHeader_->next;
	}
	S_SAFE_DELETE(pBuff);
	lock.unlock();
}

void NetSocket::RecvMsg(const boost::system::error_code& ec, size_t bytes_transferred)
{
	TimeoutCancel();
	if (ec)
	{
		printf("[ERROR]:Recv error msg,%s\n", ec.message().c_str());
		assert(0);
		SetLocalClose(true);
		return;
	}

	if (m_eRecvStage == REVC_FSRS_HEAD)
	{
		m_eRecvStage = REVC_FSRS_BODY;
		uint32_t nextSizeLen = 0;
		memcpy(&nextSizeLen, m_arrRecvBuffer, bytes_transferred);
		ReadMsg(m_cRecvBodyBuffer, nextSizeLen);
	}
	else
	{
		
		uint32_t nextSizeLen = 0;
		memcpy(&nextSizeLen, m_arrRecvBuffer, PACKAGE_HEADER_SIZE);
		assert(nextSizeLen == bytes_transferred);

		boost::mutex::scoped_lock lock(m_writeBufferMutex);
		DataBuffer* dataBuff = new DataBuffer((uint8_t*)(m_arrRecvBuffer + PACKAGE_HEADER_SIZE), bytes_transferred);
		if (recvQueueHeader_ == NULL && recvQueueLastest_ == NULL)
		{
			recvQueueHeader_ = dataBuff;
			recvQueueLastest_ = dataBuff;
		}
		else
		{
			recvQueueLastest_->next = dataBuff;
			recvQueueLastest_ = recvQueueLastest_->next;
		}
		lock.unlock();
		m_eRecvStage = REVC_FSRS_HEAD;
		ReadMsg(m_cRecvHeadBuffer, PACKAGE_HEADER_SIZE);
	}
}

void NetSocket::Clear()
{
	m_eRecvStage = REVC_FSRS_NULL;
	m_bBreakUpdateIo = false;
	m_bEnventClose = false;
	m_bEventCloseBegin = false;
	m_bEventCloseFinish = false;
}

void NetSocket::ParkMsg(const uint8_t* data, int32_t leng)
{
	DataBuffer* sendData = new DataBuffer(data, leng);
	async_write(*this, boost::asio::buffer(sendData->data_all, sendData->data_len), 
		transfer_exactly(sendData->data_len),
		boost::bind(&NetSocket::SendMsg,this,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	delete sendData;
}

void NetSocket::SendMsg(const boost::system::error_code& ec, size_t bytes_transferred)
{
	if (ec)
	{
		printf("[ERROR]:Send msg data error\n");
		assert(0);
		SetLocalClose(true);
		return;
	}
}

void NetSocket::HandleWait(const boost::system::error_code& error)
{
	if (error)
	{
		return;
	}
	printf("[INFO]:That is timeout!\n");
	SetLocalClose(true);
}

void NetSocket::Run()
{
	m_eRecvStage = REVC_FSRS_HEAD;
	ReadMsg(m_cRecvHeadBuffer, PACKAGE_HEADER_SIZE);
}

const string NetSocket::GetIp() const
{
	return remote_endpoint().address().to_string();
}

uint16_t NetSocket::GetPort() const
{
	return remote_endpoint().port();
}

void NetSocket::OnEventColse()
{
	printf("[WARRING]:OnEventColse\n");
	SetLocalClose(true);
}

void NetSocket::SetTimeout(int32_t nTimeout)
{
	assert(nTimeout > -1);
	m_nTimeout = nTimeout;
}

void NetSocket::TimeoutStart()
{
	if (m_nTimeout)
	{
		m_cTimer.cancel();
		m_cTimer.expires_from_now(boost::posix_time::seconds(m_nTimeout));
		m_cTimer.async_wait(boost::bind(&NetSocket::HandleWait, this, boost::asio::placeholders::error));
	}
}

void NetSocket::TimeoutCancel()
{
	if (m_nTimeout)
	{
		m_cTimer.cancel();
	}
}




