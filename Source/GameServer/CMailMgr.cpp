#include "CMailMgr.hpp"

#include "CPlayer.hpp"
#include "CWorld.hpp"
#include "GameService.h"

CMailMgr::CMailMgr()
{
}

CMailMgr::~CMailMgr()
{
}

void CMailMgr::OnSystemStart()
{
	fogs::proto::msg::QueryMailRequest proReq;
	proReq.set_uid(0);
	proReq.set_start_index(0);
	GameService::Instance()->SendToDp(::comdef::msg_ss,::msg_maj::QueryMailRequestID, proReq);
}

void CMailMgr::OnlinePlayer(uint64_t uid)
{
	// 加载个人邮件
	fogs::proto::msg::QueryMailRequest proReq2;
	proReq2.set_uid(uid);
	proReq2.set_start_index(0);
	GameService::Instance()->SendToDp(::comdef::msg_ss,::msg_maj::QueryMailRequestID, proReq2);
}

void CMailMgr::OfflinePlayer(uint64_t uid)
{
	std::vector<CMail*> vecEntry;
	GetByUID(vecEntry,uid);
	for (std::vector<CMail*>::iterator it = vecEntry.begin(); it != vecEntry.end(); ++it)
	{
		Release(*it);
	}
}

void CMailMgr::UnSerialize(const ::fogs::proto::msg::QueryMailResponse proto)
{
	for (int i = 0; i < proto.record_list_size(); ++i)
	{
		const ::msg_maj::MailRecordS& recond = proto.record_list(i);
		AddRecord(recond, false);
	}

	if (proto.last_num() == 0 && proto.uid() > 0)
	{
		CPlayer* pPlayer = CWorld::Instance()->GetPlayerByUUID(proto.uid());
		if (pPlayer)
		{
			SendMailList(pPlayer,0);
		}
	}
}


bool CMailMgr::SendToPlayer(const CPlayer& toPlayer, const std::string& title, const std::string& content, int32_t room_cards)
{
	return SendToPlayer(0, "system", toPlayer.GetCharID(), toPlayer.GetCharName(), title, content, room_cards);
}

void CMailMgr::SeendToPlayers(const std::vector< const CPlayer* > &vecPlayer, const std::string& title, const std::string& content, int32_t room_cards)
{
	for (std::vector< const CPlayer* >::const_iterator it = vecPlayer.begin(); it != vecPlayer.end(); ++it)
	{
		SendToPlayer(*(*it), title, content, room_cards);
	}
}

bool CMailMgr::SendToPlayer(uint64_t fromID, const std::string& fromName, uint64_t toUid, const std::string& toName, const std::string& title, const std::string& content, int32_t room_cards)
{
	::msg_maj::MailRecordS  proto;
	zUUID zuuid;
	proto.set_id(zuuid.generate());
	proto.set_type(toUid > 0 ? ::msg_maj::mail_t_system_one : ::msg_maj::mail_t_system_all);
	proto.set_from_id(fromID);
	proto.set_from_name(fromName);
	proto.set_to_id(toUid);
	proto.set_to_name(toName);
	proto.set_title(title);
	proto.set_content(content);
	proto.set_room_cards(room_cards);
	proto.set_mark(::msg_maj::mark_t_unread);
	proto.set_create_time(time(NULL));
	proto.set_fetch_time(0);

	AddRecord(proto, true);

	return true;
}

bool CMailMgr::GetByID(CMail* &entry, int64_t nMailID)
{
	CMail* obj = (CMail*)zEntryMgr< zEntryID<0> >::getEntryByID(nMailID);
	if (obj)
	{
		if (CheckAndRelease(obj))
			return false;
		entry = obj;
		return true;
	}
	return false;
}

bool CMailMgr::GetSys(std::vector<CMail*>& vecEntry,uint64_t uid)
{
	std::map<uint64_t, CMail*, std::greater<uint64_t> >::iterator it = mapSysRecords.begin();
	for (; it != mapSysRecords.end(); ++it)
	{
		CMail* mail = it->second;
		if (mail)
		{
			CMailSysLog* sysLog = CMailSysLogMgr::Instance()->GetByUIDMailID(uid, mail->GetMailID());
			if (sysLog == NULL || sysLog->GetMark() < ::msg_maj::mark_t_deleted)
			{
				vecEntry.push_back(mail);
			}
		}
	}
	return !vecEntry.empty();
}

