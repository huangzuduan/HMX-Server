#ifndef FOGSCONNECTION_HPP_
#define FOGSCONNECTION_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
//#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <google/protobuf/message.h>
#include "FogsProtocol.hpp"
#include "FogsMessageBuffer.hpp"
//#include <zlib.h>

namespace fogs
{
namespace net
{

using namespace boost::asio;


class FogsTcpConnection
	: public boost::enable_shared_from_this<FogsTcpConnection>,
		private boost::noncopyable
{

public:
	enum
	{
		BUFFER_NOT_SENT = 0,
		BUFFER_SENT = 1
	};

	enum EncryptType
	{
		NOT_ENCRYPT = 0,
		WHOLE_ENCRYPT,
		HEAD_ENCRYPT,
		TAIL_ENCRYPT
	};

	struct SendDataBuffer
	{
		uint8_t* data;
		uint32_t data_len;
		SendDataBuffer* next;

		SendDataBuffer(FogsHeader *header, uint8_t* dataCache):next(NULL)
		{
			data_len = header->fp_length + sizeof(FogsHeader);

			assert(data_len < MAX_SEND_SIZE);
			//data = new uint8_t[data_len];
			data = dataCache;
			memcpy(data, (char*)header, data_len);
		}

		SendDataBuffer(uint32_t type, uint32_t msg_id, uint32_t session_id,
				const google::protobuf::Message &msg, uint8_t* dataCache )
			:next(NULL)
		{
			int msgLen = msg.ByteSize();
			data_len = msgLen + sizeof(FogsHeader) ;
			assert(data_len < MAX_SEND_SIZE);
			//data = new uint8_t[data_len];

			data = dataCache;

			memset(data, 0, data_len);
			FogsHeader *header = reinterpret_cast<FogsHeader *>(data);

			header->fp_type = type;
			header->fp_msg_id = msg_id;
			header->fp_session_id = session_id;
			header->fp_length = msgLen;

			msg.SerializeToArray(data + sizeof(FogsHeader), msgLen);
		}

		SendDataBuffer(uint32_t type, uint32_t msg_id, uint32_t session_id,
				uint32_t msg_len, uint8_t* payLoad, uint8_t* dataCache)
			:next(NULL)
		{
			data_len = sizeof(FogsHeader) + msg_len;
			//data = new uint8_t[data_len];
			data = dataCache;

			FogsHeader *header = reinterpret_cast<FogsHeader *>(data);
			header->fp_type = type;
			header->fp_msg_id = msg_id;
			header->fp_session_id = session_id;
			header->fp_length = msg_len;

			memcpy(data + sizeof(FogsHeader), payLoad, msg_len);
		}

		SendDataBuffer(uint32_t msg_id, const std::vector<uint32_t>& sessions,
				const google::protobuf::Message& msg, uint8_t* dataCache)
			:next(NULL)
		{
			int session_num = sessions.size();
			int msgLen = msg.ByteSize();
			int sessionsLen =  session_num * sizeof(uint32_t);
			int headerLen = 4 *sizeof(uint32_t);

			data_len = msgLen + sessionsLen + headerLen;
			//data = new uint8_t[data_len];
			data = dataCache;

			FogsHeader *header = reinterpret_cast<FogsHeader *>(data);
			header->fp_type = FOGS_MSG_TYPE_BROADCAST;
			header->fp_msg_id = msg_id;
			header->fp_length = msgLen + sessionsLen;
			header->fp_session_num = session_num;

			int id = 0;
			for(std::vector<uint32_t>::const_iterator iter = sessions.begin();
					iter != sessions.end(); ++iter)
			{
				header->fp_sessions[id] = (*iter);
				id++;
			}

			msg.SerializeToArray(data + headerLen + sessionsLen, msgLen);
		}

		SendDataBuffer(uint32_t msg_id, const google::protobuf::Message& msg, uint8_t* dataCache)
			:next(NULL)
		{
			int msgLen = msg.ByteSize();
			int headerLen = 4 *sizeof(uint32_t);

			data_len = msgLen + headerLen;
			//data = new uint8_t[data_len];
			data = dataCache;

			FogsHeader *header = reinterpret_cast<FogsHeader *>(data);
			header->fp_type = FOGS_MSG_TYPE_BROADCAST;
			header->fp_msg_id = msg_id;
			header->fp_length = msgLen;
			header->fp_session_num = 0;

			msg.SerializeToArray(data + headerLen, msgLen);
		}

		~SendDataBuffer()
		{
			next = reinterpret_cast<SendDataBuffer*>(0xdeaddeef);
		}

	private:
		SendDataBuffer():data(NULL),data_len(0), next(NULL){};

	};



	const char * name;

	typedef boost::int32_t desc_t;
	typedef boost::shared_ptr<FogsTcpConnection> pointer;


	typedef boost::function2<void,
			const boost::system::error_code&,
			FogsHeader *> PacketHandler;

	typedef boost::function1<void,
			const boost::system::error_code&> ErrorHandler;


	static pointer create(boost::asio::io_service& io_service,
			bool autoStartRecv = true,
			const char * name = "conn")
	{
		return pointer(new FogsTcpConnection(io_service,
										autoStartRecv, name));
	}

	static pointer connect(boost::asio::io_service& io_service,
			const std::string &ip, uint16_t port,
			boost::system::error_code& ec)
	{
		pointer conn = pointer(new FogsTcpConnection(io_service,
				true, ""));

		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(ip), port);
		conn->socket_.connect(ep, ec);
		if (ec)
		{
			conn.reset();
			return conn;
		}

		boost::asio::ip::tcp::no_delay option(true);
		conn->socket_.set_option(option);

		boost::asio::socket_base::keep_alive option1(true);
		conn->socket_.set_option(option1);
		return conn;
	}

