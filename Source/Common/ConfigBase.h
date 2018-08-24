#ifndef __CONFIG_BASE_H_
#define __CONFIG_BASE_H_

#include "SrvEngine.h"

#pragma pack(push,1)

// CharType
struct CharTypeBase
{
	const DWORD getUniqueID() const
	{
		return field0;
	}
	DWORD  field0;		// 编号(类型) 
	char   field1[32];	// 名称 
	DWORD  field2;		// 技能1 
	DWORD  field3;		// 技能2 
	DWORD  field4;		// 技能3 
	DWORD  field5;		// 技能4 
};

struct zCharTypeB : zEntry
{
	DWORD id;			// 技能ID
	std::string name;     	// 名称 
	DWORD skill1;		// 技能1 
	DWORD skill2;		// 技能2 
	DWORD skill3;		// 技能3 
	DWORD skill4;		// 技能4 
	inline uint64_t GetID() {return id;}
	inline uint64_t GetTempID() { return _entry_tempid; }
	inline const std::string& GetName() { return name; }
	void fill(const CharTypeBase& base)
	{
		id = base.field0;
		name = base.field1;
		skill1 = base.field2;
		skill2 = base.field3;
		skill3 = base.field4;
		skill4 = base.field5;
	}

	zCharTypeB() :zEntry()
	{
		id = skill1 = skill2 = skill3 = skill4 = 0;
	}
};


// CharLevel
struct CharLevelBase
{
	const DWORD getUniqueID() const
	{
		return field0;
	}
	DWORD field0;		// 编号 
	DWORD field1;		// 角色类型  
	DWORD field2;		// 等级 
	DWORD field3;		// 经验上限 
	DWORD field4;		// 生命上限 
	DWORD field5;		// 生命回复 
	DWORD field6;		// 怒气上限 
	DWORD field7;		// 怒气回复 
	DWORD field8;		// 普攻 
	DWORD field9;		// 普防 
	DWORD field10;		// 技攻 
	DWORD field11;		// 技防 
	DWORD field12;		// 暴击率:百份比 
	DWORD field13;		// 暴击伤害 
	DWORD field14;		// 韧性 
	DWORD field15;		// 格挡值 
	DWORD field16;		// 闪避:百份比 
	DWORD field17;		// 命中:百份比 
	DWORD field18;		// 攻速 
	DWORD field19;		// 移速 
}; 

struct zCharLevelB : zEntry
{
	DWORD id;
	DWORD type;		// 角色类型 
	DWORD level;		// 等级 
	DWORD exp;		// 经验上限 
	DWORD hp;		// 生命上限 
	DWORD hpRecover;		// 生命回复 
	DWORD mp;		// 怒气上限 
	DWORD mpRecover;		// 怒气回复 
	DWORD pa;		// 物攻 
	DWORD pd;		// 物防 
	DWORD ma;		// 魔攻 
	DWORD md;		// 魔防 
	DWORD criteRate;		// 暴击率:百份比 
	DWORD criteVal;		// 暴击伤害 
	DWORD tenacity;		// 韧性:百份比 
	DWORD block;		// 格挡 
	DWORD dodge;		// 闪避:百份比 
	DWORD hit;		// 命中:百份比 
	DWORD as;		// 攻速 
	DWORD ms;		// 移速 

	void fill(const CharLevelBase& base)
	{
		id = base.field0;
		type = base.field1;
		level = base.field2;
		exp = base.field3;
		hp = base.field4;
		hpRecover = base.field5;
		mp = base.field6;
		mpRecover = base.field7;
		pa = base.field8;
		pd = base.field9;
		ma = base.field10;
		md = base.field11;
		criteRate = base.field12;
		criteVal = base.field13;
		tenacity = base.field14;
		block = base.field15;
		dodge = base.field16;
		hit = base.field17;
		as = base.field18;
		ms = base.field19;
	}

	zCharLevelB() : zEntry()
	{
		id = type = level = exp = hp = hpRecover = mp = mpRecover = 0;
		pa = pd = ma = md = criteRate = criteVal = tenacity = block = dodge = hit = as = ms = 0;
	}
};


