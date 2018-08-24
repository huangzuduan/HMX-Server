#ifndef __DB_RECORDSET_H_
#define __DB_RECORDSET_H_

#include "DbConfig.h"
#include "DbField.h"
#include "DbMysql.h"

class DbRecord;

/*-------------------------------------------------------------------
 * @Brief : 数据库多行操作类
 * 
 * @Author:hzd 2012/04/03
 *------------------------------------------------------------------*/
class DbRecordSet : public IDbRecordSet
{
	friend class DbRecord;
public:

	DbRecordSet();
	virtual ~DbRecordSet();

	virtual bool Create(MYSQL_RES* pRES);
	virtual void Release();
	virtual IDbRecord* GetRecord() const;
	virtual void* GetRecordData(uint32_t nIndex) const;
	virtual int32_t Rows() const;
	virtual void Move( uint32_t nIndex );
	std::vector<DbFieldInfo>& GetFieldInfos();
	int32_t FieldsCount() const;

	void Remove( DbRecord* pRec );
	char* GetTableName();
	const DbFieldInfo&	GetFieldInfo( int32_t nIndex ) const;

private:                                                                                                                                                                                                                                                                                                                                                                           

	DbRecordSet( const DbRecordSet& res );
	DbRecordSet& operator= ( const DbRecordSet& res );

private:

	int32_t		m_nCursor;
	char		m_arrTableName[32];
	uint32_t		m_nKeyIndex;			// 
	uint32_t		m_nAutoIncIndex;

	std::vector<DbRecord*>		m_vecRecord;
	std::vector<DbFieldInfo>		m_vecFieldInfo;

};

#endif



