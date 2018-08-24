#ifndef __WebSocketChatRoom__Client__
#define __WebSocketChatRoom__Client__

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

#include <google/protobuf/message.h>
#include "NetConfig.h"
#include "CWebCommon.hpp"

static const uint16_t g_usHeartBeatTime		= 3; //心跳包时间
static const uint16_t g_usHeartBeatTimes	= 3; //心跳包次数

typedef boost::function<void(CWebClient* pSocket)>	PWSEnterHandler;
typedef boost::function<void(CWebClient* pSocket)>	PWSExistHandler;
typedef boost::function<void(CWebClient* pSocket, PbMsgWebSS* pMsg, int32_t nSize)> PWSOnMsgHandler;
 
class CWebClient /*: public boost::enable_shared_from_this<CWebClient>*/
{
public:
	CWebClient(boost::asio::io_service &service);
	CWebClient(boost::asio::io_service &service, uint32_t unSessionID);
    ~CWebClient();
	void init(PWSEnterHandler onEnter, PWSOnMsgHandler onMsg, PWSExistHandler onExit);
    void start();
	bool close();
    void read_handler(const boost::system::error_code &ec);
	void conn_error_handler(const boost::system::error_code& error);
     
    void do_hand_shake();
    bool do_receive();
    void do_send(char* pBuf, uint32_t unLen);
	void sendresponse(uint16_t usCmd, uint16_t usCCmd, const ::google::protobuf::Message& msg);

	void sendresponse(const PbMsgWebSS* pMsg,int32_t nLength);

	inline boost::asio::ip::tcp::socket &get_socket(){ return m_socket; }

	inline uint32_t GetSessionID() const { return m_unSessionID; }

	inline void SetIP(const std::string& strIP) { m_strIP = strIP; }

	inline const std::string& GetIP() { return m_strIP; }

private:

	void parsedata(char* pBuf, uint32_t unLen);

    void retrieve_message();

protected:

    boost::asio::ip::tcp::socket m_socket;

	uint32_t m_unSessionID;

	std::string m_strIP;

    bool m_bHandshake;

	//fogs::FogsTimer* m_pTimer;

	uint16_t m_usTimes;

	uint16_t m_usProtectTimes;

	PWSEnterHandler	m_pOnEnter;		// 连接回调 
	PWSOnMsgHandler	m_pOnMsg;		// 消息回调 
	PWSExistHandler	m_pOnExit;		// 断开回调 
};

 
#endif /* defined(__WebSocketChatRoom__Client__) */