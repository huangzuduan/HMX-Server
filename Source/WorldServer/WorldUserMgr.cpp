#include "WorldServer_PCH.h"
#include "WorldUserMgr.h"
#include "SceneRegMgr.h"

WorldUserMgr::WorldUserMgr()
{

}

WorldUserMgr::~WorldUserMgr()
{

}

bool WorldUserMgr::getUniqeID(QWORD& tempid)
{
	return true;
}

void WorldUserMgr::putUniqeID(const QWORD& tempid)
{
}

WorldUser* WorldUserMgr::CreateObj()
{
	return objpool.CreateObj();
}

void WorldUserMgr::DestroyObj(WorldUser* user)
{
	objpool.DestroyObj(user);
}

bool WorldUserMgr::add(WorldUser *user)
{
	return zEntryMgrsessid::addEntry(user);
}

WorldUser* WorldUserMgr::get(QWORD id)
{
	return (WorldUser*)zEntryMgrsessid::getEntryByID(id);
}

WorldUser* WorldUserMgr::getBySessID(QWORD sessid)
{
	return (WorldUser*)getEntryBysessid(sessid);
}

WorldUser* WorldUserMgr::getByName(const char* name)
{
	return (WorldUser*)zEntryMgrsessid::getEntryByName(name);
}

void WorldUserMgr::remove(WorldUser* user)
{
	zEntryMgrsessid::removeEntry(user);
}

//////////////////////////////////////////////////////////////////////////

bool WorldUserMgr::checkmd5(int64 accid, int32 keytime, const char* keymd5)
{
	// 校验md5
	std::ostringstream outstr;
	outstr << accid;
	outstr << SERVERKEY;
	outstr << keytime;

	unsigned char makeKeymd5[MAX_NAMESIZE + 1];
	memset(makeKeymd5, 0, sizeof(makeKeymd5));
	EncryptMD5(makeKeymd5, (unsigned char*)outstr.str().c_str());
	makeKeymd5[MAX_NAMESIZE] = '\0';

	char reciveKeymd5[MAX_NAMESIZE + 1];
	memset(reciveKeymd5, 0, sizeof(reciveKeymd5));
	strncpy(reciveKeymd5, keymd5, MAX_NAMESIZE);

	if (stricmp((const char*)makeKeymd5, (const char*)reciveKeymd5) != 0)
	{
		H::logger->error("Md5检验失败，密钥不匹配 需要:%s,传入:%s", makeKeymd5, reciveKeymd5);
		return false;
	}

	if (keytime + 86400 < H::timeTick->now())
	{
		H::logger->error("Md5检验失败,时间过期");
		return false;
	}

	return true;
}

void WorldUserMgr::sendRoleList(int64 accid, int64 fepsid, int64 sessid)
{
	char wheres[100];
	memset(wheres, 0, sizeof(wheres));
	sprintf(wheres, "`accid`=%lld AND `status`=%d", accid, 0);

	const dbCol fields[] =
	{
		{ "id",DB_QWORD,sizeof(int64) },
		{ "name",DB_STR,MAX_NAMESIZE +1 },
		{ "level",DB_WORD,sizeof(int16) },
		{ NULL,0,0 }
	};

#pragma pack(push,1)
	struct MyStruct
	{
		int64 id;
		char name[MAX_NAMESIZE + 1];
		int16 level;
		MyStruct()
		{
			id = level = 0;
			memset(name, 0, sizeof(name));
		}
	};
#pragma pack(pop)

	MyStruct* dataList, *dataTmp;
	int32 retsize = GameService::getMe().getDbMysql()->ExecSelect("USER", fields, wheres, NULL, (unsigned char**)&dataList);
	if (retsize < 0)
	{
		H::logger->warn("获取角色列表失败");
	}

	C::RtUserListLogon send;
	if (retsize && dataList)
	{
		dataTmp = &dataList[0];
		for (int i = 0; i < retsize && i < sizeof(send.datas) / sizeof(send.datas[0]); ++i)
		{
			send.datas[i].id = dataTmp->id;
			send.datas[i].level = dataTmp->level;
			strncpy(send.datas[i].name, dataTmp->name, MAX_NAMESIZE);
			dataTmp++;
		}
		SAFE_DELETE_VEC(dataList);
	}

	if (sessid && fepsid) // 转发到fep 
	{
		zSession* fepSs = GameService::getMe().getSessionMgr().getFep(fepsid);
		if (fepSs)
		{
			send.sessid = sessid;
			send.fepsid = fepsid;
			fepSs->sendMsg(&send, sizeof(send));
			return;
		}
		else
		{
			H::logger->error("fepsid=%lld有误,",fepsid);
			ASSERT(0);
			return;
		}
	}
	else
	{
		H::logger->error("sessid=%lld或fepsid=%lld有误,",sessid,fepsid);
		ASSERT(0);
		return;
	}
}