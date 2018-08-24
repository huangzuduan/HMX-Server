#include "CCacheMailMgr.hpp"
#include "CCacheMail.hpp"
#include "GameService.h"
#include "MysqlProtobufHelper.h"

::boost::object_pool<CCacheMail> g_objpoolCacheMail;

CCacheMailMgr::CCacheMailMgr()
{

}

CCacheMailMgr::~CCacheMailMgr()
{
}

bool CCacheMailMgr::AddMail(CCacheMail* pMail)
{
	bool bRet = zEntryMgr< zEntryID<0> >::addEntry(pMail);
	if (!bRet)
	{
		return false;
	}

	std::map<uint64_t, std::map<uint64_t, CCacheMail*, std::greater<uint64_t> > >::iterator it = mapUidRecords.find(pMail->GetMailProto().to_id());
	if (it != mapUidRecords.end())
	{
		it->second.insert(std::make_pair(pMail->GetMailProto().id(), pMail));
	}
	else
	{
		std::map<uint64_t, CCacheMail*, std::greater<uint64_t> > mapUidR;
		mapUidR.insert(std::make_pair(pMail->GetMailProto().id(), pMail));
		mapUidRecords.insert(std::make_pair(pMail->GetMailProto().to_id(), mapUidR));
	}

	return true;
}

CCacheMail* CCacheMailMgr::GetByID(uint64_t uid)
{
	return (CCacheMail*)zEntryMgr< zEntryID<0> >::getEntryByID(uid);
}

void CCacheMailMgr::RemoveMail(CCacheMail* pMail)
{
	zEntryMgr< zEntryID<0> >::removeEntry(pMail);
}

bool CCacheMailMgr::GetByUid(uint64_t uid, std::vector<CCacheMail*>& vecMail)
{
	std::map<uint64_t, std::map<uint64_t, CCacheMail*, std::greater<uint64_t> > >::iterator it = mapUidRecords.find(uid);
	if (it != mapUidRecords.end())
	{
		std::map<uint64_t, CCacheMail*, std::greater<uint64_t> >& uidMails = it->second;
		std::map<uint64_t, CCacheMail*, std::greater<uint64_t> >::iterator it2 = uidMails.begin();
		for (; it2 != uidMails.end(); ++it2)
		{
			vecMail.push_back(it2->second);
		}
	}

	if (vecMail.empty())
	{
		std::set<uint64_t>::iterator it = setUidQuery.find(uid);
		if (it != setUidQuery.end())
		{
			return true;
		}
	}
	else
	{
		return true;
	}
	return false;
}

void CCacheMailMgr::AddQuery(uint64_t uid)
{
	setUidQuery.insert(uid);
}

void CCacheMailMgr::AddModify(uint64_t uid)
{
	std::map<uint64_t, time_t>::iterator it = m_mapModifys.find(uid);
	if (it != m_mapModifys.end())
	{
		if (it->second <= time(NULL))
		{
			it->second = time(NULL) + 1; // ¼ÓËÙ±£´æ 
		}
		else
		{
			it->second = time(NULL) + g_unModifyDelayTime;
		}
	}
	else
	{
		m_mapModifys.insert(std::make_pair(uid, time(NULL) + g_unModifyDelayTime));
	}
}

void CCacheMailMgr::AddOffline(uint64_t uid)
{
	std::map<uint64_t, time_t>::iterator it = m_mapOfflines.find(uid);
	if (it != m_mapOfflines.end())
	{
		it->second = time(NULL) + g_unOfflineDelayTime;
	}
	else
	{
		m_mapOfflines.insert(std::make_pair(uid, time(NULL) + g_unOfflineDelayTime));
	}
}

void CCacheMailMgr::CheckModify()
{
	time_t now = time(NULL);
	for (std::map<uint64_t, time_t>::iterator it = m_mapModifys.begin(); it != m_mapModifys.end();)
	{
		if (it->second <= now)
		{
			CCacheMail* obj = GetByID(it->first);
			if (obj)
			{
				fogs::proto::msg::SaveMailRequest proto;
				proto.mutable_records()->CopyFrom(obj->GetMailProto());

				const ::msg_maj::MailRecordS& m_proData = proto.records();

				std::stringstream smData;
				smData << "replace into tb_mail(id, type, from_id, from_name, to_id, to_name, title, content, room_cards, mark, create_time, fetch_time ) values("
					<< m_proData.id() << ", "
					<< m_proData.type() << ", "
					<< m_proData.from_id() << ", "
					<< "'" << m_proData.from_name() << "',"
					<< m_proData.to_id() << ", "
					<< "'" << m_proData.to_name() << "',"
					<< "'" << m_proData.title() << "',"
					<< "'" << m_proData.content() << "',"
					<< m_proData.room_cards() << ", "
					<< m_proData.mark() << ", "
					<< m_proData.create_time() << ", "
					<< m_proData.fetch_time() << ") ";
				int32_t nRet = doQuery(*GameService::getMe().GetDataRef(), smData.str());
				if (nRet == 0)
				{
					H::logger->info("tb_mail replace success!");
				}
				else
				{
					H::logger->error("tb_mail replace failure!");
				}
				
			}
			m_mapModifys.erase(it++);
		}
		else
		{
			++it;
		}
	}
}

void CCacheMailMgr::CheckOffline()
{
	time_t now = time(NULL);
	for (std::map<uint64_t, time_t>::iterator it = m_mapOfflines.begin(); it != m_mapOfflines.end();)
	{
		if (it->second <= now)
		{
			CCacheMail* obj = GetByID(it->first);
			if (obj)
			{
				RemoveMail(obj);
				std::map<uint64_t, std::map<uint64_t, CCacheMail*, std::greater<uint64_t> > >::iterator it = mapUidRecords.find(obj->GetMailProto().to_id());
				if (it != mapUidRecords.end())
				{
					std::map<uint64_t, CCacheMail*, std::greater<uint64_t> >& mapSortEntryGreator = it->second;
					std::map<uint64_t, CCacheMail*, std::greater<uint64_t> >::iterator it2 = mapSortEntryGreator.find(obj->GetMailID());
					if (it2 != mapSortEntryGreator.end())
					{
						mapSortEntryGreator.erase(it2);
					}
				}
				g_objpoolCacheMail.destroy(obj);
			}
			m_mapOfflines.erase(it++);
		}
		else
		{
			++it;
		}
	}
}