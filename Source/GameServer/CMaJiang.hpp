#ifndef _CMA_JIANG_H_
#define _CMA_JIANG_H_
#include <boost/pool/object_pool.hpp>

#include "CMajingRule.hpp"

struct stSeatEvent
{
	::msg_maj::event_type etype;	//事件类型
	uint16_t usSeat;				//座位
	bool bAction;					//动作

	stSeatEvent()
	{
		etype = ::msg_maj::e_none;
		usSeat = 0;
		bAction = false;
	}
};
typedef std::vector<stSeatEvent> vecSeatEvent;

enum eActionType
{
	eActionType_NULL		= 0, //空
	eActionType_SendCard	= 1, //发牌
	eActionType_Discard		= 2, //打牌
};

class CRoom;

class CMaJiang
{
public:
	CMaJiang(CRoom* pRoom);
	~CMaJiang();

	inline void SetRule(CMajingRule* pRule) { m_pRule = pRule; }

	void Release();

	bool InitMajing();

	void InitMaPai();

	void OpenMaPai();

	void OpenYiMaAllHit();

	void GMSetMajiang(const std::vector<uint16_t>& pailist);

	void GMSetPai(uint16_t usPai);

	uint16_t GetPai();

	inline const std::vector<uint16_t>& GetRemainPaiList() { return m_vecPaiList; }

	inline bool CheckHasPai() const { return GetRemainPaiNum() > 0; }

	inline uint16_t GetRemainPaiNum() const { return m_vecPaiList.size() - m_usMaPaiNum; }

	void InitPai();

	void GetFilterPai(std::vector<uint16_t>& vevFilter);

	void GetMaxCardTypeNum(uint16_t usSeat, eCardType& etype, uint16_t& usNum);

	void ChangePai(uint16_t usSeat, std::vector<uint16_t>& changelist);

	bool ChangePaiEx(uint16_t usSeat, std::vector<uint16_t>& pailist);

	void RandomRoll();

	uint32_t GetRandRoll() const;

	bool GMOper();

	bool InitFanGhostPai();

	void AddSeatEvent(::msg_maj::event_type etype, uint16_t usSeat, bool bAction = false);

	uint16_t GetEventSeatNum();

	bool DelSeatEvent(uint16_t usSeat);

	bool CheckEvent(::msg_maj::event_type etype, uint16_t usSeat);

	bool DoSeatEvent(::msg_maj::event_type etype, uint16_t usSeat);

	bool IsDoAllSeatEvent() const;

	const vecSeatEvent& GetEventList() { return m_vecSeatEvent; }

	void AddHuPai(const stHuPai& st);

	void GetHuPai(uint16_t usPos, stHuPai& hupai) const;

	void DelHuPai(uint16_t usSeat);

	inline void ClearHuPai() { m_vecHuPai.clear(); }

	::msg_maj::hu_way GetHuWay() const;

	void GetActionEvent(stSeatEvent& st) const;

	::msg_maj::event_type GetEventTypeBySeat(uint16_t usSeat) const;

	bool IsHasHuEvent() const;

	inline bool IsHasEvent() { return m_vecSeatEvent.size() > 0; }

	inline uint16_t GetCurPos() const { return m_curMJPos; }
	inline uint16_t GetMaxPos() const { return m_maxMjPos; }

	inline uint16_t GetUsCurActionPos() const { return m_usCurActionPos; }

	inline uint16_t GetMaPaiNum() const { return m_usMaPaiNum; }
	inline const ::vector<uint16_t>& GetMaPaiList() const { return m_vecMaPai; }

	inline vecHuPai& GetVecHuPai() { return m_vecHuPai;}
	inline uint16_t GetHuPaiSize() const { return m_vecHuPai.size(); }
	inline const stHuPai& GetHuPaiFirst() { return m_vecHuPai[0]; }
	inline bool IsNotHued() const { return m_vecHuPai.empty(); }
	void DeleteHuPaiExtOne(uint16_t nSeat);

