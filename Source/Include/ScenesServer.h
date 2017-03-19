#ifndef __SCENE_SERVER_H_
#define __SCENE_SERVER_H_


#include "srvEngine.h"
#include "ConfigBase.h"
#include "CommandS.h"

class SceneEntryPk;
class SceneNpc;
class Scene;
class SceneEntryPk;
class SceneUser;
class SceneTask;
class SceneTaskManager;
class QuestList;
class Vars;
class Condition;
class Action;

class GuardNpc;
class CartoonPet;
class Dice;

class Scene;
class ScenePet;
struct zSkill;
struct zSkillB;


//sky 特殊处理技能的ID
#define SKILLID_IMMOLATE	24	//献祭
#define SKILLID_SOUL		88	//灵魂状态
//sky 被攻击有几率移出的技能
#define SKILLID_FEAR		53	//恐惧
#define SKILLID_FROZEN		34	//冰冻
#define SKILLID_LIME		64	//石灰粉
#define SKILLID_REPENTANCE	57	//忏悔 

/**
* \brief AI类型,npc会做的基本动作
* 走、攻击、巡逻、跳转等
*
*/
enum SceneNpcAIType
{
	NPC_AI_NORMAL,///普通AI
	NPC_AI_SAY,///说话
	NPC_AI_MOVETO,///移动到某位置
	NPC_AI_ATTACK,///在某范围内攻击
	NPC_AI_FLEE,///逃离玩家
	NPC_AI_RETURN_TO_REGION,///回到活动范围
	NPC_AI_GO_ON_PATH,///按照一定路线移动
	NPC_AI_CHANGE_MAP,///切换地图（同一服务器内）
	NPC_AI_WARP,///同一地图内瞬间移动
	NPC_AI_PATROL,///巡逻
	NPC_AI_CLEAR,///清除该npc
	NPC_AI_WAIT,///等待,什么也不做
	NPC_AI_GUARD_DOOR,///门卫
	NPC_AI_GUARD_ARCHER,///弓卫
	NPC_AI_GUARD_GUARD,///侍卫
	NPC_AI_GUARD_PATROL,///巡逻卫士
	NPC_AI_DROP_ITEM,///丢东西
	NPC_AI_CALL_PET,///招宠物
	NPC_AI_RANDOM_CHAT///随机说话
};

///sky npc行为模式
enum NpcAIFlag
{
	AIF_ATK_PDEF = 0x00000001, ///优先攻击物防最低的敌人
	AIF_ATK_MDEF = 0x00000002, ///优先攻击魔防最低的敌人
	AIF_ATK_HP = 0x00000004, ///优先攻击生命值最低的敌人
	AIF_GIVEUP_10_SEC = 0x00000008, ///追逐10秒放弃目标
	AIF_GIVEUP_6_SEC = 0x00000010, ///6秒未受到伤害放弃目标
	AIF_GIVEUP_3_SEC = 0x00000020, ///3秒未受到伤害放弃目标
	AIF_FLEE_30_HP = 0x00000040, ///HP30%以下逃跑4格
	AIF_FLEE_3_ENEMY_4 = 0x00000080, ///被3个以上敌人围攻逃跑4格
	AIF_NO_BATTLE = 0x00000100,///非战斗npc
	AIF_NO_MOVE = 0x00000200, ///不移动（弓卫、买卖、路标等）
	AIF_WARP_MOVE = 0x00000400, ///瞬移方式移动
	AIF_CALL_FELLOW_7 = 0x00000800, ///召唤7*7范围的未激活npc(几率50%)
	AIF_CALL_FELLOW_9 = 0x00001000, ///召唤9*9范围的未激活npc（几率50%）
	AIF_CALL_BY_ATYPE = 0x00002000, ///召唤同种攻击类型的同伴（与上两个标志合作）
	AIF_HELP_FELLOW_5 = 0x00004000,///帮助5*5范围内的同伴攻击（用于被动npc）
	AIF_ATK_MASTER = 0x00008000,///直接攻击宠物的主人
	AIF_ATK_REDNAME = 0x00010000,///攻击红名的玩家
	AIF_DOUBLE_REGION = 0x00020000,///搜索范围加倍
	AIF_SPD_UP_HP20 = 0x00040000,///hp20%以下移动速度加倍
	AIF_ASPD_UP_HP50 = 0x00080000,///hp50%以下攻击速度加倍
	AIF_ACTIVE_MODE = 0x00100000,///主动攻击
	AIF_RUN_AWAY = 0x00200000,///逃离敌人
	AIF_LOCK_TARGET = 0x00400000,///不切换攻击目标直到死
	AIF_RCV_UNDER_30 = 0x00800000,///hp30%以下持续回血1%
	AIF_RCV_REST = 0x01000000,///脱离战斗30秒后回血一次5%
	AIF_LIMIT_REGION = 0x02000000  ///限制活动范围
};

///npc说话的类型
enum NpcChatType
{
	NPC_CHAT_ON_FIND_ENEMY = 1,///发现敌人
	NPC_CHAT_ON_ATTACK,///攻击时说的话
	NPC_CHAT_ON_RETURN,///追逐返回时说的话
	NPC_CHAT_ON_DIE,///死的时候说的话
	NPC_CHAT_ON_FLEE,///逃跑时说的话
	NPC_CHAT_ON_HIT,///被打时说的话
	NPC_CHAT_ON_HELP,///帮助同伴时说的话
	NPC_CHAT_ON_BE_HELP,///同伴来帮助时说的话
	NPC_CHAT_RANDOM    ///随机说话
};

// 怪物使用技能的条件 [sky add 先做这些 后期再扩充]
enum NpcSkillCond
{
	NPC_COND_ALWAYS,			//无条件
	NPC_COND_HPGMAXRATE,		//自身HP高于n%时
	NPC_COND_HPLMAXRATE,		//自身HP低于n%时
	NPC_COND_FHPLMAXRATE,		//友方魔物HP低于n%时。范围是周围8格半径
	NPC_COND_ATPCGE,			//攻击的PC数量>=n的话
	NPC_COND_TARGEHPGMAX,		//攻击对象的HP高于n%时
	NPC_COND_TARGEHPLMAX,		//攻击对象的HP低于n%时
	NPC_COND_TARGETSTATUON,		//当攻击对象得到某个异常状态时(以cond2为基准)
	NPC_COND_TARGETSTATUOFF,	//当攻击对象没有某个异常状态时(以cond2为基准)
	NPC_COND_MAXSTHPGMAX,		//主人的HP高于n时(预留给智能BB用)
	NPC_COND_MAXSTHPLMAX,		//主人的HP低于n时(预留给智能BB用)
	NPC_COND_MASTERSTATUON,		//当主人没有某个异常状态时(以cond2为基准)(预留给智能BB用)
	NPC_COND_MASTERSTATUOFF,	//当主人得到某个异常状态时(以cond2为基准)(预留给智能BB用)
	NPC_COND_CLOSEDATACKED,		//被近身攻击时
	NPC_COND_LONGRANGEATTACKED,	//被远程攻击时
	NPC_COND_RUDEATTACKED,		//被攻击而不能反击时(暂时用不到)

								//异常状态的状况用于 NPC_COND_TARGETSTATUON  NPC_COND_TARGETSTATUOFF 等（暂时只留拉2个接口）
	NPC_COND_STAN,		//昏眩
	NPC_COND_SLEEP		//睡眠
};

enum PkAttrType
{
	PK_ATTRIBUTE_STATUS = 0,		// 状态 
	PK_ATTRIBUTE_LEVEL,				// 等级 
	PK_ATTRIBUTE_RED,				// 红 
	PK_ATTRIBUTE_REDMAX,			// 红MAX
	PK_ATTRIBUTE_BLUE,				// 蓝 
	PK_ATTRIBUTE_BLUEMAX,			// 蓝MAX
	PK_ATTRIBUTE_REDRECOVER,		// 红恢复 
	PK_ATTRIBUTE_BLUERECOVER,		// 蓝恢复 
	PK_ATTRIBUTE_PHYSICATTACK,		// 物理攻击 
	PK_ATTRIBUTE_PHYSICDEFEND,		// 物理防御 
	PK_ATTRIBUTE_SPELLATTACK,		// 法术攻击 
	PK_ATTRIBUTE_SPELLDEFEND,		// 法术防御 
	PK_ATTRIBUTE_BAOJILV,			// 暴击率 
	PK_ATTRIBUTE_BAOJI,				// 暴击 
	PK_ATTRIBUTE_GEDANGLV,			// 隔挡率 
	PK_ATTRIBUTE_GEDANG,			// 隔挡 
	PK_ATTRIBUTE_SHANBILV,			// 闪避率 
	PK_ATTRIBUTE_MINGZHONGLV,		// 命中率 
	PK_ATTRIBUTE_ATTACKSPEED,		// 攻击速度 
	PK_ATTRIBUTE_MOVESPEED,			// 移动速度 
	PK_ATTRIBUTE_MAX,
};

enum PKStatus
{
	PK_STATUS_NULL = 0,

	PK_STATUS_ALIVE = 0x00000001,	// 活着 
	PK_STATUS_DEAD = 0x00000002,	// 死亡 

	PK_STATUS_DEHUANMAN = 0x00000008,	// 抗缓慢 
	PK_STATUS_XUANYUN = 0x00000010,	// 眩晕 
	PK_STATUS_DEXUANYUN = 0x00000020,	// 抗眩晕 
	PK_STATUS_HUNLUAN = 0x00000040,	// 混乱 
	PK_STATUS_DEHUNLUAN = 0x00000080,	// 抗混乱 
	PK_STATUS_DINGSHEN = 0x00000100,	// 定身 
	PK_STATUS_DEDINGSHEN = 0x00000200,	// 抗定身 
	PK_STATUS_CHENMO = 0x00000400,	// 沉默 
	PK_STATUS_DECHENMO = 0x00000800,	// 抗沉默 
	PK_STATUS_MIWU = 0x00001000,	// 迷雾 
	PK_STATUS_DEMIWU = 0x00002000,	// 抗迷雾 
	PK_STATUS_FUKONG = 0x00004000,	// 浮空 
	PK_STATUS_DEFUKONG = 0x00008000,	// 抗浮空 
	PK_STATUS_JIDAO = 0x00010000,	// 击倒 
	PK_STATUS_DEJIDAO = 0x00020000,	// 抗击倒 
	PK_STATUS_SHOUJI = 0x00040000,	// 受击 
	PK_STATUS_DESHOUJI = 0x00080000,	// 抗受击 
	PK_STATUS_DEJITUI = 0x00200000,	// 抗击退 
};

enum PKAttackType
{
	PK_ATTACK_TYPE_NULL,

	PK_ATTACK_TYPE_Melee = 0x00000001,	// 近战 
	PK_ATTACK_TYPE_Remote = 0x00000002,	// 远程 
	PK_ATTACK_TYPE_PHYSIC = 0x00000004,	// 物理 
	PK_ATTACK_TYPE_SPELL = 0x00000008,	// 法术 
};

struct PkValue
{
	PkValue()
	{
		bzero(dwValue, sizeof(dwValue));
	}
	void init()
	{
		bzero(dwValue, sizeof(dwValue));
	}
	union
	{
		struct
		{
			int32 nStatus;			// 状态(二进制位运算值) 
			int32 nLevel;			// 等级 
			int32 nRed;				// 红(血) 
			int32 nRedMax;			// 红上限 
			int32 nBlue;			// 蓝(法术) 
			int32 nBlueMax;			// 蓝上限 
			int32 nRedRecover;		// 红恢复 
			int32 nBlueRecover;		// 蓝恢复 
			int32 nPhysicAttack;	// 物理攻击 
			int32 nPhysicDefend;	// 物理防御 
			int32 nSpellAttack;		// 法术攻击 
			int32 nSpellDefend;		// 法术防御 
			int32 nBaojilv;			// 暴击率 
			int32 nBaoji;			// 暴击 
			int32 nGedanglv;		// 隔挡率 
			int32 nGedang;			// 隔挡 
			int32 nShanbilv;		// 闪避率 
			int32 nMingzhonglv;		// 命中率 
			int32 nAttackSpeed;		// 速度 
			int32 nMoveSpeed;		// 移速 
		};
		DWORD dwValue[PK_ATTRIBUTE_MAX];
	};
};

/**
* \brief 点结构
*/
struct Point
{
	/// 名称
	char name[MAX_NAMESIZE + 1];

	/// 位置
	zPos pos;

	/**
	* \brief 构造函数初始化
	*/
	Point() : pos()
	{
		bzero(name, sizeof(name));
	}

	/**
	* \brief 拷贝构造
	* \param point 点
	*/
	Point(const Point &point)
	{
		bcopy(point.name, name, sizeof(name), sizeof(name));
		pos = point.pos;
	}

	/**
	* \brief 重载操作符,拷贝点
	* \param point 被拷贝的点
	*/
	Point & operator= (const Point &point)
	{
		bcopy(point.name, name, sizeof(name), sizeof(name));
		pos = point.pos;
		return *this;
	}
};

// [ranqd] 区域类型定义
struct zZone {
	zPos pos;// 左上角的点
	int  width; // 区域宽度
	int  height; // 区域高度

	zZone()
	{
		pos = zPos(0, 0);
		width = 0;
		height = 0;
	}
	bool IsInZone(zPos p) // 判断点p是否在此区域内
	{
		return  p.x >= pos.x && p.x < pos.x + width && p.y >= pos.y && p.y < pos.y + height;
	}
	zPos GetRandPos() // 返回该区域内随机一点
	{
		zPos p;
		p.x = randBetween(pos.x, pos.x + width - 1);
		p.y = randBetween(pos.y, pos.y + height - 1);
		return p;
	}
	bool IsEmpty()
	{
		return width == 0 && height == 0;
	}
};
// [ranqd] 带地图名称的区域
struct zPoint
{
	/// 地图名称
	char name[MAX_NAMESIZE + 1];

	/// 地图区域
	zZone pos;

	/**
	* \brief 构造函数初始化
	*/
	zPoint() : pos()
	{
		bzero(name, sizeof(name));
	}

	/**
	* \brief 拷贝构造
	* \param point 点
	*/
	zPoint(const zPoint &point)
	{
		bcopy(point.name, name, sizeof(name), sizeof(name));
		pos = point.pos;
	}

	/**
	* \brief 重载操作符,拷贝点
	* \param point 被拷贝的点
	*/
	zPoint & operator= (const zPoint &point)
	{
		bcopy(point.name, name, sizeof(name), sizeof(name));
		pos = point.pos;
		return *this;
	}
};

