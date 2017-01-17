#ifndef __DEF_ENTITY_H_
#define __DEF_ENTITY_H_

#include "ServerDefine.h"
#include "srvEngine.h"

#pragma pack(push, 1)

// 实体类型 
enum EntityType
{
	ENTITY_TYPE_NPC			= 1,
	ENTITY_TYPE_PLAYER		= 2,
	ENTITY_TYPE_MASTER		= 3,
	ENTITY_TYPE_TRANSFER	= 4,
};

#define MAX_SPELL_CONTROL_NUM 4

/*-------------------------------------------------------------------
* @Brief : PK对象属性定义
*
* @Author:hzd 2015:11:12
*------------------------------------------------------------------*/
////////////////////////////////////战斗对象共用属性 start//////////////////////////////////////
struct EntryPkValBase
{
	int32 nStatus;							// 状态(二进制位运算值) 
	int32 nLevel;							// 等级 
	int32 nRed;								// 红(血) 
	int32 nRedMax;							// 红上限 
	int32 nBlue;							// 蓝(法术) 
	int32 nBlueMax;							// 蓝上限 
	int32 nRedRecover;						// 红恢复 
	int32 nBlueRecover;						// 蓝恢复 
	int32 nPhysicAttack;					// 物理攻击 
	int32 nPhysicDefend;					// 物理防御 
	int32 nSpellAttack;						// 法术攻击 
	int32 nSpellDefend;						// 法术防御 
	int32 nBaojilv;							// 暴击率 
	int32 nBaoji;							// 暴击 
	int32 nGedanglv;						// 隔挡率 
	int32 nGedang;							// 隔挡 
	int32 nShanbilv;						// 闪避率 
	int32 nMingzhonglv;						// 命中率 
	int32 nAttackSpeed;						// 速度 
	int32 nMoveSpeed;						// 移速 

	EntryPkValBase()
	{
		memset(this , 0, sizeof(*this));
	}

	EntryPkValBase(const EntryPkValBase& pkVal)
	{
		operator=(pkVal);
	}

	EntryPkValBase& operator=(const EntryPkValBase& pkVal)
	{
		memcpy(this, &pkVal, sizeof(*this));
		return *this;
	}

};




// 生物体类型 
/*-------------------------------------------------------------------
* @Brief : 本类属性，是指在地图上使用的，共用的，也就是地图上的PK相关
*			的数据，而功能属性不注册在这里
* @Author:hzd 2015:11:28
*------------------------------------------------------------------*/
enum EntiryBaseAttrType
{
	////////////////////////////////////Entry共用属性//////////////////////////////////////
	ENTITY_ATTRIBUTE_MAPID,
	ENTITY_ATTRIBUTE_POS_X,
	ENTITY_ATTRIBUTE_POS_Y,
	ENTITY_ATTRIBUTE_INVIEWRANGE,
	ENTITY_ATTRIBUTE_OUTVIEWRANGE,
	ENTITY_ATTRIBUTE_MAX,
};

struct BaseAttribute
{
	int32 nMapID;					// 地图ID 
	zPos sPos;						// 坐标 
	int32 nInViewRange;				// 进入视野距离 
	int32 nOutViewRangle;			// 离开视野距离 
	BaseAttribute()
	{
		sPos.x = sPos.y = 0;
		nInViewRange = nOutViewRangle = 0;
	}
};

//////////////////////////////////////////////////////////////////////////

struct SpellData
{
	uint32 nSpellID;	// 技能ID 
	int32 nPosition;    // 携带位置 (-1未携带,0 - 4 携带在对应的位置上) 
};

enum CharacterType
{
	CHARACTER_TYPE_NULL		= 0,    // 非法 
	CHARACTER_TYPE_SHAOLIN	= 1,	// 少林 
	CHARACTER_TYPE_MOJIAO	= 2,	// 魔教 
	CHARACTER_TYPE_GUMU		= 3,	// 古墓 
	CHARACTER_TYPE_XIAOYAO	= 4,	// 逍遥 
};

//////////////////////////////////角色////////////////////////////////////////

// 角色专有的基本数据，大部分数据已经继承于PK类  
struct SceneUserAttr
{
	int64 nUid;						// UID
	char  arrName[MAX_NAME_LENGTH]; // 角色名 
	int32 nExp;						// 经验 
	int32 nExpMax;					// 经验上限 
	int32 nLandID;					// 地图ID(副本或主地图) 加载时会先检查副本地图，再检查主地图 
	int32 nLandX;
	int32 nLandY;
	int32 nInstanceID;				// 副本ID 
	int32 nInstanceX;
	int32 nInstanceY;
	int32 nRoleType;				// 角色类型 
	int32 nClothesID;				// 衣物装备ID 
	int32 nWeaponID;				// 武器装备ID 
	int32 nGold;
	int32 nSilver;
	int32 nCopper;
	int32 nLastLogin;
	int32 nCountry;
	int32 nSceneID;
	int32 nZoneID;
	int32 nTeamID;
	int32 nVip;
	SceneUserAttr()
	{

	}
	SceneUserAttr(const SceneUserAttr& pkVal)
	{
		operator=(pkVal);
	}

	SceneUserAttr& operator=(const SceneUserAttr& pkVal)
	{
		memcpy(this, &pkVal, sizeof(*this));
		return *this;
	}

	/*void Serialize(::protobuf::UserBinary& proto);
	void Unserialize(const ::protobuf::UserBinary& proto);*/

};

enum SceneUserAttrType
{
	USER_ATTR_UID = 0,
	USER_ATTR_EXP,
	USER_ATTR_EXPMAX,		
	USER_ATTR_LAND_ID,		
	USER_ATTR_LAND_X,
	USER_ATTR_LAND_Y,
	USER_ATTR_INSTANCE_ID,	
	USER_ATTR_INSTANCE_X,
	USER_ATTR_INSTANCE_Y,
	USER_ATTR_ROLETYPE,
	USER_ATTR_CLOTHESID,
	USER_ATTR_WEAPONID,

	USER_ATTR_GOLD,
	USER_ATTR_SILVER,
	USER_ATTR_COPPER,
	USER_ATTR_LASTLOGIN,
	USER_ATTR_COUNTRY,
	USER_ATTR_SCENEID,
	USER_ATTR_ZONEID,
	USER_ATTR_TEAMID,
	USER_ATTR_VIP,
	USER_ATTR_MAX
};


// 背包数据 
struct SceneUserItemSlot
{
	int32 nCapacity;
	int32 nUseCapacity;

};


//////////////////////////////////////////////////////////////////////////


// 角色身上穿的三件装备 
struct CharacterWearData
{
	uint64 nCharacterID;	// 角色ID  
	uint32 nClothesID;		// 衣服ID 
	uint32 nWeaponID;		// 武器ID 
};

#pragma pack(pop)

#endif

