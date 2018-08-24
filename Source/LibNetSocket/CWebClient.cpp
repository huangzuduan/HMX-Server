#include "CWebClient.h"
#include "CWebCommon.hpp"

#ifdef _WIN32
#include<Winsock2.h>
#else
#include <arpa/inet.h>
#endif

#include "CWebServer.h"

using namespace boost::asio;

CWebClient::CWebClient(io_service &service) :
	m_socket(service),
	m_bHandshake(false),
	m_usTimes(0),
	m_usProtectTimes(0)
{
	static int32_t s_unm_unSessionID = 0;
	m_unSessionID = ++s_unm_unSessionID;
}
 
CWebClient::CWebClient(io_service &service, uint32_t unSessionID) :
	m_socket(service),
	m_unSessionID(unSessionID),
	m_bHandshake(false),
	m_usTimes(0),
	m_usProtectTimes(0)
{
}
 
CWebClient::~CWebClient()
{
	if (m_socket.is_open())
	{
		boost::system::error_code ec;
		m_socket.close(ec);
		if (ec)
		{
			printf("CWebClient::~CWebClient(): %s \n", ec.message().c_str());
		}
	}
}

void CWebClient::init(PWSEnterHandler onEnter, PWSOnMsgHandler onMsg, PWSExistHandler onExit)
{
	m_pOnEnter = onEnter;
	m_pOnMsg = onMsg;
	m_pOnExit = onExit;
	m_pOnEnter(this);
}
 
void CWebClient::start()
{
	m_socket.async_read_some(null_buffers(), boost::bind(&CWebClient::read_handler,this, boost::asio::placeholders::error));
}

bool CWebClient::close()
{
	m_pOnExit(this);
	if (!m_socket.is_open())
	{
		return false;
	}

	printf("Disconnect: %s \n", m_strIP.c_str());

	boost::system::error_code ec;
	m_socket.close(ec);
	if (ec)
	{
		printf("close connection failed: %s \n", ec.message().c_str());
	}
	return true;
}
 
void CWebClient::read_handler(const boost::system::error_code &ec)
{
    if(!ec)
    {
        size_t size= m_socket.available();
        if(size!=0)
        {
            bool flag=true;
             
			if (!m_bHandshake)
			{
				do_hand_shake();
			}
			else
			{
				flag = do_receive();
			} 
			if (flag)
			{
				start();
			}    
			else
			{
				close();
			}	
        }
		else
		{
			close();
		}	
    }
	else
	{
		close();
	}
}

void CWebClient::conn_error_handler(const boost::system::error_code& error)
{
	printf("CWebClient::conn_error_handler()");
	close();
}
 
void CWebClient::do_hand_shake()
{
	boost::asio::streambuf content;
    boost::system::error_code ec;
    std::size_t length=read_until(m_socket,content,"\r\n\r\n",ec);
    if(ec)
        return;
     
	boost::asio::streambuf::const_buffers_type bufs=content.data();
    std::string lines(buffers_begin(bufs),buffers_begin(bufs)+length);
   /* std::cout << "websocket:......" << std::endl;
	std::cout << lines << std::endl;*/
     
    std::string response,key,encrypted_key;
     
    //find the Sec-WebSocket-Key
    size_t pos=lines.find("Sec-WebSocket-Key");
	
    if(pos==lines.npos)
        return;
    size_t end=lines.find("\r\n",pos);
    key=lines.substr(pos+19,end-pos-19)+"258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

	//std::cout << "****************key: " << key << std::endl;
     
    //get the base64 encode string with sha1
    boost::uuids::detail::sha1 sha1;
    sha1.process_bytes(key.c_str(), key.size());
    unsigned int digest[5];
    sha1.get_digest(digest);
    //key.clear();
    for(int i=0;i<5;i++)
    {
        const char* tmp = reinterpret_cast<char*>(digest);
        key[i*4] = tmp[i*4+3];
        key[i*4+1] = tmp[i*4+2];
        key[i*4+2] = tmp[i*4+1];
        key[i*4+3] = tmp[i*4];
    }
    std::string first;
    for(int i=0;i<20;i++)
    {
        first.append(1,key[i]);
    }
    base64_encode(first, encrypted_key);
     
    //set the response text
    response.append("HTTP/1.1 101 WebSocket Protocol Handshake\r\n");
    response.append("Upgrade: websocket\r\n");
    response.append("Connection: Upgrade\r\n");
    response.append("Sec-WebSocket-Accept: "+encrypted_key+"\r\n");
    response.append("Sec-WebSocket-Version: 13\r\n\r\n");
     
    m_socket.send(buffer(response));
    m_bHandshake = true;
}
 
bool CWebClient::do_receive()
{
    retrieve_message();

	return true;
}
 
void CWebClient::do_send(char* pBuf, uint32_t unLen)
{
	if (!m_socket.is_open())
	{
		return;
	}
		
	STFrameBuffer* pSend = frame_buffer_new(1, 2, unLen, pBuf);
	if (pSend)
	{
		m_socket.send(buffer(pSend->data, pSend->len));
		delete pSend;
	}
}