/**
* \brief 传点定义
*/
struct WayPoint
{
	friend class WayPointM;
private:

	/// 目的坐标点集合
	//   std::vector<Point> dest;
	// [ranqd] 传送点更改为区域型
	std::vector<zPoint> dest;

	/// 目的坐标点数目
	WORD destC;
public:
	/// 传送坐标点集合
	// std::vector<zPos> point;
	// [ranqd] 传送点更改为区域型
	std::vector<zZone> point;
	/// 传送坐标点数目
	WORD pointC;

	bool init(zXMLParser *parser, const xmlNodePtr node, DWORD countryid);
	WayPoint();
	const Point getRandDest();
	const zPos getRandPoint();
};

class WayPointM
{
private:
	/// 传点集合
	std::vector<WayPoint> wps;
public:
	bool addWayPoint(const WayPoint &wp);
	WayPoint *getWayPoint(const zPos &pos);
	WayPoint *getWayPoint(const char *filename);
	WayPoint *getRandWayPoint();
};

/**
* \brief 定义Npc跟踪状态
*
*/
enum SceneNpcChase
{
	CHASE_NONE,     /// 没有跟踪状态
	CHASE_ATTACK,   /// 跟踪攻击状态
	CHASE_NOATTACK    /// 普通跟踪状态
};


/**
* \brief Npc类型
* 静态的还是动态分配的
*/
enum SceneNpcType
{
	STATIC,       /// 静态的
	GANG        /// 动态的
};

/**
* \brief 一个AI的定义
*
*/
struct t_NpcAIDefine
{
	///类型,NPC在该阶段的主要动作
	SceneNpcAIType type;
	///位置 根据不同动作位置的意义也略不相同
	///移动时表示目的地,其他表示活动范围中心
	zPos pos;
	///范围 
	///移动时表示到达目的地的判定范围,其他表示活动范围
	int regionX, regionY;
	//zRTime endTime;
	///该AI的持续时间(秒)
	int lasttime;

	///是否正在逃跑
	bool flee;
	///逃跑的方向
	int fleeDir;
	///逃跑计数
	int fleeCount;

	///切换地图时,要去的地图
	///说话时,要说的话
	char str[MAX_CHATINFO];


	/**
	* \brief 默认构造函数
	*
	*/
	t_NpcAIDefine()
		:type(NPC_AI_NORMAL), pos(zPos(0, 0)), regionX(2), regionY(2), lasttime(0), flee(false), fleeDir(-1), fleeCount(0)
	{
		bzero(str, sizeof(str));
	}

	/**
	* \brief 构造函数
	*
	*
	* \param type AI类型
	* \param pos 位置
	* \param regionX 范围宽
	* \param regionY 范围高
	* \param lasttime 持续时间
	* \return
	*/
	t_NpcAIDefine(SceneNpcAIType type, const zPos &pos, int regionX, int regionY, int lasttime)
		:type(type), pos(pos), regionX(regionX), regionY(regionY), lasttime(lasttime)
	{
		bzero(str, sizeof(str));
	}


	/**
	* \brief 拷贝构造函数
	*
	* \param ad 要复制的对象
	*/
	t_NpcAIDefine(const t_NpcAIDefine &ad)
	{
		type = ad.type;
		pos = ad.pos;
		regionX = ad.regionX;
		regionY = ad.regionY;
		lasttime = ad.lasttime;
		flee = ad.flee;
		fleeDir = ad.fleeDir;
		fleeCount = ad.fleeCount;
		strncpy_s(str, ad.str, sizeof(str) - 1);
	}

	/**
	* \brief 赋值
	*
	* \param ad 要拷贝的对象
	* \return 返回自身地址
	*/
	t_NpcAIDefine & operator = (const t_NpcAIDefine &ad)
	{
		type = ad.type;
		pos = ad.pos;
		regionX = ad.regionX;
		regionY = ad.regionY;
		lasttime = ad.lasttime;
		flee = ad.flee;
		fleeDir = ad.fleeDir;
		fleeCount = ad.fleeCount;
		strncpy_s(str, ad.str, sizeof(str) - 1);

		return *this;
	}
};


typedef std::vector<zPos> zPosIndex;

/**
* \brief 区域的定义
* 包括开头、中心、结束点的坐标和区域内非阻挡点索引
*
*/
struct zRegion
{
	zPos s;        /// 左上点
	zPos c;        /// 中心点
	zPos e;        /// 右下点
	zPosIndex index;  /// 非阻挡点索引
					  /**
					  * \brief 构造函数
					  *
					  */
	zRegion()
	{
	}
	/**
	* \brief 拷贝构造函数
	*
	*/
	zRegion(const zRegion &reg)
	{
		s = reg.s;
		c = reg.c;
		e = reg.e;
		index = reg.index;
	}
	/**
	* \brief 赋值操作符号
	*
	*/
	zRegion & operator= (const zRegion &reg)
	{
		s = reg.s;
		c = reg.c;
		e = reg.e;
		index = reg.index;
		return *this;
	}

	/**
	* \brief 判断坐标是否在区域范围之内
	*
	*/
	const bool isIn(const zPos &pos) const
	{
		return pos >= s && pos <= e;
	}

};



//配置文件中关于NPC的定义
/**
* \brief npc定义结构
* 包括编号,出生位置、范围、间隔等信息
*
*/
struct t_NpcDefine
{
	DWORD id;                //编号
	char  name[MAX_NAMESIZE + 1];        //名称
	zPos  pos;                //坐标
	WORD  width;              //矩形宽
	WORD  height;              //矩形长
	DWORD num;                //数量
	DWORD interval;              //刷新时间
	zSceneEntry::SceneEntryState initstate;  //初始状态,隐藏或者非隐藏
	zRegion region;              //范围数据,包括范围内的可行走点数据索引

								 //std::vector<zPos> path;//固定移动的路线

	DWORD rushID;//触发攻城ID
	BYTE rushRate;//触发攻城的几率
	DWORD rushDelay;//触发攻城的延时

	int scriptID;//智能脚本的id
	DWORD intervalAmendment;		//sky 复活时间修正值
	DWORD AmendmentFactor;		//sky 修正系数
	WORD Camp;					//sky 所属阵营索引值

	std::map<DWORD, std::pair<DWORD, DWORD> > petList;
	std::map<DWORD, std::pair<DWORD, DWORD> > summonList;
	std::map<DWORD, std::pair<DWORD, DWORD> > deathSummonList;
	std::list< std::pair<DWORD, zPos> > dieList;
	/**
	* \brief 构造函数
	*
	*/
	t_NpcDefine() : pos(), region()
	{
		id = 0;
		bzero(name, sizeof(name));
		width = 0;
		height = 0;
		num = 0;
		interval = 0;
		rushID = 0;
		rushRate = 0;
		rushDelay = 0;
		initstate = zSceneEntry::SceneEntry_Normal;
		scriptID = 0;
		intervalAmendment = 0;
		AmendmentFactor = 0;
		Camp = 0;
	}
	/**
	* \brief 拷贝构造函数
	*
	*/
	t_NpcDefine(const t_NpcDefine &reg)
	{
		id = reg.id;
		bcopy(reg.name, name, sizeof(name), sizeof(name));
		pos = reg.pos;
		width = reg.width;
		height = reg.height;
		num = reg.num;
		interval = reg.interval;
		initstate = reg.initstate;
		region = reg.region;
		//path = reg.path;
		rushID = reg.rushID;
		rushRate = reg.rushRate;
		rushDelay = reg.rushDelay;
		scriptID = reg.scriptID;
		petList = reg.petList;
		summonList = reg.summonList;
		deathSummonList = reg.deathSummonList;
		dieList = reg.dieList;
		intervalAmendment = reg.intervalAmendment;
		AmendmentFactor = reg.AmendmentFactor;
		Camp = reg.Camp;
	}
	/**
	* \brief 赋值操作符号
	*
	*/
	t_NpcDefine & operator= (const t_NpcDefine &reg)
	{
		id = reg.id;
		bcopy(reg.name, name, sizeof(name), sizeof(name));
		pos = reg.pos;
		width = reg.width;
		height = reg.height;
		num = reg.num;
		interval = reg.interval;
		initstate = reg.initstate;
		region = reg.region;
		//path = reg.path;
		rushID = reg.rushID;
		rushRate = reg.rushRate;
		rushDelay = reg.rushDelay;
		scriptID = reg.scriptID;
		petList = reg.petList;
		summonList = reg.summonList;
		deathSummonList = reg.deathSummonList;
		dieList = reg.dieList;
		intervalAmendment = reg.intervalAmendment;
		AmendmentFactor = reg.AmendmentFactor;
		Camp = reg.Camp;
		return *this;
	}

	void fillNpcMap(const char * tempChar, std::map<DWORD, std::pair<DWORD, DWORD> > &map)
	{
		std::vector<std::string> vs;
		std::vector<std::string> sub_vs;
		vs.clear();
		stringtok(vs, tempChar, ";");
		for (DWORD i = 0; i<vs.size(); i++)
		{
			sub_vs.clear();
			stringtok(sub_vs, vs[i].c_str(), "-");
			if (sub_vs.size() == 2)
				map[atoi(sub_vs[0].c_str())] = std::make_pair(atoi(sub_vs[1].c_str()), 100);
			else if (sub_vs.size() == 3) //npcID,num,rate
				map[atoi(sub_vs[0].c_str())] = std::make_pair(atoi(sub_vs[1].c_str()), atoi(sub_vs[2].c_str()));
		}
	}

	//sky 计算复活时间修改系数
	void InitIntervalAmendment()
	{
		//sky 复活时间为0或者数量小于1的时候
		if (interval == 0 || num <= 1)
			return;

		//sky 系数取复活时间与刷怪数量的平均值(时间先转换成毫秒级)
		intervalAmendment = (interval * 1000) / num;
		AmendmentFactor = num;

		return;
	}

	//sky 获取复活时间修正值
	//Dead 生命状态 (true:重生 false:死亡)
	DWORD GetIntervalAmendmaent(bool Dead)
	{
		if (Dead)
		{
			//sky 如果是重生,把重生的系数提高
			AmendmentFactor++;
			if (AmendmentFactor > num)
				AmendmentFactor = num;
		}
		else
		{
			//sky 如果是死亡,就把重生的系数减少
			AmendmentFactor--;
			if (AmendmentFactor < 0)
				AmendmentFactor = 0;
		}

		//sky 返回修正值
		return intervalAmendment * AmendmentFactor;
	}
};

typedef std::vector<t_NpcDefine> NpcDefineVector;

#define MAX_NPC_GROUP 5

/**
* \brief 场景物件的回调类
*
* 只要是用于遍历一屏物件,而对某些物件操作
*
* 使用者必须要实现exec方法
*/
struct zSceneEntryCallBack
{
	virtual bool exec(zSceneEntry *entry) = 0;
	virtual ~zSceneEntryCallBack() {};
};

//配置文件中关于区域类型定义
/**
* \brief 区域类型的定义
* 包括类型、大小等
*
*/
struct ZoneTypeDef
{
	enum
	{
		ZONE_NONE = 0, //一般区
		ZONE_PK_SAFE = 1,   // pk安全区
		ZONE_ABSOLUTE_SAFE = 2,   // 绝对安全区
		ZONE_RELIVE = 4,   // 死亡重生区
		ZONE_NEWBIE = 8,   // 新手出生区
		ZONE_SPORTS = 16,   // 竞技区
		ZONE_FOREIGN_RELIVE = 32,   // 国外死亡重生区
		ZONE_PRIVATE_STORE = 128,      // 摆摊区
		ZONE_PRIVATE_DARE = 256,      // 国战跳转区
		ZONE_PRIVATE_RELIVE = 512,    // 国战复活区
		ZONE_PRIVATE_UNION = 1024,     // 帮会所属地跳转区
		ZONE_COUNTRY_WAR = 2048,    // 边境的国战跳转区
		ZONE_PRIVATE_DARE_UNION = 4096,    // 帮会战挑战方跳转区
		ZONE_DARE_SAFE = 8192,    // 国战时为绝对安全区,平时为非安全区
		ZONE_PRIVATE_THIRD_UNION = 16384,    // 帮会所属地第三方跳转区
		ZONE_EMPEROR_DEF_RELIVE = 32768,    // 皇城战守方复活区
		ZONE_EMPEROR_ATT_RELIVE = 65536,    // 皇城战攻方复活区  
	};

	zPos  pos;                //坐标
	WORD  width;              //矩形宽
	WORD  height;              //矩形长
	DWORD type;                //矩形区域的类型
	zSceneEntry::SceneEntryState initstate;  //初始状态,隐藏或者非隐藏
	zSceneEntry::SceneEntryState state;    //当前状态,隐藏或者非隐藏
	zRegion region;              //范围数据,包括范围内的可行走点数据索引

								 /**
								 * \brief 构造函数
								 *
								 */
	ZoneTypeDef() : pos(), region()
	{
		width = 0;
		height = 0;
		type = 0;
		initstate = zSceneEntry::SceneEntry_Normal;
		state = zSceneEntry::SceneEntry_Normal;
	}
	/**
	* \brief 拷贝构造函数
	*
	*/
	ZoneTypeDef(const ZoneTypeDef &zone)
	{
		pos = zone.pos;
		width = zone.width;
		height = zone.height;
		type = zone.type;
		initstate = zone.initstate;
		state = zone.state;
		region = zone.region;
	}
	/**
	* \brief 赋值操作符号
	*
	*/
	ZoneTypeDef & operator= (const ZoneTypeDef &zone)
	{
		pos = zone.pos;
		width = zone.width;
		height = zone.height;
		type = zone.type;
		initstate = zone.initstate;
		state = zone.state;
		region = zone.region;
		return *this;
	}
};

typedef std::vector<ZoneTypeDef> ZoneTypeDefVector;

//------------------------------------
// ObjectBase
//------------------------------------
struct ObjectBase {
	const DWORD getUniqueID() const
	{
		return dwField0;
	}

	DWORD  dwField0;    // 编号
	char  strField1[64];    // 名称
	DWORD  dwField2;    // 最大数量
	DWORD  dwField3;    // 类型
	DWORD  dwField4;    // 职业限定
	DWORD  dwField5;    // 需要等级
	DWORD  dwField6;    // 道具等级
	char  strField7[256];    // 孔
	DWORD  dwField8;    // 配合物品
	char  strField9[256];    // 药品作用
	DWORD  dwField10;    // 最大生命值
	DWORD  dwField11;    // 最大法术值
	DWORD  dwField12;    // 最大体力值
	DWORD  dwField13;    // 最小物攻
	DWORD  dwField14;    // 最大物攻
	DWORD  dwField15;    // 最小魔攻
	DWORD  dwField16;    // 最大魔攻
	DWORD  dwField17;    // 物防
	DWORD  dwField18;    // 魔防
	DWORD  dwField19;    // 伤害加成

