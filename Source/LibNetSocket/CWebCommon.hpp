#ifndef _CWEB_COMMON_H_
#define _CWEB_COMMON_H_

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/uuid/sha1.hpp>
#include <google/protobuf/message.h>

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#endif

class CWebClient;

static const int32_t g_unMsgLen = 1024 * 96;

//frame buffer
struct STFrameBuffer
{
	char *data;
	uint64_t len;

	STFrameBuffer()
	{
		data = NULL;
		len = 0;
	}

	~STFrameBuffer()
	{
		if (data)
		{
			delete[]data;
		}
	}
};

//参数1：是否结束(1:是 0:否) 参数2:发送模式(1:文本 2:二进制数据)
STFrameBuffer* frame_buffer_new(uint8_t fin, uint8_t opcode, uint64_t payload_len, const char *payload_data);

bool base64_encode(std::string &input, std::string &output);

//websokcet消息组包
int WsEnCode(char * sendmsg, const google::protobuf::Message& pbMsg, uint16_t usCmd, uint16_t usCCmd);

int WsEnCodeEx(char * sendmsg, uint32_t unLen, uint8_t* pBuf, uint16_t usCmd, uint16_t usCCmd);


#endif // !_CWEB_COMMON_H_
