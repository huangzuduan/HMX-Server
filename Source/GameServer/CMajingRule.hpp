#ifndef __MAJIANG_RULE_H__
#define __MAJIANG_RULE_H__

#include "Global.hpp"
#include "GamePublic.h"
#include "MaJiangPublic.h"

class CRoom;
class CPlayer;
class CMaJiang;
enum eRoomStatus;

enum eWanFaMask
{
	WAN_FA_MASK_GHOST = 1,
	WAN_FA_MASK_DaHuJiaBei = 2,
	WAN_FA_MASK_CanPaoHu = 4,
	WAN_FA_MASK_GangShangPaoBao3Jia = 8,
	WAN_FA_MASK_QiangGangBao3Jia = 16,
	WAN_FA_MASK_GangKaiHuaBao3Jia = 32,
	WAN_FA_MASK_258ZuoJiang = 64,
	WAN_FA_MASK_258ZuoJiangJiaBei = 128,
	WAN_FA_MASK_Hu258JiaBei = 256,
	WAN_FA_MASK_QingYiSeJiaBei = 512,
	WAN_FA_MASK_WuGuiJiaBei = 1024,
	WAN_FA_MASK_DaHuDianPao = 2048,
	// 玩法 1:无鬼加陪,2:大胡加番,4:可接炮胡,8:可杠上炮 16抢杠包三家 32杠上花包三家,64:258做将,128:258做将加番,256:胡258加番,512:清一色加番,1024:无鬼加番,2048:大胡可点炮
};

struct stHuPai
{
	::msg_maj::hu_type m_eHupaiType;	//胡牌类型
	::msg_maj::hu_way m_eHupaiWay;		//胡牌方式
	uint16_t m_usHupaiPos;				//胡牌位置
	uint16_t m_usMulti;					//胡牌倍数
	uint16_t m_usPai;					//胡的牌
	stHuPai()
	{
		m_eHupaiType = ::msg_maj::hu_none;
		m_eHupaiWay = ::msg_maj::hu_way_none;
		m_usHupaiPos = m_usMulti = m_usPai = 0;
	}
	::msg_maj::hu_way getDefHuWay() const
	{
		return (::msg_maj::hu_way)(m_eHupaiWay % 10);
	}
};
typedef std::vector<stHuPai> vecHuPai;

struct stLastHuInfo
{
	uint16_t seat;
	uint16_t times;
	stLastHuInfo()
	{
		seat = times = 0;
	}
};
typedef std::vector<stLastHuInfo> vecLastHuInfo;

// 连庄数据
struct stLastBanker
{
	uint16_t seat;
	uint16_t times;
	stLastBanker()
	{
		seat = times = 0;
	}
};

// 每次胡的详细
struct stHuDetail
{
	int16_t mySeat;		// 我的位置,如果我的位置与胡的位置相同，则显示自摸，如不同，则被自摸
	int16_t huSeat;		// 胡的位置
	int16_t doedSeat;	// 被操作位置(-1:三家,0本家,1下家,2对家,3上家)
	int16_t score;		// 加减分
	int16_t huway;		// 胡的方式
	int16_t hutype;     // 胡的类型
	int16_t humulti;    // 胡的倍数
	uint16_t huTile;	// 胡的牌

	int16_t item1;
	int16_t item2; 
	int16_t item3; 
	int16_t item4; 
	int16_t item5; 
	int16_t item6;
	int16_t item7;
	int16_t item8;
	int16_t item9;
	int16_t item10;
	int16_t item11;

	std::vector<int16_t> doedMultiSeat;

	stHuDetail()
	{
		mySeat = huSeat = doedSeat = -1;
		score = huway = hutype = humulti = huTile = 0;
		item1 = item2 = item3 = item4 = item5 = item6 = item7 = item8 = item9 = item10 = item11 = 0;
	}

