#include "DbMysql.h"

#include <iostream>
#include <string.h>

#include "DbRecordSet.h"
#include "DbResult.h"
#include "DbRequest.h"

DbMysql::DbMysql():m_pMysql(NULL), m_bOpen(false)
{	
	uint32_t s_nIncDbID = 0;
	m_nID = ++s_nIncDbID;

	readTimeout_ = 100; //
	writeTimeout_ = 100;
	connectTimeout_ = 100;

}

DbMysql::DbMysql(const DbMysql& other)
{
	this->m_strHost = other.m_strHost;
	this->m_strUser = other.m_strUser;
	this->m_nID = other.m_nID;
	this->m_strPasswd = other.m_strPasswd;
	this->m_strDBName = other.m_strDBName;
}

DbMysql& DbMysql::operator=(const DbMysql& other)
{
	return *this;
}

DbMysql::~DbMysql()
{
	while ( m_queAsyncSQLRequest.size() )
	{
#ifdef WIN32
		Sleep(100);
#else
		usleep(100);
#endif
	}
	this->Close();
}

uint32_t DbMysql::ID()
{
	return m_nID;
}

void DbMysql::Release()
{ 
	delete this;
}

int32_t DbMysql::OnThreadDestroy()
{
	mysql_thread_end();
	return 0;
}

void DbMysql::Close()
{
	m_bOpen = false;
#ifdef WIN32
	Sleep(100);
#else
	usleep(100);
#endif
	if (m_pMysql != NULL)
	{
		mysql_close(m_pMysql);
		m_pMysql = NULL;
	}
}

bool DbMysql::Open(const std::string& ip, uint16_t port, const std::string& username, const std::string& passwd, const std::string& dbname, bool bSQLChk /*= true*/)
{
	m_strHost = ip;
	m_strUser = username;
	m_strPasswd = passwd;
	m_strDBName = dbname;
	if (this->Reconnect(m_strHost, m_strUser, m_strPasswd, m_strDBName, port))
	{
		if (m_pMysql)
		{
			m_bOpen = true;
			boost::thread t(boost::bind(&DbMysql::OnThreadCreate, this));
			printf("dbtool connect success.\n");
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		printf("ERROR: dbtool connect failed.\n");
		return false;
	}
}

bool DbMysql::Reconnect(const std::string& ip, const std::string& user, const std::string& passwd, const std::string& dbname, uint16_t port, char* dbsocket, int32_t timeout)
{	
	m_pMysql = mysql_init(NULL);
	if (NULL == m_pMysql)
		return false;

	mysql_options(m_pMysql, MYSQL_OPT_CONNECT_TIMEOUT, &connectTimeout_);
	mysql_options(m_pMysql, MYSQL_OPT_READ_TIMEOUT, &readTimeout_);
	mysql_options(m_pMysql, MYSQL_OPT_WRITE_TIMEOUT, &writeTimeout_);

	MYSQL* handle = mysql_real_connect(m_pMysql, ip.c_str(),
		user.c_str(), passwd.c_str(),
		dbname.c_str(), port, NULL, CLIENT_MULTI_STATEMENTS);

	if (!handle || mysql_errno(m_pMysql) != 0)
	{
		const char* errMsg = mysql_error(m_pMysql);
		printf("ERROR: errMsg=%s", errMsg);
		mysql_close(m_pMysql);
		return false;
	}

	mysql_set_character_set(m_pMysql, "utf8");

	return true;
}

uint32_t DbMysql::GetRequestSize()
{ 
	return m_queAsyncSQLRequest.size();
}

uint32_t DbMysql::GetResultSize()
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

int32_t DbMysql::OnThreadCreate() 
{
	while( m_bOpen && m_pMysql )
	{
		this->OnThreadProcess();
	}
	return 0;
}

int32_t DbMysql::OnThreadProcess()
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
#ifdef WIN32
		Sleep(1);
#else
		usleep(1);
#endif
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

int32_t DbMysql::ExecSQL(const char* pszSQL ,int length)
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
		printf("strlen(pszSQL) = %d.\n", (int32_t)strlen(pszSQL));
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
		printf("MysqlClientHandle::FetchSelectSql null pointer error.retsize=%d \n", retsize);
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
					*(int16_t*)(tempData + offset) = strtoul(row[i], (char**)NULL, 10);
				}
				else
				{
					*(int16_t*)(tempData + offset) = 0;
				}
			}
			break;
			case DB_DWORD:
			{
				if (row[i])
				{
					*(int32_t*)(tempData + offset) = strtoul(row[i], (char**)NULL, 10);
				}
				else
				{
					*(int32_t*)(tempData + offset) = 0L;
				}
			}
			break;
			case DB_QWORD:
			{
				if (row[i])
				{
					*(int64_t*)(tempData + offset) = strtoull(row[i], (char**)NULL, 10);
				}
				else
				{
					*(int64_t*)(tempData + offset) = 0LL;
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
				memset(tempData + offset, 0, sizeof(int32_t));
				if (row[i])
				{
					uint32_t bin2size = *((int32_t*)row[i]) + sizeof(int32_t);
					memset(tempData + offset,0,bin2size);
					memcpy(tempData + offset, row[i], bin2size > lengths[i] ? lengths[i]: bin2size);
				}
			}
			break;
			}
			i++;
		}
		offset += temp->size == 0 ? *((int32_t*)tempData + offset) : temp->size;
		temp++;
	}
	return offset;
}

