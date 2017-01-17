#include "DbMysql.h"

#include <iostream>
#include <string.h>

#include "DbRecordSet.h"
#include "DbResult.h"
#include "DbRequest.h"

DbMysql::DbMysql():m_pMysql(NULL),m_bOpen(false) 
{	
	memset(m_arrHost,0,sizeof(m_arrHost));
	memset(m_arrUser,0,sizeof(m_arrUser));
	memset(m_arrPasswd,0,sizeof(m_arrPasswd));
	memset(m_arrDBName,0,sizeof(m_arrDBName));
	static uint32 s_nIncDbID = 0;
	m_nID = ++s_nIncDbID;
}

DbMysql::~DbMysql()
{
	while ( m_queAsyncSQLRequest.size() )
	{
		SSleep(100);
	}
	this->Close();
}

uint32 DbMysql::ID()
{
	return m_nID;
}

void DbMysql::Release()
{ 
	delete this;
}

int32 DbMysql::OnThreadDestroy()
{
	mysql_thread_end();
	return 0;
}

void DbMysql::Close()
{
	m_bOpen = false;
	SSleep(100);
	if (m_pMysql != NULL)
	{
		mysql_close(m_pMysql);
		m_pMysql = NULL;
	}
}

bool DbMysql::Open(const char* ip, uint16 port, const char* username, const char* passwd, const char* dbname, bool bSQLChk /*= true*/)
{
	strncpy(m_arrHost, ip, DB_MAX_STRINGSIZE);
	strncpy(m_arrUser, username, DB_MAX_STRINGSIZE);
	strncpy(m_arrPasswd, passwd, DB_MAX_STRINGSIZE);
	strncpy(m_arrDBName, dbname, DB_MAX_STRINGSIZE);

	if (!ip || !username || !passwd || !dbname)
		return false;

	m_pMysql = this->Connect( m_arrHost, m_arrUser, m_arrPasswd, m_arrDBName, port);
	if (m_pMysql)
	{	
		m_bOpen =  true;
		boost::thread t(boost::bind( &DbMysql::OnThreadCreate, this ));
		printf("dbtool connect success.\n");
		return true;
	}else
	{
		printf("ERROR: dbtool connect failed.\n");
		return false;
	}
}

MYSQL* DbMysql::Connect(char* ip, char* user, char* passwd, char* dbname, uint16 port, char* dbsocket, int32 timeout)
{	
	if(MYSQL* pHdbc = mysql_init( NULL ))
	{
		mysql_options( pHdbc , MYSQL_READ_DEFAULT_GROUP , "" );
		mysql_options( pHdbc , MYSQL_OPT_CONNECT_TIMEOUT , "" );

		pHdbc->options.read_timeout = timeout;
		pHdbc->reconnect = 1;
		pHdbc->free_me = 1;

		if ( mysql_real_connect( pHdbc , ip, user, passwd, dbname,
			port, dbsocket , CLIENT_MULTI_RESULTS | CLIENT_MULTI_STATEMENTS | CLIENT_FOUND_ROWS | CLIENT_INTERACTIVE ) )
		{
			mysql_set_character_set( pHdbc, "utf8" );
			mysql_set_server_option( pHdbc, MYSQL_OPTION_MULTI_STATEMENTS_ON );
			return pHdbc;
		}else
		{
			printf( "ERROR: dbtool real connect failed: %s \n" , mysql_error(pHdbc) );
			mysql_close(pHdbc);
			return NULL;
		}
	}
	return NULL;
}

uint32 DbMysql::GetRequestSize()
{ 
	return m_queAsyncSQLRequest.size();
}

uint32 DbMysql::GetResultSize()
{ 
	return m_queAsyncSQLResult.size(); 
}

MYSQL* DbMysql::GetDBHandle()
{
	return m_pMysql;
}

bool DbMysql::IsOpen()
{
	return m_bOpen;
}

/*
SQL替换字符串，确保数据库安全 
*/
void DbMysql::WsSQLReplaceStr(char *to,const char *from,unsigned long length)
{
	// 暂时还不知道该替换些啥，先原样返回就好了 
	to[0] = '\0';
	memcpy( to, from, length);
	to[length] = '\0';
}

int32 DbMysql::OnThreadCreate() 
{
	while( m_bOpen && m_pMysql )
	{
		this->OnThreadProcess();
	}
	return 0;
}

