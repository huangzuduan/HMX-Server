#ifndef __DB_FIELD_H_
#define __DB_FIELD_H_

#include "DbConfig.h"

class DbRecord;

struct DbFieldInfo
{
	std::string strName;
	uint32_t nType;
	uint32_t nAttr;//1:NOT NULL,2:PRIMARY KEY,4:UNIQUE KEY,8:Key,16:BLOB,32:UNSIGNED,64:ZEROFILL,128:BINARY
	uint32_t nLen;
};

/*-------------------------------------------------------------------
 * @Brief : 数据库字段类
 * 
 * @Author:hzd 2012/04/03
 *------------------------------------------------------------------*/
class DbField : public IDbData
{
	friend class DbRecord;

public:

	DbField( const DbFieldInfo sInfo  , DbRecord& rDbRecord);
	DbField( const DbField& rField );
	virtual ~DbField();

	DbField& operator = ( const DbField& rField );

public:

	virtual void Release();
	virtual operator char() const;
	virtual operator int16_t() const;
	virtual operator uint16_t() const;
	virtual operator int32_t() const;
	virtual operator uint32_t() const;
	virtual operator int64_t() const;
	virtual operator uint64_t() const;
	virtual operator float32() const;
	virtual operator float64() const;
	virtual operator char*() const;
	virtual operator const char*() const;

	virtual IDbData& operator = ( char chOp );
	virtual IDbData& operator = ( int16_t nOp );
	virtual IDbData& operator = ( uint16_t unOp );
	virtual IDbData& operator = ( int32_t iOp );
	virtual IDbData& operator = ( uint32_t uOp );
	virtual IDbData& operator = ( int64_t uOp );
	virtual IDbData& operator = ( uint64_t uOp );
	virtual IDbData& operator = ( float32 fltOp );
	virtual IDbData& operator = ( float64 dblOp );
	virtual IDbData& operator = ( const char* szVal );

public:

	const char* GetName() const;
	uint32_t GetType() const;
	uint32_t GetAttr() const;
	uint32_t GetLen() const;
	bool IsChanged() const;
	void TagChanged( bool bChange );
	bool SetValue( const char* pszValue );
	char* GetValue();

private:
	static void FireError();
private:

	const DbFieldInfo	m_Info;			/* 字段信息 */ 
	bool				m_bChanged;		/* 是否发生改变 */ 
	DbRecord&			m_rDbRecord;	/* 所在的行 */ 
	uint16_t				m_nBufStart;	/* 在行buff中数据的起始位置  */ 

};

#endif