	DWORD  dwField20;    // 攻击速度
	DWORD  dwField21;    // 移动速度
	DWORD  dwField22;    // 命中率
	DWORD  dwField23;    // 躲避率
	DWORD  dwField24;    // 改造
	DWORD  dwField25;    // 合成等级
	DWORD  dwField26;    // 打造
	char  strField27[32];    // 需要技能
	char  strField28[1024];    // 需要原料
	DWORD  dwField29;    // 装备位置
	DWORD  dwField30;    // 耐久度
	DWORD  dwField31;    // 价格
	DWORD  dwField32;    // 颜色
	DWORD  dwField33;    // 格子宽
	DWORD  dwField34;    // 格子高
	DWORD  dwField35;    // 金子
	DWORD  dwField36;    // 合成单价
	DWORD  dwField37;    // 重击
	DWORD  dwField38;    // 神圣概率
	char  strField39[256];    // 神圣标识 

							  //sky 新增属性
	DWORD  dwField40;    // 力量
	DWORD  dwField41;    // 智力
	DWORD  dwField42;    // 敏捷
	DWORD  dwField43;    // 精神
	DWORD  dwField44;    // 耐力
	DWORD  dwField45;    // 物理免伤
	DWORD  dwField46;    // 魔法免伤
};//导出 ObjectBase 成功，共 940 条记录 


/**
* \brief 物品基本表
*/
struct zObjectB :public zEntry
{
	DWORD maxnum;        // 最大数量
	BYTE kind;          // 类型
	BYTE job;          // sky 职业限制
	WORD level;          // 道具等级
	std::vector<DWORD> hole;  //孔

	WORD needobject;      // 配合物品
	struct leechdom_t {
		WORD id; //功能标识
		WORD effect; //效果
		WORD time; //时间
		leechdom_t(const std::string& _id = "", const std::string& _effect = "", const std::string& _time = "")
			: id(atoi(_id.c_str())), effect(atoi(_effect.c_str())), time(atoi(_time.c_str()))
		{ }
	} leechdom;         // 药品作用

	WORD needlevel;        // 需要等级

	DWORD maxhp;          // 最大生命值
	DWORD maxmp;          // 最大法术值
	DWORD maxsp;          // 最大体力值

	DWORD pdamage;        // 最小攻击力
	DWORD maxpdamage;      // 最大攻击力
	DWORD mdamage;        // 最小法术攻击力
	DWORD maxmdamage;      // 最大法术攻击力

	DWORD pdefence;        // 物防
	DWORD mdefence;        // 魔防

	WORD damagebonus;      //伤害加成

	WORD akspeed;        // 攻击速度
	WORD mvspeed;        // 移动速度
	WORD atrating;        // 命中率
	WORD akdodge;        // 躲避率

	DWORD color;        // 颜色  

						//struct socket
						//{
						//  WORD odds;
						//  BYTE min;
						//  BYTE max;
						//  socket(const std::string& odds_,const std::string& number_)
						//  {
						// odds=atoi(odds_.c_str());
						// min=0;
						// max=0;
						//    std::string::size_type pos = 0;
						//    if  ( (pos = number_.find("-")) != std::string::npos )
						//    {
						//      
						//      min = atoi(number_.substr(0,pos).c_str());
						//      max = atoi(number_.substr(pos+strlen("-")).c_str());
						//      //if (odds) Zebra::logger->debug("odds:%d\tmin:%d\tmax:%d",odds,min,max);
						//    }
						//  }
						//} hole;            //孔

	BYTE recast;        // 改造

	BYTE recastlevel;       // 合成等级
	WORD recastcost;      // 合成单价


	WORD make;          // 打造
	struct skills
	{
		WORD id;
		BYTE level;
		skills(const std::string& id_ = "0", const std::string& level_ = "0") : id(atoi(id_.c_str())), level(atoi(level_.c_str()))
		{ }
	};
	skills need_skill;      // 需要技能

	struct material
	{
		WORD gold;
		struct  stuff
		{
			WORD id;
			WORD number;
			BYTE level;
			stuff(const std::string& id_, const std::string& level_, const std::string& number_) : id(atoi(id_.c_str())), number(atoi(number_.c_str())), level(atoi(level_.c_str()))
			{ }
		};
		std::vector<stuff> stuffs;
		typedef std::vector<stuff>::iterator stuffs_iterator;
	};
	material need_material;    // 需要原料

	BYTE setpos;        // 装备位置
	WORD durability;      // 耐久度
	DWORD price;        // 价格

	BYTE width;          // 格子宽
	BYTE height;        // 格子高
	union
	{
		DWORD cardpoint;      // 金子 (已经无用)
		DWORD cointype;        // 货币类型
	};
	WORD bang;          //重击
	DWORD holyrating;      //神圣概率
	std::vector<DWORD> holys;     //神圣标识

								  // sky 新增基本属性
	WORD str;				 //力量
	WORD inte;			 //智力
	WORD dex;				 //敏捷
	WORD spi;				 //精神
	WORD con;				 //耐力

	WORD atkhpp;  //魔法免伤
	WORD mtkhpp;  //魔法免伤

	int  nSuitData;

	void fill(ObjectBase &data)
	{
		nSuitData = -1;

		id = data.dwField0;
		strncpy(name, data.strField1, MAX_NAMESIZE);

		maxnum = data.dwField2;
		kind = data.dwField3;
		job = data.dwField4;
		needlevel = data.dwField5;
		level = data.dwField6;

		init_identifier(hole, data.strField7);

		needobject = data.dwField8;
		init_leechdom(data.strField9);

		maxhp = data.dwField10;
		maxmp = data.dwField11;
		maxsp = data.dwField12;

		pdamage = data.dwField13;
		maxpdamage = data.dwField14;
		mdamage = data.dwField15;
		maxmdamage = data.dwField16;
		pdefence = data.dwField17;
		mdefence = data.dwField18;
		damagebonus = data.dwField19;

		akspeed = data.dwField20;
		mvspeed = data.dwField21;
		atrating = data.dwField22;
		akdodge = data.dwField23;

		recast = data.dwField24;
		recastlevel = data.dwField25;

		make = data.dwField26;

		init_need_skills(data.strField27);
		init_need_material(data.strField28);

		setpos = data.dwField29;
		durability = data.dwField30;
		price = data.dwField31;

		//sky  新游戏里已经不需要这个属性拉
		/*bluerating = data.dwField34;
		goldrating = data.dwField35;*/

		color = data.dwField32;
		width = data.dwField33;
		height = data.dwField34;
		cardpoint = data.dwField35;
		recastcost = data.dwField36;
		bang = data.dwField37;

		holyrating = data.dwField38;
		init_identifier(holys, data.strField39);

		//sky 新增加属性
		str = data.dwField40;	//力量
		inte = data.dwField41;	//智力
		dex = data.dwField42;	//敏捷
		spi = data.dwField43;	//精神
		con = data.dwField44;	//耐力
		atkhpp = data.dwField45;  //魔法免伤
		mtkhpp = data.dwField46;  //魔法免伤


	}

	zObjectB() :zEntry()/*,hole("0","0-0")*/
	{
		bzero(this, sizeof(zObjectB));
	};

	void init_identifier(std::vector<DWORD>& list, const std::string& info)
	{
		list.clear();
		//getAllNum(info.c_str(), list);
	}

	void init_leechdom(const std::string& info)
	{
		/*leechdom_t* p = Parse3<leechdom_t>()(info, ":");
		if (p) {
			leechdom = *p;
			SAFE_DELETE(p);
		}*/
	}

	/*void init_socket(const std::string& socket_info)
	{
	std::string::size_type pos = socket_info.find(':');
	if (pos != std::string::npos) {
	hole = socket(socket_info.substr(0,pos),socket_info.substr(pos+1));
	}

	}*/

	void init_need_skills(const std::string& skills_list)
	{
		std::string::size_type pos = skills_list.find(':');
		if (pos != std::string::npos) {
			need_skill = skills(skills_list.substr(0, pos), skills_list.substr(pos + 1));
		}
	}

	void init_need_material(const std::string& materials)
	{
		/*need_material.stuffs.clear();
		Split<Parse3> p;
		std::string::size_type pos = materials.find(':');
		if (pos != std::string::npos) {
			need_material.gold = atoi(materials.substr(0, pos).c_str());
			p(materials.substr(pos + 1), need_material.stuffs, ";", "-");
		}*/
	}

};

//------------------------------------
// ColorObjectBase
//------------------------------------
struct ColorObjectBase {
	const DWORD getUniqueID() const
	{
		return dwField0;
	}

	DWORD  dwField0;    // 编号
	char  strField1[64];    // 名称
	char  strField2[32];    // 连接符
	char  strField3[128];    // 金色品质
	char  strField4[32];    // 力量
	char  strField5[32];    // 智力
	char  strField6[32];    // 敏捷
	char  strField7[32];    // 精神
	char  strField8[32];    // 体质
	char  strField9[32];    // 五行属性
	char  strField10[32];    // 最小物攻
	char  strField11[32];    // 最大物攻
	char  strField12[32];    // 最小魔攻
	char  strField13[32];    // 最大魔攻
	char  strField14[32];    // 物防
	char  strField15[32];    // 魔防
	char  strField16[32];    // 最大生命值
	char  strField17[32];    // 最大法术值
	char  strField18[32];    // 最大体力值
	char  strField19[32];    // 移动速度
	char  strField20[32];    // 生命值恢复
	char  strField21[32];    // 法术值恢复
	char  strField22[32];    // 体力值恢复
	char  strField23[32];    // 攻击速度
	char  strField24[32];    // 增加物理攻击力
	char  strField25[32];    // 增加物理防御力
	char  strField26[32];    // 增加魔法攻击力
	char  strField27[32];    // 增加魔法防御力
	char  strField28[32];    // 命中率
	char  strField29[32];    // 闪避率
	char  strField30[32];    // 抗毒增加
	char  strField31[32];    // 抗麻痹增加
	char  strField32[32];    // 抗眩晕增加
	char  strField33[32];    // 抗噬魔增加
	char  strField34[32];    // 抗噬力增加
	char  strField35[32];    // 抗混乱增加
	char  strField36[32];    // 抗冰冻增加
	char  strField37[32];    // 抗石化增加
	char  strField38[32];    // 抗失明增加
	char  strField39[32];    // 抗定身增加
	char  strField40[32];    // 抗减速增加
	char  strField41[32];    // 抗诱惑增加
	char  strField42[32];    // 恢复耐久度
	char  strField43[32];    // 重击
	DWORD  dwField44;    // 神圣装备几率
	char  strField45[1024];    // 技能加成
	char  strField46[32];    // 全系技能加成
};

struct zObject :zEntry
{
	friend class GlobalObjectIndex;
public:
	t_Object data;
	zObjectB *base;

	//only for RebuildObject::make,it's ugly,but .....sigh
	WORD* _p1[5];
	WORD* _p2[18];

	static zObject *create(zObjectB *objbase, DWORD num = 1, BYTE level = 0);
	static void destroy(zObject* ob);
	static void logger(QWORD createid, DWORD objid, char *objname, DWORD num, DWORD change, DWORD type, DWORD srcid, char *srcname, DWORD dstid, char *dstname, const char *action, zObjectB *base, BYTE kind, BYTE upgrade);
	static DWORD RepairMoney2RepairGold(DWORD dwObjectRepair);
	static zObject *create(zObject *objsrc);
	static zObject *load(const SaveObject *o);
	bool getSaveData(SaveObject *save);
	int foundSocket();
	bool canMail();
	void checkBind();

	//zCountryMaterialB* canContribute(); // 是否能被捐献
	DWORD getMaterialKind(); // 获得原料类别: 0,普通物资，1,丝线,2,矿石,3,矿产,4,木材，5,皮毛,6,草药

	const stObjectLocation &reserve() const;
	void restore(const stObjectLocation &loc);

	union
	{
		struct
		{
			DWORD createtime;
			DWORD dwCreateThisID;
		};
		QWORD createid;
	};
	// */
private:
	//friend class Package;
	//friend class Packages;
	//friend class MainPack;
	//friend class zSceneObject;
	//friend class luabind::detail::delete_s<zObject>;

	zObject();
	~zObject();

	bool free() const;
	void free(bool flag);

	void fill(t_Object& d);
	void generateThisID();
	bool inserted;

	//[Shx Add 检查该物品是否套装组成]
	void MakeSuit(zObjectB *objbase);
	void FillSuit();
	void FillSuitPPT(int nIndex);
};
struct zSceneObject :public zSceneEntry
{
	static zSceneObject *create(zObject *obj, const zRTime &ct)
	{
		if (obj == NULL) return NULL;
		zSceneObject *ret = new zSceneObject(obj, ct);
		return ret;
	}
	/**
	* \brief 检查地上物品是否过期
	* 过期的地上物品会消失掉
	* \param ct 当前时间
	* \return 是否过期
	*/
	bool checkOverdue(const zRTime &ct) const
	{
		return ct >= this->ct;
	}

	bool checkProtectOverdue(const zRTime &ct)
	{
		if (ownerID == 0)
		{
			return false;
		}
		if (ct > protectTime)
		{
			protectTime = 0;
			ownerID = 0;
			return true;
		}
		return false;
	}

	void setOwner(DWORD dwID, int protime = 10)
	{
		if (dwID)
		{
			ownerID = dwID;
			zRTime ctv;
			protectTime = ctv;
			this->protectTime.addDelay(protime * 1000);
		}
	}

	void setOverDueTime(zRTime &ct_1)
	{
		ct = ct_1;
	}
	DWORD getOwner()
	{
		return ownerID;
	}

	~zSceneObject()
	{
		//if (o) o->free();
		zObject::destroy(o);
	}

	void clear()
	{
		o = NULL;
	}

	zObject *getObject()
	{
		return o;
	}

	// sky 重新设置保护时间
	void setprotectTime(int i)
	{
		protectTime.addDelay(i * 1000);
	}

