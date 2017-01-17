#include "WorldServer_PCH.h"
#include "ProcFepHandler.h"

ProcFepHandler::ProcFepHandler()
{

}


ProcFepHandler::~ProcFepHandler()
{

}

void ProcFepHandler::RqPlayerExit(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const F2WRqPlayerExit* packet = static_cast<const F2WRqPlayerExit*>(pMsg);
	WorldUser* user = NetService::getMe().getWorldUserMgr().getBySessID(packet->sessid);
	if (user)
	{
		NetService::getMe().getWorldUserMgr().remove(user);
		NetService::getMe().getWorldUserMgr().DestroyObj(user);
	}
}

void ProcFepHandler::RqSelectRole(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C2WSelectRole* packet = static_cast<const C2WSelectRole*>(pMsg);
	WorldUser* oldUser = NetService::getMe().getWorldUserMgr().get(packet->uid);
	if (oldUser) // 有两个号在登录 
	{
		//请求断开并交换内存，这里不选择重新加载内存原因是加载不到最新的
		//通过原有的内存修改所属最为方便
		zSession* fepSession = static_cast<zSession*>(pSession);
		if (oldUser->sessid != packet->sessid || oldUser->fepSession != fepSession)
		{
			NetService::getMe().getWorldUserMgr().remove(oldUser);
			oldUser->sessid = packet->sessid;
			if (!NetService::getMe().getWorldUserMgr().add(oldUser))
			{
				Zebra::logger->error("添加角色内存失败");
				NetService::getMe().getWorldUserMgr().remove(oldUser);
				return;
			}
			oldUser->fepSession = fepSession;

			//oldUser->SendToFep(); 
			//oldUser->SendSs();
		}
		else
		{
			Zebra::logger->warn("重复请求加载内存");
		}
		return;
	}
	else
	{
		// 加载基本的数据
		const dbCol selectFields[] =
		{
			{ "ID",DB_QWORD,sizeof(int64) },
			{ "ACCID",DB_QWORD,sizeof(int64) },
			{ "NAME",DB_STR,MAX_NAMESIZE + 1 },
			{ "LEVEL",DB_WORD,sizeof(int16) },
			{ "SCENEID",DB_QWORD,sizeof(int64)},
			{ "MAPID",DB_DWORD,sizeof(int32)},
			{ NULL,0,0 }
		};

#pragma pack(push,1)
		struct MyUser
		{
			int64 id;
			int64 accid;
			char name[MAX_NAMESIZE + 1];
			int16 level;
			int64 sceneid;
			int32 mapid;
		};
#pragma pack(pop)

		MyUser data;
		char wheres[100];
		memset(wheres, 0, sizeof(wheres));
		sprintf(wheres, "`id`=%lld", packet->uid);
		int32 retsize = NetService::getMe().getDbMysql()->ExecSelectLimit("User", selectFields, wheres, NULL, (unsigned char*)&data, 1);
		if (retsize < 1)                                                                                                                                                                                                                                                                                                 
		{
			Zebra::logger->error("加载角色内存失败，找不到数据");
			return;
		}

		WorldUser* newUser = NetService::getMe().getWorldUserMgr().CreateObj();
		newUser->id = data.id;
		newUser->sessid = packet->sessid;
		strncpy(newUser->name,data.name,MAX_NAMESIZE);
		newUser->level = data.level;
		newUser->sceneid = data.sceneid;
		newUser->mapid = data.mapid;

		if (!NetService::getMe().getWorldUserMgr().add(newUser))
		{
			Zebra::logger->error("加载角色内存失败，数据Key有重复");
			NetService::getMe().getWorldUserMgr().remove(newUser);
			return;
		}

		newUser->fepSession = static_cast<zSession*>(pSession);

		SceneReg* reg = SceneRegMgr::getMe().get(newUser->sceneid);
		if(reg)
		{
			zSession* ss = NetService::getMe().getSessionMgr().get(reg->sessid);
			if (ss)
			{
				newUser->sceneSession = ss;
			}
		}

		newUser->level = data.level;
		newUser->mapid = data.mapid;
		newUser->sceneid = data.sceneid;
		newUser->enterscenetime = Zebra::timeTick->getNowTime();


		// 发送到指定的场景->网关 
		W2SRqEnterScene send;
		send.fepsid = packet->fepsid;
		send.sessid = packet->sessid;
		send.uid = packet->uid;
		send.mapid = newUser->mapid;
		send.sceneid = newUser->sceneid;
		send.enterscenetime = newUser->enterscenetime;

		// 其他参数 

		newUser->sendToSs(&send,send.GetPackLength());
		

	}

}

