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
enum  EMsgRead
{
	MSG_READ_INVALID,
	MSG_READ_WAITTING,
	MSG_READ_OK,
	MSG_READ_REVCING,
};

// SCOKET 断开原因 
enum ESocketExist
{
	ESOCKET_EXIST_NULL = 0,				/* 0:无 */
	ESOCKET_EXIST_LOCAL,				/* 1:本地主动断开-------服务端调用了SetWellColse */
	ESOCKET_EXIST_REMOTE,				/* 2:远端主动断开-------用户直接 */
	ESOCKET_EXIST_TIMEOUT,				/* 3:超时断开-----------该值由启动服务器端设定 */
	ESOCKET_EXIST_PACK_LENGTH_ERROR,	/* 4:包头长度值非法-----小于sizeof(NetMsgHead)或大于设置接收最大包大小 */
	ESOCKET_EXIST_WRITE_TOO_DATA,		/* 5:写入数据到buffer中失败--收到的数据过多，而服务器处理包速度过慢，或者设定的buffer容量太小 */
	ESCOKET_EXIST_SEND_CONNECT_INVAILD, /* 6:发送数据时失败------连接失效 */
};

class NetSocket : public tcp::socket
{
	friend class NetServer;
	friend class NetClient;
public:
	NetSocket(io_service& rIo_service,int32 nMaxRecivedSize,int32 nMaxSendoutSize,int32 nMaxRecivedCacheSize,int32 nMaxSendoutCacheSize);
	virtual ~NetSocket();

	/*
	 *
	 *	Detail:  获得SocketID，从0开始自增 
	 *
	 */
	int32 SID() { return m_nID; }
	int64 SLongID() { return m_nLongID; }

	/*
	 *
	 *	Detail:  压入要准备发送的数据 
	 *
	 *
	 */
	void ParkMsg(const NetMsgSS* pMsg,int32 nLength);

	/*
	 *
	 *	Detail:  压入要准备发送的数据
	 *
	 *
	 */
	void ParkMsg(const NetMsgC* pMsg, int32 nLength);

	/*
	 *	Detail:  发送数据 
	 *
	 */
	void SendMsg();

	/*
	 *
	 *	Detail:  读取缓存中的数据 
	 *
	 */
	EMsgRead ReadMsg(NetMsgSS** pMsg,int32& nSize);

	/*
	 *	Detail: 移除缓存中的数据 
	 *
	 */
	void RemoveMsg(uint32 nLen);

	/*
	 *	Detail: 启动Socket，可以进入收发数据 
	 */
	void Run();

	/*
	 *	Detail: 获得Socket客户端IP地址 
	 */
	const string GetIp();

	/*
	 * 获得连连的端口 
	 */
	uint16 GetPort();

	/*
	 *	Detail: 将关闭Socket(主动断开客户端) 
	 *
	 */
	void OnEventColse();

	/*
	 *
	 *	Detail: 超过断开 
	 *
	 */
	void SetTimeout(int32 nTimeout);

	/*
	 *
	 *	Detail: 定时启动 
	 *
	 */
	void TimeoutStart();

	/*
	 *	Detail: 定时关闭 
	 */
	void TimeoutCancel();

	/*
	 * 0:无
	 * 1:本地主动断开-------服务端调用了SetWellColse
	 * 2:远端主动断开-------用户直接
	 * 3:超时断开-----------该值由启动服务器端设定
	 * 4:包头长度值非法-----小于sizeof(NetMsgHead)或大于设置接收最大包大小 
	 * 5:写入数据到buffer中失败--收到的数据过多，而服务器处理包速度过慢，或者设定的buffer容量太小
	 * 6:发送数据时失败------连接失效 
	 * @Author:hzd 2013:11:19
	 */
	int32 ErrorCode(std::string& error);

	/*
	 *	中断读消息，返回为warriting 
	 */
	void BreakUpdateIO();

	/*
	 *	去掉中断，让read消息处于waitting中 
	 */
	void UnBreakUpdateIO(); 

	/*
	 * 增加事件，将会关闭socket
	 */ 
	void AddEventLocalClose();

