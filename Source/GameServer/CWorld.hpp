#ifndef _GAME_WORLD_H_ 
#define _GAME_WORLD_H_

#include "Global.hpp"
#include "FogsTimerService.hpp"

class CPlayer;

struct stSessionAccount
{
	uint32_t unUserID;
	std::string strAccount;
	std::string strName;
	std::string strIconAddr;
	stSessionAccount()
	{
		unUserID = 0;
	}
};
typedef boost::unordered_map<std::string, stSessionAccount> umapSessionAccountName;

static const uint32_t g_unUpdateServerTime		= 120;	//更新服务器信息定时器时间
static const uint32_t g_unSaveDataTime			= 120;	//保存玩家数据定时器时间
static const uint16_t g_unNoticeTime			= 15;	//公告定时器时间


class CWorld : public Single<CWorld>
{
public:
	CWorld();
	~CWorld();
	bool Init();
	void Release();
	void AddPlayer(CPlayer* pPlayer);
	CPlayer* CreatePlayer(uint64_t unSessionID, uint32_t unFepServerID, const ::msg_maj::Role& proData);
	CPlayer* LoadPlayer(uint64_t unSessionID,uint32_t unFepServerID, const ::msg_maj::Role& proData);
	CPlayer* GetPlayerBySessionID(uint64_t unSessionID) const;
	CPlayer* GetPlayerByUUID(uint64_t ulUUID) const;
	CPlayer* GetPlayerByAccount(const std::string& strAccount) const;
	void ResetSessionID(CPlayer* pPlayer, uint64_t unSessionID);
	void LeaveGame(uint32_t unSessionID);
	void SavePlayerData();
	void GatewayDisconnect();
	void SendWorldMsg(uint16_t usCmd,uint16_t usMsg, const google::protobuf::Message& msg);
	void AddSessionIP(uint64_t unSessionID, const std::string& strIP);
	void DelSessionIP(uint64_t unSessionID);
	void AddSessionAccountName(uint32_t unUserID, const std::string& strAccount, const std::string& strName, const std::string& strIconAddr);
	void DelSessionAccountName(const std::string& strAccount);
	void GetSessionAccount(const std::string& strAccount, stSessionAccount& st);
	bool SessionAccount(const std::string& strAccount) const;
	std::string GetSessionIP(uint64_t unSessionID);
	void AddRoomInfo(uint32_t unRoomID, uint32_t unServerID);
	void DelRoomInfo(uint32_t unRoomID);
	uint32_t GetServerIDByRoomID(uint32_t unRoomID) const;
	uint32_t GetOnlinePlayerNum() const;
	void AddSavePlayer(uint64_t ulCharID);
	void DelSavePlayer(uint64_t ulCharID);
	inline const std::map<uint64_t, CPlayer*>& GetOnlinePlayers() const { return m_mapPlayerByUUID; }

	CPlayer* GetFreeRobot();
	void AddRobot(CPlayer* pPlayer);
	void DelRobotByUid(uint64_t uid);

	void SendMoneyLog(uint16_t charID, const std::string& nickname, int32_t num, int32_t totalNum, ::fogs::proto::msg::log_type type);
	void LoadConfigFromDB();

	const fogs::proto::msg::RewardConfig& GetInvitationRewardConfig() const { return m_proInvitationRewardConfig; }
	void SetInvitationRewardConfig(const fogs::proto::msg::RewardConfig& proData) { m_proInvitationRewardConfig.CopyFrom(proData); }
	const fogs::proto::msg::RewardConfig& GetShareRewardConfig() const { return m_proShareRewardConfig; }
	void SetShareRewardConfig(const fogs::proto::msg::RewardConfig& proData) { m_proShareRewardConfig.CopyFrom(proData); }
	void SetFreeConfig(const fogs::proto::msg::GetFreeConfigResp& proResp) { m_proFreeConfig.CopyFrom(proResp); }
	const fogs::proto::msg::GetFreeConfigResp& GetFreeConfigConfig() const { return m_proFreeConfig; }
	void SetNotifyConfig(const fogs::proto::msg::GetNotifyConfigResp& proData) { m_proNotifyConfig.CopyFrom(proData); }
	const fogs::proto::msg::GetNotifyConfigResp& GetNotifyConfig() const { return m_proNotifyConfig; }
	void SetRoomSetConfig(const fogs::proto::msg::GetRoomSetConfigResp& proData) { m_proRoomSetConfig.CopyFrom(proData); }
	const fogs::proto::msg::GetRoomSetConfigResp& GetRoomSetConfig() const { return m_proRoomSetConfig; }

	bool IsFreeCard() const;

private:

	fogs::FogsTimer* m_pSaveDataTimer;

	typedef std::map<uint64_t, CPlayer*> mapPlayerByUUID;
	mapPlayerByUUID		m_mapPlayerByUUID;

	typedef std::map<uint64_t, CPlayer*> mapPlayerBySessionID;
	mapPlayerBySessionID m_mapPlayerBySessionID;

	typedef boost::unordered_map<std::string, CPlayer*> umapPlayerByAccount;
	umapPlayerByAccount m_umapPlayerByAccount;

	std::map<uint64_t, std::string> m_mapSessionIP;

	umapSessionAccountName m_umapSessionAccountName;

	std::map<uint32_t, uint32_t> m_mapRoomInfo;

	std::set<uint64_t> m_setSavePlayer;

	std::map<uint64_t, CPlayer*> m_mapRobotID;

	fogs::proto::msg::RewardConfig m_proInvitationRewardConfig; //邀请奖励配置

	fogs::proto::msg::RewardConfig m_proShareRewardConfig;		//分享奖励配置

	fogs::proto::msg::GetFreeConfigResp m_proFreeConfig;		//免费配置

	fogs::proto::msg::GetNotifyConfigResp m_proNotifyConfig;	//后台公告

	fogs::proto::msg::GetRoomSetConfigResp m_proRoomSetConfig;	//房间设置

};
#endif