int32 DbMysql::OnThreadProcess()
{
	if (m_queAsyncSQLRequest.size())
	{
		m_queueMutex.lock();
		DbRequest* pRequest = m_queAsyncSQLRequest.front();
		m_queAsyncSQLRequest.pop();
		m_queueMutex.unlock();

		if(pRequest->m_queryFunc == NULL)
		{
			m_dbMutex.lock();
			if ( mysql_query( m_pMysql, pRequest->m_arrSql) != 0 )
			{
				printf("[MYSQL]Error in database requesting %s\n",mysql_error(m_pMysql));
				S_SAFE_DELETE(pRequest);
				m_dbMutex.unlock();
				return 0;			
			}
			MYSQL_RES* pRes = mysql_store_result(m_pMysql);
			mysql_free_result( pRes );
			mysql_next_result(m_pMysql); 
			m_dbMutex.unlock();
			S_SAFE_DELETE(pRequest);
		}else
		{
			MYSQL_RES* pRES = ResultSQL( pRequest->m_arrSql );
			if(pRES == NULL)
			{
				S_SAFE_DELETE(pRequest);
				return NULL;
			}
			DbRecordSet* pRecordSet = new DbRecordSet();
			if (!pRecordSet || !pRecordSet->Create(pRES))
			{
				S_SAFE_DELETE(pRequest);
				S_SAFE_DELETE(pRecordSet);
				return 0;					
			}
			while(mysql_next_result(m_pMysql) == 0)
			{
				MYSQL_RES* pRes = mysql_store_result(m_pMysql);
				mysql_free_result( pRes );
			}

			DbResult* pResult = new DbResult();
			pResult->m_bFlag		= true;
			pResult->m_pRecordSet	= pRecordSet;
			pResult->m_pCallResult = pRequest->m_queryFunc;

			S_SAFE_DELETE(pRequest);

			m_queueMutex.lock();
			m_queAsyncSQLResult.push( pResult );
			m_queueMutex.unlock();
		}
		return 0;
	}
	else
	{
		SSleep(1);
		return 0;
	}
}

MYSQL_RES* DbMysql::ResultSQL(const char* pszSQL)
{
	m_dbMutex.lock();
	if(mysql_query(m_pMysql,pszSQL) != 0 )	// =0 suceess, !=0 fail
	{	
		printf("Exec sql Fail,sql=%s, error:%s\n",pszSQL,mysql_error(m_pMysql));
		m_dbMutex.unlock();
		return NULL;
	}
	MYSQL_RES* pRes = mysql_store_result(m_pMysql);
	if (pRes == NULL) {
		m_dbMutex.unlock();
		return NULL;
	}
	m_dbMutex.unlock();
	return pRes; //mysql_free_result(pRes); 在使用完成pRes后，调用释放 
}

int32 DbMysql::ExecSQL(const char* pszSQL ,int length)
{
	m_dbMutex.lock();
#ifdef _DEBUG
	printf("[MYSQL]Exec sql:%s\n", pszSQL);
#endif // _DEBUG
	if (length == 0)
	{
		if (mysql_query(m_pMysql, pszSQL) != 0)	// =0 suceess, !=0 fail
		{
			printf("Exec sql Fail,sql=%s, error:%s\n", pszSQL, mysql_error(m_pMysql));
			m_dbMutex.unlock();
			return -1;
		}
	}
	else
	{
		if (mysql_real_query(m_pMysql, pszSQL, length) != 0)	// =0 suceess, !=0 fail
		{
			printf("Exec sql Fail,sql=%s, error:%s\n", pszSQL, mysql_error(m_pMysql));
			m_dbMutex.unlock();
			return -1;
		}
	}

	m_dbMutex.unlock();
	return 0;
}

void DbMysql::Escape(char* pOutSql,const char* pInSql)
{
	mysql_real_escape_string(m_pMysql,pOutSql,pInSql,::strlen(pInSql));
}

