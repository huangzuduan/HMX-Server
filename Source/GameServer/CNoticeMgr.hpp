#ifndef _CNOTICE_MGR_H_
#define _CNOTICE_MGR_H_

#include "Global.hpp"
#include "SrvEngine.h"

class CNotice;
class CPlayer;

/*
 * 通告系统，不作游戏数据库保存
 */
class CNoticeMgr : public zEntryMgr< zEntryID<0> >, public Singleton< CNoticeMgr >
{
public:
	CNoticeMgr();
	~CNoticeMgr();

	void Load(const std::string& filenmae);
	void Release();

	CNotice* GetNotice(uint64_t notice_id);
	void Remove(CNotice* obj);
	void AddRecord(const ::msg_event::NoticeS& notice,bool isNew);

	template <class YourUserEntry>
	inline bool execEveryNotice(execEntry<YourUserEntry> &exec)
	{
		return zEntryMgr< zEntryID<0> >::execEveryEntry<>(exec);
	}

	bool GetByLastest(std::vector<CNotice*>& vecEntry);//

	void SendNoticeList(CPlayer* pPlayer);
	void SendNewNotice(CPlayer* pPlayer, const CNotice* pNotice);
	void Broadcast(const CNotice* pNotice);

	inline uint64_t GetMaxID() const { return m_unMaxID; }

private:

	time_t GetTimeValue(const std::string& ymdhms);
	int GetDataValue(const char* value);

	uint64_t m_unMaxID;

private:

};

#endif



