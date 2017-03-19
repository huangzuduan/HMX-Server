#include "WorldServer_PCH.h"
#include "OfflineUser.h"

OfflineUser::OfflineUser()
{

}

OfflineUser::~OfflineUser()
{

}

bool OfflineUser::loadDB()
{

	const dbCol fields[] =
	{
		{ "ID",DB_QWORD,sizeof(int64) },
		{ "NAME",DB_STR,MAX_NAMESIZE + 1 },
		{ "LEVEL",DB_WORD,sizeof(int16) },
		{ "VIP",DB_BYTE,sizeof(int8) },
		{ "COUNTRY",DB_BYTE,sizeof(int8) },
		{ "TEAMID",DB_DWORD,sizeof(int32) },
		{ "INFO",DB_BIN2, 0 },
		{ NULL,0,0 }
	};

#pragma pack(push,1)
	struct Base
	{
		int64 id;
		char name[MAX_NAMESIZE + 1];
		int16 level;
		int8 vip;
		int8 country;
		int32 teamid;
	};

	struct Record
	{
		Base base;
		int32 size;
		BinaryHeader header;
	};

#pragma pack(pop)


	char buffer[MAX_USERDATASIZE];

	Record* ret = (Record*)buffer;
	char wheres[100];
	memset(wheres, 0, sizeof(wheres));
	sprintf(wheres, "`id`=%lld", this->id);
	int32 retsize = GameService::getMe().getDbMysql()->ExecSelectLimit("USER", fields, wheres, NULL, (unsigned char*)ret, 1);
	if (retsize < 1)
	{
		H::logger->error("加载角色内存失败，找不到数据");
		return false;
	}

	strncpy(this->name,ret->base.name,MAX_NAMESIZE);
	this->level = ret->base.level;
	this->vip = ret->base.vip;
	this->country = ret->base.country;
	this->teamid = ret->base.teamid;
	if (ret->size == sizeof(ret->header) + ret->header.size)
	{
		this->readBinary(ret->header.data, ret->header.size);
	}
	else
	{
		H::logger->error("数据出错,name=%s", this->name);
		ASSERT(0);
		return false;
	}
	return true;
}

void OfflineUser::saveDB()
{

}

void OfflineUser::readBinary(const char* data, int32 len)
{
	if (len < sizeof(BinaryMember))
		return;

	const BinaryMember* pMember = (const BinaryMember*)data;
	while (pMember->type != BINARY_USER_NULL && pMember->type < BINARY_USER_MAX)
	{
		switch (pMember->type)
		{
			case BINARY_USER_COUNTER:
			{
				::protobuf::CounterProto proto;


			}
			break;
			case BINARY_USER_RELATION:
			{

			}
			break;
		}
		pMember = (const BinaryMember*)(&pMember->data[pMember->size]);
	}
}

int32 OfflineUser::writeBinary(char* data)
{
	int32 dwSize = 0;
	BinaryMember* item = (BinaryMember*)data;
	for (int type = BINARY_USER_NULL + 1; type < BINARY_USER_MAX; ++type)
	{
		item->type = type;
		item->size = 0;
		switch (type)
		{
			//protobuf
			//serilaze
			//item->size += protobuf.ByteSize();
			//serilazetoarray
		}

		if (item->size)
		{
			dwSize += sizeof(BinaryMember);
			dwSize += item->size;
			item = (BinaryMember*)(&item->data[item->size]);
		}
	}

	item = (BinaryMember*)(&item->data[dwSize]);
	item->type = BINARY_USER_NULL;
	item->size = 0;
	dwSize += sizeof(BinaryMember) + 0;

	return dwSize;
}