	// sky 强行删除物品保护
	bool DelProtectOverdue()
	{
		if (ownerID == 0)
			return false;

		protectTime = 0;
		ownerID = 0;
		return true;
	}

private:
	DWORD ownerID;
	zRTime protectTime;
	zObject *o;
	zRTime ct;
	zSceneObject(zObject *obj, const zRTime &ct) :zSceneEntry(SceneEntry_Object), ct(ct)
	{
		this->ct.addDelay(600 * 1000);
		o = obj;
		ownerID = 0;
		id = obj->data.qwThisID;
		tempid = obj->base->id;
		strncpy_s(name, obj->data.strName, MAX_NAMESIZE);
	}
};

/**
* \brief 场景物件屏索引
*/
class zSceneEntryIndex : private zNoncopyable
{

protected:

	///场景宽和高
	zPos sceneWH;
	///最大屏索引编号
	DWORD screenMax;
	///横向多少屏幕
	DWORD screenx;
	///纵向多少屏幕
	DWORD screeny;

private:

	typedef std::set<zSceneEntry *, std::less<zSceneEntry *> > SceneEntry_SET;
	typedef std::set<SceneNpc *, std::less<SceneNpc *> > Npc_Index;

	typedef UNORDERED_MAP<zPosI, SceneEntry_SET> PosIMapIndex;
	typedef UNORDERED_MAP<DWORD, Npc_Index> SpecialNpc_Index;

	/**
	* \brief map索引容器
	*/
	PosIMapIndex index[zSceneEntry::SceneEntry_MAX];
	/// 所有物件的索引
	SceneEntry_SET all[zSceneEntry::SceneEntry_MAX];
	/// 对于特殊npc的索引
	SpecialNpc_Index special_index;
	/// 对于功能npc的索引
	Npc_Index functionNpc;

	typedef std::map<DWORD, int, std::less<DWORD> > PosiEffectMap;

	typedef PosiEffectMap::iterator PosiEffectMap_iter;
	PosiEffectMap posiEffect[MAX_NPC_GROUP];

	//在加载的时候计算九屏关系并保存
	typedef UNORDERED_MAP<DWORD, zPosIVector> NineScreen_map;
	typedef NineScreen_map::iterator NineScreen_map_iter;
	typedef NineScreen_map::const_iterator NineScreen_map_const_iter;
	typedef NineScreen_map::value_type NineScreen_map_value_type;
	NineScreen_map ninescreen;
	NineScreen_map direct_screen[8];
	NineScreen_map reversedirect_screen[8];

	void freshEffectPosi(const zPosI oldposi, const zPosI newposi);

public:

	/**
	* \brief 构造函数
	*/
	zSceneEntryIndex() {}
	/**
	* \brief 析构函数
	*/
	virtual ~zSceneEntryIndex() {}

	virtual void freshGateScreenIndex(SceneUser *pUser, const DWORD screen) = 0;

	bool refresh(zSceneEntry *e, const zPos & newPos);
	bool removeSceneEntry(zSceneEntry *e);
	void execAllOfScreen(const zPosI screen, zSceneEntryCallBack &callback);
	void execAllOfScreen(const zSceneEntry::SceneEntryType type, const zPosI screen, zSceneEntryCallBack &callback);
	void execAllOfScene(zSceneEntryCallBack &callback);
	void execAllOfScene(const zSceneEntry::SceneEntryType type, zSceneEntryCallBack &callback);
	void execAllOfScene_npc(const DWORD id, zSceneEntryCallBack &callback);
	void execAllOfScene_functionNpc(zSceneEntryCallBack &callback);

	void setSceneWH(const zPos sceneWH, const DWORD screenx, const DWORD screeny, const DWORD screenMax);
	zSceneEntry *getSceneEntryByPos(zSceneEntry::SceneEntryType type, const zPos &pos, const bool bState = true, const zSceneEntry::SceneEntryState byState = zSceneEntry::SceneEntry_Normal);

	void execAllOfEffectNpcScreen(const DWORD group, zSceneEntryCallBack &callback);

	/**
	* \brief 获取地图宽
	* 单位是格点
	* \return 地图宽
	*/
	const DWORD width() const { return sceneWH.x; }
	/**
	* \brief 获取地图高
	* 单位是格点
	* \return 地图高
	*/
	const DWORD height() const { return sceneWH.y; }
	/**
	* \brief 获取地图宽
	* 单位是屏
	* \return 地图宽
	*/
	const DWORD getScreenX() const { return screenx; }
	/**
	* \brief 获取地图高
	* 单位是屏
	* \return 地图高
	*/
	const DWORD getScreenY() const { return screeny; }
	/**
	* \brief 坐标转化
	* 绝对坐标转化为屏编号相对坐标
	* \param p 绝对坐标系统
	* \param pi 相对坐标系统
	* \return 返回转化后的相对坐标系统
	*/
	zPosI &zPos2zPosI(const zPos &p, zPosI &pi) const
	{
		zSceneEntry::zPos2zPosI(sceneWH, p, pi);
		return pi;
	}
	/**
	* \brief 重新计算坐标，保证不越界
	* \param pos 待验证的坐标
	*/
	const void zPosRevaluate(zPos &pos) const
	{
		if (pos.x & 0x80000000)
			pos.x = 0;
		if (pos.y & 0x80000000)
			pos.y = 0;
		if (pos.x >= sceneWH.x)
			pos.x = sceneWH.x - 1;
		if (pos.y >= sceneWH.y)
			pos.y = sceneWH.y - 1;
	}
	/**
	* \brief 验证坐标是否合法，是否越界
	* \param pos 坐标
	* \return 是否合法
	*/
	const bool zPosValidate(const zPos &pos) const { return pos.x < sceneWH.x && pos.y < sceneWH.y; }
	/**
	* \brief 验证坐标是否合法，是否越界
	* \param posi 坐标
	* \return 是否合法
	*/
	const bool zPosIValidate(const zPosI &posi) const { return posi < screenMax; }
	/**
	* \brief 检查两个坐标编号是否有9屏关系
	* \param one 第一个编号
	* \param two 第二个编号
	* \return 是否有9屏关系
	*/
	bool checkTwoPosIInNine(const zPosI one, const zPosI two) const
	{
		int oneX, oneY, twoX, twoY;
		oneX = one % screenx;
		oneY = one / screenx;
		twoX = two % screenx;
		twoY = two / screenx;
		if (abs(oneX - twoX) <= 1 && abs(oneY - twoY) <= 1)
		{
			return true;
		}
		return false;
	}
	/**
	* \brief 判断两点之间距离是否超出了半径
	* \param pos1 起点
	* \param pos2 终点
	* \param radius 半径
	* \return 是否超出范围
	*/
	const bool zPosShortRange(const zPos &pos1, const zPos &pos2, const int radius) const
	{
		if (abs((long)(pos1.x - pos2.x)) <= radius
			&& abs((long)(pos1.y - pos2.y)) <= radius)
			return true;
		else
			return false;
	}
	/**
	* \brief 判断两点之间距离是否超出了矩形范围
	* \param pos1 起点
	* \param pos2 终点
	* \param wide 矩形宽
	* \param height 矩形高
	* \return 是否超出范围
	*/
	const bool zPosShortRange(const zPos &pos1, const zPos &pos2, const int wide, const int height) const
	{
		if (abs((long)(pos1.x - pos2.x)) <= wide
			&& abs((long)(pos1.y - pos2.y)) <= height)
			return true;
		else
			return false;
	}
	/*
	* \brief 得到两点的距离
	* 这个距离只是作为比较判断，不是作为实际的距离
	* \param pos1 位置1
	* \param pos2 位置2
	* \return 距离
	*/
	DWORD getDistance(zPos pos1, zPos pos2) const { return abs((long)(pos1.x - pos2.x)) + abs((long)(pos1.y - pos2.y)); }
	/**
	* \brief 方向取反
	* \param direct 方向
	* \return 相反的方向
	*/
	int getReverseDirect(const int direct) const { return (direct + 4) % 8; }
	/**
	* \brief 根据两屏判断九个方向
	* \param posiorg 原点屏编号
	* \param posinew 结束点屏编号
	* \return 方向编号，如果为-1表示不是九个方向之一
	*/
	int getScreenDirect(const zPosI posiorg, const zPosI posinew) const
	{
		using namespace Cmd;
		DWORD orgX = posiorg % screenx;
		DWORD orgY = posiorg / screenx;
		DWORD newX = posinew % screenx;
		DWORD newY = posinew / screenx;
		if (orgX == newX && orgY == newY + 1)
		{
			return _DIR_UP;
		}
		else if (orgX + 1 == newX && orgY == newY + 1)
		{
			return _DIR_UPRIGHT;
		}
		else if (orgX + 1 == newX && orgY == newY)
		{
			return _DIR_RIGHT;
		}
		else if (orgX + 1 == newX && orgY + 1 == newY)
		{
			return _DIR_RIGHTDOWN;
		}
		else if (orgX == newX && orgY + 1 == newY)
		{
			return _DIR_DOWN;
		}
		else if (orgX == 1 + newX && orgY + 1 == newY)
		{
			return _DIR_DOWNLEFT;
		}
		else if (orgX == 1 + newX && orgY == newY)
		{
			return _DIR_LEFT;
		}
		else if (orgX == 1 + newX && orgY == 1 + newY)
		{
			return _DIR_LEFTUP;
		}
		else
			return _DIR_WRONG;
	}

	/**
	* \brief 查找我在另一个坐标点的大致方向
	* \param myPos 我的位置
	* \param otherPos 对方的位置
	* \return 我在otherPos的相对方向
	*/
	static int getCompDir(const zPos &myPos, const zPos &otherPos)
	{
		int x = otherPos.x - myPos.x;
		int y = otherPos.y - myPos.y;
		int absx = abs(x);
		int absy = abs(y);
		if (absx > absy && absy < absx / 2)
			y = 0;
		else if (absx < absy && absx < absy / 2)
			x = 0;

		int bkDir = 0;

		if (x < 0 && y < 0)
			bkDir = 7;
		else if (x < 0 && 0 == y)
			bkDir = 6;
		else if (x < 0 && y > 0)
			bkDir = 5;
		else if (0 == x && y > 0)
			bkDir = 4;
		else if (x > 0 && y > 0)
			bkDir = 3;
		else if (x > 0 && 0 == y)
			bkDir = 2;
		else if (x > 0 && y < 0)
			bkDir = 1;
		else if (0 == x && y < 0)
			bkDir = 0;
		return bkDir;
	}
	const zPosIVector &getScreenByRange(const zPos &pos, const int range);
	/**
	* \brief 以中心屏获取周围9屏的屏幕编号
	* \param posi 中心屏
	* \param pv 输出的屏编号向量
	*/
	const zPosIVector &getNineScreen(const zPosI &posi)
	{
		NineScreen_map_const_iter iter = ninescreen.find((DWORD)posi);
		if (iter != ninescreen.end())
		{
			return iter->second;
		}
		//如果出现异常返回0编号的屏索引
		return ninescreen[(DWORD)-1];
	}

	/**
	* \brief 以中心屏获取向前的3屏或者5屏的屏幕编号
	* \param posi 中心屏
	* \param direct 方向
	* \return 输出的屏编号向量
	*/
	const zPosIVector &getDirectScreen(const zPosI &posi, const int dir)
	{
		NineScreen_map_const_iter iter = direct_screen[dir].find((DWORD)posi);
		if (iter != direct_screen[dir].end())
		{
			return iter->second;
		}
		//如果出现异常返回0编号的屏索引
		return direct_screen[dir][(DWORD)-1];
	}

	/**
	* \brief 以中心屏获取向后的3屏或者5屏的屏幕编号
	* \param posi 中心屏
	* \param direct 方向
	* \return 输出的屏编号向量
	*/
	const zPosIVector &getReverseDirectScreen(const zPosI &posi, const int dir)
	{
		NineScreen_map_const_iter iter = reversedirect_screen[dir].find((DWORD)posi);
		if (iter != reversedirect_screen[dir].end())
		{
			return iter->second;
		}
		//如果出现异常返回0编号的屏索引
		return reversedirect_screen[dir][(DWORD)-1];
	}

};

//需要进行AI动作的npc
typedef std::set<SceneNpc *, std::less<SceneNpc *> > MonkeyNpcs;

enum
{
	MAP_FUNCTION_NORIDE = 0x1,	//sky 不可以骑坐骑
	MAP_FUNCTION_CAPITAL = 0x2,	//sky 首都
	MAP_FUNCTION_MAZE = 0x4,	//sky 地下城
	MAP_FUNCTION_NOSCROLL = 0x8,	//sky 不可以使用卷轴
	MAP_FUNCTION_NORED = 0x10,	//sky 不红名
	MAP_FUNCTION_NOVICE = 0x20,	//sky 新手保护
	MAP_FUNCTION_NOTEAM = 0x40, //sky 不可以组队
	MAP_FUNCTION_NOCALLOBJ = 0x80, //sky 不可以使用令牌
	MAP_FUNCTION_BATTLEFIEL = 0x100,//sky 战场类地图

};

/**
* \brief 格子定义
*/
#define TILE_BLOCK      0x01  // 阻挡点
#define TILE_MAGIC_BLOCK  0x02  // 魔法阻挡点
#define TILE_NOCREATE    0x04  // 不能建造点
#define TILE_DOOR      0x08  // 门
#define TILE_ENTRY_BLOCK  0x10  // 人物或者Npc阻挡
#define TILE_OBJECT_BLOCK  0x20  // 物品阻挡
#pragma  pack(1)
/**
* \brief 格字数据结构
*
*/
struct stSrvMapTile
{
	BYTE  flags;  // 格子属性
	BYTE  type;  // 格子类型
};
#pragma pack()

typedef stSrvMapTile Tile;
typedef std::vector<Tile> zTiles;


/**
* \brief 地图场景
*/
class Scene :public zScene, public zSceneEntryIndex
{

protected:

	Scene();

public:

	//由Session控制刷新的npc
	std::map<DWORD, SceneNpc *> bossMap;

	/**
	* \brief 场景类型定义
	*/
	enum SceneType
	{
		STATIC,   /// 静态地图
		GANG    /// 动态地图
	};

	virtual ~Scene();
	virtual bool save() = 0;

	bool init(DWORD countryid, DWORD mapid);
	void final();
	void freshGateScreenIndex(SceneUser *pUser, const DWORD screen);