int32_t DbMysql::ExecSelect(const char* tableName,const dbCol *column,const char *where,const char *order,unsigned char** data, unsigned int limit, int32_t limit_from)
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
		printf("MysqlClientHandle::FetchSelectSql null pointer error.retsize=%d \n",retsize);
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

int32_t DbMysql::ExecSelectLimit(const char* tableName, const dbCol *column, const char *where, const char *order, unsigned char* data, unsigned int limit, int32_t limit_from)
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
		printf("MysqlClientHandle::FetchSelectSql null pointer error.retsize=%d \n", retsize);
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

int DbMysql::FetchSelectSql(const char* tableName,const dbCol *column,const char *wheres,const char *order,int32_t limit/* = 0*/,int32_t limit_from/* = 0*/, bool UseBak/* = false*/)
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

int32_t DbMysql::ExecInsert(const char *tableName,const dbCol *column,const char *data)
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
	BDATA td;
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
				strSql << *(const int16_t*)(data+offset);
				break;
			case DB_DWORD:
				strSql << *(const int32_t*)(data+offset);
				break;
			case DB_FLOAT:
				strSql << *(const float*)(data+offset);
				break;
			case DB_QWORD:
				strSql << *(const int64_t*)(data+offset);
				break;
			case DB_STR:
				{
					uint32_t len = strlen((const char *)(data+offset));
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
				td.len = temp->size;
				BinaryToString((const char *)(data + offset), td.pData, temp->size);
				strSql << "\'" << td.pData << "\'";
			}
			break;
			case DB_BIN2:
			{
				int32_t _size = *((int32_t*)(data + offset)) + sizeof(int32_t);  // +size
				int32_t binsize = _size * 2 + 1; // tosize = fromsize * 2 + 1 					int32 binsize = _size * 2 + 1; // tosize = fromsize * 2 + 1 是mysql将char2str的最小约定 
				char* bindata = new char[binsize];
				BinaryToString((const char *)(data + offset), bindata, _size);
				strSql << "\'" << bindata << "\'";
				delete[] bindata;
			}
			break;
			default:
				printf("invalid zebra mysql type.\n");
				return (int32_t)-1;
			}
		}
		if (temp->size==0)
			offset+=(*((const int32_t *)(data+offset)) + sizeof(int32_t));
		else
			offset+=temp->size;
		temp++;
	}   
	strSql << ")";

	int32_t ret = ExecSQL(strSql.str().c_str());
	if (ret == 0)
	{
		return mysql_insert_id(m_pMysql);
	}
	else
	{
		return ret;
	}
}


int32_t DbMysql::ExecDelete(const char *tableName,const char *where)
{
	if (tableName==NULL)
	{
		return (int32_t)-1;
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

int32_t DbMysql::ExecUpdate(const char *tableName,const dbCol *column,const char *data,const char *where)
{
	std::ostringstream out_sql;
	const dbCol *temp;
	if (tableName==NULL || column==NULL || data==NULL)
	{
		printf("MysqlClientHandle::exeUpdate null pointer error.\n");
		return (int32_t)-1;
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
				out_sql << *(const int16_t *)(data+offset);
				break;
			case DB_DWORD:
				out_sql << *(const int32_t *)(data+offset);
				break;
			case DB_QWORD:
				out_sql << *(const int64_t *)(data+offset);
				break;
			case DB_STR:
				{
					uint32_t _len=strlen((const char *)(data+offset));
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
					int32_t _size = *((int32_t*)(data+offset)) + sizeof(int32_t);  // +size 字段大小 
					int32_t binsize = _size * 2 + 1; // tosize = fromsize * 2 + 1 是mysql将char2str的最小约定 
					char* bindata = new char[binsize];
					BinaryToString((const char *)(data + offset), bindata, _size);
					out_sql << "\'" << bindata << "\'";
					delete[] bindata;
				}
				break;
			default:
				printf("invalid zebra mysql type.\n");
				return (int32_t)-1;
			}
		}
		if (temp->size==0)
			offset+=(*((int32_t *)(data+offset)) + sizeof(int32_t));
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
	int32_t ret = ExecSQL(sql, sizeof(sql));
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