//------------------------------------
// NpcBase
//------------------------------------
struct NpcBase
{
	const DWORD getUniqueID() const
	{
		return field0;
	}
	DWORD  field0;		// 编号 
	char   field1[32];	// 名称 
	DWORD  field2;		// 类型 
	DWORD  field3;		// 等级 
	DWORD  field4;		// 生命值 
	DWORD  field5;		// 经验值 
	DWORD  field6;		// 体力 
	DWORD  field7;		// 智力 
	DWORD  field8;		// 敏捷 
	DWORD  field9;		// 精神 
	DWORD  field10;		// 体质 
	DWORD  field11;		// 颜色 
	DWORD  field12;		// 基本备用1 
	DWORD  field13;		// 基本备用2 
	DWORD  field14;		// AI 
	DWORD  field15;		// 移动间隔 
	DWORD  field16;		// 攻击间隔 
	DWORD  field17;		// 攻击类型 
	DWORD  field18;		// 最小攻击 
	DWORD  field19;		// 最大攻击 
	DWORD  field20;		// 最小法攻 
	DWORD  field21;		// 最大法攻 
	DWORD  field22;		// 最小物防 
	DWORD  field23;		// 最大物防 
	DWORD  field24;		// 最小法防 
	DWORD  field25;		// 最大法防 
	DWORD  field26;		// 躲避率 
	DWORD  field27;		// 命中率 
	DWORD  field28;		// PK备用1 
	DWORD  field29;		// PK备用2 
	DWORD  field30;		// PK备用3 
	DWORD  field31;		// PK备用4 
	DWORD  field32;		// 技能1 
	DWORD  field33;		// 技能2 
	DWORD  field34;		// 技能3 
	DWORD  field35;		// 技能4 
	DWORD  field36;		// 五行属性 
	DWORD  field37;		// 五行点数 
	char  field38[4096];// 携带物品 
};

/**
* \brief Npc基本表格数据 
*
*/
struct zNpcB : public zEntry
{
	DWORD id;
	std::string name;   // 名称 
	DWORD kind;        	// 类型 
	DWORD level;       	// 等级 
	DWORD hp;       	// 生命值 
	DWORD exp;      	// 经验值 
	DWORD strong;       // 体力 
	DWORD intellect;	// 智力 
	DWORD flexible;     // 敏捷 
	DWORD spirit;		// 精神 
	DWORD physique;     // 体质 
	DWORD color;        // 颜色 
	DWORD backup1;  	// 基本备用1 
	DWORD backup2; 		// 基本备用2 
	DWORD ai;			// AI  
	DWORD move_time;	// 移动间隔  
	DWORD attack_time;  // 攻击间隔  
	DWORD attack_type;  // 攻击类型 
	DWORD physicAttackMin;	// 最小攻击 
	DWORD physicAttackMax;	// 最大攻击  
	DWORD spellAttackMin;	// 最小法攻 
	DWORD spellAttackMax;	// 最大法攻 
	DWORD physicDefendMin;	// 最小物防    
	DWORD physicDefendMax;	// 最大物防 
	DWORD spellDefendMin;	// 最小法防   	
	DWORD spellDefendMax;	// 最大法防 
	DWORD dodge;			// 躲避率 
	DWORD hit;				// 命中率 
	DWORD pk1;				// PK备用1 
	DWORD pk2;				// PK备用2 
	DWORD pk3;				// PK备用3 
	DWORD pk4;				// PK备用4    	
	DWORD skill1;			// 技能1 
	DWORD skill2;      		// 技能2 
	DWORD skill3;  			// 技能3 
	DWORD skill4;    		// 技能4 
	DWORD fivelineType;		// 五行属性 
	DWORD fivelinePoint;	// 五行点数 
							//char carryObjs[256];	// 携带物品 

	void fill(const NpcBase &base)
	{
		id = base.field0;
		kind = base.field2;
		level = base.field3;
		hp = base.field4;
		exp = base.field5;
		strong = base.field6;
		intellect = base.field7;
		flexible = base.field8;
		spirit = base.field9;
		physique = base.field10;
		color = base.field11;
		backup1 = base.field12;
		backup2 = base.field13;
		ai = base.field14;
		move_time = base.field15;
		attack_time = base.field16;
		attack_type = base.field17;
		physicAttackMin = base.field18;
		physicAttackMax = base.field19;
		spellAttackMin = base.field20;
		spellAttackMax = base.field21;
		physicDefendMin = base.field22;
		physicDefendMax = base.field23;
		spellDefendMin = base.field24;
		spellDefendMax = base.field25;
		dodge = base.field26;
		hit = base.field27;
		pk1 = base.field28;
		pk2 = base.field29;
		pk3 = base.field30;
		pk4 = base.field31;
		skill1 = base.field32;
		skill2 = base.field33;
		skill3 = base.field34;
		skill4 = base.field35;
		fivelineType = base.field36;
		fivelinePoint = base.field37;
		//strncpy(name, base.field1, 32);
	}

