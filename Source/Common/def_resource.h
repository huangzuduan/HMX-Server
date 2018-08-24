#ifndef __DEF_RESOURCE_H_
#define __DEF_RESOURCE_H_




#pragma pack(push, 1)

struct StRoleTypeInitCfg
{
	int32_t nRoleType;
	int32_t arrSkillId[5];
	int32_t nLandMapId;
	int32_t nLandX;
	int32_t nLandY;
	int32_t nInViewRange;
	int32_t nOutViewRange;
	int32_t nInitRed;
	int32_t nInitBlue;
	int32_t nAttackType;
	int32_t nSpeed;
};


struct StCharacterLevelCfg
{
	int32_t nIdx;			// ID  
	int32_t nCharType;	// 角色类型   
	int32_t nLevel;		// 等级 
	int32_t nUpLevelExp;  // 升一级需要经验  
	int32_t nRedMax;		// 最大红  
	int32_t nRedRecover;  // 红回复/s  
	int32_t nBlueMax;     // 最大蓝 
	int32_t nBlueRecover; // 蓝回复/s 
	int32_t nPhysicAttack;// 普通攻击  
	int32_t nPhysicDefend;// 普通防御 
	int32_t nSpellAttack; // 技能攻击 
	int32_t nSpellDefend; // 技能防御 
	int32_t nBaojilv;		// 暴击率 
	int32_t nBaoji;		// 暴击(倍数) 
	int32_t nGedanglv;    // 格挡率（格挡对方的物伤害） 
	int32_t nGedang;		// 格挡值 
	int32_t nShanbilv;	// 闪避率(闪避对方的技能) 
	int32_t nMingZhonglv; // 命中率(击中对方，用技能) 
};

// 地图信息 
struct StMapInfoResCfg
{
	int32_t	nMapId;
	int32_t	nSceneType;
	std::string	strZoneFileName;
	std::string	strSceneFileName;
};

// 地图区域 
struct StMapZoneResCfg
{
	int32_t nMapId;									// 地图ID 
	int32_t nXAmount;									// 横向格子数 
	int32_t nYAmount;									// 坚下格子数 
	int32_t nXCellLength;								// 长大小，与阻挡的小格子单位相同 
	int32_t nYCellLength;								// 宽大小，与阻挡的小格子单位相同 
	int32_t nBlock;									// 块参数（暂无用） 
	int32_t nNpc;										// NPC配置（暂无用） 
	std::string strData;							// 0246值 
	std::vector<std::vector<int8_t> > regionValue;	// 区域格子的值 
};

// 地图阻挡 
struct StMapSceneResCfg
{
	int32_t nMapId;	// 地图ID 
	int32_t nXAmount; // 横向格子数 
	int32_t nYAmount;	// 坚下格子数 
	int32_t nXCellLength;// 长像素，最小的格子长度 
	int32_t nYCellLength;// 宽像素，最小的格子长度 
	std::string strData; // 0246 值 
	std::vector<std::vector<int8_t> > regionValue;	// 区域格子的值 
	/*--------------------------------------------
	 *  @brief    :	像素的大小要与真实地图的尺寸做一个换算
	 *  @input	  : 地图单体为(米或cm等)
	 *  @return   :	
	 *-------------------------------------------*/
};


// 任务配置表 
struct StQuestInfoResCfg  
{
	int32_t nId;
	int32_t nType;
	int32_t nSubType;

	std::string strTitle;
	std::string strContent;

	struct AcceptInfo
	{
		int32_t nType;
		int32_t nArg0;
		int32_t nArg1;

	};
	AcceptInfo accept[4];

	struct FinishInfo
	{
		int32_t nType;
		int32_t nArg0;
		int32_t nArg1;
	};

	FinishInfo finish[4];

	struct AwardInfo
	{
		int32_t nType;
		int32_t nArg0;
		int32_t nArg1;
	};

	AwardInfo award[4];

};

#pragma pack(pop)

#endif