bool DbMysql::ExecSQLAsync(const char* pszSQL, DBQueryFunc* queryFun)
{
	if ( !this->IsOpen() )
		return false;

	if ( strlen(pszSQL) == 0 )
	{
		printf("sql command is null.\n");
		return false;
	}

	// chk sql
	if ( !(pszSQL && strlen(pszSQL) > 0 && strlen(pszSQL) < 10240) )
	{
		printf("strlen(pszSQL) = %d.\n", (int32)strlen(pszSQL));
		return false;
	}

	DbRequest* pRequest = new DbRequest;
	if (pRequest == NULL) 
	{
		printf("memory (new dbRequest) allocating failed.\n");
		return false;
	}

	pRequest->m_queryFunc = queryFun;
	strncpy( pRequest->m_arrSql , pszSQL , ::strlen(pszSQL));

	m_queueMutex.lock();
	m_queAsyncSQLRequest.push( pRequest );
	m_queueMutex.unlock();

	return true;
}

bool DbMysql::ExecSelectAsync(const char* tableName, const dbCol *column, const char *swhere, const char *order, DBQueryFunc* queryFun)
{
	if (tableName == NULL || column == NULL)
	{
		printf("MysqlClientHandle::exeSelect null pointer error.\n");
		return false;
	}

	int retsize = FetchSelectSql(tableName, column, swhere, order);
	if (retsize == 0)
	{
		printf("MysqlClientHandle::FetchSelectSql null pointer error.\n");
		return false;
	}

	DbRequest* pRequest = new DbRequest;
	if (pRequest == NULL) {
		printf("memory (new dbRequest) allocating failed.\n");
		return false;
	}

	//pRequest->m_queryFunc = queryFun;
	//strncpy(pRequest->m_arrSql, sql.c_str(), ::strlen(sql.c_str()));

	m_queueMutex.lock();
	m_queAsyncSQLRequest.push(pRequest);
	m_queueMutex.unlock();

	return true;
}

bool DbMysql::ExecInsertAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun)
{
	return true;
}

bool DbMysql::ExecDeleteAsync(const char* tableName, const char *where, DBQueryFunc* queryFun)
{
	return true;
}

bool DbMysql::ExecUpdateAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun)
{
	return true;
}

bool DbMysql::CheckSQL( const char* szSQL )
{
	if ( !szSQL )
		return false;

	char pszSQL[DB_MAX_SQL] = "";
	strcpy( pszSQL , szSQL );
	if ( 0 == strcmp(pszSQL, "UPDATE") )	
	{
		if ( !strstr(pszSQL, "WHERE") || !strstr(pszSQL, "LIMIT") )
		{
			return false;
		}
	}
	if ( 0 == strcmp(pszSQL, "DELETE") )
	{
		if ( !strstr(pszSQL, "WHERE") )
		{
			return false;
		}
	}

	return true;
}

IDbResult* DbMysql::GetAsyncResult()
{
	if (m_queAsyncSQLResult.size())
	{
		m_queueMutex.lock();
		IDbResult* pResult = m_queAsyncSQLResult.front();
		m_queAsyncSQLResult.pop();
		m_queueMutex.unlock();
		return pResult;
	}
	return NULL;
}

void DbMysql::BinaryToString(const char* pBinaryData,char* o_strBinarayData,int nLen)
{
	assert(nLen > 0 && nLen < 65336);
	assert(o_strBinarayData);
	memset(o_strBinarayData,0,nLen);
	mysql_real_escape_string(m_pMysql,o_strBinarayData,pBinaryData,nLen);
}

unsigned int DbMysql::fullSelectDataByRow(MYSQL_ROW row, unsigned long* lengths, const dbCol* temp, unsigned char* tempData)
{
	int offset = 0;
	int i = 0;
	while (temp->name)
	{
		if (strlen(temp->name) != 0)
		{
			switch (temp->type)
			{
			case DB_CHAR:
			{
				if (row[i])
				{
					*(char*)(tempData + offset) = strtoul(row[i], (char**)NULL, 10);
				}
				else
				{
					*(char*)(tempData + offset) = 0;
				}
			}
			break;
			case DB_BYTE:
			{
				if (row[i])
				{
					*(char*)(tempData + offset) = strtoul(row[i], (char**)NULL, 10);
				}
				else
				{
					*(char*)(tempData + offset) = 0;
				}
			}
			break;
			case DB_WORD:
			{
				if (row[i])
				{
					*(int16*)(tempData + offset) = strtoul(row[i], (char**)NULL, 10);
				}
				else
				{
					*(int16*)(tempData + offset) = 0;
				}
			}
			break;
			case DB_DWORD:
			{
				if (row[i])
				{
					*(int32*)(tempData + offset) = strtoul(row[i], (char**)NULL, 10);
				}
				else
				{
					*(int32*)(tempData + offset) = 0L;
				}
			}
			break;
			case DB_QWORD:
			{
				if (row[i])
				{
					*(int64*)(tempData + offset) = strtoull(row[i], (char**)NULL, 10);
				}
				else
				{
					*(int64*)(tempData + offset) = 0LL;
				}
			}
			break;
			case DB_STR:
			case DB_BIN:
			{
				memset(tempData + offset, 0, temp->size);
				if (row[i])
				{
					memcpy(tempData + offset, row[i],temp->size > lengths[i] ? lengths[i]:temp->size);
				}
			}
			break;
			case DB_BIN2:
			{
				memset(tempData + offset, 0, sizeof(int32));
				if (row[i])
				{
					int32 bin2size = *((int32*)row[i]) + sizeof(int32);
					memset(tempData + offset,0,bin2size);
					memcpy(tempData + offset, row[i], bin2size > lengths[i] ? lengths[i]: bin2size);
				}
			}
			break;
			}
			i++;
		}
		offset += temp->size == 0 ? *((int32*)tempData + offset) : temp->size;
		temp++;
	}
	return offset;
}