	template<typename ConnectHandler>
	static pointer asyncConnect(boost::asio::io_service& io_service,
			const std::string &ip, uint16_t port,
			ConnectHandler & handler)
	{
		pointer conn = pointer(new FogsTcpConnection(io_service,
				true, ""));

		ip::tcp::endpoint ep(ip::address::from_string(ip), port);
		conn->socket_.async_connect(ep, handler);

		/*ip::tcp::no_delay option(true);
		conn->socket_.set_option(option);

		socket_base::keep_alive option1(true);
		conn->socket_.set_option(option1);*/

		return conn;
	}

	static void setOption(const pointer& conn)
	{
		ip::tcp::no_delay option(true);
		conn->socket_.set_option(option);

		socket_base::keep_alive option1(true);
		conn->socket_.set_option(option1);
	}

	FogsTcpConnection(boost::asio::io_service& io_service,
			bool autoStartRecv = true,
			const char * name = "conn");

	~FogsTcpConnection();

	boost::asio::ip::tcp::socket& socket(void)
	{
		return socket_;
	}

	void close()
	{
		boost::system::error_code ec;

		socket_.close(ec);
		if (ec)
		{
			// LOG4CXX_INFO(fogs::log::gNetLogger, "close connection failed, " << ec.message().c_str());
			//LOG(INFO) << "close connection failed, " << ec.message().c_str() << std::endl;
		}

		packetHandler_ = NULL;
		errorHandler_ = NULL;
	}

	boost::asio::ip::tcp::endpoint getPeer(void) const
	{
		return peer_;
	}

	void setPeer()
	{
		boost::system::error_code ec;
		peer_ = socket().remote_endpoint(ec);
		if (ec)
		{
             //LOG4CXX_INFO(fogs::log::gNetLogger, "Failed to get remote endpoint, ec: " << ec.message().c_str());
			//LOG(INFO) << "Failed to get remote endpoint, ec: " << ec.message().c_str() << std::endl;
		}
	}


	void startAsyncRecvPacket(const PacketHandler &packetHandler)
	{
		 //LOG4CXX_DEBUG(fogs::log::gNetLogger, "start receive message from connection ");
		//LOG(INFO) << "start receive message from connection " << std::endl;

		packetHandler_ = packetHandler;
		doRecv();
	}

	void connErrorHandler(const boost::system::error_code& error);

	void registerErrorHandler(const ErrorHandler & errorHandler)
	{
		errorHandler_ = errorHandler;
	}

	int writePacket(uint32_t type, uint32_t msg_id, uint32_t session_id, uint8_t * msg, int msgLen);