	zNpcB() : zEntry()
	{
		id = kind = level = hp = exp = strong = intellect = flexible = spirit = physique = color = 0;
		backup1 = backup2 = ai = move_time = attack_time = attack_type = 0;
		physicAttackMin = physicAttackMax = spellAttackMin = spellAttackMax = physicDefendMin = physicDefendMax = spellDefendMin = spellDefendMax = 0;
		dodge = hit = pk1 = pk2 = pk3 = pk4 = skill1 = skill2 = skill3 = skill4 = fivelineType = fivelinePoint = 0;
	}

};

struct ShopBase
{
	const DWORD getUniqueID() const
	{
		return field0;
	}
	int32_t  field0;		// 编号 
	char   field1[32];	// 名称 
	int32_t  field2;		// 分类 
	int32_t  field3;		// 位置 
	int32_t  field4;		// 道具ID 
	int32_t  field5;		// 道具数量 
	int32_t  field6;		// 卖钱类型 
	int32_t  field7;		// 卖钱值  
	int32_t  field8;		// 购买需求等级 
};

/**
* \brief Npc基本表格数据 
*
*/
struct zShopB : public zEntry
{
	int32_t id;
	std::string name;     	// 名称 
	int32_t category;     // 类型 
	int32_t position;		// 位置  
	int32_t itemID;       	// 等级 
	int32_t itemNum;       	// 生命值 
	int32_t sellMoneyType;      	// 经验值 
	int32_t sellMoneyValue;       // 体力 
	int32_t needLevel;	// 等级  
	void fill(const ShopBase &shop)
	{
		id = shop.field0;
		category = shop.field2;
		position = shop.field3;
		itemID = shop.field4;
		itemNum = shop.field5;
		sellMoneyType = shop.field6;
		sellMoneyValue = shop.field7;
		needLevel = shop.field8;
	}
	zShopB() : zEntry()
	{
		id = category = position = itemID = itemNum = sellMoneyType = sellMoneyValue = needLevel = 0;
	}
};


// 道具表 
struct ItemBase 
{
	const DWORD getUniqueID() const
	{
		return field0;
	}

	DWORD field0;
	string field1; // 名称 
	DWORD field2;	// 主类型 
	DWORD field3;	// 出售钱类型 
	DWORD field4;	// 出售钱数量 
	DWORD field5;	// 标记功能 
	DWORD field6;	// 格子最多叠加 
	string field7;	// 使用效果1 
	string field8;	// 使用效果2 
	DWORD field9;	// 装备位置 
	DWORD field10;  // 品质 
	DWORD field11;  // 等级 
	DWORD field12;	// 生命上限  
	DWORD field13;	// 法力上限
	DWORD field14;	// HP恢复 
	DWORD field15;	// MP恢复 
	DWORD field16;	// 物攻 
	DWORD field17;	// 物防 
	DWORD field18;	// 法攻 
	DWORD field19;	// 法防 
	DWORD field20;  // 暴击值 
	DWORD field21;	// 暴击率 
	DWORD field22;	// 韧性率 
	DWORD field23;	// 格挡值 
	DWORD field24;	// 闪避率 
	DWORD field25;	// 命中率 
	DWORD field26;	// 攻速 
	DWORD field27;	// 移速 
	//DWORD field28;	// 展示图片 
	//DWORD field29;	// 描述 
};

struct zItemB : zEntry
{

	enum ItemTye
	{
		TYPE_NONE = 0,
		TYPE_ITEM,	/* 普通道具 */
		TYPE_EQUIP, /* 装备 */
		TYPE_QUEST, /* 任务道具 */
		TYPE_PKING, /* PK中使用道具 */
	};

	struct Effect
	{
		DWORD target;
		DWORD funcType;
		DWORD funcID;
		DWORD funcVal;
	};

	/* 使用对象 */
	enum EffectTarget
	{
		TARGET_MINE = 1,
		TARGET_OPPOSING,
	};

	/* 效果类型 */
	enum EffectFunc
	{
		FUNC_MONEY, 
		FUNC_EXP,
		FUNC_PKVAL,
		FUNC_BUFF,
		FUNC_PET,
	};