int32 DbMysql::ExecSelect(const char* tableName,const dbCol *column,const char *where,const char *order,unsigned char** data, unsigned int limit, int32 limit_from)
{
	
	int retval=-1;
	*data = NULL;
	if (tableName==NULL || column==NULL)
	{
		printf("MysqlClientHandle::exeSelect null pointer error.\n");
		return retval;
	}

	int retsize = FetchSelectSql(tableName,column,where,order,limit,limit_from);
	if(retsize < 1)
	{
		printf("MysqlClientHandle::FetchSelectSql null pointer error.\n");
		return retval;
	}
	
	MYSQL_RES* pRes = mysql_store_result(m_pMysql);
	if (pRes == NULL)
	{
		return retval;
	}

	unsigned long retCount = mysql_num_rows(pRes);
	if(retCount < 1)
	{
		mysql_free_result(pRes);
		return retval;
	}

	// 注意此处内存泄露 
	*data = new unsigned char[retsize * retCount];
	if (*data == NULL)
	{
		return retval;
	}

	memset(*data, 0, retsize * retCount);

	unsigned char* tempData = *data;
	
	unsigned int count = 0;
	while (MYSQL_ROW row = mysql_fetch_row(pRes))
	{
		unsigned long* lengths = mysql_fetch_lengths(pRes);
		unsigned int fullsize = fullSelectDataByRow(row,lengths,column,tempData);
		if (fullsize == 0)
		{
			S_SAFE_DELETE_VEC(*data);
			mysql_free_result(pRes);
			return count;
		}
		tempData += fullsize;
		count++;
	}
	return count;
}

int32 DbMysql::ExecSelectLimit(const char* tableName, const dbCol *column, const char *where, const char *order, unsigned char* data, unsigned int limit, int32 limit_from)
{
	int retval = -1;
	*data = NULL;
	if (tableName == NULL || column == NULL)
	{
		printf("MysqlClientHandle::exeSelect null pointer error.\n");
		return retval;
	}

	int retsize = FetchSelectSql(tableName, column, where, order,limit,limit_from);
	if (retsize < 1)
	{
		printf("MysqlClientHandle::FetchSelectSql null pointer error.\n");
		return retval;
	}

	MYSQL_RES* pRes = mysql_store_result(m_pMysql);
	if (pRes == NULL)
	{
		return retval;
	}

	unsigned int retCount = mysql_num_rows(pRes);
	if (retCount < 1)
	{
		mysql_free_result(pRes);
		return 0;
	}

	MYSQL_ROW row;
	unsigned char* tempData = data;
	unsigned int count = 0;
	while ((row = mysql_fetch_row(pRes)) && count < limit)
	{
		unsigned long *lengths = mysql_fetch_lengths(pRes);
		unsigned int fullsize = fullSelectDataByRow(row, lengths, column, tempData);
		if (fullsize == 0)
		{
			mysql_free_result(pRes);
			return count;
		}
		tempData += fullsize;
		count++;
	}
	return count;
}