	bool sendCmdToWatchTrap(const zPosI screen, const void *pstrCmd, const int nCmdLen);
	bool sendCmdToNine(const zPosI screen, const void *pstrCmd, const int nCmdLen, unsigned short dupIndex = 0);
	bool sendCmdToNineUnWatch(const zPosI screen, const void *pstrCmd, const int nCmdLen);
	bool sendCmdToScene(const void *pstrCmd, const int nCmdLen, unsigned short dupIndex = 0);
	bool sendCmdToNineExceptMe(zSceneEntry *pEntry, const zPosI screen, const void *pstrCmd, const int nCmdLen);
	bool sendCmdToDirect(const zPosI screen, const int direct, const void *pstrCmd, const int nCmdLen, unsigned short dupIndex = 0);
	bool sendCmdToReverseDirect(const zPosI screen, const int direct, const void *pstrCmd, const int nCmdLen, unsigned short dupIndex = 0);
	bool findEntryPosInNine(const zPos &vpos, zPosI vposi, zPosVector &range);
	bool findEntryPosInOne(const zPos &vpos, zPosI vposi, zPosVector &range);

	int summonNpc(const t_NpcDefine &define, const zPos &pos, zNpcB *base, unsigned short dupIndex = 0);
	template <typename Npc>
	Npc* summonOneNpc(const t_NpcDefine &define, const zPos &pos, zNpcB *base, unsigned short dupIndex, DWORD standTime = 0, zNpcB* abase = NULL, BYTE vdir = 4, SceneEntryPk * m = NULL);

	bool refreshNpc(SceneNpc *sceneNpc, const zPos & newPos);

	/**
	* \brief 获取重生地图
	* \return 重生地图ID
	*/
	DWORD backtoMap() const { return backtoMapID; }
	/**
	* \brief 获取回城地图
	* \return 回城地图ID
	*/
	DWORD backtoCityMap() const { return backtoCityMapID; }
	/**
	* \brief 允许相互pk的等级
	* \return 是true
	*/
	DWORD getPkLevel() const { return pklevel; }
	/**
	* \brief 检测该地图是否可以骑马
	* \return 可骑马时true
	*/
	bool canRide() const { return !(function & MAP_FUNCTION_NORIDE); }
	/**
	* \brief 不能使用卷轴
	* \return 是主城返回true
	*/
	bool canUserScroll() const { return !(function & MAP_FUNCTION_NOSCROLL); }
	/**
	* \brief 检测该地图是否可以组队
	* \return 可组队时true
	*/
	bool noTeam() const { return (function & MAP_FUNCTION_NOTEAM); }
	/**
	* \brief 检测该地图是否可以使用令牌
	* \return 是否可用
	*/
	bool checkCallObj() const { return (function & MAP_FUNCTION_NOCALLOBJ); }
	/**
	* \brief 是否是主城
	* \return 是主城返回true
	*/
	bool isMainCity() const { return (function & MAP_FUNCTION_CAPITAL); }
	/**
	* \brief 是否是地洞类
	* \return 是主城返回true
	*/
	bool isField() const { return (function & MAP_FUNCTION_MAZE); }
	/**
	* \brief sky 修改为新手保护地图
	* \return 是新手保护地图返回true
	*/
	bool isNovice() const { return (function & MAP_FUNCTION_NOVICE); }
	/**
	* \brief 是否是不红名地图
	* \return 是true
	*/
	bool isNoRedScene() const { return (function & MAP_FUNCTION_NORED); }
	/**
	* \brief 是否是PK地图
	* \return 是true
	*/
	bool isPkMap() const { return getRealMapID() >= 213 && getRealMapID() <= 215; }
	/**
	* \brief 获取地图编号
	* \return 地图编号
	*/
	const DWORD getRealMapID() const { return id & 0x0000FFFF; }
	/**
	* \brief 获取地图所属国家
	* \return 地图所属国家
	*/
	const DWORD getCountryID() const { return countryID; }

	const char *getCountryName() const;

	/**
	* \brief 获取地图名称
	* \return 地图名称(用于服务间)
	*/
	const char *getName() const { return name; }
	/**
	* \brief 获取地图名称
	* \return 地图名称(未进行组合的名称)
	*/
	const char *getRealName() const
	{
		char *real = const_cast<char*>(strstr(name, "·"));
		if (real != NULL)
			return real + 2;
		else
			return name;
	}
	/**
	* \brief 获取地图文件名称
	* 名称不包括前缀
	* \return 地图文件名称(用于服务间)
	*/
	const char *getFileName() const { return fileName.c_str(); }
	/**
	* \brief 获取地图文件名称
	* 名称不包括前缀
	* \return 地图文件名称(为进行组合的名称)
	*/
	const char *getRealFileName() const { return fileName.c_str() + fileName.find(".") + 1; }
	/**
	* \brief 获取指定地图文件名称
	* 名称不包括前缀
	* \param file 文件名
	* \return 地图文件名称(为进行组合的名称)
	*/
	const char *getRealFileName(std::string file) const { return file.c_str() + file.find(".") + 1; }
	/**
	* \brief 检查坐标阻挡信息
	* \param pos 坐标
	* \param block 阻挡标记
	* \return 是否阻挡点
	*/
	const bool checkBlock(const zPos &pos, const BYTE block) const
	{
		if (zPosValidate(pos))
			return (0 != (allTiles[pos.y * width() + pos.x].flags & block));
		else
			return true;
	}
	/**
	* \brief 检查坐标阻挡信息
	* \param pos 坐标
	* \return 是否阻挡点
	*/
	const bool checkBlock(const zPos &pos) const { return checkBlock(pos, TILE_BLOCK | TILE_ENTRY_BLOCK); }
	/**
	* \brief 设置目标阻挡点标记
	* \param pos 坐标
	* \param block 阻挡标记
	*/
	void setBlock(const zPos &pos, const BYTE block)
	{
		if (zPosValidate(pos))
			allTiles[pos.y * width() + pos.x].flags |= block;
	}
	/**
	* \brief 设置目标阻挡点标记
	* \param pos 坐标
	*/
	void setBlock(const zPos &pos) { setBlock(pos, TILE_ENTRY_BLOCK); }

	// [ranqd] 设置区域阻挡点标记
	void setBlock(const zZone &zone, const BYTE block)
	{
		for (int x = zone.pos.x; x < zone.pos.x + zone.width; x++)
		{
			for (int y = zone.pos.y; y < zone.pos.y + zone.height; y++)
			{
				zPos pos;
				pos.x = x;
				pos.y = y;
				if (zPosValidate(pos))
					allTiles[pos.y * width() + pos.x].flags |= block;
			}
		}
	}

	void setBlock(const zZone &pos) { setBlock(pos, TILE_ENTRY_BLOCK); }
	/**
	* \brief 清除目标阻挡点标记
	* \param pos 坐标
	* \param block 阻挡标记
	*/
	void clearBlock(const zPos &pos, const BYTE block)
	{
		if (zPosValidate(pos))
			allTiles[pos.y * width() + pos.x].flags &= ~block;
	}
	/**
	* \brief 清除目标阻挡点标记
	* \param pos 坐标
	*/
	void clearBlock(const zPos &pos) { clearBlock(pos, TILE_ENTRY_BLOCK); }
	/**
	* \brief 检查坐标阻挡信息
	* 主要在丢物品的时候使用
	* \param pos 坐标
	* \return 是否阻挡点
	*/
	const bool checkObjectBlock(const zPos &pos) const { return checkBlock(pos, TILE_BLOCK | TILE_OBJECT_BLOCK); }
	/**
	* \brief 设置目标阻挡点标记
	* 主要在丢物品的时候使用
	* \param pos 坐标
	*/
	void setObjectBlock(const zPos &pos) { setBlock(pos, TILE_OBJECT_BLOCK); }
	/**
	* \brief 清除目标阻挡点标记
	* 主要在丢物品的时候使用
	* \param pos 坐标
	*/
	void clearObjectBlock(const zPos &pos) { clearBlock(pos, TILE_OBJECT_BLOCK); }
	/**
	* \brief 获取地表数据
	* \param pos 坐标
	* \return 返回地表数据
	*/
	const Tile* getTile(const zPos &pos) const
	{
		if (zPosValidate(pos))
			return &allTiles[pos.y * width() + pos.x];
		else
			return NULL;
	}
	/**
	* \brief 根据位置得到路点
	* \param pos 要查找的位置
	* \return 找到的路点,失败返回0
	*/
	//WayPoint *getWayPoint(const zPos &pos) { return wpm.getWayPoint(pos); }
	/**
	* \brief 根据目标找到路点
	* \param filename 目标地图文件名
	* \return 找到的路点,失败返回0
	*/
	//WayPoint *getWayPoint(const char *filename) { return wpm.getWayPoint(filename); }
	/**
	* \brief 随机选一个路点
	* \return 找到的路点
	*/
	//WayPoint *getRandWayPoint() { return wpm.getRandWayPoint(); }
	/**
	* \brief 返回地图上的人数
	* \return 一张地图上的人数
	*/
	const DWORD countUser() const { return userCount; }
	/**
	* \brief 人数增加
	* \return 增加后的人数
	*/
	const DWORD addUserCount() { return ++userCount; }
	/**
	* \brief 人数减少
	* \return 减少后的人数
	*/
	const DWORD subUserCount() { return --userCount; }

	bool findPosForObject(const zPos &pos, zPos &findedPos);
	bool findPosForUser(const zPos &pos, zPos &findedPos);
	SceneUser *getSceneUserByPos(const zPos &pos, const bool bState = true, const zSceneEntry::SceneEntryState byState = zSceneEntry::SceneEntry_Normal);
	SceneUser *getUserByID(DWORD userid);
	SceneUser *getUserByTempID(DWORD usertempid);
	SceneUser *getUserByName(const char *username);
	SceneNpc *getSceneNpcByPos(const zPos &pos, const bool bState = true, const zSceneEntry::SceneEntryState byState = zSceneEntry::SceneEntry_Normal);
	SceneNpc *getNpcByTempID(DWORD npctempid);
	zSceneObject *getSceneObjectByPos(const zPos &pos);

	bool addObject(unsigned short dupIndex, zObject *ob, const zPos &pos, const unsigned long overdue_msecs = 0, const unsigned long dwID = 0, int protime = 10);
	bool addObject(unsigned short dupIndex, zObjectB *ob, const int num, const zPos &pos, const unsigned long dwID = 0, DWORD npc_mul = 0, DWORD teamID = 0);
	void removeUser(SceneUser *so);
	void removeObject(zSceneObject *so);
	void removeNpc(SceneNpc *sn);
	bool checkZoneType(const zPos &pos, const int type) const;
	int getZoneType(const zPos &pos) const;
	bool randzPosByZoneType(const int type, zPos &pos) const;
	int changeMap(SceneUser *pUser, bool deathBackto = true, bool ignoreWar = false);
	bool randzPosByZoneType(const int type, zPos &pos, const zPos orign);
	bool randzPosOnRect(const zPos &center, zPos &pos, WORD rectx = SCREEN_WIDTH, WORD recty = SCREEN_HEIGHT) const;

	bool getNextPos(int &side, const int direct, const zPos &orgPos, const int clockwise, zPos &crtPos) const;
	void getNextPos(const zPos &orgPos, const int dir, zPos &newPos) const;
	bool SceneEntryAction(const zRTime& ctv, const DWORD group);
	void removeSceneObjectInOneScene();

	
	void reliveSecGen();
	const DWORD getTax() const { return countryTax; }
	void addFieldMapName(const char *name)
	{
		stMapName mapname;
		strncpy_s(mapname.strMapName, name, MAX_NAMESIZE);
		fieldMapName.push_back(mapname);
	}
	void clearFieldMapName() { fieldMapName.clear(); }
	DWORD getField(const char *ou) const
	{
		stMapName *out = (stMapName *)ou;
		int i = 0;
		for (std::vector<stMapName>::const_iterator iter = fieldMapName.begin(); iter != fieldMapName.end(); iter++)
		{
			strncpy_s((&out[i])->strMapName, (*iter).strMapName, MAX_NAMESIZE);
			i++;
		}
		return i;
	}
	bool checkField(const char *out) const
	{
		for (std::vector<stMapName>::const_iterator iter = fieldMapName.begin(); iter != fieldMapName.end(); iter++)
		{
			if (strncmp((char *)out, (*iter).strMapName, MAX_NAMESIZE) == 0)
			{
				return true;
			}
		}
		return false;
	}
	void addMainMapName(const char *name)
	{
		stMapName mapname;
		strncpy_s(mapname.strMapName, name, MAX_NAMESIZE);
		mainMapName.push_back(mapname);
	}

	void clearMainMapName() { mainMapName.clear(); }
	DWORD getMainCity(const char *ou) const
	{
		stMapName *out = (stMapName *)ou;
		int i = 0;
		for (std::vector<stMapName>::const_iterator iter = mainMapName.begin(); iter != mainMapName.end(); iter++)
		{
			strncpy_s((&out[i])->strMapName, (*iter).strMapName, MAX_NAMESIZE);
			i++;
		}
		return i;
	}
	bool checkMainCity(const char *out) const
	{
		for (std::vector<stMapName>::const_iterator iter = mainMapName.begin(); iter != mainMapName.end(); iter++)
		{
			if (strncmp((char *)out, (*iter).strMapName, MAX_NAMESIZE) == 0)
			{
				return true;
			}
		}
		return false;
	}

	void addIncMapName(const char *name)
	{
		stMapName mapname;
		strncpy_s(mapname.strMapName, name, MAX_NAMESIZE);
		incMapName.push_back(mapname);
	}

	void clearIncMapName() { incMapName.clear(); }
	DWORD getIncCity(const char *ou) const
	{
		stMapName *out = (stMapName *)ou;
		int i = 0;
		for (std::vector<stMapName>::const_iterator iter = incMapName.begin(); iter != incMapName.end(); iter++)
		{
			strncpy_s((&out[i])->strMapName, (*iter).strMapName, MAX_NAMESIZE);
			i++;
		}
		return i;
	}
	bool checkIncCity(const char *out) const
	{
		for (std::vector<stMapName>::const_iterator iter = incMapName.begin(); iter != incMapName.end(); iter++)
		{
			if (strncmp((char *)out, (*iter).strMapName, MAX_NAMESIZE) == 0)
			{
				return true;
			}
		}
		return false;
	}


	DWORD sceneExp(DWORD exp) const { return (DWORD)(exp * exprate); }
	DWORD winnerExp(DWORD exp) const
	{/*
		if (winner_exp)
		{
			return (DWORD)(exp * 0.5f);
		}
		else*/
		{
			return 0;
		}
	}
	BYTE getLevel() const { return level; }
	bool checkUserLevel(SceneUser *pUser);


	/**
	* \brief 是否是收费地图
	* \return 是否是收费地图
	*/
	bool isTrainingMap()
	{
		DWORD i = id & 0x0000FFFF;
		return (i >= 193 && i <= 202);
	}
	void initRegion(zRegion &reg, const zPos &pos, const WORD width, const WORD height);

