#ifndef __WORLD_SERVER_H_
#define __WORLD_SERVER_H_


#include "srvEngine.h"
#include "ConfigBase.h"
#include "CommandS.h"
#include "chatmsg.pb.h"

#define MAX_MSG_LEN 256

/**
* \brief 聊天频道
*
*/
class WorldChannel : public zEntry
{

public:
	WorldChannel();
	~WorldChannel();

	struct UserData
	{
		int64 uid;
		char name[MAX_NAMESIZE + 1];
		int32 createtime;
		int32 receivetime;
	};

	struct MsgData
	{
		int64 msgid;
		int32 createtime;
		char msgstr[MAX_MSG_LEN + 1];
	};

	bool loadDB();
	void saveDB();

	void serialize(protobuf::ChatMsgBinary& proto);
	void unserialize(const protobuf::ChatMsgBinary& proto);

	bool sendNine(UserData *user, const NetMsgSS *cmd, DWORD len);
	bool sendPrivate(UserData *user, const NetMsgSS *cmd, DWORD len);
	bool sendTeam(QWORD teamid, const NetMsgSS *cmd, DWORD len);
	bool sendCountry(UserData *user, const NetMsgSS *cmd, DWORD len);
	bool sendCmdToMap(DWORD mapID, const NetMsgSS *cmd, int len);
	bool sendCmdToAll(const NetMsgSS *cmd, int len);

	UserData* getUser(int64 uid);
	void addUser(const UserData& userdata);
	void removeUser(int64 uid);

private:

	std::map<int64, UserData> userlist;
	std::map<int64, MsgData> msglist;

};

/**
* \brief 频道管理器
*
*/
class WorldChannelM : public zEntryMgr< zEntryID, zEntryTempID, zEntryName >
{
private:
	zUniqueDWORDID *channelUniqeID;
	zMutex mlock;
	ObjPool<WorldChannel> objpool;

	bool getUniqeID(QWORD &tempid);
	void putUniqeID(const QWORD &tempid);

public:
	WorldChannelM();
	~WorldChannelM();

	void loadDB();

	bool add(WorldChannel *channel);
	void remove(WorldChannel *channel);
	WorldChannel* get(DWORD dwChannelID);

	WorldChannel* CreateObj();
	void DestroyObj(WorldChannel* obj);

};





#endif
