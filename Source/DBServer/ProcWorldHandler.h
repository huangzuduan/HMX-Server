#ifndef _PROC_WORLD_HANDLER_H_
#define _PROC_WORLD_HANDLER_H_

#include "Includes.h"

class zSession;
struct DUser;
struct NetMsgSS;


class ProcWorldHandler : public Single<ProcWorldHandler>
{
public:
	ProcWorldHandler();
	~ProcWorldHandler();

	void ReqLogin(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	void ReqNotifyServerInfo(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	void ReqNotifySceneInfo(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	void ReqQueryEventInfo(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	void ReqSelectRole(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	void ReqLoadSortLists(zSession* pBaseSession, const NetMsgSS* pMsg, int32 nSize);

	void ReqSaveSortLists(zSession* pBaseSession, const NetMsgSS* pMsg, int32 nSize);

	//////////////////////////////////////////////////////////////////////////

	void CallBackSelectRole(int32 nCSID, DUser* pUserMem);
	

};


#endif

