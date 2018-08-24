#ifndef __NET_SOCKET_H_
#define __NET_SOCKET_H_


#include "NetIOBuffer.h"

/*
 *
 *	Detail: Socket 类 
 *
 *  Created by hzd 2013-1-1
 *
 */
enum ERecvType
{
	REVC_FSRS_NULL = 0,
	REVC_FSRS_HEAD,
	REVC_FSRS_BODY,
};

class NetSocket : public tcp::socket
{
	friend class NetServer;
	friend class NetClient;
public:
	NetSocket(io_service& rIo_service);
	virtual ~NetSocket();

	// 获得SocketID，从0开始自增 
	inline uint64_t SocketID() const { return m_usSocketID; }

	//  压入要准备发送的数据 
	void ParkMsg(const uint8_t* data, int32_t leng);

	/***
	 * 读取缓存中的数据 
	 * -1 连接异常
	 * 0 等待中
	 * > 0数据长度
	 */ 
	int ReadDataMsg(uint8_t** data);

	// 移除缓存中的数据 
	void RemoveQueueHeader();

	// 启动Socket，可以进入收发数据 
	void Run();

	// 获得Socket客户端IP地址 
	const string GetIp() const;

	// 获得连连的端口 
	uint16_t GetPort() const;

	// 将关闭Socket(主动断开客户端) 
	void OnEventColse();

	 // 超过断开 
	void SetTimeout(int32_t nTimeout);

	// 定时启动 
	void TimeoutStart();

	//  定时关闭 
	void TimeoutCancel();

	/*
	 *	中断读消息，返回为warriting 
	 */
	inline void BreakUpdateIO() { m_bBreakUpdateIo = true; }

	/*
	 *	去掉中断，让read消息处于waitting中 
	 */
	inline void UnBreakUpdateIO() {m_bBreakUpdateIo = false; }

	/*
	 * 增加事件，将会关闭socket
	 */ 
	inline void SetLocalClose( bool bEventClose) { m_bEnventClose = bEventClose; }
	inline bool GetIsClose() const { return m_bEnventClose; }
	inline void SetIsCloseBeing(bool isBegin) { m_bEventCloseBegin = isBegin; }
	inline bool GetIsCloseBegin() const { return m_bEventCloseBegin; }
	inline void SetIsCloseFinish(bool isFinish) { m_bEventCloseFinish = isFinish; }
	inline bool GetIsCloseFinish() const { return m_bEventCloseFinish; }

private:

	NetSocket();

	// 断开 socket
	void Disconnect();

	// 关闭 socket
	void HandleClose(const boost::system::error_code& error);
	
	// 恢复到构造函数那种状态 
	void Clear();

	// 收到指定长度数据回调函数 
	void RecvMsg(const boost::system::error_code& ec, size_t bytes_transferred);

	//  发送数据回调函数，发送后发现有新数据，则会选择断续发送（一般不会发生这种情况）
	void SendMsg(const boost::system::error_code& ec, size_t bytes_transferred);

	//  读消息头 
	void ReadMsg(mutable_buffers_1& _buffers, uint32_t dataLen);

	// 超时回调函数，将会关闭 socket 
	void HandleWait(const boost::system::error_code& error);

private:

	uint64_t			m_usSocketID;			// socketID， 一个进程所的 Socket 唯一ID从0开始 
	mutable_buffers_1	m_cRecvHeadBuffer;		// 收到头数据缓存绑定类 
	mutable_buffers_1	m_cRecvBodyBuffer;		// 收到头数据缓存绑定类 

	deadline_timer		m_cTimer;				// 收发定时器，用于检测用户多久没有与服务器通信，否则会角色 HandleWait 函数 
	deadline_timer		m_cCloseTimer;			// 关闭连接定时器 

	// 一次收与发的中间转存(Buffer)空间
	ERecvType			m_eRecvStage;
	char				m_arrRecvBuffer[PACKAGE_MAX_SIZE];

	DataBuffer*		recvQueueHeader_;	//本次要发送的头
	DataBuffer*		recvQueueLastest_;	//本次数组的结尾

	int32_t				m_nTimeout;			// 超时断开,0不,>0指定秒数 

	bool m_bBreakUpdateIo; /* 中断收的IO，让消息处于等待中 */ 

	bool m_bEnventClose;		// 是否有退出事件 
	bool m_bEventCloseBegin;	// 开始退出事件
	bool m_bEventCloseFinish;	// 完成退出事件

	boost::mutex   m_writeBufferMutex;
};

typedef boost::function<void(NetSocket& pSocket)>	PNetServerEnterHandler;
typedef boost::function<void(NetSocket& pSocket)>	PNetServerExistHandler;
typedef boost::function<void(NetSocket& pSocket, NetMsgSS* pMsg,int32_t nSize)>	PNetServerOnMsgHandler;


typedef list<NetSocket*> SocketList;
typedef list<NetSocket*>::iterator SocketListIter;
typedef vector<NetSocket*> SocketVector;
typedef vector<NetSocket*>::iterator SocketVectorIter;

typedef map<uint64_t,NetSocket*> SocketMap;
typedef map<uint64_t, NetSocket*>::iterator SocketMapIter;

#endif

