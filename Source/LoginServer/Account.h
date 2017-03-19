#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_
#include "SrvEngine.h"

namespace acc
{

	enum 
	{
		TYPE_5_MIN = 1,	// 5分钟	
		TYPE_10_MIN,	// 10分钟
		TYPE_20_MIN,	// 10分钟
		TYPE_30_MIN,	// 60分钟
		TYPE_1_HOUR,	// 1小时
		TYPE_1_DAY,		// 1天
	};

#pragma pack(push,1)

	const dbCol Id[] =
	{
		{ "ID",DB_QWORD,sizeof(QWORD) },
		{ NULL,0,0 },
	};

	const dbCol fields[] =
	{
		{ "ID",DB_QWORD,sizeof(int64) },
		{ "USERNAME",DB_STR,MAX_NAMESIZE + 1 },
		{ "PASSWORD",DB_STR,MAX_NAMESIZE + 1 },
		{ "CREATETIME",DB_DWORD,sizeof(int32) },
		{ "LASTLOGIN",DB_DWORD,sizeof(int32) },
		{ "STATE",DB_BYTE,sizeof(int8) },
		{ "TYPE",DB_BYTE,sizeof(int8) },
		{ "INFO",DB_BIN2, 0 },
		{ NULL,0,0 }
	};


	struct dbID
	{
		QWORD id;
	};

	struct Base
	{
		int64 id;
		char username[MAX_NAMESIZE + 1];
		char password[MAX_NAMESIZE + 1];
		int8 state;//0正常使用,1...其他原因被锁定
		int8 type; //0普通帐号,1临时5,2临时10,3临时30,4临时60,5临时24,6凌晨3点
		int32 createtime;
		int32 lastlogin;
	};

	struct Record
	{
		Base base;
		int32 size;
		BinaryHeader header;
	};

#pragma pack(pop)

}


class Account : public zEntry
{
public:
	Account();
	~Account();
	bool loadDB();
	void saveDB();
	void readBinary(const char* data, int32 len);
	int32 writeBinary(char* data);
	void timer();

public:
	char password[MAX_NAMESIZE + 1];
	int32 createtime;
	int32 lastlogin;
};



#endif




