#ifndef _CMAIL_H_
#define _CMAIL_H_

#include <boost/pool/object_pool.hpp>

#include "Global.hpp"
#include "SrvEngine.h"

/*
 
	单个邮件:邮件ID、类型、发送者、接收者、标题、内容、附件、标记、时间

 */

class CPlayer;

class CMail : public zEntry
{
public:
	CMail(const ::msg_maj::MailRecordS& mail);
	~CMail();
	USE_IMP_ENTRY_GetID;
	USE_IMP_ENTRY_TempID;
	USE_IMP_ENTRY_GetName;
	inline uint64_t GetMailID() const { return m_unMailID; }
	inline ::msg_maj::mail_type GetType() const { return m_eType; }
	inline uint64_t GetFromID() const { return m_unFromID; }
	inline const std::string& GetFromName() const { return m_strFromName; };
	inline uint64_t GetToID() const { return m_unToID; }
	inline const std::string& GetToName() const { return m_strToName; }
	inline const std::string& GetTitle() const { return m_strTitle; }
	inline const std::string& GetContent() const { return m_strContent; }
	inline int32_t GetRoomCards() const { return m_nRoomCards; }
	inline ::msg_maj::mark_type GetMark() const { return m_eMark; }
	inline void SetMark(::msg_maj::mark_type _type) { m_eMark = _type; }
	inline time_t GetCreateTime() const { return m_nCreateTime; }
	inline void SetFetchTime(time_t _time) { m_nFetchTime = _time; }
	inline time_t GetFetchTime() const { return m_nFetchTime; }

	bool DoRead();
	bool DoFetchAward();
	bool DoDelete();

	void Save();

	bool IsExpire();
	
private:

	uint64_t&				m_unMailID;		// 邮件ID
	::msg_maj::mail_type   m_eType;		// 类型
	uint64_t				m_unFromID;		// 发送者ID
	std::string				m_strFromName;	// 发送者名字
	uint64_t				m_unToID;		// 接收者ID
	std::string				m_strToName;	// 接收者名字
	std::string				m_strTitle;		// 邮件标题
	std::string				m_strContent;	// 邮件内容
	int32_t					m_nRoomCards;	// 奖励房卡
	::msg_maj::mark_type	m_eMark;		// 操作标记
	time_t					m_nCreateTime;	// 创建时间
	time_t					m_nFetchTime;	// 领取时间
	time_t					m_expireTime;	// 过期时间
};

extern ::boost::object_pool<CMail> objpoolMail;


class CMailSysLog : public zEntry
{
public:
	CMailSysLog(const ::msg_maj::MailSystemLogS& mail);
	~CMailSysLog();
	//virtual inline uint64_t GetID() = 0;/* { return _entry_id; };*/
	virtual inline uint64_t GetTempID() { return _entry_tempid; }
	virtual inline const std::string& GetName() { return _entry_name; }
	virtual inline uint64_t GetID() { return m_unUnID; }
	inline uint64_t GetMailID() const { return m_unMailID; }
	inline uint64_t GetUID() const { return m_unUID; }
	inline ::msg_maj::mark_type GetMark() const { return m_eMark; }
	inline void SetMark(::msg_maj::mark_type _type) { m_eMark = _type; }
	inline time_t GetCreateTime() const { return m_nCreateTime; }
	inline void SetFetchTime(time_t _time) { m_nFetchTime = _time; }
	inline time_t GetFetchTime() const { return m_nFetchTime; }
	inline uint32_t GetRoomCards();

	bool DoRead();
	bool DoFetchAward();
	bool DoDelete();

	void Save();
	bool IsExpire();

private:

	uint64_t&				m_unUnID;		// 唯一ID
	uint64_t				m_unMailID;		// 邮件ID
	uint64_t				m_unUID;		// 接收者ID
	::msg_maj::mark_type	m_eMark;		// 操作标记
	time_t					m_nCreateTime;	// 创建时间
	time_t					m_nFetchTime;	// 领取时间
	time_t					m_expireTime;	// 过期时间
};

extern ::boost::object_pool<CMailSysLog> objpoolMailSysLog;

#endif

