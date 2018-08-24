#ifndef __CNOTICE_H_
#define __CNOTICE_H_

#include <boost/pool/object_pool.hpp>

#include "Global.hpp"
#include "SrvEngine.h"

/*
 *
 * 通告信息
 *
 */
class CNotice : public zEntry
{
public:
	CNotice() {};
	CNotice(const ::msg_event::NoticeS& notice);
	~CNotice();
	virtual inline uint64_t GetID() { return m_nID; }
	virtual inline uint64_t GetTempID() { return _entry_tempid; }
	virtual inline const std::string& GetName() { return _entry_name; }
	bool LoadConfig(zXMLParser& xml, xmlNodePtr node);

	inline uint64_t GetNoticeID() const { return m_nID; }
	inline const std::string& GetContent() const { return m_strContent; }

private:

	uint64_t m_nID;
	std::string m_strContent;

private:

	time_t GetTimeValue(const std::string& ymdhms);
	int GetDataValue(const char* value);

};

extern ::boost::object_pool<CNotice> objpoolNotice;
#endif

