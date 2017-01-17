#ifndef __DB_RESULT_H_
#define __DB_RESULT_H_

#include "DbConfig.h"

/*-------------------------------------------------------------------
 * @Brief : 异步查询sql的结果集对象 
 * 
 * @Author:hzd 2016:2:18
 *------------------------------------------------------------------*/
class DbResult : public IDbResult
{
public:
	DbResult();
	~DbResult();
	virtual void Release();
	virtual DbResult& operator=(IDbResult* pResult);
	virtual void DBCallRead();
	virtual IDbRecordSet* GetRecordSet();
public:
	bool   			m_bFlag;
	IDbRecordSet*	m_pRecordSet;
	DBQueryFunc*	m_pCallResult;
};

#endif