	/* 效果子类型 */
	enum EffectID
	{
		FUNC_ID_MONEY_GOLD = 1,
		FUNC_ID_MONEY_SILVER = 2,
		FUNC_ID_MONEY_COPPER = 3,
	};


	//DWORD field0;
	//char field1[32]; // 名称 
	DWORD id;	// 
	std::string name;
	DWORD mainType;	// 主类型 
	DWORD sellType;	// 出售钱类型 
	DWORD sellVal;	// 出售钱数量 
	DWORD flag;	// 标记功能 
	DWORD amount;	// 格子最多叠加 
	Effect effect1;	// 使用效果1 
	Effect effect2;	// 使用效果2 
	DWORD equipPos;	// 装备位置 
	DWORD quilty;  // 品质 
	DWORD useLevel;  // 等级 
	EntryPkValBase pkVal;

	void fill(const ItemBase& base)
	{
		id = base.field0;
		mainType = base.field2;
		sellType = base.field3;
		sellVal = base.field4;
		flag = base.field5;
		amount = base.field6;

		{
			std::vector<std::string> obs;
			stringtok(obs, base.field7, ",-;");
			if (obs.size() != 4)
			{
				ASSERT(0);
				return;
			}

			effect1.target = atoi(obs[0].c_str());
			effect1.funcType = atoi(obs[1].c_str());
			effect1.funcID = atoi(obs[2].c_str());
			effect1.funcVal = atoi(obs[3].c_str());
		}

		{
			std::vector<std::string> obs;
			stringtok(obs, base.field8, ",-;");
			if (obs.size() != 4)
			{
				ASSERT(0);
				return;
			}

			effect2.target = atoi(obs[0].c_str());
			effect2.funcType = atoi(obs[1].c_str());
			effect2.funcID = atoi(obs[2].c_str());
			effect2.funcVal = atoi(obs[3].c_str());
		}

		equipPos = base.field9;
		quilty = base.field10;
		useLevel = base.field11;

		pkVal.nRedMax = base.field12;				// 生命上限 
		pkVal.nBlueMax = base.field13;				// 法力上限
		pkVal.nRedRecover = base.field14;		// HP恢复 
		pkVal.nBlueRecover = base.field15;			// MP恢复 
		pkVal.nPhysicAttack = base.field16;			// 物攻 
		pkVal.nPhysicDefend = base.field17;		// 物防 
		pkVal.nSpellAttack = base.field18;		// 法攻 
		pkVal.nSpellDefend = base.field19;			// 法防 
		pkVal.nBaojilv = base.field20;				// 暴击值 
		pkVal.nBaoji = base.field21;				// 暴击率 
		pkVal.nGedanglv = base.field22;				// 韧性率 
		pkVal.nGedang = base.field23;				// 格挡值 
		pkVal.nShanbilv = base.field24;			// 闪避率 
		pkVal.nMingzhonglv = base.field25;			// 命中率 
		pkVal.nAttackSpeed = base.field26;		// 攻速 
		pkVal.nMoveSpeed = base.field27;	// 移速 

	}
	zItemB(): zEntry()
	{

	}
};


//------------------------------------
// SkillBase
//------------------------------------
/**
* \brief 根据技能类型和等级计算一个临时唯一编号
*
*/
#define skill_hash(type,level) ((type - 1) * 100 + level)


struct SkillBase
{
	const DWORD getUniqueID() const
	{
		return field0;
	}
	DWORD field0;		// 编号 
	char field1[32];	// 名称 
	DWORD field2;		// 分类 
	DWORD field3;		// 伤害类型 
	string field4;	// 效果1 
	string field5;	// 效果2 
	string field6;	// 升级需求 
	string field7;	// 升级获得子技能  
	string field8;	// 描述  

};



struct zSkillB : zEntry
{

	struct SkillEffect
	{
		DWORD batttype;
		DWORD emitobj;		// 施放对象 
		DWORD effectVal;	// 基础值 
		DWORD effectValInc;	// 增长值（与等级有关） 
		DWORD effectRate;	// 施放概率 
		DWORD effectRateInc;// 施放概率增长值 
	};

	struct SkillUplevel
	{
		DWORD uptype;
		DWORD upid;
		DWORD upnum;
		DWORD upnumInc;
	};