void CWebClient::parsedata(char* pBuf, uint32_t unLen)
{
	if (unLen < 4)
	{
		printf("CWebClient::parsedata() :len < 4");
		return;
	}
		
	// 解析cmd
	uint16_t usCmd = 0;
	usCmd |= (pBuf[0] & 0x00ff);
	usCmd <<= 8;
	usCmd |= (pBuf[1] & 0x00ff);
	// 解析ccmd
	uint16_t usCCmd = 0;
	usCCmd |= (pBuf[2] & 0x00ff);
	usCCmd <<= 8;
	usCCmd |= (pBuf[3] & 0x00ff);

	static char msgEnBuffer[65536];
	static char msgUnBuffer[65536];

	int nCHeadSize = sizeof(PbMsgWeb);
	int nSHeadSize = sizeof(PbMsgWebSS);
	memcpy(&msgEnBuffer[0], pBuf, unLen);

	// 组装为PbMsgWebSS头协议，中间补两种头协议的字节差 
	memcpy(&msgUnBuffer[0], msgEnBuffer, nCHeadSize);
	memset(&msgUnBuffer[nCHeadSize], 0, nSHeadSize - nCHeadSize);
	memcpy(&msgUnBuffer[nSHeadSize], &msgEnBuffer[nCHeadSize], unLen - nCHeadSize);
	PbMsgWebSS* pNewMsg = (PbMsgWebSS*)&msgUnBuffer[0];
	pNewMsg->cmd = usCmd;
	pNewMsg->cmdType = usCCmd;
	pNewMsg->size = unLen - nCHeadSize;
	m_pOnMsg(this, pNewMsg, unLen + nSHeadSize - nCHeadSize);
}
 
void CWebClient::retrieve_message()
{
    //receive fin and opcode
    unsigned char fin_opcode;
	if (m_socket.available() <= 0)
	{
		printf("websoket recv available = 0");
		return;
	}
    m_socket.receive(buffer(&fin_opcode,sizeof(fin_opcode)));
    unsigned char fin=fin_opcode>>7;
    unsigned char opcode=fin_opcode&0x7f;
    if(fin==char(0x00))
    {
        printf("%02x\n",fin);
        return;
    }
    switch(opcode)
    {
        case 0x01:
        case 0x02:
            break;
        case 0x08://client send close
			printf("client send close!");
			close();	
            return;
        case 0x09://client send ping
			printf("client send ping!");
            return;
        case 0x0A://client send pong
			printf("client send pong!");
            return;
        default:
            return;
    }
     
    //get payload_len
    unsigned char payload_len;
	if (m_socket.available() <= 0)
	{
		printf("websoket recv available = 0");
		return;
	}
    m_socket.receive(buffer(&payload_len,sizeof(payload_len)));
    unsigned char is_mask=payload_len>>7;
    unsigned short length=0;
    uint64_t tmp=payload_len&0x7f;
    if(tmp==126)
    {
        uint16_t len;
		if (m_socket.available() <= 0)
		{
			printf("websoket recv available = 0");
			return;
		}
        m_socket.receive(buffer(&len,sizeof(len)));
        length=ntohs(len);
    }
    else if(tmp==127)
    {
		if (m_socket.available() <= 0)
		{
			printf("websoket recv available = 0");
			return;
		}
        m_socket.receive(buffer(&tmp,sizeof(tmp)));
        length=ntohs(tmp);
    }
    else
        length=static_cast<unsigned short>(tmp);
     
    //get mask if exists
    char mask[4];
    if(is_mask)
    {
		if (m_socket.available() <= 0)
		{
			printf("websoket recv available = 0");
			return;
		}
        m_socket.receive(buffer(mask,sizeof(mask)));
    }
     
    //get data
    if(length==0)
        return;
    char *data=new char[length];
	if (m_socket.available() <= 0)
	{
		printf("websoket recv available = 0");
		return;
	}
    m_socket.receive(buffer(data,length));
    if(is_mask)
    {
        for(uint64_t i=0;i<length;i++)
        {
            data[i]=data[i]^mask[i%4];
        }
    }

	parsedata(data, length);
	delete []data;
}
 
void CWebClient::sendresponse(uint16_t usCmd, uint16_t usCCmd, const ::google::protobuf::Message& msg)
{
	char msgbody[g_unMsgLen];
	int sendlen = WsEnCode(msgbody, msg, usCmd, usCCmd);
	do_send(msgbody, sendlen);
}

void CWebClient::sendresponse(const PbMsgWebSS* pMsg, int32_t nLength)
{
	char msgbody[g_unMsgLen];
	int sendlen = WsEnCodeEx(msgbody, pMsg->size, (uint8_t*)pMsg->data, pMsg->cmd, pMsg->cmdType);
	do_send(msgbody, sendlen);
}
