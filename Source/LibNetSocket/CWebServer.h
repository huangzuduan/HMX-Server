#ifndef __WebSocketChatRoom__Server__
#define __WebSocketChatRoom__Server__
#include <boost/asio.hpp>

#include "CWebCommon.hpp"
#include "NetConfig.h"
#include "CWebClient.h"

class CWebServer
{
public:
	CWebServer(boost::asio::io_service &service, const std::string & strIP, uint16_t usPort);
	~CWebServer();
     
    void start();
    void accept_handler(CWebClient* client,const boost::system::error_code &ec);

public:

	void init(PWSEnterHandler onEnter, PWSOnMsgHandler onMsg, PWSExistHandler onExit);

	void sendresponse(uint32_t sessionID, const PbMsgWebSS* pMsg, int32_t nLength);

	void add_client(CWebClient* client);

	void del_client(CWebClient* client);

	void clear_close();

	void broadcast(uint16_t usCmd, uint16_t usCCmd, const ::google::protobuf::Message& msg);

	uint32_t GetPersons() { return m_mapClient.size(); }

	std::string GetIPBySessionID(uint32_t unSessionID);

protected:

	std::string m_strIP;

	uint16_t m_usPort;
	
	boost::asio::ip::tcp::acceptor m_acceptor;

	std::map<uint32_t, CWebClient*> m_mapClient;

	std::vector<CWebClient*> m_vecClose;  // 已经colse要删除的对象 

	PWSEnterHandler	m_pOnEnter;		// 连接回调 
	PWSOnMsgHandler	m_pOnMsg;		// 消息回调 
	PWSExistHandler	m_pOnExit;		// 断开回调 

};
 
#endif /* defined(__WebSocketChatRoom__Server__) */