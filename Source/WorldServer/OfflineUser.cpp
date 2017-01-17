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

	const dbCol user_fields[] =
	{
		{ "ID",DB_QWORD,sizeof(int64) },
		{ "NAME",DB_STR,MAX_NAMESIZE + 1 },
		{ "LEVEL",DB_WORD,sizeof(int16) },
		{ "VIP",DB_BYTE,sizeof(int8) },
		{ "COUNTRY",DB_BYTE,sizeof(int8) },
		{ "TEAMID",DB_DWORD,sizeof(int32) },
		{ NULL,0,0 }
	};

#pragma pack(push,1)
	struct stUserRecord
	{
		int64 id;
		char name[MAX_NAMESIZE + 1];
		int16 level;
		int8 vip;
		int8 country;
		int32 teamid;
	};
#pragma pack(pop)

	stUserRecord data;
	char wheres[100];
	memset(wheres, 0, sizeof(wheres));
	sprintf(wheres, "`id`=%lld", this->id);
	int32 retsize = NetService::getMe().getDbMysql()->ExecSelectLimit("User", user_fields, wheres, NULL, (unsigned char*)&data, 1);
	if (retsize < 1)
	{
		Zebra::logger->error("加载角色内存失败，找不到数据");
		return false;
	}

	strncpy(this->name,data.name,MAX_NAMESIZE);
	this->level = data.level;
	this->vip = data.vip;
	this->country = data.country;
	this->teamid = data.teamid;

	return true;
}