	bool randPosByRegion(const zPosIndex &index, zPos &pos) const;
public:
	struct stMapName
	{
		stMapName()
		{
			bzero(strMapName, sizeof(strMapName));
		}
		char strMapName[MAX_NAMESIZE + 1];
	};
	//练功点地图
	std::vector<stMapName> fieldMapName;
	//主城地图
	std::vector<stMapName> mainMapName;
	//增值地图
	std::vector<stMapName> incMapName;
	std::map<std::string, std::string> params;

	///给npc分组处理
	DWORD execGroup;

	/// 帮会夺城战进行标志
	bool isUnionDare;

	/// 该场景所属帮会
	DWORD dwHoldUnionID;

	/// 该场景占领者国家ID
	DWORD dwHoldCountryID;


	/// 正式国战正在该场景进行的标志
	bool isCountryFormalDare;

	/// 皇城战正在该场景进行的标志
	bool isEmperorDare;

	/// 皇城战的守方
	DWORD dwEmperorDareDef;

	///本场景的攻城列表
	//std::list<Rush *> rushList;

	///一秒定时器
	Timer _one_sec;

	///已经初始化
	bool inited;

	///所有的地图格子
	zTiles allTiles;
	///所有的npc定义
	NpcDefineVector npcDefine;
	///场景中各种区域的定义
	ZoneTypeDefVector zoneTypeDef;

	///本场景用户数
	DWORD userCount;
	///如果本地图没有重生区时需要跳转到的地图
	DWORD backtoMapID;
	///回到主城的地图id
	DWORD backtoCityMapID;
	///回到国战目的地
	DWORD backtoDareMapID;
	/// 外国人死亡后应该回到的地图id(没有国家信息)
	DWORD foreignerBacktoMapID;
	/// 在公共国死亡后应该回到的地图id(没有国家信息)
	DWORD commonCountryBacktoMapID;
	/// 无国籍人在外国死亡重生地
	DWORD commonUserBacktoMapID;
	/// 国战战场死亡后,守方死亡复活地
	DWORD countryDefBackToMapID;
	///地图特殊说明
	DWORD function;
	/// 可相互pk的等级
	DWORD pklevel;
	///国家id
	DWORD countryID;
	///场景对应的文件名
	std::string fileName;
	///路点管理器
	WayPointM wpm;
	///本地图收取税费
	DWORD countryTax;
	///本地图允许进入的最小玩家等级
	BYTE level;
	///场景地图加成
	float exprate;

	struct FixedRush
	{
		DWORD id;//ID
		DWORD nextTime;//下次的时间
		DWORD allStart;//总开始时间
		DWORD allEnd;//总结束时间
		int weekDay;//星期几
		tm startTime;//一天中开始的时间
		tm endTime;//一天中结束的时间
		DWORD delay;//开始延迟

		FixedRush()
		{
			id = 0;//ID
			nextTime = 0;//下次的时间
			allStart = 0;//总开始时间
			allEnd = 0;//总结束时间
			weekDay = 0;//星期几
			delay = 0;//开始延迟
		}
	} fixedRush;

	//sky 战场规则文件配置相对路径
	char DulesFileName[MAX_PATH];

	bool initWayPoint(zXMLParser *parser, const xmlNodePtr node, DWORD countryid);
	bool loadMapFile();
	void initNpc(SceneNpc *sceneNpc, zRegion *init_region, zPos myPos = zPos(0, 0));
	bool initByNpcDefine(const t_NpcDefine *pDefine);

	void runCircle_anti_clockwise(const int side, const DWORD X, const DWORD Y, DWORD &CX, DWORD &CY) const;
	void runCircle_clockwise(const int side, const DWORD X, const DWORD Y, DWORD &CX, DWORD &CY) const;

	void updateSceneObject();

	zPosIndex _index;  /// 非阻挡点索引
public:
	//sky 新增战场类场景虚函数
	virtual bool IsGangScene() { return false; }
	virtual void GangSceneTime(const zRTime& ctv) { return; }
	virtual DWORD ReCampThisID(BYTE index) { return 0; }
	//sky 新增战场类场景虚函数 end
};

/**
* \brief 静态场景
*
*/
class StaticScene :public Scene
{
public:
	StaticScene();
	~StaticScene();
	bool save();
	virtual bool IsGangScene() { return false; }
};

/**
* \brief 对每个scene执行的回调基类
*
*/
struct SceneCallBack
{
	virtual bool exec(Scene *scene) = 0;
	virtual ~SceneCallBack() {};
};

/**
* \brief 场景管理器
*
*/
class SceneManager
	:public zSceneManager
{
public:
	typedef std::vector<std::pair<DWORD, DWORD> > NewZoneVec;
	typedef NewZoneVec::iterator newZoneVec_iter;
public:

	DWORD getMapId(DWORD countryid, DWORD mapid);

private:
	///唯一实例
	static SceneManager * sm;
	///唯一ID分配器
	zUniqueDWORDID *sceneUniqeID;

	///是否已初始化
	bool inited;

	SceneManager();
	~SceneManager();

	bool getUniqeID(QWORD &tempid);
	void putUniqeID(const QWORD &tempid);

	///sky 队伍唯一ID分配器
	zUniqueDWORDID *sceneTeamID;

	//sky DWORD1 队伍唯一ID  
	//TeamManager 队伍对象
	//std::map<DWORD, TeamManager*> ScenTeamMap;

	bool newzone;
	NewZoneVec newzon_vec;

public:
	static SceneManager &getInstance();
	static void delInstance();
	bool init();
	void final();

	NewZoneVec &queryNewZonePos();
	bool isNewZoneConfig();
	bool randzPosNewZone(Scene *intoScene, zPos &findedPos);
	void addNewZonePos(DWORD x, DWORD y);
	void setNewZoneConfig(bool type);
	Scene * getSceneByFileName(const char * name);
	Scene * getSceneByName(const char * name);
	Scene * getSceneByTempID(DWORD tempid);
	Scene * getSceneByID(DWORD id);
	Scene * loadScene(/*Scene::SceneType type*/int type, DWORD countryid, DWORD mapid);
	//sky 新增战场动态地图生成
	Scene * loadBattleScene(DWORD baseid);
	//sky end
	void unloadScene(std::string &name);
	void unloadScene(Scene * &scene);
	void unloadAllScene();

	void freshEverySceneField();
	void execEveryScene(SceneCallBack &callback);
	//void execEveryMap(MapCallBack &callback);
	template <class YourEntry>
	void execEveryMap(execEntry<YourEntry> &callback)
	{
		SceneManager::MapMap_iter map_iter = SceneManager::getInstance().map_info.begin();
		for (; map_iter != SceneManager::getInstance().map_info.end(); map_iter++)
		{
			callback.exec(&map_iter->second);
		}
	}

	void checkUnloadOneScene();

	//sky 队伍管理
	///sky 操作队伍唯一ID分配器的方法
	bool getTeamID(DWORD &tempid);
	void putTeamID(const DWORD &tempid);

	//sky 根据队伍的唯一ID返回队伍对象指针
	//TeamManager* GetMapTeam(DWORD TeamID);
	//bool SceneNewTeam(SceneUser *pUser);		//sky 新建队伍
	//bool SceneNewTeam(Cmd::Session::t_Team_Data* send);	//sky 新建队伍(跨场景专用)
														//sky 删除当前场景的队伍管理器里的队伍 同时通知Session也删除队伍管理器的队伍
	bool SceneDelTeam(DWORD TeamID);
	//sky 只删除当前场景的队伍管理器里的队伍
	bool DelMapTeam(DWORD TeamID);
	//sky 遍历队伍管理器处理roll事宜
	void TeamRollItme();
	//sky 队伍 end

	/**
	* \brief 国家信息
	*
	*/
	struct CountryInfo
	{
		///编号
		DWORD id;
		///名字
		char name[MAX_NAMESIZE + 1];
		///所在的地图名字
		DWORD mapid;
		///国家功能标识字段
		DWORD function;
	};
	/**
	* \brief 地图信息
	*
	*/
	struct MapInfo
	{
		///编号
		DWORD id;
		///名字
		char name[MAX_NAMESIZE + 1];
		///对应的地图文件名
		char filename[MAX_NAMESIZE + 1];
		///玩家在该地图死后回到的地图
		DWORD backto;
		///玩家在该地图死后回到的城市
		DWORD backtoCity;
		///玩家在外国地图死后回到的城市
		DWORD foreignbackto;
		///玩家在公共国地图死后回到的城市
		DWORD commoncountrybackto;
		///无国家人在外国地图死后回到的城市
		DWORD commonuserbackto;
		///国战目的地
		DWORD backtodare;
		///国战期间,在国战战场（目前在王城）死亡后,攻方复活城市
		DWORD countrydarebackto;
		///国战期间,在国战战场（目前在王城）死亡后,守方复活城市
		DWORD countrydefbackto;
		///可相互pk的等级
		DWORD pklevel;
		///表示该地图某些功能是否可用,骑马等
		DWORD function;
		///表示该地图允许的level级别的玩家进入
		BYTE level;
		///表示该地图的经验加成(使用时/100求出比率)
		BYTE exprate;
	};
	typedef std::map<DWORD, CountryInfo> CountryMap;
	typedef CountryMap::iterator CountryMap_iter;
	typedef CountryMap::value_type CountryMap_value_type;
	///国家信息和ID的映射
	CountryMap country_info;
	DWORD getCountryIDByCountryName(const char *name);
	const char * getCountryNameByCountryID(DWORD);
	DWORD getMapIDByMapName(const char *name);
	const char *getMapMapNameByMapID(DWORD mapid);
	DWORD buildMapID(DWORD countryid, DWORD mapid);
	bool buildMapName(DWORD countryid, const char *in, char *out);
	bool buildMapName(DWORD countryid, DWORD mapid, char *out);
	typedef std::map<DWORD, MapInfo> MapMap;
	typedef MapMap::value_type MapMap_value_type;
	typedef MapMap::iterator MapMap_iter;
	///地图信息和ID的映射
	MapMap map_info;
};


/**
* \brief 对每个特殊npc执行的回调
*
*/
struct specialNpcCallBack
{
public:
	virtual bool exec(SceneNpc *npc) = 0;
	virtual ~specialNpcCallBack() {};
};

/**
* \brief npc管理器
*
*/
class SceneNpcManager : public zEntryMgr< zEntryTempID >
{
public:

	bool init();
	bool addSceneNpc(SceneNpc *sceneNpc);
	bool addSpecialNpc(SceneNpc *, bool = false);
	void removeSceneNpc(SceneNpc *sceneNpc);

	SceneNpc *getNpcByTempID(DWORD tempid);
	static SceneNpcManager &getMe();
	static void destroyMe();
	/**
	* \brief 对每个npc执行回调函数
	*
	*
	* \param exec 回调函数
	* \return 是否继续执行
	*/
	template <class YourNpcEntry>
	bool execEveryNpc(execEntry<YourNpcEntry> &exec)
	{
		rwlock.rdlock();
		bool ret = execEveryEntry<>(exec);
		rwlock.unlock();
		return ret;
	}

	/**
	* \brief 删除符合条件的npc
	*
	* \param pred 判断条件
	*/
	template <class YourNpcEntry>
	void removeNpc_if(removeEntry_Pred<YourNpcEntry> &pred)
	{
		rwlock.wrlock();
		removeEntry_if<>(pred);
		rwlock.unlock();
	}

	/**
	* \brief 删除一场景内的npc
	*
	*
	* \param scene 场景
	*/
	void removeNpcInOneScene(Scene *scene);
	void SpecialAI();
	/**
	* \brief 对每个特殊npc执行回吊调函数
	*
	*
	* \param callback 回调函数
	* \return
	*/
	void execAllSpecialNpc(specialNpcCallBack &callback)
	{
		rwlock.wrlock();
		for (MonkeyNpcs::iterator it = specialNpc.begin(); it != specialNpc.end(); it++)
		{
			if (!callback.exec(*it))
			{
				rwlock.unlock();
				return;
			}
		}
		rwlock.unlock();
	}

	MonkeyNpcs &getSepcialNpc()
	{
		return specialNpc;
	}
	bool getNpcCommonChat(DWORD type, char * content);
	void removeSpecialNpc(SceneNpc *);
	void closeFunctionNpc();
private:
	///specialNpc是指即使没有玩家在附近也要做处理的NPC
	///包括宠物、boss、任务NPC
	MonkeyNpcs specialNpc;

	SceneNpcManager();
	~SceneNpcManager();

	///SceneNpcManager的唯一实例
	static SceneNpcManager *snm;
	///读写锁
	zRWLock rwlock;

	bool getUniqeID(QWORD &tempid) { return true; }
	void putUniqeID(const QWORD &tempid) {}

	///npc随机说话的内容
	std::map<DWORD, std::vector<std::string> > NpcCommonChatTable;
	///npc随机说话的概率
	std::map<DWORD, int> NpcCommonChatRate;

	bool loadNpcCommonChatTable();
};

//sky 动态地图配置类
class stRangMap
{
private:
	WORD Countryid;	//sky 战场国家ID
	WORD BaseID;		//sky 原ID(根据这个来寻找地图的基本配置)
	WORD MinID;			//sky 该场景动态可分配的最小ID
	WORD MaxID;			//sky 该场景动态可分配的最大ID
	zUniqueDWORDID * MapIDManager;	//sky 唯一ID分配器

public:
	stRangMap()
	{
		Countryid = 0;
		BaseID = 0;
		MinID = 0;
		MaxID = 0;
		MapIDManager = NULL;
	}

	~stRangMap()
	{
		if (MapIDManager)
			delete MapIDManager;
	}

	void init(WORD countryid, WORD baseid, WORD minid, WORD maxid)
	{
		Countryid = countryid;
		BaseID = baseid;
		MinID = minid;
		MaxID = maxid;
		MapIDManager = new zUniqueDWORDID(minid, maxid);
	}

	WORD GetCountryid()
	{
		return Countryid;
	}

	/**
	* \brief 生成一个唯一ID
	*/
	bool getUniqeID(QWORD &tempid)
	{
		tempid = MapIDManager->get();
		return (tempid != MapIDManager->invalid());
	}

	/**
	* \brief 释放唯一ID
	*/
	void putUniqeID(const QWORD &tempid)
	{
		MapIDManager->put(tempid);
	}
};

//sky 动态地图配置容器
extern std::map<WORD, stRangMap*> RangMapData;


