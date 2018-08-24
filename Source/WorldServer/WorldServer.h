#ifndef __WORLD_SERVER_H_
#define __WORLD_SERVER_H_


#include "SrvEngine.h"
#include "base/hmx_data.pb.h"

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
		int64_t uid;
		char name[MAX_NAMESIZE + 1];
		int32_t createtime;
		int32_t receivetime;
	};

	struct MsgData
	{
		int64_t msgid;
		int32_t createtime;
		char msgstr[MAX_MSG_LEN + 1];
	};

	inline uint64_t GetID(){ return _entry_id; }
	inline uint64_t GetTempID(){ return _entry_tempid; }
	inline const std::string& GetName() { return _entry_name; }

	bool loadDB();
	void saveDB();

	bool sendNine(UserData *user, const NetMsgSS *cmd, DWORD len);
	bool sendPrivate(UserData *user, const NetMsgSS *cmd, DWORD len);
	bool sendTeam(QWORD teamid, const NetMsgSS *cmd, DWORD len);
	bool sendCountry(UserData *user, const NetMsgSS *cmd, DWORD len);
	bool sendCmdToMap(DWORD mapID, const NetMsgSS *cmd, int len);
	bool sendCmdToAll(const NetMsgSS *cmd, int len);

	UserData* getUser(int64_t uid);
	void addUser(const UserData& userdata);
	void removeUser(int64_t uid);

private:

	std::map<int64_t, UserData> userlist;
	std::map<int64_t, MsgData> msglist;

};

/**
* \brief 频道管理器
*
*/
class WorldChannelM : public zEntryMgr< zEntryID<0>, zEntryID<1>, zEntryName >
{
public:
	WorldChannelM();
	~WorldChannelM();

	void loadDB();

	WorldChannel* get(QWORD id);
	bool add(WorldChannel *channel);
	void remove(WorldChannel *channel);
	


private:

	int32_t maxid; // 最大的id
	zObjPool<WorldChannel> objpool;



};





#endif
