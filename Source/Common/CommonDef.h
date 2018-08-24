#ifndef COMMONDEF_H_
#define COMMONDEF_H_

#include "boost/cstdint.hpp"

enum ServerType
{
	FOGS_SERVER_TYPE_VOID     	= 0,
	FOGS_SERVER_TYPE_CENTER		= 1,
	FOGS_SERVER_TYPE_GAME     	= 2,
	FOGS_SERVER_TYPE_GAMEDB		= 3,
	FOGS_SERVER_TYPE_GATEWAY  	= 4,
	FOGS_SERVER_TYPE_LOGIN		= 5,
	FOGS_SERVER_TYPE_		= 6,
	FOGS_SERVER_TYPE_PLAT		= 7,
	FOGS_SERVER_TYPE_RANK		= 8,
	FOGS_SERVER_TYPE_Log		= 9,
};

static const uint16_t usCenterServerNum		= 1; //中心服务器数量
static const uint16_t usGameServerNum		= 1; //游戏服务器数量
static const uint16_t usGamedbServerNum		= 1; //数据库服务器数量
static const uint16_t usGatewayServerNum	= 1; //网关服务器数量
static const uint16_t usLoginServerNum		= 1; //登陆服务器数量
static const uint16_t usIdipServerNum		= 1; //web服务器数量
static const uint16_t usPlatServerNum		= 1; //平台服务器数量
static const uint16_t usRankServerNum		= 1; //排行榜服务器数量

inline ServerType GetServerType(const std::string& strName)
{
	ServerType etype = FOGS_SERVER_TYPE_VOID;
	if (strName == "CenterServer")
	{
		etype = FOGS_SERVER_TYPE_CENTER;
	}
	else if (strName == "GameServer")
	{
		etype = FOGS_SERVER_TYPE_GAME;
	}
	else if (strName == "DBServer")
	{
		etype = FOGS_SERVER_TYPE_GAMEDB;
	}
	else if (strName == "GatewayServer")
	{
		etype = FOGS_SERVER_TYPE_GATEWAY;
	}
	else if (strName == "LoginServer")
	{
		etype = FOGS_SERVER_TYPE_LOGIN;
	}
	else if (strName == "IdipServer")
	{
		etype = FOGS_SERVER_TYPE_;
	}
	else if (strName == "PlatServer")
	{
		etype = FOGS_SERVER_TYPE_PLAT;
	}
	else if (strName == "RankServer")
	{
		etype = FOGS_SERVER_TYPE_RANK;
	}

	return etype;
}

#define GET_DEST_SERVER_TYPE(fp_type) \
	((fp_type >>25) & 0x1F)

#define GET_DEST_SERVER_UUID(fp_type) \
	((fp_type >> 15) & 0x7FFF)

#define GET_DEST_SERVER_ID(fp_type) \
	((fp_type >> 15) & 0x3FF)

#define GET_SRC_SERVER_TYPE(fp_type) \
	((fp_type >> 10) & 0x1F)

#define GET_SRC_SERVER_INDEX(fp_type) \
	(fp_type & 0x3FF)

#define GET_SRC_SERVER_UUID(fp_type) \
	(fp_type & 0x7FFF)

#define GET_SRC_SERVER_ID(fp_type) \
	(fp_type & 0x3FF)

#define IS_BROADCAST_MSG(fp_type) \
	((fp_type >> 30) & 0x01)


#define GENERATE_FP_TYPE(isBroadCast, destSrvType, destSrvId, srcSrvType, srcSrvId) \
	( ((isBroadCast & 0x01) <<30) | ((destSrvType & 0x1F) << 25) | ((destSrvId & 0x3FF) << 15) | \
			((srcSrvType& 0x1F) << 10) | (srcSrvId & 0x3FF) )

#define  GENERATE_RETURN_FP_TYPE(recv_fp_type) \
		GENERATE_FP_TYPE(0, GET_SRC_SERVER_TYPE(recv_fp_type),\
				GET_SRC_SERVER_INDEX(recv_fp_type), \
				GET_DEST_SERVER_TYPE(recv_fp_type), \
				GET_DEST_SERVER_INDEX(recv_fp_type))

#define REACQUIRE_DEST_SERVER_ID(destSrvType,reDestSrvIndex) \
	((destSrvType << 10) | (reDestSrvIndex & 0x3FF))

#define GET_BROADCAST_SERVER_LIMIT(destSrvType,serverID) \
	(destSrvType == ((serverID >> 10) & 0x3FF))

#define ACCORDING_TO_ID_GET_DEST_SERVER_TYPE(serverID) \
	((serverID >> 10) & 0x3FF)

#define ACCORDING_TO_ID_GET_DEST_SERVER_INDEX(serverID) \
	(serverID & 0x3FF)

/*
服务器说明
server Index： 表示每种类型服务器的下标
ServerID为int32整型存储，高17位全部为0，低10位为Server Index的值， 中间其余位数（5位）为server type
*/

#endif /* COMMONDEF_H_ */
