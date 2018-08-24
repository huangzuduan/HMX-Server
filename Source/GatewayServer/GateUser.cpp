#include "GateUser.h"
#include "GameService.h"

GateUser::GateUser(const ::msg_maj::RoleFep& proto)
{
	dataProto.CopyFrom(proto);
}

GateUser::~GateUser()
{
}

bool GateUser::IsNineOfScene(int32_t x, int32_t y)
{
	return true;
}

struct GateUserExce : public execEntry<GateUser>
{
	int32_t msgtype;
	int32_t regid;	
	int64_t userid;	
	int32_t x;		
	int32_t y;
	int32_t len;
	const NetMsgSS* msg;

	std::vector<int64_t> userlist; /* 获得广播的玩家记录 */

	GateUserExce(int32_t _len, const NetMsgSS* _msg, int32_t _msgtype, int32_t _regid = 0, int64_t _userid = 0, int32_t _x = 0, int32_t _y = 0)
		: len(_len), msg(_msg), msgtype(_msgtype), regid(_regid), userid(_userid), x(_x), y(_y)
	{

	}

	bool exec(GateUser *u)
	{
		zSession* session = GameService::getMe().SessionMgr()->get(u->GetID());
		if (session)
		{
			//const ::msg_maj::RoleFep& info = u->GetDataProto();
			//if (msgtype == S::SSNtBoradCastMsg::TYPE_ALL)
			//{
			//	
			//}
			//else if (msgtype == S::SSNtBoradCastMsg::TYPE_COUNTRY && regid == info.countryid())
			//{

			//}
			//else if (msgtype == S::SSNtBoradCastMsg::TYPE_MAPID && regid == info.mapid())
			//{

			//}
			//else if (msgtype == S::SSNtBoradCastMsg::TYPE_SCENE && regid == info.sceneid())
			//{

			//}
			//else if (msgtype == S::SSNtBoradCastMsg::TYPE_ZONE && regid == info.zoneid())
			//{

			//}
			//else if (msgtype == S::SSNtBoradCastMsg::TYPE_NINE && u->IsNineOfScene(x, y))
			//{

			//}
			//else if (msgtype == S::SSNtBoradCastMsg::TYPE_TEAM && regid == info.teamid())
			//{

			//}
			//else
			//{
			//	return true;
			//}

			userlist.push_back(u->GetID());

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
		S_SAFE_DELETE(ins);
	}
}

GateUser* GateUserManager::add(const ::msg_maj::RoleFep& proto)
{
	GateUser* obj = objpool.CreateObj(proto);
	if (!zEntryMgr< zEntryID<0> , zEntryID<1> >::addEntry(obj))
	{
		objpool.DestroyObj(obj);
		return NULL;
	}
	return obj;
}

void GateUserManager::remove(GateUser* user)
{
	rwlock.wrlock();
 	removeEntry(user);
	rwlock.unlock();
	objpool.DestroyObj(user);
}

GateUser* GateUserManager::get(uint64_t userID)
{
	rwlock.rdlock();
	GateUser *ret = (GateUser *)zEntryID<0>::getEntryByID(userID);
	rwlock.unlock();
	return ret;
}

GateUser* GateUserManager::getBySessID(uint64_t tempID)
{
	rwlock.rdlock();
	GateUser *ret = (GateUser *)zEntryID<1>::getEntryByID(tempID);
	rwlock.unlock();
	return ret;
}

void GateUserManager::sendToAllUser(const NetMsgSS* msg, int32_t len)
{
	//H::logger->info("sendToAllUser");
	//GateUserExce exce(len, msg, S::SSNtBoradCastMsg::TYPE_ALL);
	//GateUserManager::getMe().execEveryUser(exce);
}

void GateUserManager::sendToCountryUser(int32_t countryID, const NetMsgSS* msg, int32_t len)
{
	//H::logger->info("sendToCountryUser");
	//GateUserExce exce(len, msg, S::SSNtBoradCastMsg::TYPE_COUNTRY,countryID);
	//GateUserManager::getMe().execEveryUser(exce);
}

void GateUserManager::sendToMapUser(int32_t mapID, const NetMsgSS* msg, int32_t len)
{
	//H::logger->info("sendToMapUser");
	//GateUserExce exce(len, msg, S::SSNtBoradCastMsg::TYPE_MAPID, mapID);
	//GateUserManager::getMe().execEveryUser(exce);
}

void GateUserManager::sendToSceneUser(int32_t sceneID, const NetMsgSS* msg, int32_t len)
{
	//H::logger->info("sendToSceneUser");
	//GateUserExce exce(len, msg, S::SSNtBoradCastMsg::TYPE_SCENE, sceneID);
	//GateUserManager::getMe().execEveryUser(exce);
}

void GateUserManager::sendToZoneUser(int32_t zoneID, const NetMsgSS* msg, int32_t len)
{
	//H::logger->info("sendToZoneUser");
	//GateUserExce exce(len, msg, S::SSNtBoradCastMsg::TYPE_ZONE, zoneID);
	//GateUserManager::getMe().execEveryUser(exce);
}

void GateUserManager::sendToTeamUser(int32_t teamID, const NetMsgSS* msg, int32_t len)
{
	//H::logger->info("sendToTeamUser");
	//GateUserExce exce(len, msg, S::SSNtBoradCastMsg::TYPE_TEAM, teamID);
	//GateUserManager::getMe().execEveryUser(exce);
}

void GateUserManager::sendToNineUser(int64_t userID, int32_t x, int32_t y, const NetMsgSS* msg, int32_t len)
{
	//H::logger->info("sendToNineUser");
	//GateUserExce exce(len, msg, S::SSNtBoradCastMsg::TYPE_NINE,0, userID, x, y);
	//GateUserManager::getMe().execEveryUser(exce);
}
