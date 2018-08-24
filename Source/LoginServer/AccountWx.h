#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_

#include "SrvEngine.h"

size_t onTokenRefresh(void *buffer, size_t size, size_t nmemb, void *parm);

class AccountWx 
{
public:
	AccountWx(const ::data::AccountWxInfo& proto);
	~AccountWx();
	void Update(const ::data::AccountWxInfo& proto);
	void Timer();

private:

	time_t					m_firstLoginTime;
	time_t					m_lastUpdateTime;
	time_t					m_nestUpdateTime;
	::data::AccountWxInfo	m_wxData;

};



#endif




