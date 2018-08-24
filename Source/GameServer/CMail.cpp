#include "CMail.hpp"
#include "CWorld.hpp"
#include "CPlayer.hpp"
#include "CMailMgr.hpp"
#include "GameService.h"

::boost::object_pool<CMail> objpoolMail;

CMail::CMail(const ::msg_maj::MailRecordS& mail):m_unMailID(_entry_id), m_unFromID(0), m_unToID(0), m_nRoomCards(0), m_eMark(::msg_maj::mark_t_unread), m_nCreateTime(0),m_nFetchTime(0) ,m_expireTime(0)
{
	this->m_unMailID = mail.id();
	this->m_eType = (::msg_maj::mail_type)mail.type();
	this->m_unFromID = mail.from_id();
	this->m_strFromName = mail.from_name();
	this->m_unToID = mail.to_id();
	this->m_strToName = mail.to_name();
	this->m_strTitle = mail.title();
	this->m_strContent = mail.content();
	this->m_nRoomCards = mail.room_cards();
	this->m_eMark = (::msg_maj::mark_type)mail.mark();
	this->m_nCreateTime = mail.create_time();
	this->m_nFetchTime = mail.fetch_time();
	this->m_expireTime = this->m_nCreateTime + 7 * 86400L;
}

CMail::~CMail()
{

}

bool CMail::DoRead()
{
	if ( ::msg_maj::mark_t_unread == GetMark())
	{
		SetMark(::msg_maj::mark_t_readed);
		Save();
		return true;
	}
	return false;
}

bool CMail::DoFetchAward()
{
	if (::msg_maj::mark_t_readed == GetMark())
	{
		if (GetRoomCards() > 0 && GetFetchTime() == 0)
		{
			CPlayer* pPlayer = CWorld::Instance()->GetPlayerByUUID(this->m_unToID);
			if (NULL == pPlayer)
			{
				return false;
			}

			SetFetchTime(time(NULL));

			pPlayer->AddRoomCards(m_nRoomCards, ::fogs::proto::msg::log_t_roomcard_add_mail);
			pPlayer->SendRoomCards();

			Save();

			return true;
		}
	}
	return false;
}

bool CMail::DoDelete()
{
	if (::msg_maj::mark_t_readed == GetMark())
	{
		if (GetRoomCards() > 0 && GetFetchTime() < 1)
		{
			return false; // 还未领取奖励
		}

		SetMark(::msg_maj::mark_t_deleted);
		Save();
		return true;
	}
	return false;
}

void CMail::Save()
{

	::fogs::proto::msg::SaveMailRequest proto;

	::msg_maj::MailRecordS* recond = proto.mutable_records();
	if (recond)
	{
		recond->set_id(this->m_unMailID);
		recond->set_type(this->m_eType);
		recond->set_from_id(this->m_unFromID);
		recond->set_from_name(this->m_strFromName);
		recond->set_to_id(this->m_unToID);
		recond->set_to_name(this->m_strToName);
		recond->set_title(this->m_strTitle);
		recond->set_content(this->m_strContent);
		recond->set_room_cards(this->m_nRoomCards);
		recond->set_mark(this->m_eMark);
		recond->set_create_time(this->m_nCreateTime);
		recond->set_fetch_time(this->m_nFetchTime);
		GameService::Instance()->SendToDp(::comdef::msg_ss, ::msg_maj::SaveMailRequestID, proto);
	}

}

bool CMail::IsExpire()
{
	return time(NULL) > m_expireTime;
}


::boost::object_pool<CMailSysLog> objpoolMailSysLog;

CMailSysLog::CMailSysLog(const ::msg_maj::MailSystemLogS& mail) :m_unUnID(_entry_id), m_unMailID(0), m_unUID(0), m_eMark(::msg_maj::mark_t_unread), m_nCreateTime(0), m_nFetchTime(0), m_expireTime(0)
{
	this->m_unUnID = mail.id();
	this->m_unMailID = mail.mail_id();
	this->m_unUID = mail.uid();
	this->m_eMark = (::msg_maj::mark_type)mail.mark();
	this->m_nCreateTime = mail.create_time();
	this->m_nFetchTime = mail.fetch_time();
	this->m_expireTime = this->m_nCreateTime + 7 * 86400L;
}

CMailSysLog::~CMailSysLog()
{

}

uint32_t CMailSysLog::GetRoomCards()
{
	CMail* entry = NULL;
	if (CMailMgr::Instance()->GetByID(entry, this->GetMailID()))
	{
		return entry->GetRoomCards();
	}
	return 0;
}

bool CMailSysLog::DoRead()
{
	if (::msg_maj::mark_t_unread == GetMark())
	{
		SetMark(::msg_maj::mark_t_readed);
		Save();
		return true;
	}
	return false;
}

bool CMailSysLog::DoFetchAward()
{
	if (::msg_maj::mark_t_readed == GetMark())
	{
		if (GetRoomCards() > 0 && GetFetchTime() == 0)
		{
			CPlayer* pPlayer = CWorld::Instance()->GetPlayerByUUID(this->m_unUID);
			if (NULL == pPlayer)
			{
				return false;
			}

			SetFetchTime(time(NULL));

			pPlayer->AddRoomCards(GetRoomCards(), ::fogs::proto::msg::log_t_roomcard_add_mail);
			pPlayer->SendRoomCards();

			Save();

			return true;
		}
	}
	return false;
}

bool CMailSysLog::DoDelete()
{
	if (::msg_maj::mark_t_readed == GetMark())
	{
		if (GetRoomCards() > 0 && GetFetchTime() < 1)
		{
			return false; // 还未领取奖励
		}

		SetMark(::msg_maj::mark_t_deleted);
		Save();
		return true;
	}
	return false;
}

void CMailSysLog::Save()
{

	::fogs::proto::msg::SaveMailSystemLogRequest proto;

	::msg_maj::MailSystemLogS* recond = proto.mutable_records();
	if (recond)
	{
		recond->set_id(this->m_unUnID);
		recond->set_mail_id(this->m_unMailID);
		recond->set_uid(this->m_unUID);
		recond->set_mark(this->m_eMark);
		recond->set_create_time(this->m_nCreateTime);
		recond->set_fetch_time(this->m_nFetchTime);
		GameService::Instance()->SendToDp(::comdef::msg_ss, ::msg_maj::SaveMailSysLogRequestID, proto);
	}

}

bool CMailSysLog::IsExpire()
{
	return time(NULL) > m_expireTime;
}