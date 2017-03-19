#ifndef __DB_CONFIG_H_
#define __DB_CONFIG_H_

#include <map>
#include <set>
#include <vector>
#include <string>
#include <memory.h>


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/container/set.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#include <mysql.h>


#ifdef WIN32
#define SSleep(ms) Sleep(ms)
#else
#define SSleep(ms) usleep(ms)
#endif

#ifndef S_SAFE_DELETE
#define S_SAFE_DELETE(x) { if (NULL != x) { delete (x); (x) = NULL; } }
#endif

#ifndef S_SAFE_DELETE_VEC
#define S_SAFE_DELETE_VEC(x) { if (NULL != x) { delete [] (x); (x) = NULL; } }
#endif

#ifdef WIN32
typedef __int64                     int64;
#else
typedef int64_t                     int64;
#endif
typedef unsigned long long          uint64;
typedef wchar_t						wchar;
typedef unsigned char				uchar;
typedef char						int8;
typedef unsigned char				uint8;
typedef short						int16;
typedef unsigned short				uint16;
typedef int							int32;
typedef unsigned int				uint32;
typedef float						float32;
typedef double						float64;

enum EDbMode
{
	E_DB_MODE_NONE = 0,
	E_DB_MODE_READ,
	E_DB_MODE_EDIT
};

const int32	DB_MAX_SQL = 50000;

#define MAX_SQL_BUFFER 1024

#define MAX_SELECT_BUFFER 1000000


/*-------------------------------------------------------------------
 * @Brief : 单个字段信息 
 * 
 * @Author:hzd 2015:12:28
 *------------------------------------------------------------------*/
class IDbData
{
public:
		
	virtual	void Release() = 0;
	virtual char* GetValue() = 0;
	virtual uint32 GetLen() const = 0;
	virtual uint32 GetType() const = 0;

	virtual operator char() const = 0;
	virtual operator uchar() const = 0;
	virtual operator int16() const = 0;
	virtual operator uint16() const = 0;
	virtual operator int32() const = 0;
	virtual operator uint32() const = 0;
	virtual operator int64() const = 0;
	virtual operator uint64() const = 0;
	virtual operator float32() const = 0;
	virtual operator float64() const = 0;
	virtual operator char*() const = 0;
	virtual operator const char*() const = 0;
		
	virtual IDbData& operator = ( char chOp ) = 0;
	virtual IDbData& operator = ( uchar chOp ) = 0;
	virtual IDbData& operator = ( int16 nOp ) = 0;
	virtual IDbData& operator = ( uint16 unOp ) = 0;
	virtual IDbData& operator = ( int32 iOp ) = 0;
	virtual IDbData& operator = ( uint32 uOp ) = 0;
	virtual IDbData& operator = ( int64 uOp ) = 0;
	virtual IDbData& operator = ( uint64 uOp ) = 0;
	virtual IDbData& operator = ( float32 fltOp ) = 0;
	virtual IDbData& operator = ( float64 dblOp ) = 0;
	virtual IDbData& operator = ( const char* szVal ) = 0;
};

/*-------------------------------------------------------------------
 * @Brief : 行记录操作类 
 * 
 * @Author:hzd 2015:12:28
 *------------------------------------------------------------------*/
class IDbRecord
{
public:
		
	virtual	void Release() = 0;
	virtual IDbData& Field( uint32 idx ) = 0;
	virtual IDbData& Field( uint32 idx ) const = 0;
	virtual IDbData& Field( const char* pszName ) = 0;
	virtual IDbData& Field( const char* pszName ) const = 0;
	virtual uint32 GetFieldCount() = 0;
	virtual IDbData& Key() = 0;
	virtual	void* GetRowBuff() = 0;
	virtual uint32 GetRecordSize() = 0;
};

/*-------------------------------------------------------------------
 * @Brief : 多行或表操作类 
 * 
 * @Author:hzd 2015:12:28
 *------------------------------------------------------------------*/
class IDbRecordSet
{
public:	
	virtual bool Create(MYSQL_RES* pRES) = 0;
	virtual	void Release() = 0;
	virtual IDbRecord* GetRecord() const = 0;
	virtual void* GetRecordData(uint32 nIndex) const = 0;
	virtual int32 Rows() const = 0;
	virtual void Move(uint32 index) = 0;
};

// 回调类型 
enum EResultHandlerType 
{
	ECALLBACK_NULL			= 0,	// 非法参数 
	ECALLBACK_DB_NULL		= 1,	// 执行数据后无需回调 
	ECALLBACK_DB_HANDLER	= 2,	// 数据结果回调（查询完后调回） 
};

// 数据库回调 
struct DBQueryFunc
{
	virtual void QueryResult(IDbRecordSet* pSet,int32 nCount)
	{
	}
};

