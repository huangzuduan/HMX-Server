#ifndef __DB_DATABASE_H_
#define __DB_DATABASE_H_

#include "DbConfig.h"
#include "DbRequest.h"
#include "DbResult.h"

#include <time.h>
#include <queue>

const uint32_t DB_MAX_DBACCESSTIME	= 10;
const uint32_t DB_MAX_STRINGSIZE		= 256;

/*-------------------------------------------------------------------
 * @Brief : MYSQL
 * 
 * @Author:hzd 2012/04/03
 *------------------------------------------------------------------*/
class DbMysql : public IDbBase
{
public:
	DbMysql();
	DbMysql(const DbMysql& other);
	DbMysql& operator= (const DbMysql& other);
	~DbMysql();

	//  
	bool Open(const std::string& ip,uint16_t port, const std::string& username, const std::string& passwd, const std::string& dbname,bool bSQLChk = true );
		
	//  
	void Close();

	// ID 
	virtual uint32_t ID();
	
	//  
	virtual	void Release();

	// sql 
	virtual MYSQL_RES* ResultSQL( const char* pszSQL );

	virtual int32_t ExecSQL(const char* pszSQL, int length = 0);

	// sql 
	virtual bool ExecSQLAsync(const char* pszSQL, DBQueryFunc* queryFun = NULL);

	// sql select 
	virtual bool ExecSelectAsync(const char* tableName, const dbCol *column, const char *swhere = NULL, const char *order = NULL,DBQueryFunc* queryFun = NULL);
	virtual bool ExecInsertAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun = NULL);
	virtual bool ExecDeleteAsync(const char* tableName, const char *swhere = NULL, DBQueryFunc* queryFun = NULL);
	virtual bool ExecUpdateAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun = NULL);

	// 'y 
	virtual IDbResult* GetAsyncResult();
	
	//  
	virtual uint32_t GetRequestSize();

	// 'y 
	virtual uint32_t GetResultSize();

	void WsSQLReplaceStr(char *to,const char *from,unsigned long length);

	//  
	MYSQL* GetDBHandle();

	//  
	bool IsOpen();

	// 
	void Escape(char* pOutSql,const char* pInSql);

	virtual void BinaryToString(const char* pBinaryData,char* o_strBinarayData,int nLen);

	virtual int32_t ExecSelect(const char* tableName,const dbCol *column,const char *where,const char *order,unsigned char** data, unsigned int limit = 0, int32_t limit_from = 0);
	virtual int32_t ExecSelectLimit(const char* tableName,const dbCol *column,const char *where,const char *order, unsigned char* data, unsigned int limit = 1, int32_t limit_from = 0);
	virtual int32_t ExecInsert(const char *tableName,const dbCol *column,const char *data);
	virtual int32_t ExecDelete(const char *tableName,const char *where);
	virtual int32_t ExecUpdate(const char *tableName,const dbCol *column,const char *data,const char *where);

	unsigned int fullSelectDataByRow(MYSQL_ROW row,unsigned long* lengths,const dbCol* column,unsigned char* tmepData);

	/**
	* \brief 
	* \param handleID 
	* \return truefalse
	*/
	bool Commit();
	
	/**
	* \brief 
	* \param handleID 
	* \return truefalse
	*/
	bool Rollback();

	/*
		SQL 
	*/
	virtual int FetchSelectSql(const char* tableName,const dbCol *column,const char *wheres,const char *order,int32_t limit = 0,int32_t limit_from = 0, bool UseBak = false);

private:

	// sql 
	bool CheckSQL(const char* szSQL);

	//  
	bool Reconnect(const std::string& ip , const std::string& user , const std::string& passwd , const std::string& dbname , uint16_t port = MYSQL_PORT, char* dbsocket = NULL, int32_t timeout = 1000 );

	// е 
	virtual int32_t OnThreadCreate();

	//  
	virtual int32_t OnThreadDestroy();

	// sqlк 
	virtual int32_t OnThreadProcess();

private:

	uint32_t	m_nID;							// ID  
	MYSQL	mMysql;						//  有了这个就不会报错,奇怪
	MYSQL*	m_pMysql;						//  
	boost::mutex m_dbMutex;					//  
	boost::mutex m_queueMutex;				// ж 

	bool	m_bOpen;							//  (ж) 
	std::string m_strHost;		// host 
	std::string m_strUser;		// username 
	std::string m_strPasswd;		// password 
	std::string m_strDBName;		//  
		
	std::queue<DbRequest*>	m_queAsyncSQLRequest;	// sql 
	std::queue<IDbResult*>	m_queAsyncSQLResult;	// sqlн 

	unsigned int readTimeout_; //seconds
	unsigned int writeTimeout_;
	unsigned int connectTimeout_;

	friend class DbConnectsMgr;

};


#endif