	void SetData(int16_t _mySeat, int16_t _huSeat,int16_t _doedSeat, int16_t _score, const stHuPai& huPai)
	{
		mySeat = _mySeat;
		huSeat = _huSeat;
		doedSeat = _doedSeat;
		score = _score;
		huway = huPai.m_eHupaiWay;
		hutype = huPai.m_eHupaiType;
		humulti = huPai.m_usMulti;
		huTile = huPai.m_usPai;
	}
};

// 刮风下雨
struct stFengYuDetail
{
	int16_t mySeat;		// 我的位置 
	int16_t huSeat;		// 杠的位置
	int16_t doedSeat;	// 被操作位置(-1:三家,0本家,1下家,2对家,3上家)
	int16_t score;		// 加减分
	int16_t fengYuType; // 1:刮风点杠,2:补杠,3:暗杠
	std::vector<uint16_t> doedMultiSeat; // 被操作的玩家ID(用于)
	stFengYuDetail()
	{
		mySeat = huSeat = doedSeat = -1;
		score = fengYuType = 0;
	}
	void SetData(int16_t _mySeat, int16_t _huSeat, int16_t _doedSeat, int16_t _score, int16_t _fengYuType)
	{
		mySeat = _mySeat;
		huSeat = _huSeat;
		doedSeat = _doedSeat;
		score = _score;
		fengYuType = _fengYuType;
	}
};

// 查花猪
struct stHuaZhuDetail
{
	int16_t mySeat;		// 我的位置 
	int16_t huSeat;		// 花猪的位置
	int16_t doedSeat;	// 被操作位置
	int16_t score;		// 加减分
	stHuaZhuDetail()
	{
		mySeat = huSeat = doedSeat = -1;
		score = 0;
	}
	void SetData(int16_t _mySeat, int16_t _huSeat, int16_t _doedSeat, int16_t _score)
	{
		mySeat = _mySeat;
		huSeat = _huSeat;
		doedSeat = _doedSeat;
		score = _score;
	}
};

// 查大叫
struct stDaJiaoDetail
{
	int16_t mySeat;		// 我的位置 
	int16_t huSeat;		// 大叫的位置
	int16_t doedSeat;	// 被操作位置(-1:三家,0本家,1下家,2对家,3上家)
	int16_t score;		// 加减分
	stDaJiaoDetail()
	{
		mySeat = huSeat = doedSeat = -1;
		score = 0;
	}
	void SetData(int16_t _mySeat, int16_t _huSeat, int16_t _doedSeat, int16_t _score)
	{
		mySeat = _mySeat;
		huSeat = _huSeat;
		doedSeat = _doedSeat;
		score = _score;
	}
};

struct stScoreDetail
{
	int16_t			type;	// 1胡,2刮风下雨,3花猪,4大叫,5退税,6呼叫转移
	stHuDetail		hu;
	stFengYuDetail	fengYu;
	stHuaZhuDetail	huaZhu;
	stDaJiaoDetail	daJiao;
	int16_t			backTax;// 退税
	int16_t			huJzy;	// 呼叫转移
};

// 获得相对位置
inline int16_t getOffsetPos(int16_t myPos, int16_t otherPos)
{
	if (otherPos < 0)
	{
		return -1;
	}
	if (myPos - otherPos == 0) {
		return 0;
	}
	else if (myPos - otherPos == -1 || myPos - otherPos == 3) {
		return 1;
	}
	else if (myPos - otherPos == 2 || myPos - otherPos == -2) {
		return 2;
	}
	else 
	{
		return 3;
	}
};

// 获得实际位置-1:三家,0本家,1下家,2对家,3上家
inline int16_t getActualPos(int16_t myPos,int16_t offsetPos)
{
	if (offsetPos < 0)
		return -1;

	if (offsetPos == 0)
		return myPos;

	return (myPos + offsetPos) % 4;
}

struct stGameResultSeat;
struct stReplayAction;

//
//	标志位设置 
//
#define INSERT_FLAG(value, query_flags)	{(value) |= (query_flags);}
#define REMOVE_FLAG(value, query_flags)	{(value) &= ~(query_flags);}
#define HAS_FLAG(value, query_flags)		( ((value) & (query_flags)) != 0 ? true : false )