	bool HadEventClose();

private:

	NetSocket();

	/*
	 *
	 *	Detail: 断开 socket
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void Disconnect();

	/*
	 *
	 *	Detail: 关闭 socket
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void HandleClose(const boost::system::error_code& error);
	
	/*
	 *
	 *	Detail: 恢复到构造函数那种状态 
	 *
	 *  Created by hzd 2013-1-20
	 *
	 */
	void Clear();

	/*
	 *
	 *	Detail: 收到指定长度数据回调函数 
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void RecvMsg(const boost::system::error_code& ec, size_t bytes_transferred);

	/*
	 *
	 *	Detail: 发送数据回调函数，发送后发现有新数据，则会选择断续发送（一般不会发生这种情况）
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void SendMsg(const boost::system::error_code& ec, size_t bytes_transferred);

	/*
	 *
	 *	Detail: 读消息头 
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void ReadHead();

	/*
	 *
	 *	Detail: 读消息主体 
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void ReadBody();

	/*
	 *
	 *	Detail: 超时回调函数，将会关闭 socket 
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void HandleWait(const boost::system::error_code& error);

private:

	int32				m_nID;				// socketID， 一个进程所的 Socket 唯一ID从0开始 
	int32				m_nIndexID;			// 自定义ID, 可以用数组下标，方便管理 
	int64				m_nLongID;		
	int64				m_nLongIndexID;
	mutable_buffers_1	m_cHeadBuffer;		// 收到头数据缓存绑定类 
	mutable_buffers_1	m_cBodyBuffer;      // 收到的主体数据绑在绑定类 
	mutable_buffers_1	m_cSendBuffer;      // 发送的数据缓存绑定类 

	deadline_timer		m_cTimer;			// 收发定时器，用于检测用户多久没有与服务器通信，否则会角色 HandleWait 函数 
	deadline_timer		m_cCloseTimer;		// 关闭连接定时器 

	NetIOBuffer			m_cIBuffer;			// 管理收到的字节管理器  
	NetIOBuffer			m_cOBuffer;			// 管理发出的字节管理器 

	ERecvType			m_eRecvStage;
	int32				m_nBodyLen;			// 主体数据长度（不包括包头） 
	char				m_arrRecvBuffer[65536];

	int32				m_bSending;
	char				m_arrSendBuffer[65536];

	int32				m_nMaxRecivedSize;
	int32				m_nMaxSendoutSize;

	int32				m_nTimeout;			// 超时断开,0不,>0指定秒数 

	/*-------------------------------------------------------------------
	 * @Brief :
	 *			-1:无
	 *			0:本地主动断开-------服务端调用了SetWellColse
	 *			1:远端主动断开-------用户直接
	 *			2:超时断开-----------该值由启动服务器端设定
	 *			3:包头长度值非法-----小于sizeof(NetMsgHead)或大于设置接收最大包大小
	 *			4:写入数据到buffer中失败--收到的数据过多，而服务器处理包速度过慢，或者设定的buffer容量太小 
	 *			5:发送数据时失败------连接失效 
	 *
	 * @Author:hzd 2013:11:19
	 *------------------------------------------------------------------*/
	int32				m_errorCode;		// 错误代码  

	bool m_bBreakUpdateIo; /* 中断收的IO，让消息处于等待中 */ 

	bool m_bEnventClose; // 是否有退出事件 

};

typedef boost::function<void(NetSocket& pSocket)>	PNetServerEnterHandler;
typedef boost::function<void(NetSocket& pSocket)>	PNetServerExistHandler;
typedef boost::function<void(NetSocket& pSocket, NetMsgSS* pMsg,int32 nSize)>	PNetServerOnMsgHandler;


typedef list<NetSocket*> SocketList;
typedef list<NetSocket*>::iterator SocketListIter;
typedef vector<NetSocket*> SocketVector;
typedef vector<NetSocket*>::iterator SocketVectorIter;

typedef map<int64,NetSocket*> SocketMap;
typedef map<int64, NetSocket*>::iterator SocketMapIter;

#endif

