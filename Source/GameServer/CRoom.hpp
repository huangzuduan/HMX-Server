#ifndef _CROOM_H_
#define _CROOM_H_
#include <boost/pool/object_pool.hpp>
#include "Global.hpp"
#include "CMaJiang.hpp"
#include "FogsTimerService.hpp"

class CPlayer;
class CMaJiang;
class CMajingRule;

enum eRoomStatus
{
	eRoomStatus_Ready		= 1, //准备状态
	eRoomStatus_ClickStart  = 2, //点击开始
	eRoomStatus_SanZhang	= 3, //换三张
	eRoomStatus_DingQue		= 4, //定缺门
	eRoomStatus_StartGame	= 5, //开始状态
	eRoomStatus_End			= 6, //结束状态
};

enum eRoomCloses
{
	eRoomCloses_Finish	= 0, // 正常打完所有小局解散
	eRoomCloses_Hand	= 1, // 手动解散
	eRoomCloses_TimeOut = 2, // 超时解散
	eRoomCloses_NotPersons = 3, // 无人解散
};

// 碰、杠信息
struct stOpenTile
{
	::msg_maj::event_type event_t;
	std::vector<int16_t> tile_list;
	stOpenTile()
	{
		event_t = ::msg_maj::e_none;
	}
};

// 胡牌信息
struct stHuInfo
{
	::msg_maj::hu_way	 hu_way;	// 胡牌方式
	::msg_maj::hu_type	 hu_type;	// 胡牌类型
	std::vector<int16_t> ma_pai_all;// 所有的马牌
	std::vector<int16_t> ma_pai_hit;// 中马的牌
	uint32_t jiang_ghost_num; // 单吊将牌时，将牌鬼的数量(0:无或不符合单吊,1:将牌1个鬼,2:将牌2个鬼)
	uint32_t jiejiegao_times; // 节节第几层
	bool wuGhostJiaBei;// 无鬼加倍
	stHuInfo()
	{
		hu_way = ::msg_maj::hu_way_none;
		hu_type = ::msg_maj::hu_none;
		jiang_ghost_num = jiejiegao_times = 0;
		wuGhostJiaBei = false;
	}
};

// 每一小局结果
struct stGameResultSeat
{
	int16_t					seat;			// 座位号
	int16_t					total_score;	// 得分
	std::vector<int16_t>	hand_titles;	// 手中的牌
	std::vector<stOpenTile> open_titles;	// 碰、杠的牌
	int16_t					an_gang;		// 暗杠的番数
	int16_t					ming_gang;		// 明杠的番数
	int16_t					guoshou_gang;	// 过手杠的番数
	stHuInfo				hu_info;		// 胡牌信息
	int16_t					hu_tile;		// 胡的牌
	int16_t					dingque;		// 定阙
	std::vector<stScoreDetail>	score_detail;
	int16_t					game_type;		// 游戏玩法
	stGameResultSeat()
	{
		seat = total_score = an_gang = ming_gang = guoshou_gang = hu_tile = dingque = game_type = 0;
	}
};

// 每一次打牌的记录
struct stReplayAction 
{
	::msg_maj::event_type	event_t;	//事件
	int16_t		actor_seat;		//发起动作的人
	int16_t		victim_seat;	//被操作者,无时-1
	stHuInfo		hu_info;		//如果是胡牌了，给胡牌信息
	std::vector<int16_t> event_tile_list;//事件关联到牌的列表
	int16_t		desk_tile_count;	// 剩余牌的数量
	stReplayAction()
	{
		event_t = msg_maj::e_none;
		actor_seat = victim_seat = desk_tile_count = 0;
	}
};

// 初始牌形
struct stSeatInfo
{
	int16_t seat;	// 座位
	std::vector<int16_t> hand_tiles;	// 手牌
	std::vector<stOpenTile> open_tiles;	// 碰、杠的牌
	std::vector<int16_t> discard_tiles; // 打出的牌
	::msg_maj::player_status pstatus;	//玩家状态
	int16_t score;		// 分数，单局分数
	int16_t dingque;	// 定阙
	stSeatInfo()
	{
		seat = score = dingque = 0;
		pstatus = ::msg_maj::normal;
	}
};

// 每一小局的信息
struct stInnRecord
{
	int16_t						inn_id;		// 局数ID
	int16_t						banker_seat;// 庄家座位号
	int16_t						dice;		// 股子数
	std::vector<stSeatInfo>		seat_info;	// 初始牌
	std::vector<stGameResultSeat> seat_result;// 座位数据
	stInnRecord()
	{
		inn_id = banker_seat = dice = 0;
	}
};

