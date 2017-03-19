#include "WorldServer_PCH.h"
#include "ProcFepHandler.h"

ProcFepHandler::ProcFepHandler()
{

}


ProcFepHandler::~ProcFepHandler()
{

}

void ProcFepHandler::doLoginTask(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void ProcFepHandler::doPlayerExit(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSNtRqPlayerExit* packet = static_cast<const  S::SSNtRqPlayerExit*>(pMsg);
	WorldUser* user = GameService::getMe().getWorldUserMgr().getBySessID(packet->sessid);
	if (user)
	{
		GameService::getMe().getWorldUserMgr().remove(user);
		GameService::getMe().getWorldUserMgr().DestroyObj(user);
	}
}

void ProcFepHandler::doSelectRole(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const  C::RqSelectRole* packet = static_cast<const  C::RqSelectRole*>(pMsg);
	WorldUser* oldUser = GameService::getMe().getWorldUserMgr().get(packet->uid);
	if (oldUser) // 有两个号在登录 
	{
		//请求断开并交换内存，这里不选择重新加载内存原因是加载不到最新的
		//通过原有的内存修改所属最为方便
		zSession* fepSession = static_cast<zSession*>(pSession);
		if (oldUser->sessid != packet->sessid || oldUser->fepSession != fepSession)
		{
			GameService::getMe().getWorldUserMgr().remove(oldUser);
			oldUser->sessid = packet->sessid;
			if (!GameService::getMe().getWorldUserMgr().add(oldUser))
			{
				H::logger->error("添加角色内存失败");
				GameService::getMe().getWorldUserMgr().remove(oldUser);
				return;
			}
			oldUser->fepSession = fepSession;

			//oldUser->SendToFep(); 
			//oldUser->SendSs();
		}
		else
		{
			H::logger->warn("重复请求加载内存");
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
		int32 retsize = GameService::getMe().getDbMysql()->ExecSelectLimit("USER", selectFields, wheres, NULL, (unsigned char*)&data, 1);
		if (retsize < 1)                                                                                                                                                                                                                                                                                                 
		{
			H::logger->error("加载角色内存失败，找不到数据");
			return;
		}

		WorldUser* newUser = GameService::getMe().getWorldUserMgr().CreateObj();
		newUser->id = data.id;
		newUser->sessid = packet->sessid;
		strncpy(newUser->name,data.name,MAX_NAMESIZE);
		newUser->level = data.level;
		newUser->sceneid = data.sceneid;
		newUser->mapid = data.mapid;

		if (!GameService::getMe().getWorldUserMgr().add(newUser))
		{
			H::logger->error("加载角色内存失败，数据Key有重复");
			GameService::getMe().getWorldUserMgr().remove(newUser);
			return;
		}

		newUser->fepSession = static_cast<zSession*>(pSession);

		SceneReg* reg = SceneRegMgr::getMe().get(newUser->sceneid);
		if(reg)
		{
			zSession* ss = GameService::getMe().getSessionMgr().get(reg->sessid);
			if (ss)
			{
				newUser->sceneSession = ss;
			}
		}

		newUser->level = data.level;
		newUser->mapid = data.mapid;
		newUser->sceneid = data.sceneid;
		newUser->enterscenetime = H::timeTick->now();


		// 发送到指定的场景->网关 
		S::SSRqEnterScene send;
		send.fepsid = packet->fepsid;
		send.sessid = packet->sessid;
		send.uid = packet->uid;
		send.mapid = newUser->mapid;
		send.sceneid = newUser->sceneid;
		send.enterscenetime = newUser->enterscenetime;

		// 其他参数 

		newUser->sendToSs(&send,sizeof(send));
		

	}

}

void ProcFepHandler::doCreateRole(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{	
	const C::RqCreateRole* packet = static_cast<const C::RqCreateRole*>(pMsg);
	if (!GameService::getMe().getWorldUserMgr().checkmd5(packet->accid, packet->keytime, packet->keymd5))
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
	int32 retsize = GameService::getMe().getDbMysql()->ExecSelect("USER", findFields, wheres, NULL, (unsigned char**)&dataList);
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
		retsize = GameService::getMe().getDbMysql()->ExecSelectLimit("USER", findFields, wheres, NULL, (unsigned char*)&dataN);
		if (retsize)
		{
			H::logger->warn("角色名重复");
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
			retsize = GameService::getMe().getDbMysql()->ExecSelectLimit("USER", findFields, NULL, orders, (unsigned char*)&maxID);
			if (retsize < 0)
			{
				H::logger->error("获得最大角色ID失败");
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
					S::t_UserSceneBase base;
					int32 size;
					BinaryHeader header;
				};

#pragma pack(pop)

				static char buffer[MAX_USERDATASIZE];
				memset(buffer, 0, sizeof(buffer));
				DCreateUser* data = (DCreateUser*)buffer;
				data->base.id = newid;
				data->base.accid = packet->accid;
				strncpy(data->base.name, packet->name, MAX_NAMESIZE);
				data->base.level = 100;
				data->base.status = 0;
				data->base.sceneid = 40104;
				data->base.mapid = 104;
				data->header.version = 0;
				data->header.size = 0;

				// 填充二进制数据 
				int32 dwSize = 0;
				BinaryMember* pMember = (BinaryMember*)(&data->header.data[data->header.size]);
				pMember->type = BINARY_USER_NULL;
				pMember->size = 0;
				dwSize += sizeof(BinaryMember);
				dwSize += pMember->size;
				data->header.size = dwSize;
				data->size += sizeof(data->header);
				data->size += data->header.size;
				int32 ret = GameService::getMe().getDbMysql()->ExecInsert("USER", S::user_columns, (const char*)data);
				if (ret != 0)
				{
					H::logger->error("创建新角色失败");
					reason = 3;
				}
			}
		}
	}

	C::RtCreateRet sendRet;
	sendRet.sessid = packet->sessid;
	sendRet.fepsid = packet->fepsid;
	sendRet.reasoin = reason;
	pSession->sendMsg(&sendRet,sizeof(sendRet));

	if (reason == 0)
	{
		GameService::getMe().getWorldUserMgr().sendRoleList(packet->accid, packet->fepsid, packet->sessid);
	}

}

void ProcFepHandler::doDeleteRole(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C::RqDeleteRole* packet = static_cast<const C::RqDeleteRole*>(pMsg);
	if (!GameService::getMe().getWorldUserMgr().checkmd5(packet->accid, packet->keytime, packet->keymd5))
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
	int32 retsize = GameService::getMe().getDbMysql()->ExecUpdate("USER",updateFields,(const char*)&dataStatus,wheres);
	if (retsize != 0)
	{
		H::logger->error("删除角色失败");
	}
	else
	{
		GameService::getMe().getWorldUserMgr().sendRoleList(packet->accid, packet->fepsid, packet->sessid);
	}
}

void ProcFepHandler::doMessageTask(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	GameService::getMe().getMessageMgr().doUserCmd(pSession, pMsg, nSize);
}
