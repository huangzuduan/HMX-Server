#ifndef _CZHAN_JI_H_
#define _CZHAN_JI_H_

#include "SrvEngine.h"

/*
 *  
 *   房间总场次历史信息
 *
 */
class CZhanJiRecord : public zEntry
{
public:
	CZhanJiRecord(const ::msg_maj::HistoryRecordS& fromRecord);
	~CZhanJiRecord() {}
	virtual inline uint64_t GetID(){ return nRecordID; }
	virtual inline uint64_t GetTempID() { return _entry_tempid; }
	virtual inline const std::string& GetName(){ return _entry_name; }
	inline uint64_t GetRecordID() const { return nRecordID;}
	inline uint64_t GetRecordTime() const { return m_protoData.time();}
	inline uint64_t GetPlayer1() const { return m_nPlayer1; }
	inline uint64_t GetPlayer2() const { return m_nPlayer2; }
	inline uint64_t GetPlayer3() const { return m_nPlayer3; }
	inline uint64_t GetPlayer4() const { return m_nPlayer4; }

	const inline ::msg_maj::HistoryRecordS& GetHistoryRecordS() const { return m_protoData; };

	void AddInnRecord(const ::msg_maj::InnRecordS& innRecord,const::msg_maj::InnReplayActionS& innReplay);
	bool IsExpire();
	void CountTotalScore();
	void ClearReplayList();

	inline void SetIsFinished(bool _isFinish) { m_bIsFinish = _isFinish; }
	inline bool GetIsFinished() const { return m_bIsFinish; }

private:

	uint64_t nRecordID;	// 房间ID ==>id

	uint64_t m_nPlayer1;
	uint64_t m_nPlayer2;
	uint64_t m_nPlayer3;
	uint64_t m_nPlayer4;

	::msg_maj::HistoryRecordS m_protoData;

	time_t m_expireTime; // 过期时间 
	bool m_bIsFinish;	// 是否已经结束

};



#endif
