
#include "DbField.h"
#include "DbRecord.h"

DbField::DbField(const DbFieldInfo rInfo, DbRecord& rDbRecord)
	: m_Info(rInfo), m_bChanged(false), m_rDbRecord(rDbRecord)
{
}		

DbField::DbField(const DbField& rField) 
	: m_Info(rField.m_Info), m_bChanged(false), m_rDbRecord(rField.m_rDbRecord)
{
}


DbField::~DbField()
{
}

void DbField::Release()
{
	delete this;
}

void DbField::FireError()
{

}

DbField& DbField::operator = (const DbField& field)
{
	if( this == &field )
		return *this;

	if ( m_Info.nType != field.m_Info.nType )
	{
		FireError();
	}
	m_bChanged = false;
	return *this;
}		


DbField::operator char() const
{
	if ( (UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_SHORT 
		|| m_Info.nType == FIELD_TYPE_LONG 
		|| m_Info.nType == FIELD_TYPE_FLOAT 
		|| m_Info.nType == FIELD_TYPE_DOUBLE )
	{
		FireError();
	}
	return 0;
}



DbField::operator uchar() const
{ 
	if ( !(UNSIGNED_FLAG & m_Info.nAttr)
		||m_Info.nType == FIELD_TYPE_SHORT 
		|| m_Info.nType == FIELD_TYPE_LONG 
		|| m_Info.nType == FIELD_TYPE_LONGLONG 
		|| m_Info.nType == FIELD_TYPE_FLOAT 
		|| m_Info.nType == FIELD_TYPE_DOUBLE )
	{
		FireError();
	}
	return 0;
}


DbField::operator int16() const
{ 
	if ( (UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_LONG 
		|| m_Info.nType == FIELD_TYPE_LONGLONG 
		|| m_Info.nType == FIELD_TYPE_FLOAT 
		|| m_Info.nType == FIELD_TYPE_DOUBLE )
	{
		FireError();
	}
	return 0;
}

DbField::operator uint16() const
{ 
	if ( !(UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_LONG 
		|| m_Info.nType == FIELD_TYPE_LONGLONG 
		|| m_Info.nType == FIELD_TYPE_FLOAT 
		|| m_Info.nType == FIELD_TYPE_DOUBLE )
	{
		FireError();
	}
	return 0;
}

DbField::operator int32() const
{ 
	if ( (UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_LONGLONG 
		|| m_Info.nType == FIELD_TYPE_FLOAT 
		|| m_Info.nType == FIELD_TYPE_DOUBLE )
	{
		FireError();
	}
	return 0;
}

DbField::operator uint32() const
{
	if ( !(UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_LONGLONG 
		|| m_Info.nType == FIELD_TYPE_FLOAT 
		|| m_Info.nType == FIELD_TYPE_DOUBLE )
	{
		FireError();
	}
	return 0;
}

DbField::operator int64() const
{
	if ( (UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_FLOAT 
		|| m_Info.nType == FIELD_TYPE_DOUBLE )
	{
		FireError();
	}
	return 0;
}

DbField::operator uint64() const
{
	if ( !(UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_FLOAT 
		|| m_Info.nType == FIELD_TYPE_DOUBLE )
	{
		FireError();
	}
	return 0;
}

DbField::operator float32() const
{
	if ( m_Info.nType != FIELD_TYPE_FLOAT )
	{
		FireError();
	}
	return 0;
}

DbField::operator float64() const
{ 
	if ( m_Info.nType != FIELD_TYPE_DOUBLE 
		&&  m_Info.nType != FIELD_TYPE_FLOAT )
	{
		FireError();
	}
	return 0;
}

DbField::operator char* () const
{
	if (m_Info.nType == FIELD_TYPE_STRING || m_Info.nType == FIELD_TYPE_VAR_STRING ||
		m_Info.nType == MYSQL_TYPE_TINY_BLOB || m_Info.nType == MYSQL_TYPE_MEDIUM_BLOB ||
		m_Info.nType == MYSQL_TYPE_LONG_BLOB || m_Info.nType == MYSQL_TYPE_BLOB )
		return NULL;
	FireError();
	return 0;
}

DbField::operator const char* () const
{
	if (m_Info.nType == FIELD_TYPE_STRING || m_Info.nType == FIELD_TYPE_VAR_STRING)
			return 0;
	FireError();
	return 0;
}

IDbData& DbField::operator = ( char cOp )
{
	if ( UNSIGNED_FLAG & m_Info.nAttr )
	{
		FireError();
	}
	m_bChanged = true;
	return *this;
}

IDbData& DbField::operator = ( uchar ucOp )
{
	if ( !(UNSIGNED_FLAG & m_Info.nAttr))
	{
		FireError();
	}

	m_bChanged = true;
	return *this;
}

IDbData& DbField::operator = ( int16 sOp )
{	
	if ( (UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_TINY )
	{
		FireError();
	}

	m_bChanged = true;
	return *this;
}

IDbData& DbField::operator = ( uint16 usOp )
{	
	if ( !(UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_TINY )
	{
		FireError();
	}

	m_bChanged = true;
	return *this;
}

IDbData& DbField::operator = ( int32 iOp )
{	
	if ( (UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_TINY
		|| m_Info.nType == FIELD_TYPE_SHORT )
	{
		FireError();
	}

	m_bChanged = true;
	return *this;
}

IDbData& DbField::operator = ( uint32 uiOp )
{	
	if ( !(UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_TINY
		|| m_Info.nType == FIELD_TYPE_SHORT )
	{
		FireError();
	}

	m_bChanged = true;
	return *this;
}

IDbData& DbField::operator = ( int64 i64Op )
{
	if ( (UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_TINY
		|| m_Info.nType == FIELD_TYPE_SHORT
		|| m_Info.nType == FIELD_TYPE_LONG )
	{
		FireError();
	}

	m_bChanged = true;
	return *this;
}

IDbData& DbField::operator = ( uint64 ui64Op )
{
	if ( !(UNSIGNED_FLAG & m_Info.nAttr)
		|| m_Info.nType == FIELD_TYPE_TINY
		|| m_Info.nType == FIELD_TYPE_SHORT
		|| m_Info.nType == FIELD_TYPE_LONG )
	{
		FireError();
	}

	m_bChanged = true;
	return *this;
}

IDbData& DbField::operator = ( float32 fOp )
{
	if ( m_Info.nType != FIELD_TYPE_FLOAT
		|| m_Info.nType != FIELD_TYPE_DOUBLE ) 
	{
		FireError();
	}

	m_bChanged = true;
	return *this;
}

IDbData& DbField::operator = ( float64 dbOp )
{
	if ( m_Info.nType != FIELD_TYPE_DOUBLE ) 
	{
		FireError();
	}

	m_bChanged = true;
	return *this;
}

IDbData& DbField::operator = (const char* pszVal)
{
	if ( m_Info.nType != FIELD_TYPE_STRING 
		&& m_Info.nType != FIELD_TYPE_VAR_STRING )
	{
		FireError();
	}

	m_bChanged = true;
	return *this;
}

bool DbField::SetValue( const char* pszValue )
{
	m_rDbRecord.StrToBytes(pszValue,GetLen(),GetType());
	m_bChanged = true;
	return true;
}
char* DbField::GetValue()
{
	return 0;
}

const char* DbField::GetName() const
{
	return m_Info.strName.c_str();
}

uint32 DbField::GetType() const
{
	return m_Info.nType;
}

uint32 DbField::GetAttr() const
{
	return m_Info.nAttr;
}

uint32 DbField::GetLen() const
{
	return m_Info.nLen;
}

bool DbField::IsChanged() const
{
	return m_bChanged;
}

void DbField::TagChanged(bool bChange)
{
	m_bChanged = bChange;
}