// 格子上道具定义 
struct zItemEntry :public zEntry
{
public:
	// id=唯一ID也是位置下标(0开始)
	DWORD itemID;
	DWORD itemNum;
};

/*
 * 物品管理器 	
 */
class zItemManager : public zEntryMgr< zEntryID, zEntryTempID >
{
protected:

	zRWLock rwlock;

	zItemEntry* getItemEntryByID(DWORD id)
	{
		rwlock.rdlock();
		zItemEntry *ret = (zItemEntry *)getEntryByID(id);
		rwlock.unlock();
		return ret;
	}

	zItemEntry* getItemEntryByTempID(DWORD tempid)
	{
		rwlock.rdlock();
		zItemEntry *ret = (zItemEntry *)getEntryByTempID(tempid);
		rwlock.unlock();
		return ret;
	}

	bool addItem(zItemEntry *user)
	{
		rwlock.wrlock();
		bool ret = addEntry((zEntry *)user);
		rwlock.unlock();
		return ret;
	}

	void removeItem(zItemEntry *user)
	{
		rwlock.wrlock();
		removeEntry((zEntry *)user);
		rwlock.unlock();
	}

	template <class YourItemEntry>
	void removeItem_if(removeEntry_Pred<YourItemEntry> &pred)
	{
		rwlock.wrlock();
		removeEntry_if<>(pred);
		rwlock.unlock();
	}

	template <class YourItemEntry>
	bool execEveryItemEntry(execEntry<YourItemEntry> &exec)
	{
		rwlock.rdlock();
		bool ret = execEveryEntry<>(exec);
		rwlock.unlock();
		return ret;
	}

public:

	zItemManager()
	{

	}

	~zItemManager()
	{
		clear();
	}
};


struct zSkill;
using namespace SkillDef;
class ScenePk
{
public:
	static bool physicalMagicU2U(const Cmd::stAttackMagicUserCmd *rev, SceneUser *pAtt, SceneUser *pDef);
	static bool attackDeathUser(SceneUser *pAtt, SceneUser *pDef);
	static bool sendChangedUserData(SceneUser *pUser);
	static bool attackDeathNpc(SceneEntryPk *pAtt, SceneNpc *pDef);
	static bool attackFailToMe(const Cmd::stAttackMagicUserCmd *rev, SceneEntryPk * pAtt, bool failed = true, bool me = false);
	static void  checkProtect(SceneEntryPk *pAtt, SceneEntryPk *pDef);
	static bool attackUserCmdToNine(const Cmd::stAttackMagicUserCmd *rev, SceneEntryPk *pAtt);
	static void attackRTHpAndMp(SceneUser *pUser);
	static void attackRTExp(SceneUser *pUser, DWORD exp, DWORD dwTempID = 0, BYTE byType = 0);
	static bool attackRTCmdToNine(const Cmd::stAttackMagicUserCmd *rev, SceneEntryPk *pAtt, SceneEntryPk *pDef, const SDWORD sdwHP, BYTE byLuck);
	static bool checkAttackSpeed(SceneUser *pAtt, const Cmd::stAttackMagicUserCmd *rev);
	static void  calpdamU2U(const Cmd::stAttackMagicUserCmd *rev, SceneUser *pAtt, SceneUser *pDef);
	static void  calpdamU2N(const Cmd::stAttackMagicUserCmd *rev, SceneUser *pAtt, SceneNpc *pDef);
	static void  calmdamU2U(const Cmd::stAttackMagicUserCmd *rev, SceneUser *pAtt, SceneUser *pDef);
	static void calmdamU2N(const Cmd::stAttackMagicUserCmd *rev, SceneUser *pAtt, SceneNpc *pDef);
	static void calpdamN2U(const Cmd::stAttackMagicUserCmd *rev, SceneNpc *pAtt, SceneUser *pDef);
	static void calmdamN2U(const Cmd::stAttackMagicUserCmd *rev, SceneNpc *pAtt, SceneUser *pDef);
	static void calpdamN2N(const Cmd::stAttackMagicUserCmd *rev, SceneNpc *pAtt, SceneNpc *pDef);
	static void calmdamN2N(const Cmd::stAttackMagicUserCmd *rev, SceneNpc *pAtt, SceneNpc *pDef);
};

/// 技能善恶类型枚举
enum {
	SKILL_GOOD = 0,
	SKILL_BAD = 1
};

/// 技能状态类型枚举
enum {
	SKILL_TYPE_INITIAVITE = 1,// 攻击技能
	SKILL_TYPE_RECOVERY = 2,  // 临时被动技能
	SKILL_TYPE_PASSIVENESS = 3  // 永久被动技能
};

/// 技能状态处理返回值枚举
enum {
	SKILL_ACTIVE = 1,//  加到活动MAP中
	SKILL_RECOVERY,    //  加到临时被动MAP中
	SKILL_PASSIVENESS,  //  加到永久被动MAP中
	SKILL_RETURN,    //  不加到任何MAP中
	SKILL_BREAK,    //  不继续投放操作
};

/// 技能状态执行步骤枚举
enum {
	ACTION_STEP_DOPASS = 0,// 一个技能状态的开始步骤
	ACTION_STEP_START = 1,// 一个技能状态的开始步骤
	ACTION_STEP_TIMER,  // 一个技能状态的定时步骤
	ACTION_STEP_STOP,  // 一个技能状态的停止步骤
	ACTION_STEP_CLEAR,  // 一个技能状态被外部清除
	ACTION_STEP_RELOAD,    // 一个技能状态被重新载入
};

/// 技能状态最大数目定义
#define SKILLSTATENUMBER 354   /// 技能状态最大编号 [sky]扩充到400

/**
* \brief  技能状态元素载体
*/
struct SkillStatusCarrier
{
	/// 技能操作
	const SkillStatus *status;
	/// 技能字典
	const zSkillB *skillbase;
	/// 收到的攻击消息
	Cmd::stAttackMagicUserCmd revCmd;
	/// 攻击者的指针
	SceneEntryPk *attacker;
	/**
	* \brief  构造函数，初始化所有属性
	*/
	SkillStatusCarrier()
	{
		status = NULL;
		skillbase = NULL;
		attacker = NULL;
	}
};

/**
* \brief  技能状态元素
*/
struct SkillStatusElement
{
	/// 状态的 id
	DWORD  id;

	/// 状态发生几率
	DWORD percent;

	/// 状态的影响数值(sky 召唤:怪物ID现在已经超过65535)
	DWORD value;

	/// 状态的持续时间
	QWORD qwTime;

	/// 状态执行的步骤标志
	DWORD state;


	///攻击者的临时ID;
	DWORD dwTempID;

	///攻击者的ID
	DWORD dwAttackerID;

	///技能ID
	DWORD dwSkillID;

	///执行时长
	DWORD dwTime;

	///执行步骤
	BYTE  byStep;

	///善恶类型
	BYTE  byGoodnessType;

	///技能的互斥大类
	BYTE  byMutexType;

	///是否刷新人物属性1为刷新0为否
	BYTE  refresh;

	///攻击者的类型
	zSceneEntry::SceneEntryType attacktype;

	/**
	* \brief  技能状态元素构造函数初始化所有属性
	*/
	SkillStatusElement()
	{
		id = 0;          //状态的id;
		percent = 0;
		value = 0;
		qwTime = 0;
		state = 0;
		dwTempID = 0;
		dwSkillID = 0;
		dwTime = 0;
		byStep = 0;
		refresh = 0;
	}
};

/**
* \brief  技能状态管理器
*/
class SkillStatusManager
{
private:
	/// 主动技能状态列表
	std::map<DWORD, SkillStatusElement> _activeElement;

	/// 临时被动技能状态列表
	std::map<DWORD, SkillStatusElement> _recoveryElement;

	/// 永久被动技能状态列表
	std::map<DWORD, SkillStatusElement> _passivenessElement;

	/// 类型定义
	typedef std::map<DWORD, SkillStatusElement>::value_type VALUE_TYPE;

	/**
	* \brief  技能状态函数列表
	*/
	struct {
		BYTE(*func)(SceneEntryPk *, SkillStatusElement &);
	}funlist[SKILLSTATENUMBER + 1];

	/// 技能状态管理器属主
	SceneEntryPk *entry;
	bool bclearActiveSkillStatus;

public:
	SkillStatusManager();
	~SkillStatusManager();
	void initMe(SceneEntryPk *pEntry);
	void loadSkillStatus(char *buf, DWORD length);
	void getSelectStates(Cmd::stSelectReturnStatesPropertyUserCmd *buf, unsigned long maxSize);
	void sendSelectStates(SceneEntryPk *pThis, DWORD state, WORD value, WORD time);
	void saveSkillStatus(char *buf, DWORD &size);
	bool putOperationToMe(const SkillStatusCarrier &carrier, const bool good = false, SWORD rangDamageBonus = 0);
	void putPassivenessOperationToMe(const DWORD skillid, const SkillStatus *pSkillStatus);
	void processPassiveness();
	inline BYTE runStatusElement(SkillStatusElement &element);
	void timer();
	void clearActiveSkillStatus();
	void clearActiveSkillStatusOnlyUseToStatus48();
	void clearBadActiveSkillStatus();
	void addBadSkillStatusPersistTime(const DWORD &value);
	void addBadSkillStatusPersistTimePercent(const DWORD &value);
	void clearMapElement(const BYTE &byMutexType, std::map<DWORD, SkillStatusElement> &myMap, DWORD dwID, bool notify = true);
	WORD getSaveStatusSize();
	void clearRecoveryElement(DWORD value);
	void clearActiveElement(DWORD value);
	void processDeath();
	void clearSkill(DWORD dwSkillID);

	//[test]-----------------------------------------------------------------
	void showValue();
	void showValueToLog();
	void showActive();
	void showRecovery();
	void showPassiveness();
	//-----------------------------------------------------------------------

	//sky 新增 begin
	void SetStatuToRecovery(DWORD id, DWORD time, DWORD percent, DWORD value = 0, DWORD state = 0);
	//sky end
};

//sky 新增技能特殊属性枚举
enum
{
	SPEC_NULL = 0,	//sky 空	
	SPEC_MAGIC = 1,	//sky 魔法类
	SPEC_PHYSICS = 2,	//sky 物理类
	SPEC_IMMUNE = 4,	//sky 可免疫
	SPEC_REBOUND = 8,	//sky 可被反弹
	SPEC_TREATMENT = 16,	//sky 治疗
	SPEC_BUFF = 32,	//sky 有益BUFF
	SPEC_DEBUFF = 64,	//sky 减益BUFF
	SPEC_DRUG = 128,	//sky 毒
	SPEC_OTHER = 256,	//sky 其他
};

/**
* \brief 技能类,定义技能的基本特性及攻击执行方法
*/
struct zSkill : zEntry
{
	static const DWORD maxUniqueID = 100000;
public:
	t_Skill data;
	const zSkillB *base;
	const zSkillB *actionbase;

	static zSkill *create(SceneEntryPk *pEntry, DWORD id, DWORD level);
	static zSkill *createTempSkill(SceneEntryPk *pEntry, DWORD id, DWORD level);
	static zSkill *load(SceneEntryPk *pEntry, const SaveSkill *s);
	bool canUpgrade(SceneEntryPk *pEntry);
	bool setupSkillBase(SceneEntryPk *pEntry);
	bool getSaveData(SaveSkill *save);
	bool canUse();
	bool checkSkillBook(bool nextbase = false);
	bool checkSkillStudy(bool nextbase = false);
	void resetUseTime();
	void clearUseTime();
	void refresh(bool ignoredirty = false);

	//sky 新增技能特殊属性检测函数
	bool IsMagicSkill();	//sky 检测技能是否是魔法系技能
	bool IsPhysicsSkill();	//sky 检测技能是否是物理系技能
	bool IsImmuneSkill();	//sky 检测技能是否能被免疫
	bool IsReboundSkill();	//sky 检测技能是否能被反射
	bool IsTreatmentSkill();//sky 检测技能是否是治疗系
	bool IsBuffSkill();		//sky 检测技能是否是增益BUFF系
	bool IsDeBuffSkill();	//sky 检测技能是否是减益BUFF系
	bool IsDrugSkill();		//sky 检测技能是否是毒系
	bool IsOtherSkill();	//sky 检测技能是否是其他系

	~zSkill();
	QWORD lastUseTime;
private:
	bool dirty;
	bool istemp;
	bool needSave;
	bool inserted;
	SceneEntryPk *_entry;
	const Cmd::stAttackMagicUserCmd *curRevCmd;
	DWORD curRevCmdLen;
	zSkill();

	//static DWORD uniqueID;

	// 新增加的技能方法
public:
	bool action(const Cmd::stAttackMagicUserCmd *rev, const DWORD cmdLen);
	inline void doOperation(const SkillStatus *pSkillStatus);
	inline void doPassivenessSkill();
	inline bool showMagicToAll();
	inline bool findAttackTarget(const SkillStatus *pSkillStatus, zPos &pd, DWORD &count, SWORD rangDamageBonus = 0);
	inline const zSkillB *getNewBase();
};

/**
* \brief  回调基类
*/
class UserSkillExec
{
public:
	virtual bool exec(zSkill *s) = 0;
};


/**
* \brief  技能管理器基类
*/
class UserSkillM : private zEntryMgr < zEntryID, zEntryTempID >
{
public:
	UserSkillM(SceneUser* u);
	~UserSkillM();
	bool getUniqeID(QWORD &tempid);
	void putUniqeID(const QWORD &tempid);
	zSkill *getSkillByTempID(DWORD id);
	void removeSkillByTempID(DWORD id);
	void removeSkill(zSkill *s);
	bool addSkill(zSkill *s);
	zSkill *findSkill(DWORD skillid);
	void execEvery(UserSkillExec &exec);
	void resetAllUseTime();
	void clearAllUseTime(DWORD skillID = 0);
	void clear();
	DWORD getPointInTree(DWORD mySubkind);
	void refresh();
	int size() const;
	void clearskill(DWORD skillid);
public:
	SceneUser* pOwner;

};


