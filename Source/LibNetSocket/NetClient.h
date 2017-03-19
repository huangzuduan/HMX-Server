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
	NetClient(int32 RecivedSize = 10 * 1024,int32 SendoutSize = 10 * 1024,int32 RecivedCacheSize = 64 * 1024,int32 SendoutCacheSize = 64 * 1024);
	virtual ~NetClient(void);
	void SetAddress( const char* pIp , uint16 nPort );
	void SetHandler( PNetServerEnterHandler pEnter ,  PNetServerOnMsgHandler pMsg , PNetServerExistHandler pExit );
	void Start();
	void Run();
	void OnUpdate();
	NetSocket* GetSocket();
	void Disconnect();

protected:
	void HandleStart();
	void HandleConnect(const boost::system::error_code& error,NetSocket* rSocket);
	void SetConnect(NetSocket& rSocket);
	void OnUpdateConnected();
	void OnUpdateRecived();

private:
		
	bool				m_connected;		// 是否连接成功  
	bool				m_onconnected;		// 是否连接调用 
	boost::thread		m_serviceThread;
	NetSocket*			pSocket;
	tcp::endpoint		m_serverAddr;
	PNetServerEnterHandler		m_pOnMsgConnected;
	PNetServerOnMsgHandler		m_pOnMsgRecevied;
	PNetServerExistHandler		m_pOnMsgDisconnect;
};

#endif

