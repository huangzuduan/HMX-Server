#ifndef __MAJIANG_RULE_XL_TDH_H__
#define __MAJIANG_RULE_XL_TDH_H__

#include "Global.hpp"
#include "CMajingRule.hpp"

/*
* 河源推倒胡麻将
*/
class CMajingRuleXL : public CMajingRule
{
public:
	CMajingRuleXL(CRoom* pRoom, const ::msg_maj::RoomOption& roomOption);
	virtual ~CMajingRuleXL();

	virtual void SetRoomRoomOption(const ::msg_maj::RoomOption& m_roomOption);

	virtual bool IsGhost() const { return m_bGhost; }

	virtual bool IsWuZi() const { return m_bWuZi; }

	virtual uint16_t GetTotalPaiNum(CRoom* pRoom);

	// 获得鬼牌
	virtual uint16_t GetGhostCard() { return 5; };

	virtual bool IsGhostCard(CRoom* pRoom, uint16_t usPai);

	// 设置庄家座位
	virtual uint16_t GetBankerSeat();

	// 检测平胡
	virtual bool CheckHupai_PingHu(const std::vector<uint16_t>& pailist);

	virtual void CountEventMingGang(uint16_t usSeat);

	virtual void CountEventAnGang(uint16_t usSeat);

	virtual void CountEventGouShouGang(uint16_t usSeat);

	virtual bool CanDianPao(CPlayer* pPlayer);


	// 计算番分
	virtual void CountResult();

	virtual void CountGangResult() {}

	// 检测胡牌(总)
	virtual ::msg_maj::hu_type CheckHupaiAll(CPlayer* pPlayer, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist,uint16_t usTingPai = 0);

	// 检测胡牌鬼牌
	virtual ::msg_maj::hu_type CheckHupaiAndGhost(CPlayer* pPlayer, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, uint16_t usTingPai = 0);

	// 获得开码的数量
	virtual uint16_t GetMaPaiNum(uint16_t nMaType);

	virtual eRoomStatus AcceptAskAllNextStatus() const;

	virtual ::msg_maj::hu_way GetHuWayZiMo() const;
	virtual ::msg_maj::hu_way GetHuWayGangShanPao() const { return ::msg_maj::hu_way_xl_gangshangpao; };
	virtual ::msg_maj::hu_way GetHuWayQiangGangHu() const { return ::msg_maj::hu_way_xl_qiangganghu; };
	virtual ::msg_maj::hu_way GetHuWayGangKaiHua() const { return ::msg_maj::hu_way_xl_gangkaihua; };
	virtual ::msg_maj::hu_way GetHuWayDiaoPao() const;

	virtual bool CanBuGang(CPlayer* pPlayer, std::vector<uint16_t>& agpailist);

	virtual bool CanGangShangPao(CPlayer* usPlayer) const { return true; }

	virtual bool GhostCanGang(CRoom* pRoom) { return true; }

	/*
	* 获得中码硬码的相关信息
	*/
	void GetHitMaDatas(const stHuPai& sthupai, uint16_t& hitMaTimes);

	/*
	* 计算胡牌的基础分
	*/
	virtual int32_t CountHupaiBaseScore(const stHuPai& sthupai, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, stHuDetail& huDetail);

	/*
	* 结算胡牌人的分
	*/
	virtual void CountHupaiScore(const stHuPai& sthupai, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, std::pair<uint16_t, uint16_t>& out_mainfo);

	virtual bool IsJieHu() const { return false; }

	virtual void SetHuInfo(const stHuPai& sthupai, uint16_t seat, ::msg_maj::HuInfo* huInfo, bool isFull);
	virtual void SetResultSeatHuInfo(const stGameResultSeat& seatData, ::msg_maj::HuInfo* huInfo);
	virtual void SetReplayActionHuInfo(const stReplayAction& actionData, ::msg_maj::HuInfo* huInfo);

	virtual eRoomStatus SendHandCardsAllNextState() const;

	virtual eRoomStatus DisoverCardAllCheckAndDoEvent() const;

	// 查花猪
	virtual void ChaHuaZhu(CRoom* pRoom);
	// 查大叫
	virtual void ChaDaJiao(CRoom* pRoom);

	// 是否属于过滤的事件牌中
	virtual bool IsMultiHues() const { return true; }
	virtual bool IsFliterPaiEvent(CPlayer* pPlayer, uint16_t usPai) const;
	virtual bool HuedCanSendCard(CPlayer* pPlayer) const;
	virtual bool HuedCanDiscard(CPlayer* pPlayer)const;
	virtual bool HuedCanEvent(CPlayer* pPlayer) const;
	virtual bool HuedCanGang(CPlayer* pPlayer) const;
	virtual bool HuedCanPeng(CPlayer* pPlayer) const;
	virtual bool HuedCanDiaoPao(CPlayer* pPlayer) const;
	virtual bool HuedCanGangShanPao(CPlayer* pPlayer) const;
	virtual bool HuedCanEnd(CRoom* pRoom) const;
	virtual bool HuedCanGangThisPai(CRoom* pRoom, const std::vector<uint16_t>& copy_pai_list, uint16_t usPai);

	virtual bool IsThisInnMyWin(CPlayer* pPlayer) const;

	inline bool IsSanZhang() const { return m_bSanZhang; }
	inline bool IsDingQue() const { return m_bDingQue; }
	inline bool IsHuJiaoZhuanYu() const { return m_bHuJiaoZhuanYu; }
	inline bool IsDaiYj() const { return m_bIsDaiYj; }
	inline bool IsDuanYj() const { return m_bIsDuanYj; }
	inline bool IsJiangjgg() const { return m_bIsJiangJGG; }
	inline bool IsMengQing() const { return m_bIsMenQing; }
	inline bool IsTianDihu() const { return m_bTianDihu; }

private:

	bool m_bSanZhang;						//换三张
	bool m_bDingQue;						//定缺门
	bool m_bHuJiaoZhuanYu;					//呼叫转移
	int16_t m_usSanZhangStep;				//发牌当前的步骤

	bool m_bIsDaiYj;
	bool m_bIsDuanYj;
	bool m_bIsJiangJGG;
	bool m_bIsMenQing;
	bool m_bTianDihu;
	bool m_bHaiDiLaoYue;

};

#endif