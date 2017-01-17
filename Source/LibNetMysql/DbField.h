#ifndef __DB_FIELD_H_
#define __DB_FIELD_H_

#include "DbConfig.h"

class DbRecord;

struct DbFieldInfo
{
	std::string strName;
	uint32 nType;
	uint32 nAttr;//1:NOT NULL,2:PRIMARY KEY,4:UNIQUE KEY,8:Key,16:BLOB,32:UNSIGNED,64:ZEROFILL,128:BINARY
	uint32 nLen;
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
	virtual operator uchar() const;
	virtual operator int16() const;
	virtual operator uint16() const;
	virtual operator int32() const;
	virtual operator uint32() const;
	virtual operator int64() const;
	virtual operator uint64() const;
	virtual operator float32() const;
	virtual operator float64() const;
	virtual operator char*() const;
	virtual operator const char*() const;

	virtual IDbData& operator = ( char chOp );
	virtual IDbData& operator = ( uchar chOp );
	virtual IDbData& operator = ( int16 nOp );
	virtual IDbData& operator = ( uint16 unOp );
	virtual IDbData& operator = ( int32 iOp );
	virtual IDbData& operator = ( uint32 uOp );
	virtual IDbData& operator = ( int64 uOp );
	virtual IDbData& operator = ( uint64 uOp );
	virtual IDbData& operator = ( float32 fltOp );
	virtual IDbData& operator = ( float64 dblOp );
	virtual IDbData& operator = ( const char* szVal );

public:

	const char* GetName() const;
	uint32 GetType() const;
	uint32 GetAttr() const;
	uint32 GetLen() const;
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
	uint16				m_nBufStart;	/* 在行buff中数据的起始位置  */ 

};

#endif

