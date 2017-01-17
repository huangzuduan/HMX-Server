#include "DbResult.h"

DbResult::DbResult()
{
	m_bFlag = false;
	m_pRecordSet = NULL;
	m_pCallResult = NULL;
};

DbResult::~DbResult()
{

};

void DbResult::Release()
{
	if(m_pRecordSet)
		m_pRecordSet->Release();
	m_pRecordSet = NULL;
	delete this;
}

DbResult& DbResult::operator=(IDbResult* pResult)
{
	if(this == pResult) return *this;
	memcpy(this,pResult,sizeof(DbResult));
	return *this;
}

IDbRecordSet* DbResult::GetRecordSet()
{
	return m_pRecordSet;
}

void DbResult::DBCallRead()
{
	IDbRecordSet* pRes = GetRecordSet();
	if(!pRes) return;
	m_pCallResult->QueryResult(pRes, pRes->Rows());
	S_SAFE_DELETE(m_pCallResult);
}

