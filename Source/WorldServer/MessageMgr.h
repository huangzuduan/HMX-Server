#ifndef __MESSAGE_MGR_H_
#define __MESSAGE_MGR_H_


#include "Includes.h"
#include "SrvEngine.h"
#include "chatmsg.pb.h"

#define MAX_MSG_LENGTH 300

typedef std::map<int32, C::t_ChatBase, std::greater<int32> > ChatMsgMapType;
typedef std::map<int32, C::t_ChatBase, std::greater<int32> > TeamChatMsgMapType;


namespace msg
{

#pragma pack(push,1)

	const dbCol Id[] =
	{
		{ "ID",DB_QWORD,sizeof(QWORD) },
		{ NULL,0,0 },
	};

	const dbCol fields[] =
	{
		{ "ID",DB_QWORD,sizeof(int64) },
		{ "CREATETIME",DB_DWORD,sizeof(int32) },
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
		int32 createtime;
	};

	struct Record
	{
		Base base;
		int32 size;
		BinaryHeader header;
	};

#pragma pack(pop)

}


/*
 *	共用临时信箱功能，有链接地址与密码就可以查看，同时还可以进行管理
 *  查看到一定次数会自动进行销毁
 *
 */
class zMessage : public zEntry
{
public:
	zMessage();
	bool loadDB();
	void saveDB();
	void readBinary(const char* data, int32 len);
	int32 writeBinary(char* data);
	bool serialize(::protobuf::MsgConent& proto);
	void unserialize(const ::protobuf::MsgConent& proto);

private:

	//int64 msgID;
	int32 createTime;
	int64 sendUid;
	char sendName[MAX_NAMESIZE + 1];
	int32 sendTime;
	char msg[MAX_MSG_LENGTH + 1];


};


class MessageMgr : protected zEntryMgr<zEntryID>
{
public:
	MessageMgr();
	~MessageMgr();

	void loadDB();


	void doUserCmd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	zMessage* CreateObj();
	void DestroyObj(zMessage* obj);

	bool addMessage(zMessage* mess);
	void removeMessage(zMessage* mess);
	void removeMessageAll();
	void removeMessageBefore(int32 time);

	zMessage* getMessage(QWORD id);
	void getMessageNearest(int num);
	void getMessageNearestFrom(int num,QWORD fromID);
	void getMessageFromTo(QWORD formID,QWORD toID);

private:

	zObjPool<zMessage> objpool;


private:

	/* 单聊信息 对方ID=>信息ID=>信息内容 */
	std::map<int64, ChatMsgMapType > chatOneMsg;

	/* 群聊信息，群ID=>信息ID=>信息内容 */
	/* 聊聊信息，通过指向信息ID去获得内容，不会未看过的，不会单独保存一份，如果是观看过，则会保存 */
	/* 公用数据只在在WS上 */
	std::map<int32, TeamChatMsgMapType > chatTeamMsg;

};

#endif