bool CMailMgr::GetByUID(std::vector<CMail*>& vecEntry, uint64_t uid, uint64_t start_index, int32_t num)
{
	std::map<uint64_t, std::map<uint64_t, CMail*, std::greater<uint64_t> > >::iterator it = mapUidRecords.find(uid);
	if ( it != mapUidRecords.end() )
	{
		std::map<uint64_t, CMail*, std::greater<uint64_t> >& mapSortEntryGreator = it->second;
		std::map<uint64_t, CMail*, std::greater<uint64_t> >::iterator it2 = mapSortEntryGreator.begin();
		for (; it2 != mapSortEntryGreator.end(); ++it2)
		{
			if (CheckAndRelease(it2->second,false))
				continue;

			if (start_index && it2->second->_entry_id >= start_index)
				continue;

			vecEntry.push_back(it2->second);
			if (vecEntry.size() > num)
				break;
		}
	}
	return !vecEntry.empty();
}

bool CMailMgr::GetByUIDMailID(CMail* &entry, uint64_t uid, uint64_t nMailID)
{
	bool bFind = false;
	std::map<uint64_t, std::map<uint64_t, CMail*, std::greater<uint64_t> > >::iterator it = mapUidRecords.find(uid);
	if (it != mapUidRecords.end())
	{
		std::map<uint64_t, CMail*, std::greater<uint64_t> >& mapSortEntryGreator = it->second;
		std::map<uint64_t, CMail*, std::greater<uint64_t> >::iterator it2 = mapSortEntryGreator.find(nMailID);
		if (it2 != mapSortEntryGreator.end())
		{
			entry = it2->second;
			bFind = true;
		}
	}
	return bFind;
}

void CMailMgr::AddRecord(const ::msg_maj::MailRecordS& record, bool isNew)
{
	CMail* obj = objpoolMail.construct(record);
	if (NULL == obj)
	{
		return;
	}

	if (!AddRecord(obj))
	{
		if (!isNew) // 如果是老数据，则更新
		{
			CMail* oldObj;
			if (GetByID(oldObj, obj->GetMailID()))
			{
				Release(oldObj);
				AddRecord(obj);
			}
			else
			{
				objpoolMail.destroy(obj);
				return;
			}
		}
		else
		{
			objpoolMail.destroy(obj);
			return;
		}
	}

	if (isNew)
	{
		obj->Save();
	}

	if (obj->GetToID() > 0) // 玩家邮件
	{
		CPlayer* pPlayer = CWorld::Instance()->GetPlayerByUUID(obj->GetToID());
		if (NULL == pPlayer)
		{
			return;
		}

		std::map<uint64_t, std::map<uint64_t, CMail*, std::greater<uint64_t> > >::iterator it = mapUidRecords.find(obj->GetToID());
		if (it != mapUidRecords.end())
		{
			std::map<uint64_t, CMail*, std::greater<uint64_t> >& secondMap = it->second;
			secondMap.insert(std::make_pair(obj->GetMailID(), obj));
		}
		else
		{
			std::map<uint64_t, CMail*, std::greater<uint64_t> > secondMap;
			secondMap.insert(std::make_pair(obj->GetMailID(), obj));
			mapUidRecords.insert(std::make_pair(obj->GetToID(), secondMap));
		}

		if (isNew)
		{	
			//不要新邮件更新
			::msg_maj::MailListResp sendProto;
			sendProto.set_type(::msg_maj::from_t_add);
			Recond2ProtoC(pPlayer->GetCharID(),*obj, *sendProto.add_record_list());
			pPlayer->SendMsgToClient(::comdef::msg_event, ::msg_event::mail_list_resp, sendProto);
		}
	}
	else // 系统邮件，内存中会存在一份，根据玩家的操作记录标记即可
	{
		std::map<uint64_t, CMail*, std::greater<uint64_t> >::iterator it = mapSysRecords.find(obj->GetMailID());
		if (it == mapSysRecords.end())
		{
			mapSysRecords.insert(std::make_pair(obj->GetMailID(), obj));
		}

		if (isNew)
		{
			::msg_maj::MailListResp sendProto;
			sendProto.set_type(::msg_maj::from_t_add);
			Recond2ProtoC(0,*obj, *sendProto.add_record_list());
			CWorld::Instance()->SendWorldMsg(::comdef::msg_event, ::msg_event::mail_list_resp, sendProto);
		}
	}
}

