#ifndef __GATEWAYS_SERVER_H_
#define __GATEWAYS_SERVER_H_


#include "SrvEngine.h"

class GateUser;
struct NetMsgSS;

/**
* \brief 聊天频道
*
*/
class GateChannel :public zEntry
{
public:
	GateChannel(GateUser *pUser);
	GateChannel(DWORD chID, const std::string& _name);
	~GateChannel();
	inline uint64_t GetID(){ return _entry_id; }
	inline uint64_t GetTempID() { return _entry_tempid; }
	inline const std::string& GetName(){ return _entry_name; }
	static bool sendNine(GateUser *pUser, const NetMsgSS *cmd, DWORD len);
	static bool sendPrivate(GateUser *pUser, const NetMsgSS *cmd, DWORD len);
	static bool sendTeam(DWORD teamid, const NetMsgSS *cmd, DWORD len);
	static bool sendCountry(GateUser *pUser, const NetMsgSS *cmd, DWORD len);

	static bool sendCmdToMap(DWORD mapID, const NetMsgSS *cmd, int len);
	static bool sendSys(GateUser *pUser, int type, const char *pattern, ...);
	static bool sendSys(DWORD dwUserTempID, int type, const char *pattern, ...);
	static bool sendCountry(GateUser *pUser, const char *pattern, ...);
	static bool sendCountryInfo(DWORD countryID, DWORD infoType, const char *pattern, ...);
	static bool sendAllInfo(DWORD infoType, const char *pattern, ...);

	bool sendCmdToAll(const NetMsgSS *cmd, int len);

	bool remove(const char *name);
	bool add(GateUser *pUser);
	WORD has(const char *name);
private:
	std::vector< GateUser > userlist;
	GateChannel* creater;

};

/**
* \brief 频道管理器
*
*/
class GateChannelM : public zEntryMgr< zEntryID<0>, zEntryID<1>, zEntryName >
{
private:
	zUniqueDWORDID *channelUniqeID;
	zMutex mlock;
	zObjPool<GateChannel> objpool;

	bool getUniqeID(QWORD &tempid);
	void putUniqeID(const QWORD &tempid);

public:
	GateChannelM();
	~GateChannelM();
	bool add(GateChannel *channel);
	void remove(DWORD dwChannelID);
	GateChannel* get(DWORD dwChannelID);
	void removeUser(const char *name);
	GateChannel* CreateObj(GateUser *pUser);
	GateChannel* CreateObj(DWORD chID, const std::string& _name);
	void DestroyObj(GateChannel* obj);

};





#endif