int DbMysql::FetchSelectSql(const char* tableName,const dbCol *column,const char *wheres,const char *order,int32 limit/* = 0*/,int32 limit_from/* = 0*/, bool UseBak/* = false*/)
{
	int retsize=0;
	const dbCol *temp;
	bool first=true;
	std::string sql;
	sql+="SELECT ";
	temp = column;
	while(temp->name) 
	{   
		retsize+=temp->size;
		if (strlen(temp->name) > 0)
		{
			if (first)
				first=false;
			else
				sql+=",";
			sql+=temp->name;
		}
		temp++;
	}
	if (strlen(tableName)>0)
	{
		sql+=" FROM `";
		sql+=tableName;
		sql += "`";
	}
	if (wheres !=NULL && strlen(wheres)>0)
	{
		sql+=" WHERE ";
		sql+= wheres;
	}
	if (order!=NULL && strlen(order)>0)
	{
		sql+=" ORDER BY ";
		sql+=order;
	}
	if (limit_from)
	{
	  char tmp[32];
	  snprintf(tmp,sizeof(tmp) - 1,"%u,%u",limit_from,limit);
	  sql+=" LIMIT ";
	  sql+=tmp;
	}
	else if (limit)
	{
	  char tmp[32];
	  snprintf(tmp,sizeof(tmp) - 1,"%u",limit);
	  sql+=" LIMIT ";
	  sql+=tmp;
	} 

	if (ExecSQL(sql.c_str(), sql.length())!=0)
	{
		return -1;
	}
	return retsize;
}

int32 DbMysql::ExecInsert(const char *tableName,const dbCol *column,const char *data)
{
	const dbCol *temp;
	if (tableName == NULL || data==NULL || column==NULL)
	{
		printf("DbMysql::ExecInsert null pointer error.\n");
		return -1;
	}
	std::ostringstream strSql;
	strSql << "INSERT INTO `";
	strSql << tableName;
	strSql << "` ( ";
	temp = column; 
	bool first=true;
	while(temp->name) 
	{
		int len = strlen(temp->name);
		if (len > 0)
		{       
			if (first)
				first=false;
			else
				strSql << ",";
			strSql << temp->name;
		}
		temp++; 
	}
	strSql << ") VALUES( ";

	first = true;
	temp = column; 
	int offset=0;
	// [ranqd] 需要绑定的二进制数据容器 
	BINDDATA ltBind;
	while(temp->name) 
	{
		if (strlen(temp->name)!=0)
		{       
			if (first)
				first=false;
			else
				strSql << ",";
			switch(temp->type)
			{
			case DB_CHAR:
				{
					short _temp = 0x00ff & (*(const char*)(data+offset));
					strSql << _temp;
				}
				break;
			case DB_BYTE:
				{
					short _temp = 0x00ff & (*(const char*)(data+offset));
					strSql << _temp;
				}
				break;
			case DB_WORD:
				strSql << *(const int16*)(data+offset);
				break;
			case DB_DWORD:
				strSql << *(const int32*)(data+offset);
				break;
			case DB_FLOAT:
				strSql << *(const float*)(data+offset);
				break;
			case DB_QWORD:
				strSql << *(const int64*)(data+offset);
				break;
			case DB_STR:
				{
					int32 len = strlen((const char *)(data+offset));
					len = (len > temp->size) ? temp->size : len;
					char* strData=new char[len * 2 + 1];
					strData[0] = '\0';
					WsSQLReplaceStr(strData,(const char *)(data+offset),len);
					strSql << "\'" << strData << "\'";
					delete[] strData;
				}
				break;
			case DB_BIN:
				{
					// [ranqd] SQLServer对二进制数据的处理不能直接放到SQL语句中，先把数据放到ltBind容器，后面执行SQL前再绑定 
					BDATA td;					
					//td.pData = new char[temp->size * 2 + 1];
					WsSQLReplaceStr( td.pData,(const char *)(data+offset),temp->size );
					td.len = temp->size;
					BinaryToString((const char *)(data + offset), td.pData, temp->size);
					strSql << "\'" << td.pData << "\'";
				}
				break;
			case DB_BIN2:
				{
					int32 _size = *((int32 *)(data + offset));
					_size += sizeof(int32);
					BDATA td;
					//td.pData = new char[temp->size * 2 + 1];
					WsSQLReplaceStr(td.pData, (const char *)(data + offset), _size);
					td.len = _size;
					BinaryToString((const char *)(data + offset), td.pData, _size);
					strSql << "\'" << td.pData << "\'";
				}
				break;
			default:
				printf("invalid zebra mysql type.\n");
				return (int32)-1;
			}
		}
		if (temp->size==0)
			offset+=(*((const int32 *)(data+offset)) + sizeof(int32));
		else
			offset+=temp->size;
		temp++;
	}   
	strSql << ")";

	int32 ret = ExecSQL(strSql.str().c_str());
	if (ret == 0)
	{
		return mysql_insert_id(m_pMysql);
	}
	else
	{
		return ret;
	}
}


