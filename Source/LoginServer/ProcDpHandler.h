#ifndef __PROC_DP_HANDLER_H_
#define __PROC_DP_HANDLER_H_

#include "BaseDefine.h"
#include "Single.h"

class zSession;
struct NetMsgSS;


class ProcDpHandler : public Single<ProcDpHandler>
{
public:
	ProcDpHandler(void);
	~ProcDpHandler(void);

	/*--------------------------------------------
	 *  @brief  : 帐号登录的返回
	 *  @input	: 
	 *  @return :	
	 *-------------------------------------------*/
	void AccountLogin(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	/*--------------------------------------------
	 *  @brief  : 角色数据返回，只有当帐号密码正确
	 *  @input	: 才会有返回，这个判断在dp中
	 *  @return :	
	 *-------------------------------------------*/
	void CharacterList(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	/*--------------------------------------------
	 *  @brief  : 创建角色结果返回
	 *  @input	: 
	 *  @return :	
	 *-------------------------------------------*/
	void RoleCreateResult(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);
};

#endif



