#ifndef __GATE_USER_H_
#define __GATE_USER_H_


#include "SrvEngine.h"

/*
 *	网关用户数据，缓存为主，真实数据在场景服
 *  该数据在用户请求进入Scene后，则SS将数据传到FEP后创建
 */
class GateUser : public zEntry
{
public:
	GateUser(const ::msg_maj::RoleFep& proto);
	~GateUser();
	virtual inline uint64_t GetID() { return dataProto.id(); };
	virtual inline uint64_t GetTempID() { return dataProto.sessionid(); };
	virtual inline const std::string& GetName() { return _entry_name; };
	inline uint64_t GetSessionID() const { return dataProto.sessionid(); }
	inline uint32_t GetSceneServerID() const { return dataProto.serverid();}
	inline const ::msg_maj::RoleFep& GetDataProto() const { return dataProto;}
	bool IsNineOfScene(int32_t x, int32_t y);
private:
	::msg_maj::RoleFep dataProto;
};

// TODO 实现十字链表，可以找到周边的玩家 from博客园
class GateUserManager : protected zEntryMgr< zEntryID<0>, zEntryID<1> >
{
public:
	static GateUserManager& getMe();
	static void destroyeMe();

	GateUser* add(const ::msg_maj::RoleFep& proto);
	void remove(GateUser* user);
	GateUser* get(uint64_t userID);
	GateUser* getBySessID(uint64_t tempID);

	void sendToAllUser(const NetMsgSS* msg,int32_t len);
	void sendToCountryUser(int32_t countryID, const NetMsgSS* msg, int32_t len);
	void sendToMapUser(int32_t mapID,const NetMsgSS* msg, int32_t len);
	void sendToSceneUser(int32_t sceneID, const NetMsgSS* msg, int32_t len);
	void sendToZoneUser(int32_t zoneID, const NetMsgSS* msg, int32_t len);
	void sendToTeamUser(int32_t teamID, const NetMsgSS* msg, int32_t len);
	void sendToNineUser(int64_t userID, int32_t x, int32_t y, const NetMsgSS* msg, int32_t len);
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
	zObjPool<GateUser> objpool;
	static GateUserManager* ins;
	
};

#endif

