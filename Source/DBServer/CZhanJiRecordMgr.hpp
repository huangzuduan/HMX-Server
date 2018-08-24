#ifndef __ZHAN_JI_MGR_H_
#define __ZHAN_JI_MGR_H_

#include <boost/pool/object_pool.hpp>

#include "SrvEngine.h"
#include "CZhanJiRecord.hpp"

/*
	总战绩系统管理器
	记录玩家一个月内的每一场比赛的详细情况，包括回放功能等
*/

class CZhanJiRecordMgr : public zEntryMgr< zEntryID<0> >, public Singleton<CZhanJiRecordMgr>
{
public:
	CZhanJiRecordMgr() {};
	~CZhanJiRecordMgr() {};

	void LoadRecords();
	void UnSerialize(const fogs::proto::msg::QueryHistoryResponse proto);

	/*
	 * 打牌历史记录
	 * recond_id 记录号，唯一
	 * innRecord 当场游戏结果数据，每个玩家的座位号、牌、番分、碰暗明杠牌、胡的牌，回放记录等
	 * roomInfo 房间信息(在添加第一场时应该赋值，后续不用)
	 * roleInfo 角色列表(在添加第一场时应该赋值，后续不用)
	 * time 创建游戏时间(在添加第一场时应该赋值，后续不用)
	 */
	void AddRecord(uint64_t recond_id, const ::msg_maj::InnRecordS& innRecord,const ::msg_maj::InnReplayActionS& innReplay, uint32_t room_id = 0 ,const ::msg_maj::RoomInfo* roomInfo = NULL,const ::msg_maj::RoleInfoListS* roleInfo = NULL,uint64_t time = 0);

	/*
	 * 完成记录，条件有几种
	 * 1、打完所有局，正常结束
	 * 2、打完部分局，申请解散
	 * 3、其它原因，房间被释放
	 */
	void FinishRecord(uint64_t record_id);

	template <class YourUserEntry>
	inline bool execEveryRecord(execEntry<YourUserEntry> &exec)
	{
		return zEntryMgr< zEntryID<0> >::execEveryEntry<>(exec);
	}

	void SendZhanjiReply(zSession* pSession, const fogs::proto::msg::ZhanjiQueryReply& proto);

public:

	bool GetByID(CZhanJiRecord* &entry,uint64_t nRecordID);
	bool GetByUID(std::vector<CZhanJiRecord*>& vecEntry, uint64_t uid);//
	bool GetByUIDRecordID(CZhanJiRecord* &entry, uint64_t uid, uint64_t nRecordID);

private:
	// 
	void AddRecord(const ::msg_maj::HistoryRecordS& record);
	bool AddRecord(CZhanJiRecord *obj);
	bool CheckAndRelease(CZhanJiRecord *obj); // 仅移除内存，不处理数据库

	void AddUidRecordMap(uint64_t insertUID, CZhanJiRecord* obj);

private:

	std::map<uint64_t, std::map<uint64_t, CZhanJiRecord* > >  mapUidRecords;

	::boost::object_pool<CZhanJiRecord> objpoolZhanJi;
};



#endif