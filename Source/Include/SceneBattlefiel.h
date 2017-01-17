//////////////////////////////////////////////////////////////////////////
/////////	sky 战场相关类定义
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <zebra/ScenesServer.h>

#define MAX_GAMEPOINT	1000000
#define MAX_CAMPREG		50000

//sky 胜利类型枚举
enum eVictoryType
{
	BATTLEFIELF_WINNT_NULL			= 0,	//NULL
	BATTLEFIELF_WINNT_KILLUSERNUM	= 1,	//杀够对方阵营成员特定数量胜利
	BATTLEFIELF_WINNT_KILLALLUSER	= 2,	//杀死全部对方阵营成员胜利
	BATTLEFIELF_WINNT_WRECKBASE		= 3,	//摧毁对方阵营的基地
	BATTLEFIELF_WINNT_WATCH_NPCATT	= 4,	//坚持完特定NPC攻击,基地没被摧毁就算胜利
	BATTLEFIELF_WINNT_REGNAMMAX		= 5,	//资源最先达标的阵营胜利
	//sky 以持续时间为前提的胜利条件
	BATTLEFIELF_WINNT_TIME_GETGO	= 16,	//坚持到时间结束
	BATTLEFIELF_WINNT_TIME_KILLUSERMUCH	= 17,	//时间结束时候杀死用户最多的阵营胜利
	BATTLEFIELF_WINNT_TIME_KILLNPCMUCH	= 18,	//时间结束时候杀死NPC最多的阵营胜利
};

//sky 奖励类型枚举
enum eRewardType
{
	REWARD_NULL		= 0,	//sky 空
	REWARD_MONEY	= 1,	//sky 金钱
	REWARD_ITEM		= 2,	//sky 道具
	REWARD_HONOR	= 3,	//sky 荣誉
};

enum enReliveType
{
	Compulsory_Resurrection = 0,
	NpcSkill_Resurrection	= 1,
	Notallowed_Resurrection	= 2,
};

//sky 奖励惩罚结构
struct stBattleReward
{
	stBattleReward()
	{
		RewardType = REWARD_NULL;
		RewardData1 = 0;
		RewardData2 = 0;
	}

	eRewardType	RewardType;	//类型
	DWORD	RewardData1; //补充1
	DWORD	RewardData2; //补充2
};

//sky 阵营成员数据结构
struct  stCampMember
{
	stCampMember()
	{
		userid = 0;
		GamePoint = 0;
		DeathTime = -1;
	}
	DWORD userid;		//sky 成员唯一ID
	int DeathTime;	//sky 死亡时间
	DWORD GamePoint;	//sky 战场点数(战场专用货币)
};

//sky 阵营数据结构
struct BCampData
{
	BCampData()
	{
		CampID = 0;
		Teamnum = 0;
		CampMembe.clear();
		KillUserNum = 0;
		KillNpcNum = 0;
		GetReg = 0;
		SoulUserNum = 0;
		CampPos.x = 0;
		CampPos.y = 0;
	}

	DWORD CampID;
	//sky 阵营成员数
	WORD Teamnum;
	//sky 阵营成员数据
	std::vector<stCampMember> CampMembe;
	//sky 杀死对方阵营成员数量
	DWORD KillUserNum;
	//sky 杀死对方阵营NPC数量
	DWORD KillNpcNum;
	//sky 自己阵营中处于灵魂状态的成员数
	WORD SoulUserNum;
	//sky 获取资源数
	DWORD GetReg;
	//sky 复活点和起始传送点
	zPos CampPos;
};

/**
* \brief sky 战场场景
*
*/
class GangScene:public Scene
{
private:
	//==== sky 战场场景外部配置数据 ====
	//sky 阵营数量
	WORD CampNum;
	//sky 阵营最大成员数
	WORD CampUserNum;
	//sky 阵营关系阵营关系(0:对抗(可以杀死对方阵营) 1:对抗(不可以杀死对方阵营) 2:合作)
	WORD CampRel;
	//sky 胜利条件类型
	eVictoryType VictoryType;
	//sky 胜利条件的补充数值
	DWORD VictoryData;
	//sky 胜利者奖励
	std::vector<stBattleReward> Victory;
	//sky 失败者奖励
	std::vector<stBattleReward> failure;
	//sky 失败者处罚
	std::vector<stBattleReward> penalty;
	//sky 奖励处罚标准(保证奖励不管什么情况都只会发生一次)
	bool bVictory;
	bool bfailure;
	bool bpenalty;
	
	//sky 击杀敌对阵营用户奖励战场点数
	DWORD KillPoint;
	//sky 复活类型
	BYTE reliveType;
	//sku 复活倒计时
	WORD reliveTime;
	//sky 杀死对方阵营成员奖励点数
	DWORD killPoint;

