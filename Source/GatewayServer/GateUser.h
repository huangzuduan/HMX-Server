#ifndef __GATE_USER_H_
#define __GATE_USER_H_

#include "Includes.h"

/*
 *	网关用户数据，缓存为主，真实数据在场景服 
 */
class GateUser : public zUser
{
public:
	GateUser();
	~GateUser();

public:

	UserGateBase base;
	int32 sceneServerid;

public:

	bool IsNineOfScene(int32 x, int32 y);

};

// TODO 实现十字链表，可以找到周边的玩家 from博客园

class GateUserManager : protected zUserManager
{
public:

	static GateUserManager& getMe();
	static void destroyeMe();

	bool getUniqeID(QWORD& tempid);
	void putUniqeID(const QWORD& tempid);

	GateUser* CreateObj();
	void DestoryObj(GateUser* obj);

	bool add(GateUser* user);
	void remove(GateUser* user);
	GateUser* get(QWORD userID);
	GateUser* getBySessID(DWORD tempID);
	GateUser* getByName(char* name);

	void sendToAllUser(const NetMsgSS* msg,int32 len);
	void sendToCountryUser(int32 countryID, const NetMsgSS* msg, int32 len);
	void sendToMapUser(int32 mapID,const NetMsgSS* msg, int32 len);
	void sendToSceneUser(int32 sceneID, const NetMsgSS* msg, int32 len);
	void sendToZoneUser(int32 zoneID, const NetMsgSS* msg, int32 len);
	void sendToTeamUser(int32 teamID, const NetMsgSS* msg, int32 len);
	void sendToNineUser(int64 userID, int32 x, int32 y, const NetMsgSS* msg, int32 len);
	template<class YourUserEntry>
	bool execEveryUser(execEntry<YourUserEntry> &exec)
	{
		rwlock.rdlock();
		bool ret = execEveryEntry<>(exec);
		rwlock.unlock();
		return ret;
	}

private:

	zRWLock rwlock;
	ObjPool<GateUser> objpool;
	static GateUserManager* ins;
	
};

#endif

