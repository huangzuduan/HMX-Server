#ifndef DP_CONFIG_H_
#define DP_CONFIG_H_

#ifdef WIN32

#ifdef DLL_FILE
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif
#else

#define DLLAPI 

#endif // WIN32

#define MAX_SERVER_CONNECTED 1024

#include "../DyNetMysql/DbConfig.h"

extern char SQL_BUFFER[ MAX_SQL_BUFFER ];

#endif