	//**** sky 可选配置 ****
	//sky 战场最大持续时间(分钟)
	DWORD GameTime;
	//sky 时间到后的判断的默认胜负条件
	eVictoryType defaultvictory;
	//**** sky 可选end ****
	//==== sky 战场场景外部配置数据 end ====
private:
	//==== sky 战场场景逻辑用变量 ====
	//sky 战场开始标志(1:开始 0:未开始 2:倒计时阶段 3:结束)
	BYTE GameStart;
	//sky 战场等待倒计时(从进入第一个玩家开始计时:秒)
	WORD StartTime;
	//sky 战场关闭倒计时
	WORD OverTime;
	//sky 战场已经经过的时间(分钟)
	DWORD passTime;
	//sky 阵营用户数据<阵营ID 阵营数据>
	std::map<DWORD ,BCampData* > camp;
	//sky 胜利阵营ID
	DWORD WinnerCamp;
	//sky 分钟定时器
	Timer _one_min;
	//==== sky 战场场景逻辑用变量 end ====
public:
	//sky 阵营ID容器
	std::map<BYTE, DWORD> CampThisID;
	//sky 阵营ID分配函数
	DWORD ReCampThisID(BYTE index);
	//sky 阵营起始传送坐标点
	std::vector<zPos> CampPos;
	//==== sky 逻辑函数 ====
	//sky 初始化配置数据
	void InitData();
	//sky 接受阵营成员并放到初始pos上
	bool AddUserToScene(DWORD UserID, const zPos & initPos);
	//sky 获取特定阵营的杀死敌对玩家数
	DWORD GetCampKillUserNum(DWORD index);
	//sky 获取特定阵营杀死敌对NPC的数量
	DWORD GetCampKillNpcNum(DWORD index);
	//sky 获取特定阵营获取资源的数量
	DWORD GetCampRegNum(DWORD index);
	//sky 增加阵营的资源
	bool AddCampReg(DWORD campID, int RegNum);
	//sky 减少阵营的资源
	bool DesCampReg(DWORD campID, int RegNum);
	//sky 获取战场已经经过的时候
	DWORD GetPassTime();
	//sky 胜负判断
	bool GetCampVictory();
	//sky 发送胜利阵营奖励
	bool largessWinVictory();
	//sky 发送失败阵营奖励
	bool largessFailureVictory();
	//sky 失败阵营惩罚
	bool givepenalty();
	//sky 增加成员战场点
	bool AddUserCamePoint(DWORD userid, DWORD point);
	//sky 减少成员战场点
	bool DesUserCampPoint(DWORD userid,	DWORD point);
	//sky 批量检处理用户复活
	bool reliveRun();
	//sky 特殊处理一个用户的死亡事件
	bool UserDeathRun(DWORD DeathID, DWORD MurderID);
	//sky 返回战场是开始状态
	BYTE GetGameStart() { return GameStart; }

	//**** sky 胜负处理函数 ****
	//sky 是否杀够其他阵营成员特定数量胜利检测(有人死亡的时候就检测凶手的阵营的杀人数)
	DWORD IfKillUserNum(DWORD CampID);
	//sky 杀死全部对方阵营成员胜利检测(警告:可以复活的战场该胜利条件将无法成立)
	DWORD IfKillAllUser();
	//sky 摧毁对方阵营的基地检测
	bool IfWreckBase(DWORD npcid);
	//sky 坚持完特定NPC攻击,基地没被摧毁就算胜利检测
	DWORD IfWatchNpcAtt();
	//sky 资源最先达标的阵营胜利检测
	DWORD IfRegNumMax(DWORD CampID);	
	//sky 以持续时间为前提的胜利条件
	//sky 坚持到时间结束检测(坚持到的阵营全算胜利)
	bool IfTimeGetGo();
	//sky 时间结束时候杀死用户最多的阵营胜利
	DWORD IfTimeKillUserMuch();
	//sky 时间结束时候杀死NPC最多的阵营胜利
	DWORD IfTimeKillNpcMuch();
	//sky 战场胜负处理函数
	bool CampVictoryRun();
	//sky 结束战场处理
	bool OverBattGame();
	//sky 战场场景定时处理函数
	virtual void GangSceneTime(const zRTime& ctv);
	//**** sky 胜负处理函数 end ****
	//==== sky 逻辑函数 end ====
public:
	//sky 用来销毁地图的时候释放占用的唯一ID
	DWORD GangmapID;
public:
	GangScene();
	~GangScene();
	bool save();
public:
	//sky 动态场景初始化
	bool GangSceneInit(DWORD countryid, DWORD baseid, DWORD mapid);
	virtual bool IsGangScene() { return true; }
}; 


/**
* \brief 建筑物类型NPC类的实现 [sky]
*/
class SceneArchitecture : public SceneNpc
{
public:
	std::vector<SummonNpcData> SummonNpc;	//sky 召唤的NPC信息(ID, 数量)
	DWORD SummonTime;					//sky 召唤间隔(毫秒)
	WORD LevelUpTime;					//sky 召唤的兵升级时间(分钟)
	BYTE SummonLevel;							//sky 召唤的士兵当前等级
	bool bOutcome;						//sky 死亡是否影响胜负
	DWORD SummonAI;						//sky 刷出来的士兵使用的移动AI_ID
public:
	SceneArchitecture(Scene* scene,zNpcB *npc,const t_NpcDefine *define,const SceneNpcType type,const SceneEntryType entrytype=SceneEntry_NPC,zNpcB *abase=NULL);
	~SceneArchitecture() {}

	virtual bool IsArchitecture() {return true;}

	//sky 建筑物的AI读取方式有自己的形式
	virtual bool laod_ai();
	virtual bool GetNpcAi(); //sky 获取AI

	//sky 建筑类NPC定时处理函数
	virtual void ArchitecTimer(const zRTime& ctv);

	//sky 初始化函数
	void Init();

	//[sky] 召唤士兵(每个士兵都是一个独立的个体不同以召唤兽或者宠物)
	int summonSoldiers(DWORD id, Cmd::petType type, WORD num, DWORD sid=0, const char * name="", DWORD anpcid = 0,zPos pos=zPos(0,0),BYTE dir=4);
private:
	//sky 一分钟定时器
	Timer _one_min;

	//sky 刷兵倒计时
	DWORD SummonCountdown;
	//sky 升级倒计时
	DWORD LevelUpCountdown;
};