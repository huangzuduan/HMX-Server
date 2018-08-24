#include <vector>
#include "FogsTcpConnection.hpp"
#include <assert.h>
//#include "dumpHex.h"
#include <memory.h>
//#include <arpa/inet.h>
#include <algorithm>

namespace fogs
{
namespace net
{

using namespace std;

void dumpData(uint8_t* data, uint32_t len)
{
	for(int i =0; i<len; i++)
	{
		////////LOG(INFO) <<(int)*(data+i)<< " ";
	}
	////////LOG(INFO) << std::endl;
}

FogsTcpConnection::FogsTcpConnection(boost::asio::io_service& io_service,
		bool autoStartRecv,
		const char * name)
	: name(name),
	  sendQueueHeader_(NULL),
	  sendQueueTail_(NULL),
	  sendQueueCursor_(NULL),
	  socket_(io_service),
	  autoStartRecv_(autoStartRecv),
	  msgBuffer_(MAX_RCV_LEN),
	  sendBuffLen_(0),
	  sendDataCache_(new uint8_t[MAX_SEND_SIZE]),
	  deflateCache_(new uint8_t[MAX_SEND_SIZE]),
	  inflateCache_(new uint8_t[MAX_SEND_SIZE]),
	  useZlib_(false),
	  encryptType_(NOT_ENCRYPT),
	  maxEncryptLen_(0),
	  secretKey_(0xBCAF5432)
{
	//LOG4CXX_INFO(gNetLogger, "FogsTcpConnection  0x" << std::hex << (long)this);
	//////////LOG(INFO) << "FogsTcpConnection  0x" << std::hex << (long)this << std::endl;
}


FogsTcpConnection::~FogsTcpConnection()
{
	//LOG4CXX_INFO(gNetLogger, "~FogsTcpConnection  0x" << std::hex << (long)this);
	//////////LOG(INFO) << "~FogsTcpConnection  0x" << std::hex << (long)this << std::endl;
	boost::system::error_code ec;
	socket_.close(ec);
	if (ec)
	{
		//LOG4CXX_INFO(gNetLogger, "Close socket failed, peer " <<
				//peer_.address().to_string().c_str() << ":" << peer_.port() <<
				//", message :" << ec.message().c_str());
			//LOG(INFO) << "Close socket failed, peer " <<
			//peer_.address().to_string().c_str() << ":" << peer_.port() <<
			//", message :" << ec.message().c_str() << std::endl;
	}

	delete []inflateCache_;
	delete []deflateCache_;
	delete []sendDataCache_;

	packetHandler_ = NULL;
	errorHandler_ = NULL;
	bufVec_.clear();
}



bool FogsTcpConnection::enDecrypt(uint8_t* data, uint32_t len)
{
//	if(encryptType_ == NOT_ENCRYPT) //表示不加密
//	{
//		return false;
//	}
//
////	std::cout <<" encrypt data, type: "<< encryptType_ << ", maxLen "
////				<< maxEncryptLen_ << ", " << secretKey_ <<std::endl;
////
////	dumpData(data, len);
//
//	// encryptType == 1表示全部加密
//	uint8_t* encryptedData = data;
//	if(encryptType_ == HEAD_ENCRYPT) //从开始端加密固定encryptLen长度
//	{
//		len = std::min(maxEncryptLen_, len);
//	}
//	else if (encryptType_ == TAIL_ENCRYPT) //从末尾端加密固定encryptLen长度
//	{
//		if(len > maxEncryptLen_)
//		{
//			encryptedData = data + (len - maxEncryptLen_);
//		}
//		len = std::min(maxEncryptLen_, len);
//	}
//
//	int intLen = len/4;
//	uint32_t* uintPtr = (uint32_t*) encryptedData;
//	uint32_t* destPtr = uintPtr + intLen;
//	while(uintPtr < destPtr)
//	{
//		uint32_t value = (*uintPtr);
//		*uintPtr =  value ^ secretKey_;
//		 uintPtr++;
//	}
//
//	for(int i = intLen*sizeof(uint32_t); i < len; i++)
//	{
//		encryptedData[i] = (uint8_t)(encryptedData[i] ^ secretKey_);
//	}

//	std::cout << "--------------------------------" << std::endl;
//	dumpData(data, len);
	return true;
}


void FogsTcpConnection::connErrorHandler(const boost::system::error_code& error)
{
    //LOG4CXX_INFO(gNetLogger, "Fogs tcp connection failed, peer " <<
    		//peer_.address().to_string().c_str() << ":" << peer_.port() <<
			//", error code: " << error.value() <<
			//", category : " << error.category().name() <<
			//", message :" << error.message().c_str());
	////////LOG(INFO) << "Fogs tcp connection failed, peer " <<
		//peer_.address().to_string().c_str() << ":" << peer_.port() <<
		//", error code: " << error.value() <<
		//", category : " << error.category().name() <<
		//", message :" << error.message().c_str() << std::endl << "\n";

	if (errorHandler_)
	{
		errorHandler_(error);
	}

	close();
}



void FogsTcpConnection::asyncRead(const boost::system::error_code& error,
		std::size_t readLen)
{
#define ERROR_PROCESS(error)  \
	if (error.value() != 0){			\
		connErrorHandler(error);\
		return;  }\

	ERROR_PROCESS(error);

	boost::system::error_code buffer_error;
	msgBuffer_.setBytesReceived(readLen, buffer_error);
	ERROR_PROCESS(buffer_error);
	
	FogsHeader * header;
	while ((header =  msgBuffer_.nextMessage(buffer_error)) != NULL)
	{
		decrypt(header);
		header = unCompress(header);
		if (packetHandler_)
		{
			packetHandler_(error, header);
		}
	}

	ERROR_PROCESS(buffer_error);
	doRecv();

#undef ERROR_PROCESS
	return;
}


int FogsTcpConnection::writePacket(uint32_t type, uint32_t msg_id, uint32_t session_id, uint8_t * msg, int msgLen)
{
	int ret = 0;
	std::vector<boost::asio::const_buffer> bufVec;

	FogsHeader header;
	header.fp_type = type;
	header.fp_msg_id = msg_id;
	header.fp_session_id = session_id;
	header.fp_length = msgLen;

	bufVec.push_back(boost::asio::buffer(&header, sizeof(header)));
	bufVec.push_back(boost::asio::buffer(msg, msgLen));

	try{
		boost::asio::write(socket_, bufVec);
		// TODO: release client connection!!
	}
	catch(std::exception& ex)
	{
	    //LOG4CXX_ERROR(gErrorLogger, "ASIO write message error, " << ex.what());
		//LOG(ERROR) << "ASIO write message error, " << ex.what() << std::endl;
		ret = 1;
	}

	return ret;
}

void FogsTcpConnection::syncWriteMessage(uint32_t type, uint32_t msg_id, uint32_t session_id,
        const google::protobuf::Message& msg)
{
	int len = msg.ByteSize();
	if(len + sizeof(FogsHeader) > MAX_SEND_SIZE)
	{
		//LOG4CXX_ERROR(gErrorLogger,
				//"FogsTcpConnection send data size >= MAX_SEND_SIZE "
				//<< len + sizeof(FogsHeader) << ", msg_id: " << msg_id);
		//LOG(ERROR) << "FogsTcpConnection send data size >= MAX_SEND_SIZE "
		//	<< len + sizeof(FogsHeader) << ", msg_id: " << msg_id << std::endl;
		return;
	}
	//uint8_t buf[len];
	uint8_t buf[10000];
	memset(buf, 0, len);

	msg.SerializeToArray(buf, sizeof(buf));

	writePacket(type, msg_id, session_id, buf, len);
}

void FogsTcpConnection::syncWriteMessage(FogsHeader* header)
{
	int data_len = header->fp_length + sizeof(FogsHeader);

	std::vector<boost::asio::const_buffer> bufVec;
	bufVec.push_back(boost::asio::buffer(header, data_len));

	try{
		boost::asio::write(socket_, bufVec);
	}
	catch(std::exception& ex)
	{
		//LOG4CXX_ERROR(gErrorLogger, "ASIO write message error, " << ex.what());
		//LOG(ERROR) << "ASIO write message error, " << ex.what() << std::endl;
	}

	return ;
}

void FogsTcpConnection::asyncWriteMessage(FogsHeader* header)
{
	int data_len = header->fp_length + sizeof(FogsHeader);
	if(data_len >= MAX_SEND_SIZE)
	{
		//LOG4CXX_ERROR(gErrorLogger, "FogsTcpConnection send data size >= MAX_SEND_SIZE " << data_len << ", msg_id: " << header->fp_msg_id);
		//LOG(ERROR) << "FogsTcpConnection send data size >= MAX_SEND_SIZE " << data_len << ", msg_id: " << header->fp_msg_id << std::endl;
		return;
	}
	SendDataBuffer* data = new SendDataBuffer(header, sendDataCache_);
	compress(data);
	encrypt(data);
	doAsyncWriteMessage(data);
	//send queue empty before insert
}
void FogsTcpConnection::doAsyncWriteMessage(SendDataBuffer* data)
{
	sendBuffLen_ += data->data_len;
	//std::cout<<"recv data "<< data->data_len<<" sendBuffLen "<<sendBuffLen_<<std::endl;
	if(sendQueueTail_)
	{
		sendQueueTail_->next = data;
		sendQueueTail_ = sendQueueTail_->next;
		if(sendQueueCursor_ == NULL)
		{
			sendQueueCursor_ = sendQueueTail_;
		}
	}
	else
	{
		sendQueueHeader_ = data;
		sendQueueTail_ = sendQueueHeader_ ;
		asyncSendPrependLen();
	}
	return;

}
void FogsTcpConnection::asyncWriteMessage(uint32_t type, uint32_t msg_id, uint32_t session_id,
		const google::protobuf::Message &msg)
{
	int data_len = msg.ByteSize() + sizeof(FogsHeader);
	if(data_len >= MAX_SEND_SIZE)
	{
		//LOG4CXX_ERROR(gErrorLogger, "FogsTcpConnection send data size >= MAX_SEND_SIZE " << data_len << data_len << ", msg_id: " << msg_id);
		//LOG(ERROR) << "FogsTcpConnection send data size >= MAX_SEND_SIZE " << data_len << data_len << ", msg_id: " << msg_id << std::endl;
		return;
	}
	SendDataBuffer* data = new SendDataBuffer(type, msg_id, session_id, msg, sendDataCache_);
	compress(data);
	encrypt(data);
	doAsyncWriteMessage(data);
}

void FogsTcpConnection::asyncWriteMessage(uint32_t type,
		uint32_t msg_id, uint32_t session_id, uint32_t msg_len, uint8_t* payload)
{
	int data_len = msg_len + sizeof(FogsHeader);
	if(data_len >= MAX_SEND_SIZE)
	{
		//LOG4CXX_ERROR(gErrorLogger, "FogsTcpConnection send data size >= MAX_SEND_SIZE " << data_len << ", msg_id: " << msg_id);
		//LOG(ERROR) << "FogsTcpConnection send data size >= MAX_SEND_SIZE " << data_len << ", msg_id: " << msg_id << std::endl;
		return;
	}
	SendDataBuffer* data = new SendDataBuffer(type, msg_id, session_id, msg_len, payload, sendDataCache_);
	compress(data);
	encrypt(data);
	doAsyncWriteMessage(data);
}

void FogsTcpConnection::sendBroadcastMessage(uint32_t msg_id, const std::vector<uint32_t>& sessions,
		const google::protobuf::Message& msg)
{
	int data_len = msg.ByteSize()+ sessions.size()*sizeof(uint32_t) + 4*sizeof(uint32_t);
	if(data_len >= MAX_SEND_SIZE)
	{
		//LOG4CXX_ERROR(gErrorLogger, "sendBroadCastMessage send data size >= MAX_SEND_SIZE " << data_len << ", msg_id: " << msg_id);
		//LOG(ERROR) << "sendBroadCastMessage send data size >= MAX_SEND_SIZE " << data_len << ", msg_id: " << msg_id << std::endl;
		return;
	}
	SendDataBuffer* data = new SendDataBuffer(msg_id, sessions, msg, sendDataCache_);
	compress(data);
	encrypt(data);
	doAsyncWriteMessage(data);
}

void FogsTcpConnection::sendBroadcastMessage(uint32_t msg_id, const google::protobuf::Message& msg)
{
	int data_len = msg.ByteSize() + 4 * sizeof(uint32_t);
	if(data_len >= MAX_SEND_SIZE)
	{
		//LOG4CXX_ERROR(gErrorLogger, "FogsTcpConnection send data size >= MAX_SEND_SIZE, size " << data_len << ", msg_id: " << msg_id);
		//LOG(ERROR) << "FogsTcpConnection send data size >= MAX_SEND_SIZE, size " << data_len << ", msg_id: " << msg_id << std::endl;
		return;
	}
	SendDataBuffer* data = new SendDataBuffer(msg_id, msg, sendDataCache_);
	compress(data);
	encrypt(data);
	doAsyncWriteMessage(data);

}


void FogsTcpConnection::asyncSendPrependLen()
{
	//only one data to send
	sendQueueCursor_ = sendQueueHeader_;
	if(sendQueueHeader_ == sendQueueTail_)
	{   // TODO: is possible that sendQueueHeader_ == NULL -- hlei
		boost::asio::async_write(socket_, boost::asio::buffer(sendQueueCursor_->data, sendQueueCursor_->data_len),
				boost::bind(&FogsTcpConnection::handleAsyncWrite, shared_from_this(),
				boost::asio::placeholders::error));
		sendQueueCursor_ = NULL;
		return;
	}

	bufVec_.clear();
	int sndLen = 0;	
	while(sendQueueCursor_ != NULL && sndLen < MAX_SEND_SIZE )
	{
		if(sndLen + sendQueueCursor_->data_len > MAX_SEND_SIZE)
		{
			break;
		}
		bufVec_.push_back(boost::asio::buffer(sendQueueCursor_->data, sendQueueCursor_->data_len));
		sndLen += sendQueueCursor_->data_len;
		sendQueueCursor_ = sendQueueCursor_->next;
	}

	assert(sndLen != 0);
	boost::asio::async_write(socket_, bufVec_,
		boost::bind(&FogsTcpConnection::handleAsyncWrite, shared_from_this(),
		boost::asio::placeholders::error));
}

void FogsTcpConnection::handleAsyncWrite(const boost::system::error_code& error)
{
	SendDataBuffer* p = sendQueueHeader_;
	while(p != sendQueueCursor_)
	{
		sendBuffLen_ -= p->data_len;
		//std::cout<<"...... send data "<< p->data_len<<" sendBuffLen "<<sendBuffLen_<<std::endl;
		sendQueueHeader_ = p->next;
		delete []p->data;
		delete p;
		p = sendQueueHeader_;
	}

	if(sendQueueCursor_ == NULL)
	{
		sendQueueTail_ = NULL;
	}
	else
	{
		asyncSendPrependLen();
	}

	if(error){
		connErrorHandler(error);
		return;
	}
	return;
}


void FogsTcpConnection::clearSendQueue()
{
	SendDataBuffer* p = sendQueueHeader_;
	while(p && p->next != sendQueueCursor_)
	{
		p = p->next;
	}
	sendQueueTail_ = p;

	p = sendQueueCursor_;
	while(p != NULL)
	{
		SendDataBuffer* np = p->next;
		sendBuffLen_ -= p->data_len;
		delete []p->data;
		delete p;
		p = np;
	}
	sendQueueCursor_ = NULL;
}

void FogsTcpConnection::compress(SendDataBuffer* sendData)
{
	/*if(needCompress(sendData))
	{
		FogsHeader *header = reinterpret_cast<FogsHeader *>(sendData->data);
		uint64_t deflateLen = MAX_SEND_SIZE;
		int err = compress2((Bytef *)deflateCache_, &deflateLen,
				reinterpret_cast<const Bytef *>(header->fp_payload),
				header->fp_length, zlibLevel_);

		if(err == Z_OK)
		{
			header->fp_length = deflateLen;
			header->setDeflate();
			sendData->data_len = header->fp_length + sizeof(FogsHeader);

			uint8_t* data = new uint8_t[sendData->data_len];
			memcpy(data, sendData->data, sizeof(FogsHeader));
			memcpy(data+sizeof(FogsHeader), deflateCache_, deflateLen);
			sendData->data = data;
			return;
		}

		LOG4CXX_ERROR(gErrorLogger, "compress error "<< err);
	}*/

	uint8_t* data = new uint8_t[sendData->data_len];
	memcpy(data, sendData->data, sendData->data_len);
	sendData->data = data;
}

FogsHeader* FogsTcpConnection::unCompress(FogsHeader* header)
{
	/*if(header->isDeflate())
	{
		uLong inflateLen = MAX_SEND_SIZE;

		int err = uncompress( (Bytef *)inflateCache_ + sizeof(FogsHeader),
				&inflateLen,
				(const Bytef *)header->fp_payload,
				(uLong)header->fp_length);

		if (err != Z_OK)
		{
			LOG4CXX_ERROR(gErrorLogger, "decompress error "<< err);
			return header;
		}

		header->fp_length = inflateLen;
		header->setInflate();
		memcpy(inflateCache_, (void*)header, sizeof(FogsHeader));
		return reinterpret_cast<FogsHeader *>(inflateCache_);
	}*/

	return header;
}

void FogsTcpConnection::encrypt(SendDataBuffer* sendData)
{
	FogsHeader *header = reinterpret_cast<FogsHeader *>(sendData->data);
	//std::cout<<"... ...encrypt, "<< header->fp_msg_id << std::endl;

	if(enDecrypt(sendData->data+sizeof(FogsHeader), header->fp_length))
	{
		header->setEncrypted();
	}
}

void FogsTcpConnection::decrypt(FogsHeader* header)
{
   if(header->isEncrypted())
   {
	  // std::cout<<">>>>>>>decrypt "<<header->fp_msg_id << std::endl;
	   if(enDecrypt(header->fp_payload, header->fp_length))
	   {
		   header->setdecrypted();
	   }
   }
}


}
}