/*-------------------------------------------------------------------
 * @Brief : 操作结果回调类(异步操作才用到)
 * 
 * @Author:hzd 2015:12:28
 *------------------------------------------------------------------*/
class IDbResult
{
public:
	virtual void Release() = 0;
	virtual IDbResult& operator=(IDbResult* pResult) = 0;
	virtual void DBCallRead() = 0;
	virtual IDbRecordSet* GetRecordSet() = 0;
};

typedef struct
{
	const char *name;	/**< 字段名字 */
	int32 type;			/**< ZEBRA数据类型 */
	int32 size;			/**< 数据大小 */
} dbCol;

enum
{
	DB_BYTE,    /**< BYTE类型 1字节长度 */
	DB_CHAR,    /**< CHAR类型 1字节长度 */
	DB_WORD,    /**< WORD类型 2字节长度 */
	DB_DWORD,    /**< DWORD类型 4字节长度 */
	DB_FLOAT,	 /**< DB_FLOAT类型 4字节长度 */
	DB_QWORD,    /**< QWORD类型 8字节长度 */
	DB_STR,      /**< 字符串类型 */
	DB_BIN,      /**< 二进制数据类型 */
	DB_ZIP,      /**< zip压缩数据类型 */
	DB_BIN2,    /**< 扩展二进制数据类型 这个struct 结构的二进制字段前多加一个DWORD size字段,mysql 字段类型为blob , 本程序不支持，变长无法长久放缓存 */
	DB_ZIP2      /**< 扩展zip压缩数据类型 */
};

typedef struct StBinData{
	uint32 len;
	char pData[5000];
} BDATA;

typedef std::vector<BDATA> BINDDATA;
typedef std::vector<BDATA>::iterator BINDDATAIT;

/*-------------------------------------------------------------------
 * @Brief : 数据库操作父类 
 * 
 * @Author:hzd 2015:12:28
 *------------------------------------------------------------------*/
class IDbBase
{
public:

	// 常用接口 
	virtual uint32 ID() = 0;
	virtual	void Release() = 0;
	virtual void BinaryToString(const char* pBinaryData,char* o_strBinarayData,int nLen) = 0;
	virtual void Escape(char* pOutSql,const char* pInSql) = 0;
	virtual MYSQL_RES* ResultSQL(const char* pszSQL ) = 0;
	virtual int32 ExecSQL(const char* pszSQL,int length = 0 ) = 0;

	// 用于获得未确定总数量定长的行，用二维指针char来存取 {{[0...]},{[1...]},...},**data 为execselect内部创建内存
	virtual int32 ExecSelect(const char *tableName,const dbCol *column,const char *where,const char *order,unsigned char** data, unsigned int limit = 0, int32 limit_from =0) = 0;

	// 用于获得定长的struct确定Limit的数据，用一维指针char来存取 {[0][1][2]...},*data 为execselect为外部创建好内存并保证足够用 
	// 也可于用于获得一个变长的struct，外部创建足够变长的内存(往往是栈内存) 
	virtual int32 ExecSelectLimit(const char* tableName, const dbCol *column, const char *where, const char *order, unsigned char* data, unsigned int limit = 1, int32 limit_from =0) = 0;
	virtual int32 ExecInsert(const char *tableName,const dbCol *column,const char *data) = 0;
	virtual int32 ExecDelete(const char *tableName,const char *where) =0;
	virtual int32 ExecUpdate(const char *tableName,const dbCol *column,const char *data,const char *where) =0;

	// 异步接口 
	virtual uint32 GetRequestSize() = 0;
	virtual uint32 GetResultSize() = 0;
	virtual IDbResult* GetAsyncResult() = 0;
	virtual bool ExecSQLAsync(const char* pszSQL, DBQueryFunc* pCallBack ) =0 ;
	virtual bool ExecSelectAsync(const char* tableName, const dbCol *column, const char *where = NULL, const char *order = NULL, DBQueryFunc* queryFun = NULL) = 0;
	virtual bool ExecInsertAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun = NULL) = 0;
	virtual bool ExecDeleteAsync(const char* tableName, const char *where = NULL, DBQueryFunc* queryFun = NULL) = 0;
	virtual bool ExecUpdateAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun = NULL) = 0;

	// 构建SQL语句 
	virtual int FetchSelectSql(const char* tableName, const dbCol *column, const char *where, const char *order, int32 limit = 0, int32 limit_from = 0, bool UseBak = false) = 0;

};
extern "C" IDbBase*	DatabaseCreate( const char* szDBServer , const char* szLoginName , const char* szPassword , const char* szDBName , bool bEnableSQLChk = true ); 


#endif
	
	
