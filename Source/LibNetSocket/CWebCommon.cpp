#include "CWebCommon.hpp"
#include <iostream>
#include <sstream>

//参数1：是否结束(1:是 0:否) 参数2:发送模式(1:文本 2:二进制数据)
STFrameBuffer* frame_buffer_new(uint8_t fin, uint8_t opcode, uint64_t payload_len, const char *payload_data)
{
	if (fin > 1 || opcode > 0xf) {
		return NULL;
	}

	uint8_t mask = 0; //must not mask at server endpoint
	char masking_key[4] = { 0 }; //no need at server endpoint

	char *p = NULL; //buffer
	uint64_t len = 0; //buffer length

	unsigned char c1 = 0x00;
	unsigned char c2 = 0x00;
	c1 = c1 | (fin << 7); //set fin
	c1 = c1 | opcode; //set opcode
	c2 = c2 | (mask << 7); //set mask

	if (!payload_data || payload_len == 0) {
		if (mask == 0) {
			p = new char[2];
			*p = c1;
			*(p + 1) = c2;
			len = 2;
		}
		else {
			p = new char[2 + 4];
			*p = c1;
			*(p + 1) = c2;
			memcpy(p + 2, masking_key, 4);
			len = 2 + 4;
		}
	}
	else if (payload_data && payload_len <= 125) {
		if (mask == 0) {
			p = new char[2 + payload_len];
			*p = c1;
			*(p + 1) = c2 + payload_len;
			memcpy(p + 2, payload_data, payload_len);
			len = 2 + payload_len;
		}
		else {
			p = new char[2 + 4 + payload_len];
			*p = c1;
			*(p + 1) = c2 + payload_len;
			memcpy(p + 2, masking_key, 4);
			memcpy(p + 6, payload_data, payload_len);
			len = 2 + 4 + payload_len;
		}
	}
	else if (payload_data && payload_len >= 126 && payload_len <= 65535) {
		if (mask == 0) {
			p = new char[4 + payload_len];
			*p = c1;
			*(p + 1) = c2 + 126;
#ifdef _WIN32
			uint16_t tmplen = ntohs((uint16_t)payload_len);
#else
			uint16_t tmplen = htons((uint16_t)payload_len);
#endif

			memcpy(p + 2, &tmplen, 2);
			memcpy(p + 4, payload_data, payload_len);
			len = 4 + payload_len;
		}
		else {
			p = new char[4 + 4 + payload_len];
			*p = c1;
			*(p + 1) = c2 + 126;
#ifdef _WIN32
			uint16_t tmplen = ntohs((uint16_t)payload_len);
#else
			uint16_t tmplen = htons((uint16_t)payload_len);
#endif
			memcpy(p + 2, &tmplen, 2);
			memcpy(p + 4, masking_key, 4);
			memcpy(p + 8, payload_data, payload_len);
			len = 4 + 4 + payload_len;
		}
	}
	else if (payload_data && payload_len >= 65536) {
		if (mask == 0) {
			p = new char[10 + payload_len];
			*p = c1;
			*(p + 1) = c2 + 127;
#ifdef _WIN32
			uint16_t tmplen = ntohl(payload_len);
#else
			uint64_t tmplen = htonl(payload_len);
#endif
			memcpy(p + 2, &tmplen, 8);
			memcpy(p + 10, payload_data, payload_len);
			len = 10 + payload_len;
		}
		else {
			p = new char[10 + 4 + payload_len];
			*p = c1;
			*(p + 1) = c2 + 127;
#ifdef _WIN32
			uint16_t tmplen = ntohl(payload_len);
#else
			uint64_t tmplen = htonl(payload_len);
#endif
			memcpy(p + 2, &tmplen, 8);
			memcpy(p + 10, masking_key, 4);
			memcpy(p + 14, payload_data, payload_len);
			len = 10 + 4 + payload_len;
		}
	}

	STFrameBuffer *fb = NULL;
	if (p && len > 0) {
		fb = new STFrameBuffer;
		if (fb) {
			fb->data = p;
			fb->len = len;
		}
	}
	return fb;
}

bool base64_encode(std::string &input, std::string &output)
{
	typedef boost::archive::iterators::base64_from_binary<boost::archive::iterators::transform_width<std::string::const_iterator, 6, 8> > Base64EncodeIterator;
	std::stringstream result;
	copy(Base64EncodeIterator(input.begin()), Base64EncodeIterator(input.end()), std::ostream_iterator<char>(result));
	size_t equal_count = (3 - input.length() % 3) % 3;
	for (size_t i = 0; i < equal_count; i++)
	{
		result.put('=');
	}
	output = result.str();

	return output.empty() == false;
}

//websokcet消息组包
int WsEnCode(char * sendmsg, const google::protobuf::Message& pbMsg, uint16_t usCmd, uint16_t usCCmd)
{
	char msghead[4] = { 0 };//消息头
	//char msgbody[g_unMsgLen] = { 0 };//消息体
	int len = 0;
	short n_c_cmd = usCmd;// ::cmd_package::msg_login;
	short n_cmd = usCCmd;// ::msg_login_package::login_resp;
	msghead[1] = (n_c_cmd & 0x00ff);
	n_c_cmd >>= 8;
	msghead[0] = (n_c_cmd & 0x00ff);
	msghead[3] = (n_cmd & 0x00ff);
	n_cmd >>= 8;
	msghead[2] = (n_cmd & 0x00ff);

	if (pbMsg.SerializeToArray(sendmsg + 4, pbMsg.ByteSize()))
	{
		len = pbMsg.ByteSize();
		memcpy(sendmsg, msghead, 4);
	}
	return len + 4;
}

int WsEnCodeEx(char * sendmsg, uint32_t unLen, uint8_t* pBuf, uint16_t usCmd, uint16_t usCCmd)
{
	char msghead[4] = { 0 };//消息头
							// cmd
	msghead[1] = (usCmd & 0x00ff);
	usCmd >>= 8;
	msghead[0] = (usCmd & 0x00ff);
	// ccmd
	msghead[3] = (usCCmd & 0x00ff);
	usCCmd >>= 8;
	msghead[2] = (usCCmd & 0x00ff);

	memcpy(sendmsg, msghead, 4);
	memcpy(sendmsg + 4, pBuf, unLen);

	return unLen + 4;
}