// 每一小局的出牌记录
struct stInnReplay
{
	int16_t						inn_id;		// 局数ID
	std::vector<stReplayAction>	replay_list;// 回放数据(打牌经过)
	stInnReplay()
	{
		inn_id = 0;
	}
};


// 每位选手信息
struct stPlayerInfo
{
	int16_t seat;
	uint64_t uid;
	std::string nick;
	std::string actor_addr;
	stPlayerInfo()
	{
		uid = seat = 0;
	}
};

class CRoom
{
public:
	CRoom(::msg_maj::RoomType roomType, ::msg_maj::maj_type majType,const ::msg_maj::RoomOption& option);
	~CRoom();

	void Release();
	inline void SetRoomID(uint32_t usRoomID) { m_unRoomID = usRoomID; }
	inline uint32_t GetRoomID() const { return m_unRoomID; }
	inline void SetRoomer(uint64_t ulRoomer) { m_ulRoomer = ulRoomer; }
	inline uint64_t GetRoomer() const { return m_ulRoomer; }

	inline eRoomStatus GetRoomStatus() const { return m_eRoomStatus; }

	inline CMaJiang* GetMajiang() const { return m_pMaj; }

	inline uint16_t GetBankerSeat() const { return m_usBankerSeat; }

	inline CMajingRule* GetRule() const { return m_pRule; }

	inline int32_t GetMaxMultiNum() const { return m_nMaxMultiNum; }

	inline bool IsClose() const { return m_bClose; }

	inline bool IsXieZhanLiu() const { return (m_usGameType == ::msg_maj::maj_t_xiezhan || m_usGameType == ::msg_maj::maj_t_xieliu); }

	inline void SetTest() { m_bTest = true; }

	inline bool IsTest() const { return m_bTest; }

	inline const ::msg_maj::RoomOption& GetRoomOption() const { return m_roomOption; }
	inline void UpdateRoomOption(const ::msg_maj::RoomOption& _roomOption) { m_roomOption.CopyFrom(_roomOption); };

	inline ::msg_maj::maj_type GetMajType() const { return m_usGameType; }

	inline bool IsHaiDiLaoYue() const { return m_bHaiDiLaoYue; }
	inline bool IsRobot() const { return m_bRobot; }
	void StartRobotJoin();

public:

	bool EnterPlayer(CPlayer* pPlayer);

	void LeavePlayer(CPlayer* pPlayer);

	void SetLeaveData(uint16_t usSeat);

	void RoomStatusEvent(CPlayer* pPlayer, bool bDisconnect);

	void ReconnectPlayer(CPlayer* pPlayer);

	void DisconnectPlayer(CPlayer* pPlayer);

	bool IsDisconnectAll();

	CPlayer* GetPlayer(uint16_t usSeat) const;

	uint16_t GetCurPersons() const; //当前人数

	inline uint16_t GetTotalPersons() const { return m_usRoomPersons; } //总人数

	void SetToProto(::msg_maj::RoomInfo* pPro);

	void BrocastMsg(uint16_t usCmd, uint16_t usCCmd, const ::google::protobuf::Message& msg, CPlayer* pPlayer = NULL);

	void SendRoomInnInfo(CPlayer* pPlayer = NULL);

private:

	bool CheckStart();

	void SendStartButton();

	void SendCancelStartButton();

	void SendHandCards();  // 发牌，用于换三张、定缺

	void RecordHandTiles();	// 设置开始，记录玩家信息

	void SendAskSanZhang(CPlayer* pPlayer = NULL);

	void SendAskDingQue(CPlayer* pPlayer = NULL);

	void ExchangeSanZhangPai();

	void StartTimerSendCard();

	void StartTimerClose();

	void CancelTimerClose();

	void Close(int32_t reason);

	void SendCard();

	void BroadcastSendCard(::msg_maj::DealNotify proData);

	bool DisoverCardAll(); //是否所有玩家发牌完毕

	bool AcceptAskAll(); //是否所有玩家都接收开始游戏

	bool SanZhangAll();

	bool DingQueAll();

	bool DissmissAcceptAll(); //是否所有玩家都同意解散

	bool PrepareRoundAll(); //是否所有玩家都准备好了

	bool End(); //单局结束

	void EndAll(); //整局结束

	void DissmissRoom(int32_t reason); //解散房间