	void syncWriteMessage(uint32_t type, uint32_t msg_id, uint32_t session_id,
			const google::protobuf::Message& msg);

	void syncWriteMessage(FogsHeader* header);

	void asyncWriteMessage(FogsHeader* header);

	void asyncWriteMessage(uint32_t type, uint32_t msg_id, uint32_t session_id,
				const google::protobuf::Message &msg);

	void sendBroadcastMessage(uint32_t msg_id, const std::vector<uint32_t>& sessions,
			const google::protobuf::Message& msg);

	//不传sessions表示全部广播
	void sendBroadcastMessage(uint32_t msg_id, const google::protobuf::Message& msg);

	void asyncWriteMessage(uint32_t type, uint32_t msg_id, uint32_t session_id,
			uint32_t msg_len, uint8_t* payload);

	//void asynWrite(uint32_t msg_id, uint32_t session_id, uint8_t* msg, int msgLen);

	void asyncSendPrependLen();

	void handleAsyncWrite(const boost::system::error_code& error);
	    
	/* Unified interface */
	void sendMessage(uint32_t msg_id, uint32_t session_id, const google::protobuf::Message &msg)
	{
	    asyncWriteMessage(1, msg_id, session_id, msg);
	}

    std::string getPeerIP()
    {
        return peer_.address().to_string();
    }
    
    uint16_t getPeerPort()
    {
    	return peer_.port();
    }

    uint32_t sendBuffLen() { return sendBuffLen_; }
    void clearSendQueue();

    void enableZlib(){ useZlib_ = true; }
    void disableZlib() { useZlib_ = false; }
    bool needCompress(SendDataBuffer* sendData)
    {
    	return useZlib_ && (sendData->data_len - sizeof(FogsHeader) >= minZlibLen_);
    }

    void compress(SendDataBuffer* sendData);

    FogsHeader* unCompress(FogsHeader* header);

    void setEncrypt(EncryptType type, int maxLen, uint32_t key)
    {
    	encryptType_ = type;
    	maxEncryptLen_ = maxLen;
    	secretKey_ = key;
    }

    void disableEncrypt(){ encryptType_ = NOT_ENCRYPT; }

    void encrypt(SendDataBuffer* sendData);
    void decrypt(FogsHeader* header);

    bool enDecrypt(uint8_t* data, uint32_t len);

protected:
    SendDataBuffer* sendQueueHeader_;	//a null SendDataBuffer, next always point to the first sendDataBuffer
    SendDataBuffer* sendQueueTail_;		//always point to the last SendDataBuffer, if null, then point to the header
    SendDataBuffer* sendQueueCursor_;	//always point to the next ready sending SendDataBuffer

private:

    void doAsyncWriteMessage(SendDataBuffer* data);
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::endpoint peer_;
	bool autoStartRecv_;
	enum {
		MAX_RCV_LEN = 96 * 1024, // 1M, experimental val.
		//MAX_SEND_SIZE = 1024 * 300 // 300K, we have verification code
		MAX_SEND_SIZE = 96 * 1024 // boost bug, no more than 64K
	};

	FogsMessageBuffer msgBuffer_;

	PacketHandler packetHandler_;
	ErrorHandler errorHandler_;
	std::vector<boost::asio::const_buffer> bufVec_;
	uint32_t sendBuffLen_;

	uint8_t* sendDataCache_;
	uint8_t* deflateCache_;
	uint8_t* inflateCache_;

	bool useZlib_;

	static const uint32_t minZlibLen_ = 150;
	static const int32_t zlibLevel_ = -1;

	//bool encrypt_;
	EncryptType encryptType_;
	uint32_t maxEncryptLen_;
	uint32_t secretKey_;

	void doRecv()
	{
		boost::asio::async_read(socket_,
			msgBuffer_.makeBuffer(),
			boost::asio::transfer_at_least(msgBuffer_.receiveAtLeast()),
			boost::bind(&FogsTcpConnection::asyncRead, shared_from_this(),
									boost::asio::placeholders::error,
									boost::asio::placeholders::bytes_transferred)
			);

		return;
	}


	void asyncRead(const boost::system::error_code& error, std::size_t readLen);


};

}
}


#endif /* FOGSCONNECTION_HPP_ */
