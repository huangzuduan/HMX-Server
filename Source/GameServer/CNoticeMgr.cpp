#include "CNoticeMgr.hpp"
#include "CNotice.hpp"
#include "CWorld.hpp"
#include "CPlayer.hpp"
#include "CommFun.h"

CNoticeMgr::CNoticeMgr(): m_unMaxID(0)
{

}

CNoticeMgr::~CNoticeMgr()
{

}

void CNoticeMgr::Load(const std::string& filename)
{
	zXMLParser xml = zXMLParser();
	if (!xml.initFile(filename))
	{
		return;
	}

	xmlNodePtr rootNode = xml.getRootNode("notices");
	if (!rootNode)
	{
		return;
	}

	xmlNodePtr notityNode = xml.getChildNode(rootNode, "notice");
	while (notityNode)
	{
		CNotice* obj = objpoolNotice.construct();
		if (NULL == obj) 
			return;

		obj->LoadConfig(xml, notityNode);
		if (!zEntryMgr< zEntryID<0> >::addEntry(obj))
		{
			ASSERT(0);
			objpoolNotice.destroy(obj);
			return;
		}
		notityNode = xml.getNextNode(notityNode, "notice");
	}
	return;
}

void CNoticeMgr::Release()
{
	// 清除表格的数据
	struct MyStruct : public execEntry<CNotice>
	{
		virtual bool exec(CNotice *entry)
		{
			CNoticeMgr::Instance()->Remove(entry);
			return true;
		}
	};
	MyStruct exec;
	CNoticeMgr::Instance()->execEveryNotice(exec);
}

CNotice* CNoticeMgr::GetNotice(uint64_t notice_id)
{
	return (CNotice*)zEntryMgr< zEntryID<0> >::getEntryByID(notice_id);
}

void CNoticeMgr::Remove(CNotice* obj)
{
	zEntryMgr< zEntryID<0> >::removeEntry(obj);
	objpoolNotice.destroy(obj);
}

void CNoticeMgr::AddRecord(const ::msg_event::NoticeS& notice, bool isNew)
{
	CNotice* obj = objpoolNotice.construct(notice);
	if (NULL == obj)
	{
		return;
	}

	if (!zEntryMgr< zEntryID<0> >::addEntry(obj))
	{
		objpoolNotice.destroy(obj);
		return;
	}

	if (obj->GetNoticeID() > m_unMaxID)
	{
		m_unMaxID = obj->GetNoticeID();
	}

	if (isNew)
	{
		Broadcast(obj);
	}
}

bool CNoticeMgr::GetByLastest(std::vector<CNotice*>& vecEntry)
{
	struct MyStruct : public execEntry<CNotice>
	{
		MyStruct(std::vector<CNotice*>& _vecEntry):m_vecEntry(_vecEntry)
		{
		}
		virtual bool exec(CNotice *entry)
		{
			//if (entry->IsBetweenTime())
			{
				m_vecEntry.push_back(entry);
			}
			return true;
		}
		std::vector<CNotice*>& m_vecEntry;
	};

	MyStruct exec(vecEntry);
	execEveryNotice(exec);
	return true;
}

void CNoticeMgr::SendNoticeList(CPlayer* pPlayer)
{
	std::vector<CNotice*> vecEntry;
	GetByLastest(vecEntry);

	::msg_event::NoticeListResp sendProto;
	sendProto.set_type(::msg_event::opt_t_all_list);
	for (std::vector<CNotice*>::iterator it = vecEntry.begin(); it != vecEntry.end(); ++it)
	{
		CNotice* pNotice = *it;
		if (pNotice)
		{
			::msg_event::NoticeS* info = sendProto.add_notice_list();
			if (info)
			{
				info->set_id(pNotice->GetNoticeID());
				info->set_begin_time(0);
				info->set_break_time(0);
				info->set_minute_time(0);
				info->set_content(pNotice->GetContent());
				info->set_sort_level(0);
			}
		}
	}

	if (sendProto.notice_list_size())
	{
		if (pPlayer)
		{
			pPlayer->SendMsgToClient(::comdef::msg_event, ::msg_event::notice_list_resp, sendProto);
		}
		else
		{
			const std::map<uint64_t, CPlayer*>& mapPlayeres = CWorld::Instance()->GetOnlinePlayers();
			for (std::map<uint64_t, CPlayer*>::const_iterator iter = mapPlayeres.begin(); iter != mapPlayeres.end(); ++iter)
			{
				CPlayer* pPlayer = iter->second;
				if (pPlayer)
				{
					pPlayer->SendMsgToClient(::comdef::msg_event, ::msg_event::notice_list_resp, sendProto);
				}
			}
		}
	}
}

void CNoticeMgr::SendNewNotice(CPlayer* pPlayer, const CNotice* pNotice)
{
	::msg_event::NoticeListResp sendProto;
	sendProto.set_type(::msg_event::opt_t_new_one);
	::msg_event::NoticeS* info = sendProto.add_notice_list();
	if (info)
	{
		info->set_id(pNotice->GetNoticeID());
		info->set_begin_time(0);
		info->set_break_time(0);
		info->set_minute_time(0);
		info->set_content(pNotice->GetContent());
		info->set_sort_level(0);
	}

	if (sendProto.notice_list_size())
	{
		pPlayer->SendMsgToClient(::comdef::msg_event, ::msg_event::notice_list_resp, sendProto);
	}
}

void CNoticeMgr::Broadcast(const CNotice* pNotice)
{
	const std::map<uint64_t, CPlayer*>& mapPlayeres = CWorld::Instance()->GetOnlinePlayers();
	for (std::map<uint64_t, CPlayer*>::const_iterator iter = mapPlayeres.begin(); iter != mapPlayeres.end(); ++iter)
	{
		CPlayer* pPlayer = iter->second;
		if (pPlayer)
		{
			CNoticeMgr::Instance()->SendNewNotice(pPlayer, pNotice);
		}
	}
}

time_t CNoticeMgr::GetTimeValue(const std::string& ymdhms)
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

int CNoticeMgr::GetDataValue(const char* value)
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
