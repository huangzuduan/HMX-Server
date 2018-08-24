#ifndef __LOGIN_ACCOUNT_MGR_H_
#define __LOGIN_ACCOUNT_MGR_H_


#include "Single.h"
#include "SrvEngine.h"

/*------------------------------------------------------------------
 *
 * @Brief : 帐号登录管理，超时失效，防暴力猜测密码检查
 *
 * @Author: hzd 
 * @File  : LoginAccountMgr.h
 * @Date  : 2015/10/19 23:21
 * @Copyright (c) 2015,hzd, All rights reserved.
 *-----------------------------------------------------------------*/

/*------------------------------------------------
 *  帐号信息
 *-----------------------------------------------*/
struct StAccountInfo
{

	int32_t nSessionID;
	int32_t nAccountId;
	char  arrName[MAX_ACCOUNT_LENG];
	int32_t nLastLogin;
	int32_t nIllegalTime;

	StAccountInfo(int32_t _nSessionID)
	{
		nSessionID = _nSessionID;
		nAccountId = nLastLogin = nIllegalTime = 0;
	}

	/*--------------------------------------------
	 *  @brief    :	记录登录
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void AddLoginTimes()
	{
		nIllegalTime++;
	}

	/*--------------------------------------------
	 *  @brief    :	是否非法
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	bool CheckLoginIllegal()
	{
		if( nIllegalTime > 3 )
		{
			nIllegalTime = 0;
			return true;
		}
		return false;
	}
};


class LoginAccountMgr : public Single<LoginAccountMgr>
{
public:

	LoginAccountMgr(void);
	~LoginAccountMgr(void);

	/*--------------------------------------------
	 *  @brief    :	定义更新
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void Update(int32_t nServerTimes);

	/*--------------------------------------------
	 *  @brief    :	获得帐号信息
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	StAccountInfo* GetAccountInfo(int32_t nFepSessionId);

	/*--------------------------------------------
	 *  @brief    :	增加帐号记录
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	StAccountInfo* AddAccountInfo(int32_t nFepSessionId);

	/*--------------------------------------------
	 *  @brief    :	删除一个帐号记录
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void RemoveAccountInfo(int32_t nFepSessionId);

private:

	typedef std::map<int32_t,StAccountInfo*> AccountInfoMapType;

	AccountInfoMapType m_mapAccountInfo;

	zObjPool<StAccountInfo> s_cAccountInfoFactory;

};

#endif



