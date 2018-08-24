#ifndef __MESSAGE_MGR_H_
#define __MESSAGE_MGR_H_

#include "SrvEngine.h"
#include "base/hmx_data.pb.h"

#define MAX_MSG_LENGTH 300

typedef std::map<int32_t,std::string, std::greater<int32_t> > ChatMsgMapType;
typedef std::map<int32_t, std::string, std::greater<int32_t> > TeamChatMsgMapType;

/*
 *	共用临时信箱功能，有链接地址与密码就可以查看，同时还可以进行管理
 *  查看到一定次数会自动进行销毁
 *
 */
class zMessage : public zEntry
{
public:
	zMessage();
	inline uint64_t GetID(){ return id; }
	inline uint64_t GetTempID(){ return _entry_tempid; }
	inline const std::string& GetName(){ return _entry_name; }

private:

	int64_t id;
	int32_t createTime;
	int64_t sendUid;
	char sendName[MAX_NAMESIZE + 1];
	int32_t sendTime;
	char msg[MAX_MSG_LENGTH + 1];


};


class MessageMgr : protected zEntryMgr< zEntryID<0> >
{
public:
	MessageMgr();
	~MessageMgr();

	void loadDB();


	void doUserCmd(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	zMessage* CreateObj();
	void DestroyObj(zMessage* obj);

	bool addMessage(zMessage* mess);
	void removeMessage(zMessage* mess);
	void removeMessageAll();
	void removeMessageBefore(int32_t time);

	zMessage* getMessage(QWORD id);
	void getMessageNearest(int num);
	void getMessageNearestFrom(int num,QWORD fromID);
	void getMessageFromTo(QWORD formID,QWORD toID);

private:

	zObjPool<zMessage> objpool;


private:

	/* 单聊信息 对方ID=>信息ID=>信息内容 */
	std::map<int64_t, ChatMsgMapType > chatOneMsg;

	/* 群聊信息，群ID=>信息ID=>信息内容 */
	/* 聊聊信息，通过指向信息ID去获得内容，不会未看过的，不会单独保存一份，如果是观看过，则会保存 */
	/* 公用数据只在在WS上 */
	std::map<int32_t, TeamChatMsgMapType > chatTeamMsg;

};

#endif


