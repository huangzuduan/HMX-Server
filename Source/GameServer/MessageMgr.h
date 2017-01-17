#ifndef __MESSAGE_MGR_H_
#define __MESSAGE_MGR_H_


#include "Includes.h"
#include "SrvEngine.h"
#include "SceneUser.h"

#include "chatmsg.pb.h"

#define MAX_MSG_LENGTH 300

typedef std::map<int32, t_ChatBase, std::greater<int32> > UidChatMsgMapType;
typedef std::map<int32, t_ChatBase, std::greater<int32> > TeamChatMsgMapType;

class zMessage : public zEntry
{
public:

	zMessage()
	{
		createTime = readyTime = len = 0;
		memset(msg, 0, sizeof(msg));
	}

	int32 createTime;
	int32 readyTime;
	int16 len;
	char msg[MAX_MSG_LENGTH];
};


class MessageMgr : protected zEntryMgr<zEntryID>
{
public:
	MessageMgr(SceneUser* u);
	~MessageMgr();

	//bool Serialize(::protobuf::MyChatMsg& proto);
	//void UnSerialize(const ::protobuf::MyChatMsg& proto);

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

	SceneUser* user;
	ObjPool<zMessage> objpool;


private:

	/* 单聊信息 对方ID=>信息ID=>信息内容 */
	std::map<int64, UidChatMsgMapType > chatOneMsg;

	/* 群聊信息，群ID=>信息ID=>信息内容 */
	/* 聊聊信息，通过指向信息ID去获得内容，不会未看过的，不会单独保存一份，如果是观看过，则会保存 */
	/* 公用数据只在在WS上 */
	std::map<int32, TeamChatMsgMapType > chatTeamMsg;

};

#endif


