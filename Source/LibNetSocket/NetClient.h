#ifndef __NET_CLIENT_H_
#define __NET_CLIENT_H_

#include "NetSocket.h"

/*
 *
 *	Detail: Socket通信Client基类
 *   
 *  Created by hzd 2012-8-4
 *
 */
class NetClient : public io_service
{
public:
	NetClient();
	virtual ~NetClient(void);
	inline uint32_t CID() const { return m_ID; }
	void SetAddress( const char* pIp , uint16_t nPort );
	void SetHandler( PNetServerEnterHandler pEnter ,  PNetServerOnMsgHandler pMsg , PNetServerExistHandler pExit );
	void Start();
	void Run();
	void OnUpdate();
	NetSocket* GetSocket();
	void Disconnect();
	void Clear();
protected:
	void HandleStart();
	void HandleConnect(const boost::system::error_code& error,NetSocket* _socket);
	void SetConnect();
	void OnUpdateConnected();
	void OnUpdateRecived();

private:
	uint32_t			m_ID;
	bool				m_connected;		// 是否连接成功  
	bool				m_onconnected;		// 是否连接调用 
	boost::thread		m_serviceThread;
	NetSocket*			m_pSocket;
	tcp::endpoint		m_serverAddr;
	PNetServerEnterHandler		m_pOnMsgConnected;
	PNetServerOnMsgHandler		m_pOnMsgRecevied;
	PNetServerExistHandler		m_pOnMsgDisconnect;
};

#endif

