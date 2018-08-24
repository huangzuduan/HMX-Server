#include "CWebServer.h"
#include "CWebClient.h"
 
CWebServer::CWebServer(boost::asio::io_service &service, const std::string& strIP, uint16_t usPort) :
	m_strIP(strIP),
	m_usPort(usPort),
	m_acceptor(service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), usPort))
{
}

CWebServer::~CWebServer()
{
	for (std::map<uint32_t, CWebClient*>::iterator iter = m_mapClient.begin(); iter != m_mapClient.end(); ++iter)
	{
		if (iter->second)
		{
			(iter->second)->close();
		}
	}
	m_mapClient.clear();
}
 
void CWebServer::start()
{
	CWebClient* client = new CWebClient(m_acceptor.get_io_service());
	m_acceptor.async_accept(client->get_socket(), boost::bind(&CWebServer::accept_handler, this, client, boost::asio::placeholders::error));
}
 
void CWebServer::accept_handler(CWebClient* client,const boost::system::error_code &ec)
{
	if (ec)
	{
		client->conn_error_handler(ec);
		start();
		return;
	}
	start();
	boost::asio::ip::tcp::endpoint remote = client->get_socket().remote_endpoint();
	client->SetIP(remote.address().to_string());
	client->init(m_pOnEnter, m_pOnMsg, m_pOnExit);
	client->start();
	add_client(client);
}

void CWebServer::add_client(CWebClient* client)
{
	m_mapClient.insert(std::make_pair(client->GetSessionID(), client));
}

void CWebServer::del_client(CWebClient* client)
{
	std::map<uint32_t, CWebClient*>::iterator iter = m_mapClient.find(client->GetSessionID());
	if (iter != m_mapClient.end())
	{
		m_mapClient.erase(iter);
	}
}

void CWebServer::clear_close()
{
	for (std::vector<CWebClient*>::iterator it = m_vecClose.begin(); it != m_vecClose.end();it++ )
	{
		del_client(*it);
		delete (*it);
	}
}

void CWebServer::broadcast(uint16_t usCmd, uint16_t usCCmd, const ::google::protobuf::Message& msg)
{
	for (std::map<uint32_t, CWebClient*>::const_iterator iter = m_mapClient.begin(); iter != m_mapClient.end(); ++iter)
	{
		(iter->second)->sendresponse(usCmd, usCCmd, msg);
	}
}

std::string CWebServer::GetIPBySessionID(uint32_t unSessionID)
{
	std::map<uint32_t, CWebClient*>::const_iterator iter = m_mapClient.find(unSessionID);
	if (iter == m_mapClient.end())
	{
		return "";
	}
	return (iter->second)->GetIP();
}

void CWebServer::init(PWSEnterHandler onEnter, PWSOnMsgHandler onMsg, PWSExistHandler onExit)
{
	m_pOnEnter = onEnter;
	m_pOnMsg = onMsg;
	m_pOnExit = onExit;
	start();
}

void CWebServer::sendresponse(uint32_t sessionID, const PbMsgWebSS* pMsg, int32_t nLength)
{
	std::map<uint32_t, CWebClient*>::const_iterator iter = m_mapClient.find(sessionID);
	if (iter == m_mapClient.end())
	{
		printf("CWebClient::sendresponseEx() sessionid: %d \n" , sessionID);
		return;
	}

	if (nLength >= g_unMsgLen)
	{
		printf("msg too long len:%d \n ", nLength);
		return;
	}

	(iter->second)->sendresponse(pMsg, nLength);
}

