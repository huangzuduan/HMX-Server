#ifndef __GATEWAYSERVER_PCH_HEADER__
#define __GATEWAYSERVER_PCH_HEADER__

// 最大客户端（玩家）连接数
#ifdef _DEBUG
#define MAX_FEP_SOCKET_CONNECT 100
#else
#define MAX_FEP_SOCKET_CONNECT 2048
#endif // _DEBUG

#include "Includes.h"
#include "DbIncludes.h"
#include "NetIncludes.h"
#include "SrvCoreIncludes.h"
#include "GateUser.h"

#include "GameService.h"
#include "NetMsgHandler.h"
#include "PlayerMsgHandler.h"
#include "ProcLsHandler.h"
#include "ProcSsHandler.h"

#endif
