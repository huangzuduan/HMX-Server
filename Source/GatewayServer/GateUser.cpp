#include "GatewayServer_PCH.h"
#include "GateUser.h"


GateUser::GateUser()
{
	sceneServerid = 0;
}

GateUser::~GateUser()
{
}

bool GateUser::IsNineOfScene(int32 x, int32 y)
{


	return true;
}

struct GateUserExce : public execEntry<GateUser>
{
	int32 msgtype;
	int32 regid;	
	int64 userid;	
	int32 x;		
	int32 y;
	int32 len;
	const NetMsgSS* msg;

	std::vector<int64> userlist; /* 获得广播的玩家记录 */

	GateUserExce(int32 _len, const NetMsgSS* _msg, int32 _msgtype, int32 _regid = 0, int64 _userid = 0, int32 _x = 0, int32 _y = 0)
		: len(_len), msg(_msg), msgtype(_msgtype), regid(_regid), userid(_userid), x(_x), y(_y)
	{

	}

	bool exec(GateUser *u)
	{
		zSession* session = NetService::getMe().getSessionMgr().get(u->tempid);
		if (session)
		{
			if (msgtype == BORADCAST_TYPE_ALL)
			{
				
			}
			else if (msgtype == BORADCAST_TYPE_COUNTRY && regid == u->base.countryID)
			{

			}
			else if (msgtype == BORADCAST_TYPE_MAPID && regid == u->base.mapid)
			{

			}
			else if (msgtype == BORADCAST_TYPE_SCENE && regid == u->base.sceneid)
			{

			}
			else if (msgtype == BORADCAST_TYPE_ZONE && regid == u->base.zoneid)
			{

			}
			else if (msgtype == BORADCAST_TYPE_NINE && u->IsNineOfScene(x,y))
			{

			}
			else if (msgtype == BORADCAST_TYPE_TEAM && regid == u->base.teamid)
			{

			}
			else
			{
				return true;
			}

			userlist.push_back(u->id);

			session->sendMsg(msg, len);
			
		}
		return true;
	}
};

GateUserManager* GateUserManager::ins(NULL);

GateUserManager& GateUserManager::getMe()
{
	if (ins == NULL)
	{
		ins = new GateUserManager();
	}
	return *ins;
}

void GateUserManager::destroyeMe()
{
	if (ins)
	{
		SAFE_DELETE(ins);
	}
}

bool GateUserManager::getUniqeID(QWORD& tempid)
{
	return true;
}

void GateUserManager::putUniqeID(const QWORD& tempid)
{

}

bool GateUserManager::add(GateUser* user)
{
	return zUserManager::addUser(user);
}

void GateUserManager::remove(GateUser* user)
{
	rwlock.wrlock();
 	removeEntry(user);
	rwlock.unlock();
}

GateUser* GateUserManager::get(QWORD userID)
{
	rwlock.rdlock();
	GateUser *ret = (GateUser *)getEntryByID(userID);
	rwlock.unlock();
	return ret;
}

GateUser* GateUserManager::getBySessID(DWORD tempID)
{
	rwlock.rdlock();
	GateUser *ret = (GateUser *)getUserBySessID(tempID);
	rwlock.unlock();
	return ret;
}

GateUser* GateUserManager::getByName(char* name)
{
	rwlock.rdlock();
	GateUser *ret = (GateUser *)getUserByName(name);
	rwlock.unlock();
	return ret;
}

GateUser* GateUserManager::CreateObj()
{
	return objpool.CreateObj();
}

void GateUserManager::DestoryObj(GateUser* obj)
{
	objpool.DestroyObj(obj);
}

void GateUserManager::sendToAllUser(const NetMsgSS* msg, int32 len)
{
	Zebra::logger->info("sendToAllUser");
	GateUserExce exce(len, msg, BORADCAST_TYPE_ALL);
	GateUserManager::getMe().execEveryUser(exce);
}

void GateUserManager::sendToCountryUser(int32 countryID, const NetMsgSS* msg, int32 len)
{
	Zebra::logger->info("sendToCountryUser");
	GateUserExce exce(len, msg, BORADCAST_TYPE_COUNTRY,countryID);
	GateUserManager::getMe().execEveryUser(exce);
}

void GateUserManager::sendToMapUser(int32 mapID, const NetMsgSS* msg, int32 len)
{
	Zebra::logger->info("sendToMapUser");
	GateUserExce exce(len, msg, BORADCAST_TYPE_MAPID, mapID);
	GateUserManager::getMe().execEveryUser(exce);
}

void GateUserManager::sendToSceneUser(int32 sceneID, const NetMsgSS* msg, int32 len)
{
	Zebra::logger->info("sendToSceneUser");
	GateUserExce exce(len, msg, BORADCAST_TYPE_SCENE, sceneID);
	GateUserManager::getMe().execEveryUser(exce);
}

void GateUserManager::sendToZoneUser(int32 zoneID, const NetMsgSS* msg, int32 len)
{
	Zebra::logger->info("sendToZoneUser");
	GateUserExce exce(len, msg, BORADCAST_TYPE_ZONE, zoneID);
	GateUserManager::getMe().execEveryUser(exce);
}

void GateUserManager::sendToTeamUser(int32 teamID, const NetMsgSS* msg, int32 len)
{
	Zebra::logger->info("sendToTeamUser");
	GateUserExce exce(len, msg, BORADCAST_TYPE_TEAM, teamID);
	GateUserManager::getMe().execEveryUser(exce);
}

void GateUserManager::sendToNineUser(int64 userID, int32 x, int32 y, const NetMsgSS* msg, int32 len)
{
	Zebra::logger->info("sendToNineUser");
	GateUserExce exce(len, msg, BORADCAST_TYPE_NINE,0, userID, x, y);
	GateUserManager::getMe().execEveryUser(exce);
}