bool CMailMgr::AddRecord(CMail *obj)
{
	return zEntryMgr< zEntryID<0> >::addEntry(obj);
}

bool CMailMgr::CheckAndRelease(CMail *obj, bool isRelease)
{
	if (obj->IsExpire() || obj->GetMark() == ::msg_maj::mark_t_deleted)
	{
		if (isRelease)
			Release(obj);
		return true;
	}
	return false;
}

void CMailMgr::Release(CMail *obj)
{
	zEntryMgr< zEntryID<0> >::removeEntry(obj);
	std::map<uint64_t, std::map<uint64_t, CMail*, std::greater<uint64_t> > >::iterator it = mapUidRecords.find(obj->GetToID());
	if (it != mapUidRecords.end())
	{
		std::map<uint64_t, CMail*, std::greater<uint64_t> >& mapSortEntryGreator = it->second;
		std::map<uint64_t, CMail*, std::greater<uint64_t> >::iterator it2 = mapSortEntryGreator.find(obj->GetMailID());
		if (it2 != mapSortEntryGreator.end())
		{
			mapSortEntryGreator.erase(it2);
		}
	}
	objpoolMail.destroy(obj);
}

void CMailMgr::TestAdd(const std::string& account)
{
	if (account == "sys")
	{
		SendToPlayer(0, "", 0, "", "Commonsmail", "content", 1);
	}
}

void CMailMgr::Recond2ProtoC(uint64_t uid, const CMail& mail, ::msg_maj::MailRecordC& distProto)
{
	distProto.set_id(mail.GetMailID());
	distProto.set_type(mail.GetType());
	distProto.set_from_name(mail.GetFromName());
	distProto.set_title(mail.GetTitle());
	distProto.set_content(mail.GetContent());
	distProto.set_room_cards(mail.GetRoomCards());
	distProto.set_create_time(mail.GetCreateTime());
	CMailSysLog* sysLog = NULL;
	if (mail.GetToID() < 1)
	{
		sysLog = CMailSysLogMgr::Instance()->GetByUIDMailID(uid, mail.GetMailID());
	}

	if (sysLog == NULL)
	{
		distProto.set_mark(mail.GetMark());
		distProto.set_fetch_time(mail.GetFetchTime());
	}
	else
	{
		distProto.set_mark(sysLog->GetMark());
		distProto.set_fetch_time(sysLog->GetCreateTime());
	}
}

void CMailMgr::SendMailList(CPlayer* pPlayer, int32_t start_index)
{
	if (NULL == pPlayer)
	{
		return;
	}

	::msg_maj::MailListResp sendProto;
	sendProto.set_type(::msg_maj::from_t_list);

	int32_t nCount = 0;
	std::vector<CMail*> vecEntry;
	if (start_index < 1)
	{
		CMailMgr::Instance()->GetSys(vecEntry, pPlayer->GetCharID());
	}

	CMailMgr::Instance()->GetByUID(vecEntry, pPlayer->GetCharID());
	std::vector<CMail*>::iterator it = vecEntry.begin();
	for (; it != vecEntry.end(); ++it)
	{
		if (start_index == 0 || (*it)->GetMailID() < start_index)
		{
			Recond2ProtoC(pPlayer->GetCharID(),*(*it), *sendProto.add_record_list());
			if (++nCount >= 10) break;
		}
	}
	
	pPlayer->SendMsgToClient(::comdef::msg_event, ::msg_event::mail_list_resp, sendProto);

}

void CMailMgr::TestModify()
{
	struct MyStruct : public execEntry<CMail>
	{
		virtual bool exec(CMail *entry)
		{
			entry->DoRead();
			return true;
		}
	};

	MyStruct exec;
	execEveryMail(exec);
	
}

//-----------------
CMailSysLogMgr::CMailSysLogMgr()
{
}

CMailSysLogMgr::~CMailSysLogMgr()
{
}

void CMailSysLogMgr::OnlinePlayer(uint64_t uid)
{
	// 加载公共邮件的个人日志
	fogs::proto::msg::QueryMailSystemLogRequest proReq;
	proReq.set_uid(uid);
	GameService::Instance()->SendToDp(::comdef::msg_ss,::msg_maj:: QueryMailSysLogRequestID, proReq);
}

