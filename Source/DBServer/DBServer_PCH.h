#ifndef __DBSERVER_PCH_HEADER__
#define __DBSERVER_PCH_HEADER__

#include "Includes.h"
#include "DbIncludes.h"
#include "NetIncludes.h"
#include "SrvCoreIncludes.h"

#include "NetService.h"
#include "NetMsgHandler.h"
#include "ProcSsHandler.h"

#include "Memory.h"
#include "MCharacter.h"
#include "Collection.h"

#include "character.pb.h"


// 创建最大的服务器连接数 
#ifdef _DEBUG
#define MAX_SERVER_CONNECTED 100
#else
#define MAX_SERVER_CONNECTED 1024
#endif // _DEBUG

extern char SQL_BUFFER[MAX_SQL_BUFFER];

#endif