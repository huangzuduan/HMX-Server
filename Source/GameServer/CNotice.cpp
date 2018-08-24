#include "CNotice.hpp"


::boost::object_pool<CNotice> objpoolNotice;

CNotice::CNotice(const ::msg_event::NoticeS& notice)
{
	//m_protoData.CopyFrom(notice);
}

CNotice::~CNotice()
{

}

bool CNotice::LoadConfig(zXMLParser& xml, xmlNodePtr node)
{
	xml.getNodePropNum(node, "id", &m_nID, sizeof(m_nID));
	xml.getNodePropStr(node, "content", m_strContent);
	return true;
}

time_t CNotice::GetTimeValue(const std::string& ymdhms)
{
	std::vector<std::string> vecDateTime;
	stringtok(vecDateTime, ymdhms, " ~/-:,");

	if (vecDateTime.size() != 6)
		return 0;

	struct tm tm_;
	int year, month, day, hour, minute, second;
	year = GetDataValue(vecDateTime[0].c_str());
	month = GetDataValue(vecDateTime[1].c_str());
	day = GetDataValue(vecDateTime[2].c_str());
	hour = GetDataValue(vecDateTime[3].c_str());
	minute = GetDataValue(vecDateTime[4].c_str());
	second = GetDataValue(vecDateTime[5].c_str());

	tm_.tm_year = year - 1900;
	tm_.tm_mon = month - 1;
	tm_.tm_mday = day;
	tm_.tm_hour = hour;
	tm_.tm_min = minute;
	tm_.tm_sec = second;
	tm_.tm_isdst = 0;
	time_t t_ = mktime(&tm_);
	return t_;
}

int CNotice::GetDataValue(const char* value)
{
	if (strlen(value) == 2)
	{
		if (value[0] == '0')
			return atoi(&value[1]);
		else
			return atoi(value);
	}
	else
	{
		return atoi(value);
	}
}
