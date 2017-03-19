#ifndef __WOROLDSERVER_PCH_HEADER__
#define __WOROLDSERVER_PCH_HEADER__

#ifdef _DEBUG
#define MAX_WS_SOCKET_CONNECT 100
#else
#define MAX_WS_SOCKET_CONNECT 1024
#endif // _DEBUG

#include "Includes.h"
#include "DbIncludes.h"
#include "NetIncludes.h"
#include "SrvCoreIncludes.h"

#include "GameService.h"
#include "OfflineUserMgr.h"
#include "WorldUserMgr.h"
#include "NetMsgHandler.h"

#include "BaseProcHandler.h"
#include "ProcDpHandler.h"
#include "ProcFepHandler.h"
#include "ProcSsHandler.h"
#include "ProcLsHandler.h"

#include "SceneRegMgr.h"
#include "OfflineUserMgr.h"
#include "WorldUserMgr.h"

#endif