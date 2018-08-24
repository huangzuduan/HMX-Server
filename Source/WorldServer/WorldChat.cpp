#include "WorldServer.h"
#include "WorldUser.h"
#include "GameService.h"

extern DWORD cancel_country_need_money;
extern DWORD is_cancel_country;


template<typename TMsg>
struct MsgSendToAllFep : public execEntry<zSession>
{
	MsgSendToAllFep(TMsg* __msg, int32_t __size) :_msg(__msg), _size(__size)
	{
	}
	virtual bool exec(zSession *entry)
	{
		if (entry->GetRemoteServerType() == 1)
		{
			entry->sendMsg(_msg, _size);
		}
		return true;
	}
	TMsg* _msg;
	int32_t _size;
};


/*
* \brief 向用户发送消息
* 如果用户不在该服务器,就由session转发
*
* \param id 用户的ID
* \param cmd 消息
* \param len 消息长度
*
* \return 是否成功
*/
bool sendCmdByID(DWORD id, const void *cmd, int len)
{

	return true;
}


/*
* \brief 向用户发送消息
* 如果用户不在该服务器,就由session转发
*
* \param id 用户的临时ID
* \param cmd 消息
* \param len 消息长度
*
* \return 是否成功
*/
bool sendCmdByTempID(DWORD id, const void *cmd, int len)
{

	return true;
}


/*
* \brief 向用户发送消息
* 如果用户不在该服务器,就由session转发
*
* \param name 用户的名字
* \param cmd 消息
* \param len 消息长度
*
* \return 是否成功
*/
bool sendCmdByName(char * name, const void *cmd, int len)
{

	return true;
}

/**
* \brief 构造函数
*
*
* \param user: 创建该频道的用户
*/
WorldChannel::WorldChannel() :zEntry()
{
}

WorldChannel::~WorldChannel()
{

}

//const dbCol chat_fields[] =
//{
//	{ "ID",DB_QWORD,sizeof(int64_t) },
//	{ "NAME",DB_STR,MAX_NAMESIZE + 1 },
//	{ "INFO",DB_BIN2,0 },
//	{ NULL,0,0 }
//};

#pragma pack(push,1)
struct stChatmsgRecord
{
	int64_t id;
	char name[MAX_NAMESIZE + 1];
	int32_t size;
	char data[0];
};
#pragma pack(pop)


bool WorldChannel::loadDB()
{
	//BUFFER_CMD(stChatmsgRecord, data, MAX_USERDATASIZE);

	//char wheres[100];
	//memset(wheres, 0, sizeof(wheres));
	//sprintf(wheres, "`id`=%lld", this->id);
	//
	//int ret = GameService::getMe().getDbMysql()->ExecSelectLimit("Chatmsg", chat_fields, wheres, NULL, (unsigned char*)data);
	//if (ret == 1)
	//{
	//	strncpy(this->name, data->name, MAX_NAMESIZE);
	//	// 解析二进制数据
	//	::protobuf::ChatMsgBinary proto;
	//	proto.ParseFromArray(data->data, data->size);
	//	unserialize(proto);
	//	return true;
	//}
	//else
	//{
	//	H::logger->error("加载频道内存失败，找不到数据");
	//	return false;
	//}
	return true;
}

void WorldChannel::saveDB()
{
	/*BUFFER_CMD(stChatmsgRecord, data, MAX_USERDATASIZE);

	data->id = this->id;
	strncpy(data->name, this->name, MAX_NAMESIZE);

	::protobuf::ChatMsgBinary proto;
	serialize(proto);
	data->size = proto.ByteSize();
	proto.SerializeToArray(data->data, MAX_USERDATASIZE);

	static char wheres[100];
	memset(wheres, 0, sizeof(wheres));
	sprintf(wheres, "`id`=%llu", this->id);

	int ret = GameService::getMe().getDbMysql()->ExecUpdate("Chatmsg", chat_fields, (const char*)data, wheres);
	if (ret == 0)
	{
		H::logger->info("保存频道成功!");
	}
	else
	{
		H::logger->error("保存频道失败!");
	}*/
}

/**
* \brief 发送给该频道的所有用户
*
*
* \param cmd: 聊天内容
* \param len:内容长度
* \return 发送是否成功
*/
bool WorldChannel::sendCmdToAll(const NetMsgSS *cmd, int len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = 0;
	//send->size = len;
	//memcpy(send->data, cmd, len);

	//MsgSendToAllFep<S::SSNtBoradCastMsg> exec(send,sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);

	return true;
}

/**
* \brief 转发聊天信息到9屏
*
*
* \param user: 请求发送者
* \param rev: 转发的内容
* \param cmdLen: 内容长度
* \return 发送是否成功
*/
bool WorldChannel::sendNine(WorldChannel::UserData *user, const NetMsgSS *cmd, DWORD len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = 0;
	//send->size = len;
	//memcpy(send->data, cmd, len);
	//MsgSendToAllFep<S::SSNtBoradCastMsg> exec(send,sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);
	return true;
}

