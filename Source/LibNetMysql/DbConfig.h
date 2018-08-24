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

#ifndef S_SAFE_DELETE
#define S_SAFE_DELETE(x) { if (NULL != x) { delete (x); (x) = NULL; } }
#endif

#ifndef S_SAFE_DELETE_VEC
#define S_SAFE_DELETE_VEC(x) { if (NULL != x) { delete [] (x); (x) = NULL; } }
#endif

typedef float						float32;
typedef double						float64;

enum EDbMode
{
	E_DB_MODE_NONE = 0,
	E_DB_MODE_READ,
	E_DB_MODE_EDIT
};

const int32_t	DB_MAX_SQL = 50000;

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
	virtual uint32_t GetLen() const = 0;
	virtual uint32_t GetType() const = 0;

	virtual operator char() const = 0;
	virtual operator int16_t() const = 0;
	virtual operator uint16_t() const = 0;
	virtual operator int32_t() const = 0;
	virtual operator uint32_t() const = 0;
	virtual operator int64_t() const = 0;
	virtual operator uint64_t() const = 0;
	virtual operator float32() const = 0;
	virtual operator float64() const = 0;
	virtual operator char*() const = 0;
	virtual operator const char*() const = 0;
		
	virtual IDbData& operator = ( char chOp ) = 0;
	virtual IDbData& operator = ( int16_t nOp ) = 0;
	virtual IDbData& operator = ( uint16_t unOp ) = 0;
	virtual IDbData& operator = ( int32_t iOp ) = 0;
	virtual IDbData& operator = ( uint32_t uOp ) = 0;
	virtual IDbData& operator = ( int64_t uOp ) = 0;
	virtual IDbData& operator = ( uint64_t uOp ) = 0;
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
	virtual IDbData& Field( uint32_t idx ) = 0;
	virtual IDbData& Field( uint32_t idx ) const = 0;
	virtual IDbData& Field( const char* pszName ) = 0;
	virtual IDbData& Field( const char* pszName ) const = 0;
	virtual uint32_t GetFieldCount() = 0;
	virtual IDbData& Key() = 0;
	virtual	void* GetRowBuff() = 0;
	virtual uint32_t GetRecordSize() = 0;
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
	virtual void* GetRecordData(uint32_t nIndex) const = 0;
	virtual int32_t Rows() const = 0;
	virtual void Move(uint32_t index) = 0;
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
	virtual void QueryResult(IDbRecordSet* pSet,int32_t nCount)
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
	int32_t type;			/**< ZEBRA数据类型 */
	uint32_t size;		/**< 数据大小 */
	void reset()
	{
		name = NULL;
		type = size = 0;
	}
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
	uint32_t len;
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
	virtual uint32_t ID() = 0;
	virtual	void Release() = 0;
	virtual void BinaryToString(const char* pBinaryData,char* o_strBinarayData,int nLen) = 0;
	virtual void Escape(char* pOutSql,const char* pInSql) = 0;
	virtual MYSQL_RES* ResultSQL(const char* pszSQL ) = 0;
	virtual int32_t ExecSQL(const char* pszSQL,int length = 0 ) = 0;

	// 用于获得未确定总数量定长的行，用二维指针char来存取 {{[0...]},{[1...]},...},**data 为execselect内部创建内存
	virtual int32_t ExecSelect(const char *tableName,const dbCol *column,const char *where,const char *order,unsigned char** data, unsigned int limit = 0, int32_t limit_from =0) = 0;

	// 用于获得定长的struct确定Limit的数据，用一维指针char来存取 {[0][1][2]...},*data 为execselect为外部创建好内存并保证足够用 
	// 也可于用于获得一个变长的struct，外部创建足够变长的内存(往往是栈内存) 
	virtual int32_t ExecSelectLimit(const char* tableName, const dbCol *column, const char *where, const char *order, unsigned char* data, unsigned int limit = 1, int32_t limit_from =0) = 0;
	virtual int32_t ExecInsert(const char *tableName,const dbCol *column,const char *data) = 0;
	virtual int32_t ExecDelete(const char *tableName,const char *where) =0;
	virtual int32_t ExecUpdate(const char *tableName,const dbCol *column,const char *data,const char *where) =0;

	// 异步接口 
	virtual uint32_t GetRequestSize() = 0;
	virtual uint32_t GetResultSize() = 0;
	virtual IDbResult* GetAsyncResult() = 0;
	virtual bool ExecSQLAsync(const char* pszSQL, DBQueryFunc* pCallBack ) =0 ;
	virtual bool ExecSelectAsync(const char* tableName, const dbCol *column, const char *where = NULL, const char *order = NULL, DBQueryFunc* queryFun = NULL) = 0;
	virtual bool ExecInsertAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun = NULL) = 0;
	virtual bool ExecDeleteAsync(const char* tableName, const char *where = NULL, DBQueryFunc* queryFun = NULL) = 0;
	virtual bool ExecUpdateAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun = NULL) = 0;

	// 构建SQL语句 
	virtual int FetchSelectSql(const char* tableName, const dbCol *column, const char *where, const char *order, int32_t limit = 0, int32_t limit_from = 0, bool UseBak = false) = 0;

};
extern "C" IDbBase*	DatabaseCreate( const char* szDBServer , const char* szLoginName , const char* szPassword , const char* szDBName , bool bEnableSQLChk = true ); 


#endif
	
	
