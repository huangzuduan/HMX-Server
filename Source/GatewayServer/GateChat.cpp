#include "GatewaysServer.h"
#include "GateUser.h"

extern DWORD cancel_country_need_money;
extern DWORD is_cancel_country;


template<typename TMsg>
struct MsgSendToAllPlayer : public execEntry<zSession>
{
	MsgSendToAllPlayer(TMsg* __msg, int32 __size) :_msg(__msg), _size(__size)
	{
	}
	virtual bool exec(zSession *entry)
	{
		if (entry->sessionType == zSession::FOR_PLAYER)
		{
			PlayerMsgHandler::getMe().SendToPlayer(entry, _msg, _size);
		}
		return true;
	}
	TMsg* _msg;
	int32 _size;
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
* \param pUser: 创建该频道的用户
*/
GateChannel::GateChannel(GateUser *pUser) :zEntry()
{
	creater.id = pUser->id;
	creater.tempid = pUser->tempid;
	strncpy(creater.name, pUser->name, MAX_NAMESIZE);
}

GateChannel::GateChannel(DWORD chID, const std::string& _name)
{
	creater.id = chID;
	creater.tempid = chID;
	strncpy(creater.name, _name.c_str(), MAX_NAMESIZE);
}

GateChannel::~GateChannel()
{

}

/**
* \brief 发送给该频道的所有用户
*
*
* \param cmd: 聊天内容
* \param len:内容长度
* \return 发送是否成功
*/
bool GateChannel::sendCmdToAll(const NetMsgSS *cmd, int len)
{
	BUFFER_CMD(S2FBoradCastMsg, send, MAX_BUFFERSIZE);
	send->msgtype = BORADCAST_TYPE_ALL;
	send->regid = 0;
	send->size = len;
	memcpy(send->data, cmd, len);

	MsgSendToAllPlayer<S2FBoradCastMsg> exec(send,sizeof(S2FBoradCastMsg) + send->size * sizeof(send->data[0]));
	NetService::getMe().getSessionMgr().execEveryConn(exec);

	return true;
}

/**
* \brief 离开频道
*
*
* \param uname: 离开该频道的用户
* \return 该频道是否还能继续存在
*/
bool GateChannel::remove(const char *uname)
{
	WORD found = has(uname);
	if (found != (WORD)-1)
	{
		Zebra::logger->info("%s离开%s的聊天频道", uname, creater.name);
		S2CChannelLeave send;
		send.channelID = tempid;
		strncpy(send.name, uname, MAX_NAMESIZE);
		sendCmdToAll(&send, sizeof(send));

		if ((found + 1) < (WORD)userlist.size())
		{
			userlist[found] = userlist.back();
		}
		userlist.pop_back();
	}
	if (userlist.empty())
		return false;
	else
		return true;
}

/**
* \brief 加入聊天频道
*
*
* \param pUser: 要加入的用户
* \return 加入是否成功
*/
bool GateChannel::add(GateUser *pUser)
{
	if (pUser != NULL)
	{
		WORD found = has(pUser->name);
		if (found == (WORD)-1)
		{
			Zebra::logger->info("%s加入%s的聊天频道", Utf8ToGBK(pUser->name), creater.name);

			zEntryC temp;
			temp.id = pUser->id;
			temp.tempid = pUser->tempid;
			strncpy(temp.name, pUser->name, MAX_NAMESIZE);
			userlist.push_back(temp);

			/* 把自己发送给所有人 */
			S2CChannelJion send;
			send.channelID = tempid;
			strncpy(send.name, pUser->name, MAX_NAMESIZE);
			sendCmdToAll(&send, sizeof(send));

			/* 发送所有成员给自己 */
			//for (DWORD i = 0; i < userlist.size(); i++)
			//{
			//	strncpy(send.name, userlist[i].name, MAX_NAMESIZE);
			//	pUser->send(&send, sizeof(send));
			//}
			return true;
		}
	}
	return false;
}

/**
* \brief 聊天频道中是否存在某人
*
*
* \param name: 用户名
* \return 存在返回该用户在频道中的位置,不存在返回-1
*/
WORD GateChannel::has(const char *name)
{
	if (name)
	{
		for (DWORD i = 0; i < userlist.size(); i++)
		{
			if (strncmp(userlist[i].name, name, MAX_NAMESIZE) == 0)
				return i;
		}
	}
	return (WORD)-1;
}

/**
* \brief 转发聊天信息到9屏
*
*
* \param pUser: 请求发送者
* \param rev: 转发的内容
* \param cmdLen: 内容长度
* \return 发送是否成功
*/
bool GateChannel::sendNine(GateUser *pUser, const NetMsgSS *cmd, DWORD len)
{
	BUFFER_CMD(S2FBoradCastMsg, send, MAX_BUFFERSIZE);
	send->msgtype = BORADCAST_TYPE_ALL;
	send->regid = 0;
	send->size = len;
	memcpy(send->data, cmd, len);
	MsgSendToAllPlayer<S2FBoradCastMsg> exec(send,sizeof(S2FBoradCastMsg) + send->size * sizeof(send->data[0]));
	NetService::getMe().getSessionMgr().execEveryConn(exec);
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
* \brief 发送国家公告
*
*
* \param countryID: countryID
* \param infoType: infoType
* \param pattern: 内容
* \return 发送是否成功
*/
bool GateChannel::sendCountryInfo(DWORD countryID, DWORD infoType, const char *pattern, ...)
{

	return true;
}

/**
* \brief 发送全服公告
*
* \param infoType: infoType
* \param pattern: 内容
* \return 发送是否成功
*/
bool GateChannel::sendAllInfo(DWORD infoType, const char *pattern, ...)
{

	return true;
}

/**
* \brief 发送信息到国家频道
*
*
* \param pUser: 请求发送者
* \param pattern: 内容
* \return 发送是否成功
*/
bool GateChannel::sendCountry(GateUser *pUser, const char *pattern, ...)
{

	return true;
}

/**
* \brief 请求发送信息到国家频道
*
*
* \param pUser: 请求指令的用户
* \param rev: 收到的指令
* \param cmdLen: 指令长度
* \return 发送是否成功
*/
bool GateChannel::sendCountry(GateUser *pUser, const NetMsgSS *cmd, DWORD len)
{
	BUFFER_CMD(S2FBoradCastMsg, send, MAX_BUFFERSIZE);
	send->msgtype = BORADCAST_TYPE_ALL;
	send->regid = 0;
	send->size = len;
	memcpy(send->data, cmd, len);
	MsgSendToAllPlayer<S2FBoradCastMsg> exec(send, sizeof(S2FBoradCastMsg) + send->size * sizeof(send->data[0]));
	NetService::getMe().getSessionMgr().execEveryConn(exec);
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
bool GateChannel::sendCmdToMap(DWORD mapID, const NetMsgSS *cmd, int len)
{
	BUFFER_CMD(S2FBoradCastMsg, send, MAX_BUFFERSIZE);
	send->msgtype = BORADCAST_TYPE_ALL;
	send->regid = mapID;
	send->size = len;
	memcpy(send->data, cmd, len);
	MsgSendToAllPlayer<S2FBoradCastMsg> exec(send, sizeof(S2FBoradCastMsg) + send->size * sizeof(send->data[0]));
	NetService::getMe().getSessionMgr().execEveryConn(exec);
	return true;
}

/**
* \brief 转发队伍信息
*
*
* \param teamid: 队伍id
* \param rev: 需要转发的指令
* \param cmdLen: 指令长度
* \return 转发是否成功
*/
bool GateChannel::sendTeam(DWORD teamid, const NetMsgSS *cmd, DWORD len)
{
	BUFFER_CMD(S2FBoradCastMsg, send, MAX_BUFFERSIZE);
	send->msgtype = BORADCAST_TYPE_ALL;
	send->regid = teamid;
	send->size = len;
	memcpy(send->data, cmd, len);
	MsgSendToAllPlayer<S2FBoradCastMsg> exec(send, sizeof(S2FBoradCastMsg) + send->size * sizeof(send->data[0]));
	NetService::getMe().getSessionMgr().execEveryConn(exec);
	return true;
}

/**
* \brief 发送系统消息
*
*
* \param pUser: 要求发送消息的用户
* \param type: 系统消息类型
* \param pattern: 内容
* \return 发送是否成功
*/
bool GateChannel::sendSys(GateUser *pUser, int type, const char *pattern, ...)
{

	return false;
}

bool GateChannel::sendSys(DWORD dwUserTempID, int type, const char *pattern, ...)
{
	//GateUser *pToUser = GateUserManager::getMe().getUserByTempID(dwUserTempID);
	//if (pToUser)
	//{
	//	char buf[MAX_CHATINFO];
	//	getMessage(buf, MAX_CHATINFO, pattern);
	//	zRTime ctv;
	//	Cmd::stChannelChatUserCmd send;
	//	send.dwType = Cmd::CHAT_TYPE_SYSTEM;
	//	send.dwSysInfoType = type;//系统消息的类型
	//	send.dwChatTime = ctv.sec();
	//	bzero(send.pstrName, sizeof(send.pstrName));
	//	bzero(send.pstrChat, sizeof(send.pstrChat));
	//	strncpy((char *)send.pstrChat, buf, MAX_CHATINFO - 1);
	//	pToUser->sendCmdToMe(&send, sizeof(send));
	//	return true;
	//}
	return false;
}

/**
* \brief 私聊
*
*
* \param pUser: 请求发送者
* \param rev:请求指令
* \param cmdLen: 指令长度
* \return 发送是否成功
*/
bool GateChannel::sendPrivate(GateUser *pUser, const NetMsgSS *rev, DWORD cmdLen)
{

	return true;
}

/**
* \brief 唯一实例
*
*/
GateChannelM::GateChannelM()
{
	channelUniqeID = new zUniqueDWORDID(1);
}

GateChannelM::~GateChannelM()
{
	SAFE_DELETE(channelUniqeID);
}

/**
* \brief 得到一个唯一编号
*
*
* \param tempid: 唯一编号(输出)
* \return 得到的编号是否唯一
*/
bool GateChannelM::getUniqeID(QWORD &tempid)
{
	tempid = channelUniqeID->get();
	return (tempid != channelUniqeID->invalid());
}

/**
* \brief 收回一个唯一编号
*
*
* \param tempid: 收回的编号
*/
void GateChannelM::putUniqeID(const QWORD &tempid)
{
	channelUniqeID->put(tempid);
}

/**
* \brief 增加聊天频道
*
*
* \param channel: 频道
* \return 增加是否成功
*/
bool GateChannelM::add(GateChannel *channel)
{
	bool ret;
	mlock.lock();
	ret = addEntry(channel);
	mlock.unlock();
	return ret;
}

/**
* \brief 从聊天频道中删除一个用户
*
*
* \param name: 用户名
*/
void GateChannelM::removeUser(const char *name)
{
	// 清理所有频道里的name用户
	for (zEntryName::hashmap::iterator it = zEntryName::ets.begin(); it != zEntryName::ets.end(); it++)
	{
		GateChannel *temp = (GateChannel *)it->second;
		temp->remove(name);
	}
}

/**
* \brief 从聊天频道中删除一个聊天频道
*
*
* \param dwChannelID: 频道id
*/
void GateChannelM::remove(DWORD dwChannelID)
{
	GateChannel *ret = NULL;
	mlock.lock();
	ret = (GateChannel *)getEntryByTempID(dwChannelID);
	removeEntry(ret);
	mlock.unlock();
}

/**
* \brief 得到一个聊天频道
*
*
* \param dwChannelID: 频道id
* \return 聊天频道
*/
GateChannel *GateChannelM::get(DWORD dwChannelID)
{
	GateChannel *ret = NULL;
	mlock.lock();
	ret = (GateChannel *)getEntryByTempID(dwChannelID);
	mlock.unlock();
	return ret;
}

GateChannel* GateChannelM::CreateObj(GateUser *pUser)
{
	return objpool.CreateObj(pUser);
}

GateChannel* GateChannelM::CreateObj(DWORD chID, const std::string& _name)
{
	return objpool.CreateObj(chID, _name);
}

void GateChannelM::DestroyObj(GateChannel* obj)
{
	objpool.DestroyObj(obj);
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