	struct SkillSub
	{
		DWORD needLevel;
		DWORD subSkillID;
		DWORD subSkillLv;
	};
	DWORD id;
	std::string name[32];
	DWORD type;
	DWORD hurttype;

	SkillEffect effect1;
	SkillEffect effect2;
	SkillUplevel uplevel;
	SkillSub subSkill;

	void fill(const SkillBase& base)
	{
		id = base.field0;
		type = base.field2;
		hurttype = base.field3;

		{
			std::vector<std::string> obs;
			stringtok(obs, base.field4, ",-;");
			if (obs.size() != 6)
			{
				ASSERT(0);
				return;
			}

			effect1.batttype = atoi(obs[0].c_str());
			effect1.emitobj = atoi(obs[1].c_str());
			effect1.effectVal = atoi(obs[2].c_str());
			effect1.effectValInc = atoi(obs[3].c_str());
			effect1.effectRate = atoi(obs[4].c_str());
			effect1.effectRateInc = atoi(obs[5].c_str());
		}

		{
			std::vector<std::string> obs;
			stringtok(obs, base.field5, ",-;");
			if (obs.size() != 6)
			{
				ASSERT(0);
				return;
			}

			effect2.batttype = atoi(obs[0].c_str());
			effect2.emitobj = atoi(obs[1].c_str());
			effect2.effectVal = atoi(obs[2].c_str());
			effect2.effectValInc = atoi(obs[3].c_str());
			effect2.effectRate = atoi(obs[4].c_str());
			effect2.effectRateInc = atoi(obs[5].c_str());
		}


		{
			std::vector<std::string> obs;
			stringtok(obs, base.field6, ",-;");
			if (obs.size() != 4)
			{
				ASSERT(0);
				return;
			}

			uplevel.uptype = atoi(obs[0].c_str());
			uplevel.upid = atoi(obs[1].c_str());
			uplevel.upnum = atoi(obs[2].c_str());
			uplevel.upnumInc = atoi(obs[3].c_str());
		}

		{
			std::vector<std::string> obs;
			stringtok(obs, base.field7, ",-;");
			if (obs.size() != 3)
			{
				ASSERT(0);
				return;
			}

			subSkill.needLevel = atoi(obs[0].c_str());
			subSkill.subSkillID = atoi(obs[1].c_str());
			subSkill.subSkillLv = atoi(obs[2].c_str());
		}


	}

	zSkillB() :zEntry()
	{

	}
};

//struct SkillBase
//{
//	const DWORD getUniqueID() const
//	{
//		return skill_hash(dwField0, dwField2);
//	}
//
//	DWORD  dwField0;      // 技能ID
//	char  strField1[32];    // 技能名称
//	DWORD  dwField2;      // 技能等级
//	DWORD  dwField3;      // 技能系别
//	DWORD  dwField4;      // 技能树别
//	DWORD  dwField5;      // 需要本线技能点数
//	DWORD  dwField6;      // 前提技能一
//	DWORD  dwField7;      // 前提技能一等级
//	DWORD  dwField8;      // 前提技能二
//	DWORD  dwField9;      // 前提技能二等级
//	DWORD  dwField10;      // 前提技能三
//	DWORD  dwField11;      // 前提技能三等级
//	DWORD  dwField12;      // 间隔时间
//	DWORD  dwField13;      // 攻击方式
//	DWORD  dwField14;      // 能否骑马使用
//	DWORD  dwField15;      // 需要物品
//	char  strField16[128];  // 需要武器
//	DWORD  dwField17;      // 消耗体力值
//	DWORD  dwField18;      // 消耗法术值
//	DWORD  dwField19;      // 消耗生命值
//	DWORD  dwField20;      // 伤害加成
//	char  strField21[1024];  // 效果
//	DWORD  dwField22;      // 消耗物品类型
//	DWORD  dwField23;      // 物品消耗数量
//};//导出 SkillBase 成功，共 1 条记录
//
#define BENIGNED_SKILL_STATE 2
#define BAD_SKILL_STATE 4
#define NONE_SKILL_STATE 1 

