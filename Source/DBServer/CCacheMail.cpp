#include "CCacheMail.hpp"

CCacheMail::CCacheMail(const ::msg_maj::MailRecordS& proto)
{
	m_mailInfo.CopyFrom(proto);
	m_nMailID = m_mailInfo.id();
}

CCacheMail::~CCacheMail()
{

}