#ifndef LOG_CONFIG_H_
#define LOG_CONFIG_H_

#include "../DyNetMysql/DbConfig.h"

// 
#ifdef _DEBUG
#define MAX_SERVER_CONNECTED 100
#else
#define MAX_SERVER_CONNECTED 1024
#endif // _DEBUG



extern char SQL_BUFFER[ MAX_SQL_BUFFER ];

#endif


