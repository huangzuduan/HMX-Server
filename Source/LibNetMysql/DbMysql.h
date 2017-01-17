#ifndef __DB_DATABASE_H_
#define __DB_DATABASE_H_

#include "DbConfig.h"
#include "DbRequest.h"
#include "DbResult.h"

#include <time.h>
#include <queue>

const uint32 DB_MAX_DBACCESSTIME	= 10;
const uint32 DB_MAX_STRINGSIZE		= 256;

/*-------------------------------------------------------------------
 * @Brief : MYSQL数据库操作类
 * 
 * @Author:hzd 2012/04/03
 *------------------------------------------------------------------*/
class DbMysql : public IDbBase
{
public:
	DbMysql();
	~DbMysql();

	// 打开数据连接 
	bool Open( const char* ip,uint16 port, const char* username,const char* passwd, const char* dbname,bool bSQLChk = true );
		
	// 关闭连接 
	void Close();

	// 获得连接ID 
	virtual uint32 ID();
	
	// 释放自己 
	virtual	void Release();

	// 同步执行sql返回结果 
	virtual MYSQL_RES* ResultSQL( const char* pszSQL );

	virtual int32 ExecSQL(const char* pszSQL, int length = 0);

	// 导步执行sql推荐 
	virtual bool ExecSQLAsync(const char* pszSQL, DBQueryFunc* queryFun = NULL);

	// 导步执行sql select推荐 
	virtual bool ExecSelectAsync(const char* tableName, const dbCol *column, const char *swhere = NULL, const char *order = NULL,DBQueryFunc* queryFun = NULL);
	virtual bool ExecInsertAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun = NULL);
	virtual bool ExecDeleteAsync(const char* tableName, const char *swhere = NULL, DBQueryFunc* queryFun = NULL);
	virtual bool ExecUpdateAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun = NULL);

	// 获得结果集 
	virtual IDbResult* GetAsyncResult();
	
	// 获得请求数 
	virtual uint32 GetRequestSize();

	// 获得结果数 
	virtual uint32 GetResultSize();

	void WsSQLReplaceStr(char *to,const char *from,unsigned long length);

	// 获得数据连接对象 
	MYSQL* GetDBHandle();

	// 是否可用中 
	bool IsOpen();

	// 字符转义
	void Escape(char* pOutSql,const char* pInSql);

	virtual void BinaryToString(const char* pBinaryData,char* o_strBinarayData,int nLen);

	virtual int32 ExecSelect(const char* tableName,const dbCol *column,const char *where,const char *order,unsigned char** data, unsigned int limit = 0, int32 limit_from = 0);
	virtual int32 ExecSelectLimit(const char* tableName,const dbCol *column,const char *where,const char *order, unsigned char* data, unsigned int limit = 1, int32 limit_from = 0);
	virtual int32 ExecInsert(const char *tableName,const dbCol *column,const char *data);
	virtual int32 ExecDelete(const char *tableName,const char *where);
	virtual int32 ExecUpdate(const char *tableName,const dbCol *column,const char *data,const char *where);

	unsigned int fullSelectDataByRow(MYSQL_ROW row,unsigned long* lengths,const dbCol* column,unsigned char* tmepData);

	/**
	* \brief 事务提交
	* \param handleID 操作的链接句柄
	* \return 成功返回true，失败返回false
	*/
	bool Commit();
	
	/**
	* \brief 事务回滚
	* \param handleID 操作的链接句柄
	* \return 成功返回true，失败返回false
	*/
	bool Rollback();

	/*
		构建SQL语句 
	*/
	virtual int FetchSelectSql(const char* tableName,const dbCol *column,const char *wheres,const char *order,int32 limit = 0,int32 limit_from = 0, bool UseBak = false);

private:

	// 检查sql语句是否合法 
	bool CheckSQL(const char* szSQL);

	// 连接数据库 
	MYSQL* Connect(char* ip , char* user , char* passwd , char* dbname , uint16 port = MYSQL_PORT, char* dbsocket = NULL, int32 timeout = 1000 );

	// 数据库线程执行的循环函数 
	virtual int32 OnThreadCreate();

	// 数据库线程销毁函数 
	virtual int32 OnThreadDestroy();

	// 处理sql执行函数 
	virtual int32 OnThreadProcess();

private:

	uint32	m_nID;							// 数据库连接ID  
	MYSQL*	m_pMysql;						// 数据库连接对象 
	boost::mutex m_dbMutex;					// 加入队列锁 
	boost::mutex m_queueMutex;				// 执行队列锁 

	bool	m_bOpen;							// 是否可用 (一般不用判断，可用) 
	char	m_arrHost[DB_MAX_STRINGSIZE];		// 数据库host 
	char	m_arrUser[DB_MAX_STRINGSIZE];		// 数据库username 
	char	m_arrPasswd[DB_MAX_STRINGSIZE];		// 数据库password 
	char	m_arrDBName[DB_MAX_STRINGSIZE];		// 数据库名 
		
	std::queue<DbRequest*>	m_queAsyncSQLRequest;	// sql请求队列 
	std::queue<IDbResult*>	m_queAsyncSQLResult;	// sql执行结果队列 

	friend class DbConnectsMgr;

};


#endif