int32 DbMysql::ExecDelete(const char *tableName,const char *where)
{
	if (tableName==NULL)
	{
		return (int32)-1;
	}
	std::ostringstream out_sql;

	out_sql << "DELETE FROM `";
	out_sql << tableName << "`";
	if (where)
	{
		out_sql << " WHERE ";
		out_sql << where;
	}
	return ExecSQL(out_sql.str().c_str());
}

int32 DbMysql::ExecUpdate(const char *tableName,const dbCol *column,const char *data,const char *where)
{
	std::ostringstream out_sql;
	const dbCol *temp;
	if (tableName==NULL || column==NULL || data==NULL)
	{
		printf("MysqlClientHandle::exeUpdate null pointer error.\n");
		return (int32)-1;
	}
	out_sql << "UPDATE `" << tableName << "` SET `";
	temp = column;
	bool first=true;
	int offset=0;
	// [ranqd] 需要绑定的二进制数据临时存放点 
	BINDDATA ltBind;
	BDATA td;
	while(temp->name)
	{
		int len = strlen(temp->name);
		// [ranqd] CHARID在SQLServer系统中为自动增长的主键，不能被Update 
		if (len > 0 && strcmp(temp->name, "`CHARID`") != 0)
		{
			if (first)
				first=false;
			else
				out_sql << ",`";
			out_sql << temp->name << "`=";
			switch(temp->type)
			{
			case DB_CHAR:
				{
					short _temp = 0x00ff & (*(const char *)(data+offset));
					out_sql << _temp;
				}
				break;
			case DB_BYTE:
				{
					short _temp = 0x00ff & (*(const char*)(data+offset));
					out_sql << _temp;
				}
				break;
			case DB_WORD:
				out_sql << *(const int16 *)(data+offset);
				break;
			case DB_DWORD:
				out_sql << *(const int32 *)(data+offset);
				break;
			case DB_QWORD:
				out_sql << *(const int64 *)(data+offset);
				break;
			case DB_STR:
				{
					int32 _len=strlen((const char *)(data+offset));
					_len = (_len > temp->size) ? temp->size : _len;
					char* strData=new char[_len * 2 + 1];
					WsSQLReplaceStr(strData,(const char *)(data+offset),_len);
					out_sql << "\'" << strData << "\'";
					delete[] strData;
				}
				break;
			case DB_BIN:
				{ 
					td.len = temp->size;
					BinaryToString((const char *)(data + offset), td.pData, temp->size);
					out_sql << "\'" << td.pData << "\'";
				}
				break;
			case DB_BIN2:
				{
					int32 _size = *((int32*)(data+offset)) + sizeof(int32);  // +size 字段大小 
					int32 binsize = _size * 2 + 1; // tosize = fromsize * 2 + 1 是mysql将char2str的最小约定 
					char* bindata = new char[binsize];
					BinaryToString((const char *)(data + offset), bindata, _size);
					out_sql << "\'" << bindata << "\'";
					delete[] bindata;
				}
				break;
			default:
				printf("invalid zebra mysql type.\n");
				return (int32)-1;
			}
		}
		if (temp->size==0)
			offset+=(*((int32 *)(data+offset)) + sizeof(int32));
		else
			offset+=temp->size;
		temp++;
	}
	if (where!=NULL)
	{
		out_sql << " WHERE " << where;
	}

	out_sql << ";";

	char sql[8196 + 1000];
	memset(sql,0,sizeof(sql));
	sql[0] = '\0';
	strncpy( sql, out_sql.str().c_str(), sizeof(sql));
	int32 ret = ExecSQL(sql, sizeof(sql));
	if(ret == 0)
	{
		do
		{
			MYSQL_RES* _result = mysql_store_result(m_pMysql);
			mysql_free_result(_result);
		} while (!mysql_next_result(m_pMysql));
	}

	return ret;
}


bool DbMysql::Commit()
{
	return (0 == ExecSQL("COMMIT"));
}

bool DbMysql::Rollback()
{
	return (0 == ExecSQL("ROLLBACK"));
}


