#ifndef __MAJIANG_RULE_yl_TDH_H__
#define __MAJIANG_RULE_yl_TDH_H__

#include "Global.hpp"
#include "CMajingRule.hpp"

/*
 * 河源推倒胡麻将
 */
class CMajingRuleYL : public CMajingRule
{
public:
	CMajingRuleYL(CRoom* pRoom,const ::msg_maj::RoomOption& roomOption);
	virtual ~CMajingRuleYL();

	// 获得鬼牌
	virtual uint16_t GetGhostCard() { return 5; };

	// 设置庄家座位
	virtual uint16_t GetBankerSeat();

	// 检测平胡
	virtual bool CheckHupai_PingHu(const std::vector<uint16_t>& pailist);

	virtual void CountEventMingGang(uint16_t usSeat);

	virtual void CountEventAnGang(uint16_t usSeat);

	virtual void CountEventGouShouGang(uint16_t usSeat);

	virtual bool CanDianPao(CPlayer* pPlayer);

	// 是否算杠分 
	virtual bool IsCanCountGang();

	// 计算番分
	virtual void CountResult();

	virtual void CountGangResult();

	// 检测胡牌(总)
	virtual ::msg_maj::hu_type CheckHupaiAll(CPlayer* pPlayer, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, uint16_t usTingPai = 0);

	// 检测胡牌鬼牌
	virtual ::msg_maj::hu_type CheckHupaiAndGhost(CPlayer* pPlayer, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, uint16_t usTingPai = 0);

	virtual ::msg_maj::hu_way GetHuWayZiMo() const { return ::msg_maj::hu_way_yl_zimo; };
	virtual ::msg_maj::hu_way GetHuWayGangShanPao() const { return ::msg_maj::hu_way_yl_gangshangpao; };
	virtual ::msg_maj::hu_way GetHuWayQiangGangHu() const { return ::msg_maj::hu_way_yl_qiangganghu; };
	virtual ::msg_maj::hu_way GetHuWayGangKaiHua() const { return ::msg_maj::hu_way_yl_gangkaihua; };
	virtual ::msg_maj::hu_way GetHuWayDiaoPao() const { return ::msg_maj::hu_way_yl_dianpao; };

	virtual bool CanBuGang(CPlayer* pPlayer, std::vector<uint16_t>& agpailist);

	virtual bool GangShangPaoBao3Jia() const { return false; }

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

	 /*
	 * 结算杠牌人的分(除了胡的人)
	 */
	void CountGangScore(const stHuPai& sthupai, uint16_t gangSeat);

	virtual void SetHuInfo(const stHuPai& sthupai, uint16_t seat,::msg_maj::HuInfo* huInfo, bool isFull);
	virtual void SetResultSeatHuInfo(const stGameResultSeat& seatData, ::msg_maj::HuInfo* huInfo);
	virtual void SetReplayActionHuInfo(const stReplayAction& actionData, ::msg_maj::HuInfo* huInfo);
	
	virtual bool IsThisInnMyWin(CPlayer* pPlayer) const;

	virtual bool IsGuoPengThisPai(CPlayer* pPlayer, uint16_t usPai);

	virtual eRoomStatus AcceptAskAllNextStatus() const;

	virtual eRoomStatus SendHandCardsAllNextState() const;

	virtual eRoomStatus DisoverCardAllCheckAndDoEvent() const;
};

#endif