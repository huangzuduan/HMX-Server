#ifndef __Net_SERVER_H_
#define __Net_SERVER_H_

#include "NetSocket.h"

#define MAX_SOCKETS 65536

/*-------------------------------------------------------------------
* @Brief : Socket服务器封装类
*
* @Author:hzd 2012/04/03
*------------------------------------------------------------------*/
class NetServer : public io_service
{
public:

	/*
	 *
	 *	Detail: 创建新服务器
	 *  @param 最大连接数
	 *  @param 最大收到单包大小
	 *  @param 最大一次发送大小(1+包)
	 *  @param 最大接收缓存大小
	 *  @param 最大发送缓存大小
	 *  Created by hzd 2012/04/03
	 *
	 */
	NetServer(int32_t nMaxConnected);
	virtual ~NetServer();

	// 获得标识ID
	int32_t SocketID();

	// 设置启动嗠地址与监听端口
	void SetAddress(const char* pIp, uint16_t pPort);

	// 超时断开时间(秒)
	void SetTimeout(int32_t nTimeout);

	// 设置Socket事件回调(如果没有指定，则会调用默认回调，可以使用继承获得回调)
	void SetHandler(PNetServerEnterHandler pEnter, PNetServerOnMsgHandler pMsg, PNetServerExistHandler pExit);

	// 启动服务
	void Start();

	// 停止服务
	void Stop();

	// 将Socket连接重新挂起
	void SetAccept(NetSocket& pSocket);

	// 消息处理
	void OnUpdate();

	// 获得Socket
	NetSocket& GetSocket(int32_t nIndex);

	// 已经连接中Socket数量
	size_t ConnectedSockets();

	// 在进行接受的Socket数量
	size_t AcceptingSockets();

	// 获得正在连接的socket
	NetSocket* getAcceptSocket(int64_t socketid);

	//  获得正在使用的socket
	NetSocket* getUsedSocket(int64_t socketid);

	// 获得正在等待连接的socket 
	SocketMap&	getSetAccepts() { return m_setWaitAccept; }

	inline std::vector<NetSocket*>& GetNetSockets() { return m_vecSocket; }

private:

	//  IO循环处理
	void Run();

	// 对所有客户端连接事件绑定启动
	void HandleStart();

	//  连接回调
	void HandleAccept(const boost::system::error_code& error, NetSocket* socket);

	// 处理连理进入
	void OnUpdateAccept();

	// 处理有消息Socket
	void OnUpdateRecived();

private:

	int32_t			m_nMaxConnected;			// 最大Socket连接数 < 65536 
	int32_t			m_nServerID;				// 服务器标识唯一ID  

	SocketMap		m_setWaitAccept;			// 设置连接的socket
	SocketMap		m_mapHadAccepted;			// 进入中的Socket  
	SocketMap		m_mapIsUsing;				// 使用中的Socket  
	
	std::vector<NetSocket*>	m_vecSocket;	// 所有的Scoket 

	tcp::endpoint   m_cServerAddr;				// 服务地址端 
	tcp::acceptor   m_cAcceptor;				// 连接管理器 

	PNetServerEnterHandler		m_pOnEnter;		// 连接回调 
	PNetServerOnMsgHandler		m_pOnMsg;		// 消息回调 
	PNetServerExistHandler		m_pOnExit;		// 断开回调 

	boost::thread  m_cServiceThread;
	boost::mutex   m_cClientListMutex;

};


#endif