	inline void SetLoopPoses(uint16_t nLoopPos) { m_nLoopPoses = nLoopPos; }
	inline uint16_t GetLoopPoses() const { return m_nLoopPoses; }
	inline void SetLoopEvents(uint16_t nLoopEvent) { m_nLoopEvents = nLoopEvent; }
	inline uint16_t GetLoopEvents() const { return m_nLoopEvents; }
	inline void AddDiscards(uint16_t usPai) { m_vecDiscards.push_back(usPai); }
	inline const std::vector<uint16_t>& GetDiscards() const { return m_vecDiscards; }
	inline const vecLastHuInfo& GetLastHuSeat() const { return m_vecLastHuInfo; }
	uint16_t GetLastHuPaiTimes(uint16_t seat); // 获得连胡的数据 
	uint16_t GetLastBankerTimes(uint16_t seat);
	inline uint16_t GetFanPai() const { return m_nFanPai; }

	inline uint16_t GetYiMaAllHitPai() const { return m_usYiMaAllHit; }

	inline uint16_t GetSendCardPos() const { return m_usSendCardPos; }
	void SetSendCardPos(uint16_t usPos);
	bool HasThisEventTypeBySeat(uint16_t usSeat, ::msg_maj::event_type etype) const;
	void AddOutPai(uint16_t usPai, uint16_t usNum);
	void CheckLastPai(uint16_t usPai, const std::vector<uint16_t>& vecPaiList, const vecEventPai& eventList, std::pair<uint16_t, uint16_t>& o_lastPaiPair);

private:

	// GMc操作使用
	bool m_bGM;
	std::vector<uint16_t> m_vecGMPailist;

	CRoom* m_pRoom; //所属房间
	CMajingRule* m_pRule;

	std::vector<uint16_t> m_vecPaiList; //所有的牌

	uint16_t m_curMJPos; //当前发牌位置(总)

	uint16_t m_maxMjPos;// 最大的位置

	uint16_t m_usMaPaiNum; //马牌数量

	std::vector<uint16_t> m_vecMaPai;	//所有马牌
	uint16_t m_usYiMaAllHit;			//一马全中
	vecHuPai m_vecHuPai;				//胡牌数据

public:

	uint32_t m_unRoll; //骰子

	uint16_t m_usSendCardPos;	//轮到发牌的位置

	uint16_t m_usSendCardNum;	//发牌的数量

	uint16_t m_usDicardPos;		//轮到打牌的位置

	eActionType m_eActionType; //动作类型

	uint16_t m_usCurActionPos;	//动作位置

	uint16_t m_usCurActionPai;	//当前发/打的牌

	vecSeatEvent m_vecSeatEvent; //牌型触发事件，用作客户端操作验证

	bool m_bActionEvent;		//是否操作事件

	uint16_t m_usGang;			//杠类型 0:无 1:暗杠 2:明杠 3:过手杠 

	// 一炮多响，有多个胡牌
	uint16_t m_nLoopPoses;		//发牌次数记录
	uint16_t m_nLoopEvents;		//事件次数记录(除了过)

	// 跟庄处理
	bool m_bHadCheckGZ;				
	bool m_bGenZhuangSuccess;		//跟庄是否成功
	std::vector<uint16_t> m_vecDiscards; // 打出的牌记录

	// 动态鬼牌
	bool m_bHadFan;
	bool m_bHadSendGhost;
	uint16_t m_nFanPai;

	// 连胡数据
	vecLastHuInfo m_vecLastHuInfo;

	// 连庄数据
	stLastBanker m_stLastBanker;

	// 上一次杠的牌
	uint16_t m_nLastGangType;
	uint16_t m_nLastGangPai;
	uint16_t m_nLastGangPos;
	uint16_t m_nLastGangFromPos;

	// 上一次碰的牌
	uint16_t m_nLastPengPai;
	uint16_t m_nLastPengFromPos;

	// 第一个胡的位置
	int16_t m_usFirstSeat;

	bool m_bEnd;				//单局结束

	std::map<uint16_t, uint16_t> m_mapOutPai;// 打出桌面上的牌，包玩家手上碰、明杠、补杠、暗杠

};

extern ::boost::object_pool<CMaJiang> g_objpoolMaJiang;

#endif // !_CMA_JIANG_H_