struct SkillElement
{
	SkillElement()
	{
		id = 0;
		value = 0;
		percent = 0;
		time = 0;
		state = 0;
	}
	union {
		struct {
			DWORD id;
			DWORD percent;
			DWORD value;
			DWORD time;
			DWORD state;
		};
		DWORD element[5];
	};
	static SkillElement *create(SkillElement elem);
};
struct SkillStatus
{
	SkillStatus()
	{
		for (int i = 0; i < (int)(sizeof(status) / sizeof(WORD)); i++)
		{
			status[i] = 0;
		}
	}
	union {
		struct {
			WORD id;//技能id
			WORD target;//目标
			WORD center;//中心点
			WORD range;//范围
			WORD mode;//飞行模式
			WORD clear;//能否清除
			WORD isInjure;//是否需要伤害计算
		};
		WORD status[7];
	};
	std::vector<SkillElement> _StatusElementList;
};
//struct zSkillB : public zEntry
//{
//	bool has_needweapon(const WORD weapontype) const
//	{
//		std::vector<WORD>::const_iterator iter;
//		if (weaponlist.empty()) return true;
//		for (iter = weaponlist.begin(); iter != weaponlist.end(); iter++)
//		{
//			if (*iter == weapontype) return true;
//		}
//		return false;
//	}
//
//	bool set_weaponlist(const char *data)
//	{
//		weaponlist.clear();
//		std::vector<std::string> v_fir;
//		stringtok(v_fir, data, ":");
//		for (std::vector<std::string>::iterator iter = v_fir.begin(); iter != v_fir.end(); iter++)
//		{
//			WORD weaponkind = (WORD)atoi(iter->c_str());
//			weaponlist.push_back(weaponkind);
//		}
//		return true;
//	}
//
//	bool set_skillState(const char *data)
//	{
//		skillStatus.clear();
//		std::vector<std::string> v_fir;
//		stringtok(v_fir, data, ".");
//		for (std::vector<std::string>::iterator iter = v_fir.begin(); iter != v_fir.end(); iter++)
//		{
//			//Zebra::logger->debug("%s",iter->c_str());
//			std::vector<std::string> v_sec;
//			stringtok(v_sec, iter->c_str(), ":");
//			/*
//			if (v_sec.size() != 2)
//			{
//			return false;
//			}
//			// */
//			SkillStatus status;
//			std::vector<std::string>::iterator iter_1 = v_sec.begin();
//			std::vector<std::string> v_thi;
//			stringtok(v_thi, iter_1->c_str(), "-");
//			if (v_thi.size() != 7)
//			{
//				//Zebra::logger->debug("操作!=7");
//				continue;
//				//return false;
//			}
//			std::vector<std::string>::iterator iter_2 = v_thi.begin();
//			for (int i = 0; i < 7; i++)
//			{
//				status.status[i] = (WORD)atoi(iter_2->c_str());
//				//Zebra::logger->debug("status.status[%ld]=%ld",i,status.status[i]);
//				iter_2++;
//			}
//			iter_1++;
//			if (iter_1 == v_sec.end())
//			{
//				//Zebra::logger->debug("空操作");
//				skillStatus.push_back(status);
//				continue;
//			}
//			std::vector<std::string> v_fou;
//			stringtok(v_fou, iter_1->c_str(), ";");
//			std::vector<std::string>::iterator iter_3 = v_fou.begin();
//			for (; iter_3 != v_fou.end(); iter_3++)
//			{
//				std::vector<std::string> v_fiv;
//				stringtok(v_fiv, iter_3->c_str(), "-");
//				if (v_fiv.size() != 5)
//				{
//					//Zebra::logger->debug("元素个数不对");
//					continue;
//					//return false;
//				}
//				std::vector<std::string>::iterator iter_4 = v_fiv.begin();
//				SkillElement element;
//				for (int i = 0; i < 5; i++)
//				{
//					element.element[i] = (DWORD)atoi(iter_4->c_str());
//					//Zebra::logger->debug("element.element[%u]=%u",i,element.element[i]);
//					iter_4++;
//				}
//				status._StatusElementList.push_back(element);
//			}
//			skillStatus.push_back(status);
//		}
//		return true;
//	}
//	DWORD  skillid;            //技能ID
//	DWORD  level;              //技能等级
//	DWORD  kind;              //技能系别
//	DWORD  subkind;            //技能树别
//	DWORD  needpoint;            //需要本线技能点数
//	DWORD  preskill1;            //前提技能1
//	DWORD  preskilllevel1;          //前提技能级别1
//	DWORD  preskill2;            //前提技能2
//	DWORD  preskilllevel2;          //前提技能级别2
//	DWORD  preskill3;            //前提技能3
//	DWORD  preskilllevel3;          //前提技能级别3
//	DWORD  dtime;              //间隔时间
//	DWORD  usetype;            //攻击方式
//	DWORD  ride;              //可否骑马使用
//	DWORD  useBook;            //需要物品
//	DWORD  spcost;              //消耗体力值
//	DWORD  mpcost;              //消耗法术值
//	DWORD  hpcost;              //消耗生命值
//	DWORD  damnum;              //伤害加成
//	DWORD  objcost;            //消耗物品类型
//	DWORD  objnum;              //消耗物品数量
//	std::vector<SkillStatus> skillStatus;  //效果
//	std::vector<WORD> weaponlist;      //武器列表
//
//
//
//	void fill(const SkillBase &data)
//	{
//		id = skill_hash(data.dwField0, data.dwField2);
//		skillid = data.dwField0;                //技能ID
//		strncpy(name, data.strField1, MAX_NAMESIZE);
//		level = data.dwField2;          //技能等级
//		kind = data.dwField3;          //技能系别
//		subkind = data.dwField4;          //技能树别
//		needpoint = data.dwField5;          //需要本线技能点数
//		preskill1 = data.dwField6;          //前提技能1
//		preskilllevel1 = data.dwField7;;          //前提技能级别1
//		preskill2 = data.dwField8;          //前提技能2
//		preskilllevel2 = data.dwField9;          //前提技能级别2
//		preskill3 = data.dwField10;          //前提技能3
//		preskilllevel3 = data.dwField11;          //前提技能级别3
//		dtime = data.dwField12;          //间隔时间
//		usetype = data.dwField13;          //攻击方式
//		ride = data.dwField14;          //可否骑马使用
//		useBook = data.dwField15;          //学习需要物品
//		set_weaponlist(data.strField16);          //需要武器
//		spcost = data.dwField17;          //消耗体力值
//		mpcost = data.dwField18;          //消耗法术值
//		hpcost = data.dwField19;          //消耗生命值
//		damnum = data.dwField20;          //伤害加成
//		set_skillState(data.strField21);
//		objcost = data.dwField22;          //消耗物品类型
//		objnum = data.dwField23;          //消耗物品数量
//	}
//
//
//	zSkillB() : zEntry()
//	{
//		id = 0;
//		skillid = 0;
//		bzero(name, sizeof(name));        //说明
//		level = 0;          //技能等级
//		kind = 0;          //技能系别
//		subkind = 0;          //技能树别
//		needpoint = 0;          //需要本线技能点数
//		preskill1 = 0;          //前提技能1
//		preskilllevel1 = 0;          //前提技能级别1
//		preskill2 = 0;          //前提技能2
//		preskilllevel2 = 0;          //前提技能级别2
//		preskill3 = 0;          //前提技能3
//		preskilllevel3 = 0;          //前提技能级别3
//		dtime = 0;          //间隔时间
//		usetype = 0;          //攻击方式
//		ride = 0;          //可否骑马使用
//		useBook = 0;          //需要物品
//		spcost = 0;          //消耗体力值
//		mpcost = 0;          //消耗法术值
//		hpcost = 0;          //消耗生命值
//		damnum = 0;          //伤害加成
//		objcost = 0;          //消耗物品类型
//		objnum = 0;          //消耗物品数量
//	}
//
//};

