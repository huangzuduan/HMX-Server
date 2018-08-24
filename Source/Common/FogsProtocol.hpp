#ifndef FOGSPROTOCOL_HPP_
#define FOGSPROTOCOL_HPP_

#include "CommonDef.h"

//#ifdef __GNUC__
//#	include <stdint.h>
//#	else
//	typedef unsigned long   uint32_t;
//	typedef unsigned short  uint16_t;
//	typedef unsigned char   uint8_t;
//#endif

#define FOGS_MSG_TYPE_NORMAL 	 1
#define FOGS_MSG_TYPE_RPC 		 2
//#define FOGS_MSG_TYPE_ACK_RPC  2
//#define FOGS_MSG_TYPE_SIMPLE_RPC 3
#define FOGS_MSG_TYPE_BROADCAST  8

namespace fogs
{
namespace net
{

/*
fp_type每位使用说明：
	fp_type低四位表示消息type，最高位表示是否加密，次高位表示是否压缩，中间26位表示消息序列
	32  31  30-5    4-1
	——  ——  ————   ————
	加密   压缩   消息序列     消息类型
*/

struct FogsHeader
{
	uint32_t fp_type;
	uint32_t fp_msg_id;
	uint32_t fp_length;

	union
	{
		struct
		{
			uint32_t session_id;
			uint8_t  payload[0];
		} unicast;

		struct
		{
			uint32_t  session_num;
			uint32_t  sessions[0];
		}broadcast;
	} un;

#define fp_session_id 		un.unicast.session_id
#define fp_session_num  	un.broadcast.session_num
#define fp_payload			un.unicast.payload
#define fp_sessions 		un.broadcast.sessions

//add for d_game by yys
#define fp_account_id 		un.unicast.session_id
#define fp_account_num  	un.broadcast.session_num
#define fp_sessions 		un.broadcast.sessions

	void setEncrypted() { fp_type |= 0x80000000; } //最高位设为1
	void setdecrypted() { fp_type &= 0x7FFFFFFF; } //最高位设为0

	//bool isEncrypted(){ return fp_type&0x80000000;}
	bool isEncrypted(){ return false;}

	void setDeflate(){ fp_type |= 0x40000000; }
	void setInflate(){ fp_type &= 0xBFFFFFFF; }
	//bool isDeflate() { return fp_type&0x40000000; }
	bool isDeflate() { return false; }

	int32_t getMsgType() {	return fp_type&0x000F; }

	void setMsgType(int32_t t) { fp_type = t; }

	uint32_t getSeqId() { return ((fp_type&0x3FFFFFFF) >> 4);}

};

}
}


#endif /* FOGSMESSAGE_HPP_ */
