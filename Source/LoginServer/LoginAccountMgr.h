#ifndef __LOGIN_ACCOUNT_MGR_H_
#define __LOGIN_ACCOUNT_MGR_H_

#include "BaseDefine.h"
#include "Single.h"
#include "ServerDefine.h"

#include "Utility.h"


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

	int32 nSessionID;
	int32 nAccountId;
	char  arrName[MAX_ACCOUNT_LENG];
	int32 nLastLogin;
	int32 nIllegalTime;

	StAccountInfo(int32 _nSessionID)
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
		int32 now = Zebra::timeTick->getNowTime();
		if(now - nLastLogin < 1) // 小于1称重登都是属于非法 
		{
			nIllegalTime++;
		}
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
	void Update(int32 nServerTimes);

	/*--------------------------------------------
	 *  @brief    :	获得帐号信息
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	StAccountInfo* GetAccountInfo(int32 nFepSessionId);

	/*--------------------------------------------
	 *  @brief    :	增加帐号记录
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	StAccountInfo* AddAccountInfo(int32 nFepSessionId);

	/*--------------------------------------------
	 *  @brief    :	删除一个帐号记录
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void RemoveAccountInfo(int32 nFepSessionId);

private:

	typedef std::map<int32,StAccountInfo*> AccountInfoMapType;


	AccountInfoMapType m_mapAccountInfo;

	static ObjPool<StAccountInfo> s_cAccountInfoFactory;

};

#endif