	void DelDiscardTile(); //删除打出的牌
	
	void CountEventGang(uint16_t usSeat, uint16_t usEventType); // 计算事件分数

	void ResetData(); //重置数据

	void ChangeBankerSeat(); //更换庄家位置

	uint32_t GetDissmissRoomProtectTime();

	void SendNotifyGhostPaiListResult(CPlayer* pPlayer, bool is_disconn = false);

public:

	//处理多个玩家事件
	void HandleEventMultiple(CPlayer* pPlayer, uint16_t usEventType, uint16_t usParam);

	//处理单个玩家事件
	void HandleEventSingle(CPlayer* pPlayer, uint16_t usEventType, uint16_t usParam);

public:
	// 客户端开始游戏请求
	void StartGameReq(CPlayer* pPlayer);
	// 客户端接受房主开始请求
	void AcceptAskReq(CPlayer* pPlayer, bool bAccept);
	// 选择定三张
	void SanZhangReq(CPlayer* pPlayer,std::vector<uint16_t>& vecSanZhang);
	// 选择定一门
	void DingQuiReq(CPlayer* pPlayer,uint16_t usLessType);
	// 调用开始发牌
	bool CheckAndCostRoomCard();

	void RecordPlayerInfo();

	void SendDingQueNotify(CPlayer* pPlayer = NULL);

	// 客户端打牌
	void DiscardTileReq(CPlayer* pPlayer, uint16_t usPai);

	// 客户端操作事件(碰、杠、胡……)
	void ResponseEventReq(CPlayer* pPlayer, uint16_t usEventType, uint16_t usParam);
	// 客户端发牌完毕上报
	void DisoverCardReq(CPlayer* pPlayer);
	// 客户端解散房间请求
	void DissmissRoomReq(CPlayer* pPlayer);
	// 解散房间同意与否
	void DissmissAcceptReq(CPlayer* pPlayer, bool bAccept);
	// 客户端准备(下一场)
	void PrepareRoundReq(CPlayer* pPlayer);
	// 检查准备阶段的状态
	void PreparRoundCheck(CPlayer* pPlayer);
	// 客户端重连加载成功
	void ReconnectReadyReq(CPlayer* pPlayer);
	void ReconnectOtherReadyReq(CPlayer* pPlayer);
	// 提玩家请求
	void KickRoleReq(CPlayer* pPlayer, uint16_t usSeat);
	// 进入房间准备好请求
	void EnterRoomReadyReq(CPlayer* pPlayer);
	// 进入房间其他玩家数据准备好
	void ReconectOtherReadyReq(CPlayer* pPlayer);

private:

	bool m_bTest;

	::msg_maj::maj_type		m_usGameType;		//游戏类型 比如抚州麻将
	::msg_maj::RoomType		m_eRoomType;		//房间类型	
	uint32_t m_unRoomID;					//房间ID
	uint64_t m_ulRoomer;					//房主

	::msg_maj::RoomOption	m_roomOption;	// 房间属性

	uint64_t m_ulRoomUUID;					//房间唯一ID
	eRoomStatus m_eRoomStatus;				//房间状态
	std::vector<CPlayer*> m_vecPlayer;		//房间玩家
	int32_t m_nAllGames;					//总局数
	int32_t m_nGames;						//局数

	int32_t m_usMaxMultiType;				//最高番类型 0:不封顶 1:20 2:80
	int32_t m_nMaxMultiNum;					//最高番番数

	bool m_bHaiDiLaoYue;

	bool m_bStart;							//是否是点击开始游戏之后游戏开始
	bool m_bClickDissmiss;					//是否点击解散
	bool m_bClose;							//是否关闭
	uint16_t m_usRoomPersons;				//房间人数

	fogs::FogsTimer* m_pTimerSendCard;		//发牌定时器
	fogs::FogsTimer* m_pTimerClose;			//关闭定时器
	CMaJiang* m_pMaj;						//麻将数据
	CMajingRule* m_pRule;					//麻将规则
	uint16_t m_usBankerSeat;				//庄家位置

	bool m_bRobot;							//是否启动机器人
	int32_t m_usLimitTime;					//是否有时间限制(时间到达，自动解散)
	
public:

	/*
	 * 记录房间信息
	 * 在开始游戏时记录
	 */
	void AddRoomInfo(uint64_t record_id,uint32_t nRoomID,int16_t room_type, const ::msg_maj::RoomOption& room_option, time_t startTime);