struct LiveSkillBase {

	const DWORD getUniqueID() const
	{
		return ((0xffff & dwField11) << 16) | (0xffff & dwField0);
	}

	DWORD  dwField0;    // 技能ID
	char  strField1[64];    // 技能名称
	DWORD  dwField2;    // 需要工具
	DWORD  dwField3;    // 初始技能
	DWORD  dwField4;    // 对应图素
	DWORD  dwField5;    // 类别
	DWORD  dwField6;    // 技能升级经验
	DWORD  dwField7;    // 可否升级
	DWORD  dwField8;    // 进阶技能
	DWORD  dwField9;    // 前提技能ID
	DWORD  dwField10;    // 所需前提技能等级
	DWORD  dwField11;    // 技能等级
	char  strField12[32];    // 技能称号
	char  strField13[256];    // 获得物品
};

struct zLiveSkillB : public zEntry
{
	enum {
		MAX_EXP_BONUS = 30,
		MIN_POINT_BONUS = 1,
		MAX_POINT_BONUS = 3,
		WORKING_TIME = 6,
		MAX_LEVEL = 30,
	};

	//DWORD skill_id; //技能标识
	//DWORD level; //技能等级
	//WORD should be enough
	DWORD id; //技能标识
	WORD skill_id; //技能标识
	WORD level; //技能等级
	DWORD point; //升级所需技能点
	DWORD weapon_kind; //武器种类
					   //std::string name; //技能名称
	std::string title; //称号
	bool orig; //初始技能
	bool upgrade; //能否升级
	DWORD kind; //技能类别
	DWORD basic_skill_id; //前提技能id
	DWORD basic_skill_level; //前提技能等级]
	DWORD up_skill_id; //进阶技能id
	DWORD map_kind;