// 检查牌形标记
enum
{
	E_Check_Flag_NONE = 0,
	E_Check_Flag_PPH = 1,
	E_Check_Flag_HYS = 2,
	E_Check_Flag_QYS = 4,
	E_Check_Flag_ZYJ = 8,
	E_Check_Flag_QYJ = 16,
	E_Check_Flag_18LH = 32,
	E_Check_Flag_QIDUI = 64,
	E_Cehck_Flag_QFeng = 128,
	E_Check_Flag_HH = 256,
	E_Check_Flag_HH2 = 512,
	E_Check_Flag_HH3 = 1024,
	E_Check_Flag_MQ = 2048,
	E_Check_Flag_JJ = 4096,
};

/*
 * 麻将规则基类
 * 
 * 现以平南麻将规则做为基础，后续有规则改如，则这里改为通用类型(非平南)，其他特别规则在自己的函数重载
 *
 */
class CMajingRule
{
public:
	CRoom*		m_pRoom;
	CMaJiang*	m_pMaj;
	const ::msg_maj::RoomOption& m_roomOption;

	uint16_t m_usPayType;		// 支付类型
	uint16_t m_usBaseScoreType;	// 底分类型
	uint16_t m_usMaiMaType;		// 买马类型
	bool m_bYiMaAllHit;			// 一马全中
	uint16_t m_usJuShuType;		// 局数类型

	uint16_t m_usRenShuType;	// 人数类型1:2人,2:3人,
	uint16_t m_usFengDingType;	// 封顶

	uint32_t m_usWanFaVal;		// 由子类赋值

	bool m_bGhost;						//可有鬼
	bool m_bWuZi;						//可无字
	bool m_bCanPaoHu;					//可炮胡
	bool m_bDaHuJiaBei;					//可大胡
	bool m_bGangShangPaoBao3Jia;		//杠上炮是否包三家
	bool m_bQiangGangBao3Jia;			//抢杠胡是否包三家
	bool m_bGangKaiHuaIsBao3Jia;		//杠上花是否包三家

	bool m_bJieHu;		// 是否截胡
	bool m_bGengZhuang; //是否跟庄
	bool m_bIsGuoPeng;
	bool m_bIsGuoHu;
	bool m_bIsGuoGang;

	std::set<uint16_t>	m_setGhostPai; // 鬼牌

public:
	CMajingRule(CRoom* pRoom,const ::msg_maj::RoomOption& roomOption);
	virtual ~CMajingRule();
	inline void SetMajiang(CMaJiang* pMaj) { m_pMaj = pMaj; }
	inline void AddGhostPai(uint16_t usPai) { m_setGhostPai.insert(usPai); }

	// 获得支付类型
	inline uint16_t GetPayType() const { return m_usPayType; }
	inline uint16_t GetPlayerNum() const { return m_usRenShuType == 1 ? 4 : m_usRenShuType == 2 ? 3 : 2; }

	// 点接受完成后要去做再询问的事件，如下炮子，没有事件会直接发手牌
	virtual eRoomStatus AcceptAskAllNextStatus() const = 0;

	// 发完手牌去做的接下来的状态改变
	virtual eRoomStatus SendHandCardsAllNextState() const = 0;

	// 发牌完毕，前端都准备好的事件，如果有事件，则去处理，返回true，返回false则直接发牌
	virtual eRoomStatus DisoverCardAllCheckAndDoEvent() const = 0;

	// 下局准备完要去做的事件
	virtual bool PrepareRoundAllCheckAndDoAskSame() { return false; };

	// 重连检查Notify
	virtual void ReconnectReadyReqCheckAndNotify(CPlayer* pPlayer) {};
	
	virtual bool IsGhost() const { return m_bGhost; }

	virtual bool IsWuZi() const { return m_bWuZi; }

	inline bool HasMaiMa() const { return m_usMaiMaType > 0; }

