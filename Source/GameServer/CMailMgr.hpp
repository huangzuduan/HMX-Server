#ifndef _CMAIL_MGR_H_
#define _CMAIL_MGR_H_

#include "Global.hpp"
#include "SrvEngine.h"
#include "CMail.hpp"

/*

	邮件管理器

 */

class CMailMgr : public zEntryMgr< zEntryID<0> > , public Single< CMailMgr >
{
public:
	CMailMgr();
	~CMailMgr();
	void OnSystemStart();
	void OnlinePlayer(uint64_t uid);
	void OfflinePlayer(uint64_t uid);
	void UnSerialize(const ::fogs::proto::msg::QueryMailResponse proto);

	/*
	 * 给某人发邮件
	 * toPlayer 玩家
	 * title 标题
	 * content 内容
	 * room_cards 是否奖励房卡
	 */
	bool SendToPlayer(const CPlayer& toPlayer, const std::string& title, const std::string& content, int32_t room_cards);

	/*
	 * 给一些人发邮件
	 * toPlayer 玩家
	 * title 标题
	 * content 内容
	 * room_cards 是否奖励房卡
	 */
	void SeendToPlayers(const std::vector<const CPlayer*> &vecPlayer, const std::string& title, const std::string& content, int32_t room_cards);

	/*
	 * 给某人发邮件
	 * fromID 发件人,0为系统
	 * fromName 发件人名字, ""为系统
	 * toUid 收件人ID
	 * toName 收件人名字
	 * title 标题
	 * content 内容
	 * room_cards 是否奖励房卡
	*/
	bool SendToPlayer(uint64_t fromID, const std::string& fromName, uint64_t toUid, const std::string& toName, const std::string& title, const std::string& content, int32_t room_cards);

	template <class YourUserEntry>
	inline bool execEveryMail(execEntry<YourUserEntry> &exec)
	{
		return zEntryMgr< zEntryID<0> >::execEveryEntry<>(exec);
	}

	bool GetByID(CMail* &entry, int64_t nMailID);
	bool GetSys(std::vector<CMail*>& vecEntry,uint64_t uid);
	bool GetByUID(std::vector<CMail*>& vecEntry, uint64_t uid,uint64_t start_index = 0,int32_t num = 50);
	bool GetByUIDMailID(CMail* &entry, uint64_t uid, uint64_t nMailID);

	void SendMailList(CPlayer* pPlayer,int32_t start_index = 0);

	void TestAdd(const std::string& account);
	void TestModify();

	void AddRecord(const ::msg_maj::MailRecordS& record, bool isNew);

private:

	bool AddRecord(CMail *obj);
	bool CheckAndRelease(CMail *obj,bool isRelease = false); // 仅移除内存，不处理数据库
	void Release(CMail *obj);
	void Recond2ProtoC(uint64_t uid,const CMail& mail, ::msg_maj::MailRecordC& distProto);

private:
	uint64_t m_unMaxID; // 序列ID 
	std::map<uint64_t, CMail*, std::greater<uint64_t> >							mapSysRecords;	// 系统邮件(ID=>内容)
	std::map<uint64_t,std::map<uint64_t,CMail*,std::greater<uint64_t> > >		mapUidRecords;	// 个人邮件(uid=>ID=>内容)
};


//----------------------------------------------------
// 系统公共邮件
class CMailSysLogMgr : public zEntryMgr< zEntryID<0> >, public Single< CMailSysLogMgr >
{
public:
	CMailSysLogMgr();
	~CMailSysLogMgr();
	void OnlinePlayer(uint64_t uid);
	void OfflinePlayer(uint64_t uid);
	void UnSerialize(const ::fogs::proto::msg::QueryMailSystemLogResponse proto);
	CMailSysLog* GetByID(int64_t nMailID);
	bool GetByUID(std::vector<CMailSysLog*>& vecEntry, uint64_t uid, uint64_t start_index = 0, int32_t num = 50);
	CMailSysLog* GetByUIDMailID(uint64_t uid,uint64_t mail_id);
	void Release(CMailSysLog *obj);
	CMailSysLog* AddRecord(const ::msg_maj::MailSystemLogS& record, bool isNew);

private:
	bool AddRecord(CMailSysLog *obj);
private:
	std::map<uint64_t, std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> > >	mapUidRecords;	// 个人邮件(uid=>ID=>内容)
};

#endif