void ProcFepHandler::RqCreateRole(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{	
	const C2WCreateRole* packet = static_cast<const C2WCreateRole*>(pMsg);
	if (!NetService::getMe().getWorldUserMgr().checkmd5(packet->accid, packet->keytime, packet->keymd5))
	{
		return;
	}
			  
	char wheres[100];
	const dbCol findFields[] =
	{
		{ "id",DB_QWORD,sizeof(int64) },
		{ NULL,0,0 }
	};
#pragma pack(push,1)
	struct MyUserID
	{
		int64 id;
		MyUserID()
		{
			id = 0;
		}
	};
#pragma pack(pop)

	int32 reason = 0;
	int64 newid = 0;
	MyUserID* dataList;
	memset(wheres, 0, sizeof(wheres));
	sprintf(wheres, "`accid`=%lld AND `status`=0", packet->accid);
	int32 retsize = NetService::getMe().getDbMysql()->ExecSelect("User", findFields, wheres, NULL, (unsigned char**)&dataList);
	if (retsize >= MAX_ROLENUM)
	{
		reason = 1;
		SAFE_DELETE_VEC(dataList);
	}
	else
	{
		MyUserID dataN;
		memset(wheres, 0, sizeof(wheres));
		sprintf(wheres, "`name`='%s'", packet->name);
		retsize = NetService::getMe().getDbMysql()->ExecSelectLimit("User", findFields, wheres, NULL, (unsigned char*)&dataN);
		if (retsize)
		{
			Zebra::logger->warn("角色名重复");
			reason = 2;
		}
		else
		{
			const dbCol MaxIdFields[] =
			{
				{ "id",DB_QWORD,sizeof(int64) },
				{ NULL,0,0 }
			};

			char orders[100];
			memset(orders, 0, sizeof(orders));
			sprintf(orders, "`id` DESC");

			MyUserID maxID;
			retsize = NetService::getMe().getDbMysql()->ExecSelectLimit("User", findFields, NULL, orders, (unsigned char*)&maxID);
			if (retsize < 0)
			{
				Zebra::logger->error("获得最大角色ID失败");
				reason = 3;
			}
			else
			{                            
				if (maxID.id == 0)
				{
					maxID.id = 100000000;
				}

				newid = maxID.id + 1;

#pragma pack(push,1)
				struct DCreateUser
				{
					UserSceneBase base;
					int32 size;
					char data[0];
				};

#pragma pack(pop)

				static char buffer[10000];
				memset(buffer, 0, sizeof(buffer));
				DCreateUser* data = (DCreateUser*)buffer;
				data->base.id = newid;
				data->base.accid = packet->accid;
				strncpy(data->base.name, packet->name, MAX_NAMESIZE);
				data->base.level = 100;
				data->base.status = 0;
				data->base.sceneid = 40104;
				data->base.mapid = 104;
				data->size = 0;
				int32 ret = NetService::getMe().getDbMysql()->ExecInsert("User", user_columns, (const char*)data);
				if (ret != 0)
				{
					Zebra::logger->error("创建新角色失败");
					reason = 3;
				}
			}
		}
	}

	W2CCreateRet sendRet;
	sendRet.sessid = packet->sessid;
	sendRet.fepsid = packet->fepsid;
	sendRet.reasoin = reason;
	pSession->sendMsg(&sendRet,sendRet.GetPackLength());

	if (reason == 0)
	{
		NetService::getMe().getWorldUserMgr().sendRoleList(packet->accid, packet->fepsid, packet->sessid);
	}

}

void ProcFepHandler::RqDeleteRole(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C2WDeleteRole* packet = static_cast<const C2WDeleteRole*>(pMsg);
	if (!NetService::getMe().getWorldUserMgr().checkmd5(packet->accid, packet->keytime, packet->keymd5))
	{
		return;
	}
	
	const dbCol updateFields[] =
	{
		{ "status",DB_BYTE,sizeof(int8) },
		{ NULL,0,0 }
	};
#pragma pack(push,1)
	struct MyStatus
	{
		int8 status;
		MyStatus()
		{
			status = 0;
		}
	};
#pragma pack(pop)

	int32 reason = 0;
	int64 newid = 0;
	MyStatus dataStatus;
	dataStatus.status = 1;
	char wheres[100];
	memset(wheres, 0, sizeof(wheres));
	sprintf(wheres, "`id`=%lld AND `accid`=%lld", packet->uid, packet->accid);
	int32 retsize = NetService::getMe().getDbMysql()->ExecUpdate("User",updateFields,(const char*)&dataStatus,wheres);
	if (retsize != 0)
	{
		Zebra::logger->error("删除角色失败");
	}
	else
	{
		NetService::getMe().getWorldUserMgr().sendRoleList(packet->accid, packet->fepsid, packet->sessid);
	}
}