	inline bool IsYiMaAllHit() const { return m_bYiMaAllHit; }

	inline int32_t GetMaiMaNum() const { return m_usMaiMaType > 0 ?( (m_usMaiMaType - 1) * 2):0; }

	inline bool IsDaHuJiaBei() const { return m_bDaHuJiaBei; }

	inline int32_t GetTopScore() const {
		return  m_usFengDingType == 1 ? 20 : m_usFengDingType == 2 ? 50 : m_usFengDingType == 1 ? 100 : 99999;
	}

	// 获得总牌数
	virtual uint16_t GetTotalPaiNum() const;

	// 获得鬼牌列表
	inline const std::set<uint16_t>& GetGhostList() const { return m_setGhostPai; };

	// 是否为鬼牌（多种鬼牌需要用到）
	virtual bool IsGhostCard(uint16_t usPai);

	// 设置庄家座位
	virtual uint16_t GetBankerSeat() = 0;

	// 杠的事件
	void CountEventGang(uint16_t usSeat, uint16_t usEventType);

	virtual void CountEventMingGang(uint16_t usSeat);

	virtual void CountEventAnGang(uint16_t usSeat);

	virtual void CountEventGouShouGang(uint16_t usSeat);

	// 是否可以补枉
	virtual bool CanBuGang(CPlayer* pPlayer, std::vector<uint16_t>& agpailist) { return true; }

	// 是否可以放炮(点胡炮)
	virtual bool CanDianPao(CPlayer* pPlayer) { return m_bCanPaoHu; }

	// 是否可以吃牌
	virtual bool CanEatPai(CPlayer* pPlayer) { return false; }

	// 是否需要
	virtual bool CanGang(CPlayer* pPlayer) { return true; }

	// 是否需要处理杠子
	virtual bool NeedGangZi(CPlayer* pPlayer) { return false; }

	// 是否需要报听
	virtual bool CanBaoTing() { return false; }

	// 是否可以天胡
	virtual bool CanTianHu() { return false; }

	// 是否可以地胡
	virtual bool CanDiHu() { return false; }

	// 是否可以海底捞月
	virtual bool CanHaiDiLaoYue() { return false; }

	// 获得中马的牌
	virtual void CheckHitMa(uint16_t usSeat, std::vector<uint16_t>& hitmalist) const;

	// 计算番分
	virtual void CountResult() = 0;

	// 计算杠分
	virtual void CountGangResult() = 0;

	virtual void CountGengZhuang(uint16_t usPai);

	// 胡的时候，至少达到该分数才能去胡
	virtual bool CanQiHuType(::msg_maj::hu_type huType) { return true;}

	virtual uint16_t GetGhostCard() { return 5; };

	// 启胡最少的番
	virtual uint16_t QiHuFanScore() { return 0; }

	// 获得底分
	virtual uint16_t GetBaseScore() const { return m_usBaseScoreType == 1?1: m_usBaseScoreType == 2?2: m_usBaseScoreType == 3?5:1;}

	// 是否算杠分 
	virtual bool IsCanCountGang() { return true; }

	// 鬼牌能不能杠
	virtual bool GhostCanGang() { return false; }

	// 获得具体胡牌方式
	virtual ::msg_maj::hu_way GetHuWayZiMo() const { return ::msg_maj::hu_way_zimo; };
	virtual ::msg_maj::hu_way GetHuWayGangShanPao() const { return ::msg_maj::hu_way_gangshangpao; };
	virtual ::msg_maj::hu_way GetHuWayQiangGangHu() const { return ::msg_maj::hu_way_qiangganghu; };
	virtual ::msg_maj::hu_way GetHuWayGangKaiHua() const { return ::msg_maj::hu_way_gangkaihua; };
	virtual ::msg_maj::hu_way GetHuWayDiaoPao() const { return ::msg_maj::hu_way_none; };