	class ITEM
	{
	public:
		DWORD item; //获得物品
		DWORD odds;  //几率
		DWORD min_number; //最小数量
		DWORD max_number; //最大数量

		ITEM(const std::string& odds_, const std::string& item_, const std::string& number_) : item(atoi(item_.c_str())), odds(atoi(odds_.c_str())), min_number(0), max_number(0)
		{
			std::string::size_type pos = 0;
			if ((pos = number_.find("-")) != std::string::npos) {

				min_number = atoi(number_.substr(0, pos).c_str());
				max_number = atoi(number_.substr(pos + strlen("-")).c_str());
			}
			//if (item) Zebra::logger->debug("劳动获得物品数据:ID(%d),几率(%d),个数(%d-%d)",item,odds,min_number,max_number);
		}
	};

	typedef std::vector<ITEM> ITEMS;
	ITEMS items;

	BYTE min_point_bonus; //最小增加技能点
	BYTE max_point_bonus; //最大增加技能点
	BYTE exp_bonus; //奖励经验
	BYTE max_level; //最大等级

	zLiveSkillB() : zEntry(), skill_id(0), level(0), point(0), weapon_kind(0),/*name("未知"),*/ title(""), orig(false), upgrade(false),
		kind(1), basic_skill_id(0), basic_skill_level(0), up_skill_id(0), map_kind(0),
		min_point_bonus(MIN_POINT_BONUS), max_point_bonus(MAX_POINT_BONUS), exp_bonus(MAX_EXP_BONUS),
		max_level(MAX_LEVEL)
	{

	}

	void fill(const LiveSkillBase& base)
	{
		skill_id = 0xffff & base.dwField0;
		//name = base.strField1;
		weapon_kind = base.dwField2;
		orig = (base.dwField3 == 1) ? true : false;
		map_kind = base.dwField4;
		kind = base.dwField5;
		point = base.dwField6;
		upgrade = (base.dwField7 == 1) ? true : false;
		up_skill_id = base.dwField8;
		basic_skill_id = base.dwField9;
		basic_skill_level = base.dwField10;
		level = 0xffff & base.dwField11;
		title = base.strField12;
		init_items(base.strField13);

		id = (level << 16) | skill_id;
	}

	void init_items(const std::string& item_list)
	{
		items.clear();
		Split<Parse3> p;
		p(item_list, items, ";", ":");

	}

};




extern zDataBM<zCharTypeB, CharTypeBase> &chartypebm;
extern zDataBM<zCharLevelB, CharLevelBase> &charlevelbm;
extern zDataBM<zNpcB, NpcBase> &npcbm;
extern zDataBM<zShopB, ShopBase> &shopbm;
extern zDataBM<zSkillB, SkillBase> &skillbm;
extern zDataBM<zItemB, ItemBase> &itembm;

//extern zDataBM<zCharacterB,CharacterBase> &characterbm;
//extern zDataBM<zExperienceB, ExperienceBase> &experiencebm;
//extern zDataBM<zHonorB, HonorBase> &honorbm;
//extern zDataBM<zSkillB, SkillBase> &skillbm;
//extern zDataBM<zLiveSkillB, LiveSkillBase> &liveskillbm;
//extern zDataBM<zSoulStoneB, SoulStoneBase> &soulstonebm;
//extern zDataBM<zHairStyleB, HairStyle> &hairstylebm;
//extern zDataBM<zHairColourB, HairColour> &haircolourbm;
//extern zDataBM<zCountryMaterialB, CountryMaterial> &countrymaterialbm;
//extern zDataBM<zHeadListB, HeadList> &headlistbm;
//extern zDataBM<zPetB, PetBase> &petbm;

#pragma pack(pop)

#endif 