void CMailSysLogMgr::OfflinePlayer(uint64_t uid)
{
	std::vector<CMailSysLog*> vecEntry;
	GetByUID(vecEntry, uid);
	for (std::vector<CMailSysLog*>::iterator it = vecEntry.begin(); it != vecEntry.end(); ++it)
	{
		Release(*it);
	}
}

void CMailSysLogMgr::UnSerialize(const ::fogs::proto::msg::QueryMailSystemLogResponse proto)
{
	for (int i = 0; i < proto.record_list_size(); ++i)
	{
		const ::msg_maj::MailSystemLogS& recond = proto.record_list(i);
		AddRecord(recond, false);
	}
}

CMailSysLog* CMailSysLogMgr::GetByID(int64_t nMailID)
{
	CMailSysLog* obj = (CMailSysLog*)zEntryMgr< zEntryID<0> >::getEntryByID(nMailID);
	return obj;
}

void CMailSysLogMgr::Release(CMailSysLog *obj)
{
	zEntryMgr< zEntryID<0> >::removeEntry(obj);
	std::map<uint64_t, std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> > >::iterator it = mapUidRecords.find(obj->GetUID());
	if (it != mapUidRecords.end())
	{
		std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> >& mapSortEntryGreator = it->second;
		std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> >::iterator it2 = mapSortEntryGreator.find(obj->GetMailID());
		if (it2 != mapSortEntryGreator.end())
		{
			mapSortEntryGreator.erase(it2);
		}
	}
	objpoolMailSysLog.destroy(obj);
}

CMailSysLog* CMailSysLogMgr::AddRecord(const ::msg_maj::MailSystemLogS& record, bool isNew)
{
	CMailSysLog* obj = objpoolMailSysLog.construct(record);
	if (NULL == obj)
	{
		return NULL;
	}

	if (!AddRecord(obj))
	{
		objpoolMailSysLog.destroy(obj);
		return NULL;
	}

	std::map<uint64_t, std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> > >::iterator it = mapUidRecords.find(obj->GetUID());
	if (it != mapUidRecords.end())
	{
		std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> >& secondMap = it->second;
		std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> >::iterator it2 = secondMap.find(obj->GetMailID());
		if (it2 == secondMap.end())
		{
			secondMap.insert(std::make_pair(obj->GetMailID(), obj));
			if (isNew)
			{
				obj->Save();
			}
		}
	}
	else
	{
		std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> > secondMap;
		secondMap.insert(std::make_pair(obj->GetMailID(), obj));
		mapUidRecords.insert(std::make_pair(obj->GetUID(), secondMap));
		if (isNew)
		{
			obj->Save();
		}
	}
	return obj;
}

bool CMailSysLogMgr::AddRecord(CMailSysLog *obj)
{
	return zEntryMgr< zEntryID<0> >::addEntry(obj);
}


bool CMailSysLogMgr::GetByUID(std::vector<CMailSysLog*>& vecEntry, uint64_t uid, uint64_t start_index, int32_t num)
{
	std::map<uint64_t, std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> > >::iterator it = mapUidRecords.find(uid);
	if (it != mapUidRecords.end())
	{
		std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> >& mapSortEntryGreator = it->second;
		std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> >::iterator it2 = mapSortEntryGreator.begin();
		for (; it2 != mapSortEntryGreator.end(); ++it2)
		{
			if (start_index && it2->second->_entry_id >= start_index)
				continue;

			vecEntry.push_back(it2->second);
			if (vecEntry.size() > num)
				break;
		}
	}
	return !vecEntry.empty();
}

CMailSysLog* CMailSysLogMgr::GetByUIDMailID(uint64_t uid, uint64_t mail_id)
{
	std::map<uint64_t, std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> > >::iterator it = mapUidRecords.find(uid);
	if (it != mapUidRecords.end())
	{
		std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> >& mapSortEntryGreator = it->second;
		std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> >::iterator it2 = mapSortEntryGreator.begin();
		for (; it2 != mapSortEntryGreator.end(); ++it2)
		{
			if (it2->second->GetMailID() == mail_id)
			{
				return it2->second;
			}
		}
	}
	return NULL;
}