	virtual ::msg_maj::hu_way GetHuWayTianHu() const { return ::msg_maj::hu_way_none; };
	virtual ::msg_maj::hu_way GetHuWayDiHu() const { return ::msg_maj::hu_way_none; };
	virtual ::msg_maj::hu_way GetHuWayHaiDiLaoYue() const { return ::msg_maj::hu_way_none; };

	virtual bool IsTianHu(CPlayer* pPlayer);
	virtual bool IsDiHu(CPlayer* pPlayer);

	// 算杠的番分
	virtual uint16_t GetFanAnGang(CPlayer* pPlayer) const;
	virtual uint16_t GetFanMingGang(CPlayer* pPlayer) const;
	virtual uint16_t GetFanNextGang(CPlayer* pPlayer) const;

	// 是否可以杠上炮
	virtual bool GangShangPaoBao3Jia() const { return m_bGangShangPaoBao3Jia; }
	virtual bool QiangGangHuBao3Jia() const { return m_bQiangGangBao3Jia; }

	// 是否抢杠胡包三家
	bool IsQiangGangHuBao3Jia(const stHuPai& sthupai) const;
	// 是否杠开花包三家
	bool IsGangKaiHuaBao3Jia(const stHuPai& sthupai) const;

	// 获得消耗的房卡
	virtual uint16_t GetCostCard();

	virtual bool IsJieHu() const { return m_bJieHu; }

	virtual void SetHuInfo(const stHuPai& sthupai, uint16_t seat, ::msg_maj::HuInfo* huInfo,bool isFull = false) = 0;
	virtual void SetResultSeatHuInfo(const stGameResultSeat& seatData, ::msg_maj::HuInfo* huInfo) = 0;
	virtual void SetReplayActionHuInfo(const stReplayAction& actionData, ::msg_maj::HuInfo* huInfo) = 0;

	/*
	* 计算胡牌的基础分
	*/
	virtual int32_t CountHupaiBaseScore(const stHuPai& sthupai, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, stHuDetail& huDetail) = 0;

	/*
	* 结算胡牌人的分
	*/
	virtual void CountHupaiScore(const stHuPai& sthupai, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, std::pair<uint16_t, uint16_t>& out_mainfo) = 0;

	// 是否属于过滤的事件牌中
	virtual bool IsMultiHues() const { return false; }
	virtual bool IsFliterPaiEvent(CPlayer* pPlayer, uint16_t usPai) const;
	virtual bool HuedCanSendCard(CPlayer* pPlayer) const;
	virtual bool HuedCanDiscard(CPlayer* pPlayer)const;
	virtual bool HuedCanEvent(CPlayer* pPlayer) const;
	virtual bool HuedCanGang(CPlayer* pPlayer) const;
	virtual bool HuedCanPeng(CPlayer* pPlayer) const;
	virtual bool HuedCanDiaoPao(CPlayer* pPlayer) const;
	virtual bool HuedCanGangShanPao(CPlayer* pPlayer) const;
	virtual bool HuedCanEnd() const { return true; }
	virtual bool HuedCanGangThisPai(const std::vector<uint16_t>& copy_pai_list, uint16_t usPai) { return false; }

	// 本局是我算胜局
	virtual bool IsThisInnMyWin(CPlayer* pPlayer) const = 0;

public:

	//检测是否胡牌（张）  
	bool    CheckAAPai(int iValue1, int iValue2);
	//检测是否三连张  
	bool    CheckABCPai(int iValue1, int iValue2, int iValu3);
	//检测是否四连张  
	bool    CheckABCDPai(int iValue1, int iValue2, int iValu3, int iValue4);
	//检测是否七连张  
	bool    CheckABCDEFGPai(int iValue1, int iValue2, int iValu3, int iValue4, int iValue5, int iValue6, int iValue7);
	//检测是否三重张  
	bool    CheckAAAPai(int iValue1, int iValue2, int iValu3);
	//检测是否四重张  
	bool    CheckAAAAPai(int iValue1, int iValue2, int iValu3, int iValue4);
	//检测是否三连对  
	bool    CheckAABBCCPai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6);

	// 删除AA 不指定
	bool DelAAPai_NULL(vecCheckPai& stlist);
	// 删除AA 指定牌
	bool DelAAPai_Pai(vecCheckPai& stlist, uint16_t usPai);
	// 删除AA 计算数量
	bool DelAAPai_Num(vecCheckPai& stlist, uint16_t& usNum);
	// 删除AAA
	bool DelAAAPai(vecCheckPai& stlist);
	// 删除AAA ABC
	bool DelAAAABCPai(vecCheckPai& stlist);
	// 删除AAA ABC 听
	bool DelAAAABCPai_ting(vecCheckPai& stlist);
	// 删除AAA ABC 逆向
	bool DelAAAABCPaiEx(vecCheckPai& stlist);
	// 删除AAA ABC 逆向 听
	bool DelAAAABCPaiEx_ting(vecCheckPai& stlist);
	// 删除AAA ABC 交叉顺向
	bool DelAAAABCJC_ting(vecCheckPai& stlist);
	// 删除AAA ABC 删除头顺向
	bool DelAAAABCHead_ting(vecCheckPai& stlist);
	// 删除AAA ABC 交叉逆向
	bool DelAAAABCJCEx_ting(vecCheckPai& stlist);
	// 删除AAA ABC 删除头逆向
	bool DelAAAABCHeadEx_ting(vecCheckPai& stlist);
	// 删除ABC 顺向
	bool DelABCPai(vecCheckPai& stlist);
	// 删除ABC 逆向
	bool DelABCPaiEx(vecCheckPai& stlist);
	// 删除AA AB AC 顺向
	bool DelAAABACPai(vecCheckPai& stlist, uint16_t& usNum);
	// 删除AA AB AC 逆向
	bool DelAAABACPaiEx(vecCheckPai& stlist, uint16_t& usNum);
	// 删除AABBCC
	bool DelAABBCC(vecCheckPai& stlist, uint16_t& usNum);
	// 删除ABC 从头删除
	bool DelAAAABC_Head(vecCheckPai& stlist);
	// 删除AC 从头删除
	bool DelAAAC_Head(vecCheckPai& stlist);

public: //结构体牌规则

	// 删除已经检测的牌，某个位置，不同个数
	void DelHasCheckPai(std::vector<uint16_t>& pailist, uint16_t usStartIndex, uint16_t usNum);
	// 删除检测后的结构体牌，某个位置，不同格式  usNum    1：ABC	2：ABAC    3：AAA	4：AA
	void DelStructPai(vecCheckPai& pailist, uint16_t usPos, uint16_t usNum);
	// 检测胡牌结构
	bool CheckStructPai(vecCheckPai& pailist);
	//检测是否有结构体牌(尾数计算)
	bool CheckStructPai1Or9(vecCheckPai& pailist);
	//检测是否有结构体牌
	bool CheckHasStructPai(const vecCheckPai& pailist, uint16_t usPai);
	// 改变结构
	void ChangeStructPai(const std::vector<uint16_t>& pailist, vecCheckPai& stpailist);
	// 改变结构
	void ChangeStructPai_Ghost(const std::vector<uint16_t>& pailist, vecCheckPai& stpailist, uint16_t& usGhostNum);
	// 改变结构-自定义鬼
	void ChangeStructPai_Ghost_Custom(const std::vector<uint16_t>& pailist, vecCheckPai& stpailist, uint16_t& usGhostNum,uint16_t usCusGhostPai);
	// 改变结构
	void ChangeStructPai_Ex(const std::vector<uint16_t>& pailist, uint16_t& usGhostNum, vecCheckPai& zilist, vecCheckPai& tonglist, vecCheckPai& tiaolist, vecCheckPai& wanlist);
	// 获取相同牌数的个数
	void GetSamePaiNumNum(const vecCheckPai& pailist, uint16_t& usNum1, uint16_t& usNum2, uint16_t& usNum3, uint16_t& usNum4);

