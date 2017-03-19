#ifndef __PROC_CLIENT_HANDLER_H_
#define __PROC_CLIENT_HANDLER_H_

#include "BaseDefine.h"
#include "Single.h"

class zSession;
struct NetMsgSS;

class ProcFepHandler : public Single<ProcFepHandler>
{
public:
	ProcFepHandler(void);
	~ProcFepHandler(void);

	void doLoginAccount(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);


public:

	struct t_Account
	{
		t_Account()
		{
			bzero(username,sizeof(username));
			bzero(namepass, sizeof(namepass));
			bzero(checkcode, sizeof(checkcode));
		}
		char username[MAX_ACCNAMESIZE + 1];
		char namepass[MAX_ACCNAMESIZE + 1];
		char checkcode[MAX_NAMESIZE + 1];
	};

};

#endif

