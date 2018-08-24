#ifndef _CCACHE_CACHE_H_
#define _CCACHE_CACHE_H_

#include "SrvEngine.h"

class CCacheMail : public zEntry
{
public:
	CCacheMail(const ::msg_maj::MailRecordS& proto);
	~CCacheMail();
	virtual inline uint64_t GetID(){ return m_nMailID; }
	virtual inline uint64_t GetTempID() { return _entry_tempid; }
	virtual inline const std::string& GetName(){ return _entry_name; }
	inline uint64_t GetMailID() const {return m_nMailID;}
	inline void UpdateMailInfo(const ::msg_maj::MailRecordS& mail) { m_mailInfo.CopyFrom(mail); }
	inline const ::msg_maj::MailRecordS& GetMailProto() const { return m_mailInfo;}

private:

	uint64_t m_nMailID;					// 邮件ID
	::msg_maj::MailRecordS	m_mailInfo;	// 邮件数据 
};

#endif // !_CCACHE_MAIL_H_


 