	/*
	 记录玩家信息
	 在创建房间开始时要记录
	 */
	void AddPlayerInfo(const std::vector<stPlayerInfo>& infos);

	/*
	开局必须要先调用一次该接口
	inn_id;		 局数ID
	banker_seat; 庄家座位号
	dice;		 股子数
	*/
	void AddInnRecord(int16_t inn_id,int16_t banker_seat,int16_t dice);

	/*
	 发完牌后，记录每个玩家的初始牌
	 seatInfos :座位信息
	 */
	void AddSeatInfo(int16_t inn_id, const std::vector<stSeatInfo>& seatInfos);

	/*
	每个牌的动作记录
	*/
	void AddReplayAction(int16_t inn_id,const stReplayAction& replay);

	/*
	结束单场时调用，保存每个座位上的信息
	seat_result 4个人座位结束时数据
	*/ 
	void AddGameResult(int16_t inn_id,const std::vector<stGameResultSeat>& seat_result,bool isDissovle = false);

	/*
	 * 房间信息 
	 */
	bool GetRoomInfo(::msg_maj::RoomInfo& roomInfo);

	/*
	 * 获得角色信息
	 */
	bool GetRoleInfoList(::msg_maj::RoleInfoListS& roomInfo);

	/*
	 * 获得单局记录
	 */
	bool GetInnRecordS(int16_t inn_id, ::msg_maj::InnRecordS& innRecord);

	/*
	 * 获得所有记录
	 */
	void GetInnRecordListS(::msg_maj::InnRecordListS* innRecordListS);

	/*
	 * 获得单局回放
	 */
	bool GetInnReplayS(int16_t inn_id, ::msg_maj::InnReplayActionS& innReplay);

	 /*
	 * 获得所有回放
	 */
	void GetInnReplayS(std::map<int16_t, ::msg_maj::InnReplayActionS>& mapInnReplay);

	/*
	 * 获得座位上的数据 
	 */
	bool GetInnRecordSeatInfo(int16_t inn_id,std::map<uint16_t, stGameResultSeat>& mapSeat);

	/*
	 * 增加游戏日志记录
	 */
	void AddRecordToLog(const ::msg_maj::RoomInfo& roomInfo,const ::msg_maj::RoleInfoListS& roleInfo, const ::msg_maj::InnRecordS& innRecordS);

	/*
	 * 
	 */
	void GetAllInnRecordSeatScore(std::map<uint16_t, int16_t>& mapSeatScore);

	/*
	 * 获得战绩唯一ID
	 */
	inline uint64_t GetRecordID() const { return m_unRecordID; }

	/*
	* 获得战绩时间
	*/
	inline uint64_t GetZjStartTime() const { return m_reconrdTime;}

	void RecordInnZhanJiLocal(bool isDissolve = false);
	void SaveInnZhangJiGamedb();
	// 组装新牌加入 
	void GetCopyPaiList(std::vector<uint16_t>& pailist_copy, CPlayer* pPlayer, uint16_t usPai);
private:

	uint64_t						m_unRecordID;		// 记录ID
	uint32_t						m_unZjRoomID;		// 房间号
	time_t							m_reconrdTime;		// 创建时间
	time_t							m_startTime;		// 开始时间
	int16_t							m_nRoomType;		// 房间类型
	::msg_maj::RoomOption			m_roomZjOption;		// 房间属性
	std::map<int16_t, stPlayerInfo>	m_mapPlayerInfos;	// 选手信息
	std::map<int16_t, stInnRecord>	m_mapInnRecords;	// 战线记录
	std::map<int16_t, stInnReplay>  m_mapInnReplays;	// 回看记录

public:

	void GetTingPaiData(CPlayer* pPlayer, std::vector< ::msg_maj::PromptPai>& vecPromptPai, const std::vector<uint16_t>& pailist_copy);
	void TingPaiDiscardPai(CPlayer* pPlayer);
	void TingPaiWaitePai(CPlayer* pPlayer,bool bTurnMe);

	uint16_t GetHuPlayerCount() const; // 已经胡的人数
	void FillHuTimesToDetail(const stScoreDetail& huDetail, ::msg_maj::ScoreDetail* pHuDetail);
	void GetReconnResp(CPlayer* pPlayer, ::msg_maj::ReconnectLoadResp& proMaj);
	void ReconnectRobot(CPlayer* pPlayer);

};

extern 	::boost::object_pool<CRoom>	g_objpoolRoom;

#endif // !_CROOM_H_
