#ifndef __DEF_RESOURCE_H_
#define __DEF_RESOURCE_H_




#pragma pack(push, 1)

struct StRoleTypeInitCfg
{
	int32 nRoleType;
	int32 arrSkillId[MAX_SKILL_COUNT];
	int32 nLandMapId;
	int32 nLandX;
	int32 nLandY;
	int32 nInViewRange;
	int32 nOutViewRange;
	int32 nInitRed;
	int32 nInitBlue;
	int32 nAttackType;
	int32 nSpeed;
};


struct StCharacterLevelCfg
{
	int32 nIdx;			// ID  
	int32 nCharType;	// 角色类型   
	int32 nLevel;		// 等级 
	int32 nUpLevelExp;  // 升一级需要经验  
	int32 nRedMax;		// 最大红  
	int32 nRedRecover;  // 红回复/s  
	int32 nBlueMax;     // 最大蓝 
	int32 nBlueRecover; // 蓝回复/s 
	int32 nPhysicAttack;// 普通攻击  
	int32 nPhysicDefend;// 普通防御 
	int32 nSpellAttack; // 技能攻击 
	int32 nSpellDefend; // 技能防御 
	int32 nBaojilv;		// 暴击率 
	int32 nBaoji;		// 暴击(倍数) 
	int32 nGedanglv;    // 格挡率（格挡对方的物伤害） 
	int32 nGedang;		// 格挡值 
	int32 nShanbilv;	// 闪避率(闪避对方的技能) 
	int32 nMingZhonglv; // 命中率(击中对方，用技能) 
};

// 地图信息 
struct StMapInfoResCfg
{
	int32	nMapId;
	int32	nSceneType;
	string	strZoneFileName;
	string	strSceneFileName;
};

// 地图区域 
struct StMapZoneResCfg
{
	int32 nMapId;									// 地图ID 
	int32 nXAmount;									// 横向格子数 
	int32 nYAmount;									// 坚下格子数 
	int32 nXCellLength;								// 长大小，与阻挡的小格子单位相同 
	int32 nYCellLength;								// 宽大小，与阻挡的小格子单位相同 
	int32 nBlock;									// 块参数（暂无用） 
	int32 nNpc;										// NPC配置（暂无用） 
	std::string strData;							// 0246值 
	std::vector<std::vector<int8> > regionValue;	// 区域格子的值 
};

// 地图阻挡 
struct StMapSceneResCfg
{
	int32 nMapId;	// 地图ID 
	int32 nXAmount; // 横向格子数 
	int32 nYAmount;	// 坚下格子数 
	int32 nXCellLength;// 长像素，最小的格子长度 
	int32 nYCellLength;// 宽像素，最小的格子长度 
	string strData; // 0246 值 
	std::vector<std::vector<int8> > regionValue;	// 区域格子的值 
	/*--------------------------------------------
	 *  @brief    :	像素的大小要与真实地图的尺寸做一个换算
	 *  @input	  : 地图单体为(米或cm等)
	 *  @return   :	
	 *-------------------------------------------*/
};


// 任务配置表 
struct StQuestInfoResCfg  
{
	int32 nId;
	int32 nType;
	int32 nSubType;

	string strTitle;
	string strContent;

	struct AcceptInfo
	{
		int32 nType;
		int32 nArg0;
		int32 nArg1;

	};
	AcceptInfo accept[4];

	struct FinishInfo
	{
		int32 nType;
		int32 nArg0;
		int32 nArg1;
	};

	FinishInfo finish[4];

	struct AwardInfo
	{
		int32 nType;
		int32 nArg0;
		int32 nArg1;
	};

	AwardInfo award[4];

};

#endif