//技能影响的状态数据
struct SkillState
{
	SkillState();
	void init();
	union
	{
		struct
		{
			SWORD dvalue;    //伤害值增加固定数值1
			SWORD dvaluep;    //伤害值增加x%2
			SWORD pdefence;    //物理防御数值变更 57，86
			SWORD pdefencep;  //物理防御变更百分比
			SWORD updam;    //物理攻击增加固定数值
			SWORD updamp;    //物理攻击增加百分比
			SWORD umdam;    //法术攻击增加固定数值
			SWORD umdamp;    //法术攻击增加百分比
			SWORD dpdam;    //物理攻击减少固定数值
			SWORD dpdamp;    //物理攻击减少百分比
			SWORD dmdam;    //法术攻击减少固定数值
			SWORD dmdamp;    //法术攻击减少百分比
			SWORD updef;    //物理防御增加固定数值
			SWORD updefp;    //物理防御增加百分比
			SWORD umdef;    //法术防御增加固定数值
			SWORD umdefp;    //法术防御增加百分比
			SWORD dpdef;    //物理防御减少固定数值
			SWORD dpdefp;    //物理防御减少百分比
			SWORD dmdef;    //法术防御减少固定数值
			SWORD dmdefp;    //法术防御减少百分比
			SWORD topet;    //变为随机小动物79
			SWORD appenddam;  //产生额外伤害83
			SWORD movespeed;  //移动速度变更百分比 16，56
			SWORD mgspeed;    //减少技能施放间隔17
			SWORD coldp;    //减少陷入冰冻状态几率18
			SWORD poisonp;    //减少陷入中毒状态几率19
			SWORD petrifyp;    //减少陷入石化状态几率20
			SWORD blindp;    //减少陷入失明状态几率21
			SWORD chaosp;    //减少陷入混乱状态几率22
			SWORD atrating;    //命中率增加33,64
			SWORD reduce_atrating;  // 命中率减少 ZJW加入
			SWORD hpspeedup;  //生命值恢复速度增加34
			SWORD mpspeedup;  //法术值恢复速度增加35
			SWORD spspeedup;  //体力值恢复速度增加36
			SWORD akdodge;    //闪避率上升37
			SWORD reduce_akdodge;  // 闪避率下降
			SWORD mdefence;    //法术防御变更59，             // 40
			SWORD mdefencep;  //法术防御变更百分比x%
			SWORD uattackspeed;  //攻击速度提高白分比
			SWORD dattackspeed;  //攻击速度降低白分比
			SWORD sevendownp;  //降低陷入七大状态几率82
			SWORD tsfdamp;    //伤害转移百分比
			SWORD tsfdam;    //伤害转移数值
			SWORD passdam;    //被动：额外伤害117
			SWORD maxhp;       //生命值最大值变更
			SWORD maxmp;       //法术值最大值变更
			SWORD maxsp;       //体力值最大值变更
			SWORD pupdam;    //物理攻击增加固定数值（被动）
			SWORD pumdam;    //法术攻击增加固定数值（被动）
			SWORD pupdef;    //物理防御增加固定数值（被动）
			SWORD pumdef;    //法术防御增加固定数值（被动）
			SWORD supdam;    //弓箭类增加物理攻击力固定值(长效)
			SWORD spupdam;    //弓箭类增加物理攻击力固定值(被动)
			SWORD spupdamp;    //弓箭类增加物理攻击力百分比(被动)
			SWORD rpupdam;    //棍子类增加物理攻击力固定值(被动)
			SWORD lupdam;    //长效物理攻击力增强固定值
			SWORD satrating;  //弓箭类提升命中率
			SWORD patrating;   // 增加命中率（被动）
			SWORD pattackspeed;  //增加攻击速度（被动）
			SWORD upattribute;  //属性点增加
			SWORD tuling;      //土灵增强
			SWORD kulou;    //骷髅弓手增强
			SWORD tianbing;    //天兵增强
			SWORD weaponupdamp; //提升武器物理攻击力百分比
			SWORD weaponumdamp; //提升武器法术攻击力百分比
			SWORD uppetdamage; //提升召唤兽的攻击力
			SWORD uppetdefence; //提升召唤兽的防御力
			SWORD pmaxhp;    //被动提升生命最大值
			SWORD bang;      //增加人物施放出重击的几率
			SWORD theurgy_updam; //仙术增加物理攻击力
			SWORD theurgy_updamp; //仙术增加物理攻击力百分比
			SWORD theurgy_updef; //仙术增加物理防御力
			SWORD theurgy_umdefp; //仙术增加法术防御力百分比
			SWORD theurgy_umdef; //仙术增加法术防御力
			SWORD theurgy_umdam; //仙术增加法术攻击力
			SWORD theurgy_umdamp; //仙术增加法术攻击力百分比
			SWORD theurgy_updefp;//仙术增加物理防御力百分比
			SWORD theurgy_dpdef; //仙术降低物理防御力
			SWORD theurgy_dmdef; //仙术降低物理防御力
			SWORD theurgy_dpdam;    //物理攻击减少固定数值
			SWORD theurgy_dmdam;    //法术攻击减少固定数值
			SWORD hpupbylevel; //根据人物等级提升最大血量                    //80
			SWORD reflect_ardor; // 反弹灼热状态给攻击自己的敌人
			SWORD reflect_poison; //反弹中毒状态给攻击自己的敌人
			SWORD reflect_lull;  // 反弹麻痹状态给攻击自己的敌人
			SWORD reflect_frost; // 反弹冰冻状态给攻击自己的敌人
			WORD introject_maxmdam; // 召唤合体增加魔法攻击
			WORD introject_maxpdam; // 召唤合体增加物理攻击
			WORD introject_mdam; // 召唤合体增加魔法攻击
			WORD introject_pdam; // 召唤合体增加物理攻击
			WORD introject_mdef; // 召唤合体增加魔法防御
			WORD introject_pdef; // 召唤合体增加物理防御
			WORD introject_maxhp; // 召唤合体增加生命上限
			SWORD summonrelive; // 召唤兽重生
			SWORD pdamtodef;  // 物攻转物防
			SWORD mdamtodef;  // 魔攻转魔防
			SWORD pdeftodam;  // 物防转物攻
			SWORD mdeftodam;  // 魔防转魔攻
			SWORD sept_updamp;  // 提升物理攻击百分比
			SWORD sept_umdamp;  // 提升魔法攻击百分比
			SWORD sept_updefp;  // 提升物理防御百分比
			SWORD sept_umdefp;  // 提升法术防御百分比
			SWORD sept_maxhp;  // 提升生命最大值百分比
			SWORD sept_maxmp;  // 提升法术最大值百分比
			SWORD blazeappend; // 火焰系法术伤害提升比例千分之几
			SWORD pblazeappend; // 火焰系法术伤害提升比例千分之几
			SWORD levinappend; // 雷电系法术伤害提升比例千分之几
			SWORD plevinappend; // 雷电系法术伤害提升比例千分之几(被动)
			SWORD trapappend;  // 陷阱系法术伤害提升比例千分之几
			SWORD iceappend;  // 陷阱系法术伤害提升比例千分之几
			SWORD udef;      // 防御提升固定值（物理和法术都升）
			SWORD magicattack;  // 两仪心法，攻击的时候附带法术伤害
			SWORD array_udamp; // 阵法的双攻比率提升
			SWORD array_ddefp; // 阵法的双防比率降低
			SWORD array_dmvspeed; // 阵法的移动速度降低
			SWORD upcon; //提升体质
			SWORD upint; //提升智力
			SWORD updex; //提升敏捷
			SWORD sword_udam; //提升弓箭攻击的伤害点数   // 110
			SWORD attackaddhpnum; // 攻击增加自己生命值数目
			SWORD dodge;         // 有一定几率闪避敌人攻击
			SWORD reflect_icelull; // 反弹一个麻痹状态 冰雷盾用
			SWORD pumdamp;    //被动提升法术攻击力百分比
			SWORD addmenp;   // 增加精神百分比
			SWORD ice_umdefp; //冰甲用提升魔法防御百分比
			SWORD protectdam; //保护状态之伤害
			SWORD protectUpAtt; //保护状态之攻击翻倍
			SWORD unitarybattle; //一元阵法投送小技能到队长正在攻击的敌人身上，此为投送的技能ID
			SWORD teamappend; //组队攻击加成，变量里存放的是组队队长的ID
			SWORD nsc_updamp; //逆手刺的专用技能提升状态。
			SWORD tgyt_updefp; //铁骨御体专用技能提升状态
			SWORD tgzh_updef; //铁骨之魂专用技能提升状态
			SWORD lm_updamp;   // 鲁莽提升物理攻击力百分比
			SWORD upallattrib; // 提升所有属性数值
			SWORD dnallattrib; // 所有属性降低数值
			SWORD upstr;      // 提升力量属性百分比
			SWORD dpallattrib; // 所有属性下降百分比
			SWORD upattribstr; // 提升力量属性百分比
			SWORD upattribcon; // 提升体质属性百分比
			SWORD upattribmen; // 提升精神属性百分比
			SWORD upattribdex; // 提升敏捷属性百分比
			SWORD upattribint; // 提升智力属性百分比
			SWORD relive;    // 再生
			SWORD nowrelive; // 立即复活时回复百分比
			SWORD brappenddam; //猎手印记所提供的额外伤害清
			SWORD dpintmen;   // 智力精神降低百分比
			SWORD dpstrdex;   // 力量敏捷降低百分比
			SWORD enervation; // 衰弱
			SWORD erupt;      // 破釜沉舟状态 魔物攻击翻300%持续时间完后会获得复活虚弱状态

							  //sky 新增技能效果
			SWORD AttAddDam;		//sky 增加伤害百分比
			SWORD reflect;		//sky 反弹伤害固定值
			SWORD reflectp;		//sky 反弹物理攻击伤害百分比
			SWORD reflect2;		//sky 反弹魔法攻击伤害百分比
			SWORD MagicReflex;	//sky 魔法系技能反射(直接把技能反射回去)
			SWORD PhyReflex;		//sky 物理反射百分比
			SWORD DaggerAddDam;	//sky 增加匕首伤害百分比
			SWORD ThroAddDam;		//sky 增加投掷武器伤害百分比
			SWORD HandsAddDam;	//sky 增加双手武器伤害百分比
			SWORD HandAddDam;		//sky 增加单手武器伤害百分比
			SWORD FlameAddDam;	//sky 增加火焰魔法伤害百分比
			SWORD IceAddDam;		//sky 增加冰霜魔法伤害百分比
			SWORD SacredAddDam;	//sky 增加神圣魔法伤害百分比
			SWORD DarkAddDam;		//sky 增加黑暗魔法伤害百分比

			SWORD DaggerAddDamA;	//sky 增加匕首伤害固定值
			SWORD ThroAddDamA;	//sky 增加投掷武器伤害固定值
			SWORD HandsAddDamA;	//sky 增加双手武器伤害固定值
			SWORD HandAddDamA;	//sky 增加单手武器伤害固定值
			SWORD FlameAddDamA;	//sky 增加火焰魔法伤害固定值
			SWORD IceAddDamA;		//sky 增加冰霜魔法伤害固定值
			SWORD SacredAddDamA;	//sky 增加神圣魔法伤害固定值
			SWORD DarkAddDamA;	//sky 增加黑暗魔法伤害固定值
		};
		SWORD swdValue[171];
	};
};

/**
* \brief 频道类型 
*
*/
enum ChannelType
{
	CHANNEL_TYPE_WORLD = 1,
};


/**
* \brief 聊天频道
*
*/
class Channel :public zEntry
{
private:
	std::vector< zEntryC > userlist;
	zEntry creater;
public:
	Channel(SceneUser *pUser);
	Channel(DWORD chID,const std::string& _name);
	~Channel();

	static bool sendNine(SceneUser *pUser, const NetMsgSS *cmd, DWORD len);
	static bool sendNine(const SceneNpc *pNpc, const char *pattern, ...);
	static bool sendPrivate(SceneUser *pUser, const NetMsgSS *cmd, DWORD len);
	static bool sendTeam(DWORD teamid, const NetMsgSS *cmd, DWORD len);
	static bool sendCountry(SceneUser *pUser, const NetMsgSS *cmd, DWORD len);
	
	static bool sendCmdToMap(DWORD mapID, const NetMsgSS *cmd, int len);
	static bool sendCmdToMap(Scene* scene, const NetMsgSS *cmd, int len);
	static bool sendSys(SceneUser *pUser, int type, const char *pattern, ...);
	static bool sendSys(DWORD dwUserTempID, int type, const char *pattern, ...);
	static bool sendCountry(SceneUser *pUser, const char *pattern, ...);
	static bool sendCountryInfo(DWORD countryID, DWORD infoType, const char *pattern, ...);
	static bool sendAllInfo(DWORD infoType, const char *pattern, ...);
	
	bool sendCmdToAll(const NetMsgSS *cmd,int len);

	bool remove(const char *name);
	bool add(SceneUser *pUser);
	WORD has(const char *name);
	
};

/**
* \brief 频道管理器
*
*/
class ChannelM : public zEntryMgr< zEntryID, zEntryTempID ,zEntryName >
{
private:
	zUniqueDWORDID *channelUniqeID;
	zMutex mlock;
	zObjPool<Channel> objpool;

	bool getUniqeID(QWORD &tempid);
	void putUniqeID(const QWORD &tempid);
	
public:
	ChannelM();
	~ChannelM();
	bool add(Channel *channel);
	void remove(DWORD dwChannelID);
	Channel* get(DWORD dwChannelID);
	void removeUser(const char *name);
	Channel* CreateObj(SceneUser *pUser);
	Channel* CreateObj(DWORD chID, const std::string& _name);
	void DestroyObj(Channel* obj);

};

/// 超级GM的id,只有1个超级GM
#define SUPER_GM_ID 1

struct Gm
{
	enum
	{
		none_mode = 0x00,
		normal_mode = 0x01,
		gm_mode = 0x02,
		captain_mode = 0x04,
		super_mode = 0x08,
		debug_mode = 0x10,
		all_mode = 0x1f,/// all_mode
						//admin_mode =   0x10,
						//magic_mode =   0x20
	};

	const char *cmd;
	bool(*parse)(SceneUser *pUser, const char *para);
	BYTE priv;
	const char *desc;

	static void sendLog(SceneUser *pUser, const char *cmd, const char * content);

	static void exec(SceneUser *pUser, char *cmd);
	static bool fetch(SceneUser *pUser, const char *para);
	static bool getgive(SceneUser *pUser, const char *para);
	static bool summon(SceneUser *pUser, const char *para);
	static bool help(SceneUser *pUser, const char *para);
	static bool levelup(SceneUser *pUser, const char *para);
	static bool goTo(SceneUser *pUser, const char *para);
	static bool goTo_Gm(SceneUser *pUser, const char *para);
	static bool gomap(SceneUser *pUser, const char *para);
	static bool gomap_Gm(SceneUser *pUser, const char *para);

};


#endif
