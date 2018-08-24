#ifndef __DB_RECORD_H_
#define __DB_RECORD_H_

#include "DbConfig.h"
#include "DbRecordSet.h"


class DbField;

/*-------------------------------------------------------------------
 * @Brief : 数据库行操作类
 * 
 * @Author:hzd 2012/04/03
 *------------------------------------------------------------------*/
class DbRecord : public IDbRecord
{
	friend class DbRecordSet;
	friend class DbField;
public:

	virtual	void Release();

	virtual IDbData& Field(uint32_t unIndex);
	virtual IDbData& Field(uint32_t unIndex) const;
	virtual IDbData& Field(const char* pszName);
	virtual IDbData& Field(const char* pszName) const;

	virtual	uint32_t GetFieldCount();
	virtual IDbData& Key();

	const char*	KeyName();
	bool BuildSQLOperation(char* pszOperationSQL);
	
	virtual void* GetRowBuff();

	std::vector<DbField>& GetMFields();
	void StrToBytes(const char* pszValue, uint32_t nLen, int32_t nType);
	virtual uint32_t GetRecordSize();
private:

	DbRecord(const DbRecord& rRecord);
	DbRecord(DbRecordSet& rRecordSet, uint32_t nFieldNum);
	DbRecord(DbRecordSet& rRecordSet, MYSQL_ROW row, uint32_t& nFieldNum);
	DbRecord(DbRecordSet& rRecordSet, MYSQL_FIELD* fields, uint32_t& nFieldNum);
	virtual ~DbRecord();
	void BuildSQLCondition(char* pszConditionSQL);

private:

	DbRecordSet&	m_rRecordSet;
	std::vector<DbField>	m_vecFields;
	char			m_arrRowBuff[655360];/* 每一行内容记录，每个字段记录它的开始位置即可，则一行记录最大为640k */ 
	uint32_t			m_nBuffBegin;		/* 已经使用的位置 */ 

};


#endif