public: //事件牌

	// 检测暗杠
	void CheckAnGang(const std::vector<uint16_t>& pailist, std::vector<uint16_t>& agpailist);
	// 检测杠牌  
	bool CheckGangPai(const std::vector<uint16_t>& pailist, uint16_t usPai);
	// 检测碰牌  
	bool CheckPengPai(const std::vector<uint16_t>& pailist, uint16_t usPai);
	// 检查吃牌
	bool CheckEatPai(const std::vector<uint16_t>& pailist, uint16_t usPai,std::set<uint16_t>& out_eatlist);

	//检测胡牌(总调用接口)
	virtual ::msg_maj::hu_type CheckHupaiAll(CPlayer* pPlayer, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist,uint16_t usTingPai = 0) = 0;

protected: //普通胡牌

	//-------------------------------------平湖-范围--------------------------------------------------
	// 检测平胡
	bool CheckHupai_PingHu(const std::vector<uint16_t>& pailist);
	// 带19顺子19将
	bool CheckHupai_PingHu_AbcJJ19(const std::vector<uint16_t>& pailist);
	// 检测平胡
	bool CheckHupai_PingHu_Jiang258(const std::vector<uint16_t>& pailist);
	// 碰碰胡
	bool IsPPHu(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);	// AAAX,BBBX,CCCX,DDD,EE
	
	// 是否门清
	bool IsMq(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// 是否将将(在平湖情况下再判断)
	bool IsJJHu(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// 混一色
	bool IsHys(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// 清一色
	bool IsQys(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// 断幺九
	bool IsDuanYj(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// 带幺九
	bool IsDaiYj(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// 金钓钓(类似全求人)
	bool IsJingGG(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// 杂幺九
	bool IsZyj(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// 全幺九
	bool IsQyj(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	//18罗汉
	bool Is18Lh(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	//豪华(只针对7有效,需要确定7对后才判断是否为豪华)
	uint16_t CheckHhNum(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);
	bool IsHh(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);
	bool IsHh2(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);
	bool IsHh3(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	//全求人
	bool IsQuanQiuRen(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	//-------------------------------------七对-范围---------------------------------------------------
	// 检测七对
	bool CheckHupai_QiDui(const std::vector<uint16_t>& pailist);

	//-------------------------------------全风头-范围---------------------------------------------------
	bool CheckHupai_QuangFeng(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	//-------------------------------------13要-范围---------------------------------------------------
	// 检测十三幺
	bool CheckHupai_13yao(const std::vector<uint16_t>& pailist);

public:
	// 是否为条筒万258作将
	bool Is258(uint16_t usPai);
	// 是否为1或1牌
	bool Is1Or9(uint16_t usPai);
public: //癞子胡牌

	// 检测筒，条，万需要的鬼牌数量，无将
	uint16_t CheckNeedGhostNum(const vecCheckPai& stlist_yuan);

	// 检测筒，条，万需要的鬼牌数量，有将
	uint16_t CheckNeedGhostNum_Jiang(const vecCheckPai& stlist_yuan, bool& bJiang);
	// 检测筒，条，万需要的鬼牌数量，有将
	uint16_t CheckNeedGhostNum_Jiang_258(const vecCheckPai& stlist_yuan, bool& bJiang);
	// 检测筒，条，万需要的鬼牌数量，有将，单个牌为将
	uint16_t CheckNeedGhostNum1_Jiang(const vecCheckPai& stlist_yuan, bool& bJiang);
	// 检测筒，条，万需要的鬼牌数量，有将，单个牌为将，逆向
	uint16_t CheckNeedGhostNum1_JiangEx(const vecCheckPai& stlist_yuan, bool& bJiang);
	// 检测筒，条，万需要的鬼牌数量，有将，重牌为将
	uint16_t CheckNeedGhostNum2_Jiang(const vecCheckPai& stlist_yuan);

	// 检测字需要的鬼牌数量，无将
	uint16_t CheckNeedGhostNumZi(const vecCheckPai& zilist_yuan);

	// 检测字牌需要的鬼牌数量，有将
	uint16_t CheckNeedGhostNumZi_Jiang(const vecCheckPai& stlist_yuan, bool& bJiang);

	// 检测平胡_鬼牌
	bool CheckHupai_PingHu_Ghost(const std::vector<uint16_t>& pailist);

	// 检测平胡_鬼牌
	bool CheckHupai_PingHu_Ghost_Jiang258(const std::vector<uint16_t>& pailist);

	// 获取平湖类型 0：普通平湖 1：鬼单调 2：鬼调鬼
	uint16_t GetQiDuiType(const std::vector<uint16_t>& pailist, uint16_t usPai);
	// 获取平湖类型 0：普通平湖 1：鬼单调 2：鬼调鬼
	uint16_t GetPingHuType(const std::vector<uint16_t>& pailist, uint16_t usPai);
	// 检测清七对_鬼牌
	bool CheckHupai_QiDui_Ghost(const std::vector<uint16_t>& pailist);
	// 检测十三幺_鬼牌
	bool CheckHupai_13yao_Ghost(const std::vector<uint16_t>& pailist);

public: // 其他
	// 输出牌
	void Display(const std::vector<uint16_t>& pailist);
	void DisplayEx(const std::vector<uint16_t>& pailist, uint16_t usNum);
	// 增加牌
	void AddPai(std::vector<uint16_t> & pailist, uint16_t usPai);
	// 获取孤牌，间邻，相邻
	void GetGuJianXiang(const std::vector<uint16_t>& pailist, std::vector<uint16_t>& gulist, std::vector<uint16_t>& jianlist, std::vector<uint16_t>& xianglist, std::vector<uint16_t>& samelist);
	// 验证牌
	bool VerifyPai(uint16_t usGhostNum, const std::vector<uint16_t> & pailist);

public: //听牌
	// 增加听牌
	void AddTingPai(std::set<uint16_t>& tinglist, uint16_t usPai);
	// 增加听牌
	void AddTingPaiEx(const vecCheckPai& stlist, std::set<uint16_t>& tinglist);
	// 获取听牌的牌，无将
	void GetTingPaiList(const vecCheckPai& stlist, std::set<uint16_t>& tinglist);
	// 获取听牌的牌，有将
	void GetTingPaiList_Jiang(const vecCheckPai& stlist, uint16_t usJiangPai, std::set<uint16_t>& tinglist);
	// 获取听牌列表字，无将
	void GetTingPaiListZi(const vecCheckPai& stlist, std::set<uint16_t>& tinglist);
	// 获取听牌列表字，有将
	void GetTingPaiListZi_Jiang(const vecCheckPai& stlist, std::set<uint16_t>& tinglist);
	// 检测听牌，平胡
	bool CheckTing_PingHu(const std::vector<uint16_t>& pailist, std::set<uint16_t>& tinglist);
	// 检测听七对
	bool CheckTing_QiDui(const std::vector<uint16_t>& pailist, std::set<uint16_t>& tinglist);
	// 检测听十三幺
	bool CheckTing_13yao(const std::vector<uint16_t>& pailist, std::set<uint16_t>& tinglist);
	// 检测听牌(0不听牌,1可听七对,2可听平胡)
	virtual int16_t CheckTingPai(const std::vector<uint16_t>& pailist, std::set<uint16_t>& tinglist);
	// 查花猪
	virtual void ChaHuaZhu() {};
	// 查大叫
	virtual void ChaDaJiao() {};

	// 是否有过胡
	virtual bool IsGuoHu() { return m_bIsGuoHu; }

	// 是否有过碰
	virtual bool IsGuoPeng() { return m_bIsGuoPeng; }

	// 是否有过杠
	virtual bool IsGuoGang() { return m_bIsGuoGang; }

	// 是否有过碰这张牌
	virtual bool IsGuoPengThisPai(CPlayer* pPlayer, uint16_t usPai) { return false; }

	// 是否有鬼牌
	virtual bool IsHasGhostPai(const std::vector<uint16_t>& pailist);

};

#endif