#define getMessage(msg,msglen,pat)  \
	do  \
{  \
	va_list ap;  \
	bzero(msg,msglen);  \
	va_start(ap,pat);    \
	vsnprintf(msg,msglen - 1,pat,ap);  \
	va_end(ap);  \
}while(false)


/**
* \brief 请求发送信息到国家频道
*
*
* \param user: 请求指令的用户
* \param rev: 收到的指令
* \param cmdLen: 指令长度
* \return 发送是否成功
*/
bool WorldChannel::sendCountry(WorldChannel::UserData *user, const NetMsgSS *cmd, DWORD len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = 0;
	//send->size = len;
	//memcpy(send->data, cmd, len);
	//MsgSendToAllFep<S::SSNtBoradCastMsg> exec(send, sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);
	return true;
}


/**
* \brief 发送给该地图的所有用户
*
* \param mapID 地图ID
* \param cmd 消息
* \param len: 长度
* \return 发送是否成功
*/
bool WorldChannel::sendCmdToMap(DWORD mapID, const NetMsgSS *cmd, int len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = mapID;
	//send->size = len;
	//memcpy(send->data, cmd, len);
	//MsgSendToAllFep<S::SSNtBoradCastMsg> exec(send, sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);
	return true;
}

/**
* \brief 私聊
*
*
* \param user: 请求发送者
* \param rev:请求指令
* \param cmdLen: 指令长度
* \return 发送是否成功
*/
bool WorldChannel::sendPrivate(WorldChannel::UserData *user, const NetMsgSS *rev, DWORD cmdLen)
{

	return true;
}

bool WorldChannel::sendTeam(QWORD teamid, const NetMsgSS *cmd, DWORD len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = teamid;
	//send->size = len;
	//memcpy(send->data, cmd, len);
	//MsgSendToAllFep<S::SSNtBoradCastMsg> exec(send, sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);
	return true;
}

/**
* \brief 唯一实例
*
*/
WorldChannelM::WorldChannelM()
{

	maxid = 0;
}

WorldChannelM::~WorldChannelM()
{
	
}

void WorldChannelM::loadDB()
{
//	const dbCol msg_id[] =
//	{
//		{ "ID",DB_QWORD,sizeof(QWORD) },
//		{ NULL,0,0 },
//	};
//
//#pragma pack(push,1)
//	struct dbUserID
//	{
//		QWORD id;
//	};
//#pragma pack(pop)
//
//	dbUserID* dataList, *dataTmp;
//	int ret = GameService::getMe().getDbMysql()->ExecSelect("Chatmsg", msg_id, NULL, NULL, (unsigned char**)&dataList);
//	if (ret > 0)
//	{
//		int loadcount = 0;
//		int failcount = 0;
//		for (int c = 0; c < ret; ++c)
//		{
//			dataTmp = &dataList[c];
//			WorldChannel* channel = CreateObj();
//			channel->id = dataTmp->id;
//			if (channel->loadDB() && add(channel))
//			{
//				loadcount++;
//			}
//			else
//			{
//				failcount++;
//				H::logger->error("加载频道失败[ID:%lld]", channel->id);
//				remove(channel);
//			}
//		}
//
//		S_SAFE_DELETE_VEC(dataList);
//		H::logger->info("共%d条数据，成功加载%d条,失败%d条", ret, loadcount, failcount);
//
//	}
}

/**
* \brief 增加聊天频道
*
*
* \param channel: 频道
* \return 增加是否成功
*/
bool WorldChannelM::add(WorldChannel *channel)
{
	return zEntryMgr< zEntryID<0>, zEntryID<1>, zEntryName >::addEntry(channel);
}

/**
* \brief 从聊天频道中删除一个聊天频道
*
*
* \param dwChannelID: 频道id
*/
void WorldChannelM::remove(WorldChannel* channel)
{
	zEntryMgr< zEntryID<0>, zEntryID<1>, zEntryName  >::removeEntry(channel);
}

/**
* \brief 得到一个聊天频道
*
*
* \param dwChannelID: 频道id
* \return 聊天频道
*/
WorldChannel *WorldChannelM::get(QWORD dwChannelID)
{
	return (WorldChannel *)zEntryID<0>::getEntryByID(dwChannelID);
}

/**
* \brief 将16进制数转为10进制
*
*
* \param ch: 16进制字符
* \return 转换猴的10进制数
*/
BYTE hexchtoi(char &ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return BYTE(ch - '0');
	}
	else if ((ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))
	{
		return BYTE(toupper(ch) - 'A') + 10;
	}
	return 0;
}



