#ifndef		___DEF_H_DDZ_PUBLIC_H_DEF__
#define		___DEF_H_DDZ_PUBLIC_H_DEF__
#include "CommonDef.h"
//开局桌子上最大人数和最小人数
#define  __MJ_PLAYER_MAX_NUM__	(5)
#define  __MJ_PLAYER_MIN_NUM__	(2)
#define __MAJING_NUM__	(136)
#define __13_YAO_NUM__	(13)
#define __HUA_NUM_4__	(4)
#define __HUA_NUM_8__	(8)

//每人发的麻将个数
#define  __MJ_NUM__	(4)
//手上牌总的张数 不算碰或扛的牌
#define  __MJ_TOTAL_NUM__	(5)

//客户端用,服务端不用管 房间数量
#define __MAX_ROOM_NUM__	(6)

//牌输赢番数定义
#define  _MJ_FANSHU_JIAOBEI_	(1)	//飘
#define  _MJ_FANSHU_TIANHU_		(2)	//天胡
#define  _MJ_FANSHU_DIHU_		(2)	//地胡
#define  _MJ_FANSHU_HAIDILAO_	(2)	//海底捞
#define  _MJ_FANSHU_HAAO_	(2)	//海底炮
#define  _MJ_FANSHU_DUIHUA_		(1)	//对花
#define  _MJ_FANSHU_QINGYISHE_	(2)	//清一色
#define  _MJ_FANSHU_ANGONG_		(2) //暗扛
#define  _MJ_FANSHU_GONG_		(1) //回头扛和点扛都是一倍
#define  _MJ_FANSHU_MINGTING_	(2)	//明听
#define  _MJ_FANSHU_ANTING_		(1)	//听
#define  _MJ_FANSHU_DUIDUIHU_	(1)	//对对胡
#define  _MJ_FANSHU_DAIYAO_		(1)	//带幺胡
#define  _MJ_FANSHU_KAWUXING_	(1)	//卡五星
#define  _MJ_FANSHU_JIANGDUI_	(1)	//将对
#define  _MJ_FANSHU_CHAJIAO_	(4)	//查叫
#define  _MJ_FANSHU_JUAZHU_		(4)	//花猪
#define  _MJ_FANSHU_ZHIMO_		(1)	//自摸
#define  _MJ_FANSHU_QIDUI_		(2)	//七对
#define  _MJ_FANSHU_MINGSIGUI_	(1)	//明四归
#define  _MJ_FANSHU_ANSIGUI_	(2)	//暗四归
#define  _MJ_FANSHU_LONGQIDUI_	(3)	//龙七对
#define  _MJ_FANSHU_SHUANGLONGQIDUI_	(4)	//双龙七对
#define  _MJ_FANSHU_DASANYUAN_	(3)	//大三元
#define  _MJ_FANSHU_XIAOSANYUAN_		(2)	//小三元
#define  _MJ_FANSHU_SHOUZHUAYI_	(2)	//手抓一
#define _MJ_FANSHU_DANDIAO_	    (1)
#define _MJ_FANSHU_HUNYISE_	    (1)	//混一色

//消息定义
//所有游戏里面送发给客户端的消息都MainID: MSG_MDM_CGS_GAME   SUBID: SUB_GAME_CGS_GAME_MSG
//收到游戏消息以后要重新解析是什么消息 转换为 CMD_GF_GameFrameHead

//游戏开始发牌消息
#define		_MJ_MSG_GAME_START_		(1)

//通知所有用户加倍和  玩家发送是否加倍
#define		_MJ_MSG_PLAYER_JIABEI_		(2)

//广播所有用户选择加倍消息结果
#define		_MJ_MSG_PLAYER_JIABEI_RET_	(3)

//广播用户换牌消息
#define		_MJ_MSG_PLAYER_HUANPAI_	(4)

//广播用户使用道具换牌结果消息
#define		_MJ_MSG_PLAYER_HUANPAI_RET_	(5)

//玩家发送打牌给服务器 服务器发送打牌给玩家
#define		_MJ_MSG_PLAYER_DAPAI_	(6)

//通知指定用户能碰扛胡牌等
#define		_MJ_MSG_PLAYER_YAOPAI_	(7)

//通知指定用户能碰扛牌等
#define		_MJ_MSG_PLAYER_YAOPAI_RET_	(8)


//广播用户碰扛胡
#define _MJ_MSG_PLAYER_PGH_	(9)

//通知指定用户名胡牌
#define		_MJ_MSG_PLAYER_HUPAI_		(10)


//其它用户抓牌  广播
#define		_MJ_MSG_PLAYER_ZHUAPAI_	(11)
//广播荒牌
#define _MJ_MSG_GAME_HUANGPAI_	(12)

//发送给玩家听/明听消息
#define 	_MJ_MSG_GAME_TING_	(13)
//玩家出牌消息
#define		_MJ_MSG_PLAYER_CHUAPAI_	(14)

//玩家听牌消息 二边互发
#define		_MJ_MSG_PLAYER_TINGPAI_		(15)
#define		_MJ_MSG_PLAYER_TINGPAI_RET_	(16)
#define __MAX_HUPAI_NUM__	(9)//胡牌数量


//翻数不够或过高的提示
#define		_MJ_MSG_HU_PROMPT_	(17)


//客户端发送错误的打牌消息过来  服务器把牌发送给当前客户端
#define	_MJ_MSG_PLAYER_SEND_ERROR_PAI_	(18)


//结算消息
#define	_MJ_MSG_GAME_JIESHUAN_	(19)

//游戏结束
#define		_MJ_MSG_PLAYER_GAME_END_	(50)


//用户断线处理  发送相应场景和数据给用户
#define _MJ_GAME_RECONNECT_SCENE_		(51)



//发牌类型
enum
{
	_MJ_TYPE_NULL_,		//不用发牌
	_MJ_TYPE_RAND_ = 1,	//随机发牌
};

//玩家手上牌的类型
typedef enum
{
	_MJ_PAI_TYPE_NULL_ = 0x00,
	_MJ_PAI_TYPE_HUAZHU_ ,	//花猪
	_MJ_PAI_TYPE_NOTING_,		//没听
	_MJ_PAI_TYPE_TING_,		//听牌
}MJ_PAI_TYPE;
//用户要牌类型  服务器只区分碰和胡(胡优先)
//客户端要牌只能是一种情况
//_MJ_YP_NORMAL_服务器用来标志用户是否要牌
typedef enum
{
	_MJ_YP_GUO_ = 0,//过或不要牌
	_MJ_YP_PENG_,	//碰
	_MJ_YP_GONG_,	//扛
	_MJ_YP_HU_,		//胡
	_MJ_YP_NORMAL_,		//服务器用
}MJ_USR_YP_TYPE;

//叫牌类型
typedef enum
{
	_MJ_USR_ACTION_NULL_ = 0x00,	//无行为
	_MJ_USR_ACTION_ANGONG_ = 0x01,	//暗扛 自己抓到的牌
	_MJ_USR_ACTION_DIANGONG_ = 0x02,	//点扛
	_MJ_USR_ACTION_HTGONG_ = 0x04,		//回头扛
	_MJ_USR_ACTION_PENG_ = 0x08,	//碰
	_MJ_USR_ACTION_CHI_ = 0x10,	//吃  暂时没用
}MJ_USR_ACTION;

//牌的类型 int 4字节能表示32种胡法
typedef enum
{
	_MJ_WIN_NULL_ = 0x0000,
	_MJ_WIN_TIANHU_ = 0x0001,		//天胡
	_MJ_WIN_DIHU_ = 0x0002,		//地胡
	_MJ_WIN_HAIDILAO_ = 0x0004,	//海底捞
	_MJ_WIN_QINGYISHE_ = 0x0008,	//清一色  ----
	_MJ_WIN_GONGHUA_ = 0x0010,		//扛上花
	_MJ_WIN_ZHIMO_ = 0x0020,		//自摸  -----
	_MJ_WIN_MINGTING_ = 0x0040,	//明听胡
	_MJ_WIN_ANTING_ = 0x0080,		//暗听胡
	_MJ_WIN_DUIDUIHU_ = 0x0100,	//对对胡   ------
	_MJ_WIN_DAIYAO_ = 0x0200,		//带幺  ------  
	_MJ_WIN_KAWUXING_ = 0x0400,	//卡五星   -----
	_MJ_WIN_JIANGDUI_ = 0x0800,	//将对     -----
	_MJ_WIN_QIANGGANG_ = 0x1000,	//抢扛胡
	_MJ_WIN_DUANYJ_ = 0x2000,	//断19
	_MJ_WIN_GONGPAO_ = 0x4000,	//扛后炮
	_MJ_WIN_HAAO_ = 0x8000,	//海底炮
	_MJ_WIN_GONG_ 	 = 0x010000,	//扛
	_MJ_WIN_DANDIAO_ 	 = 0x020000,	//单钓
	_MJ_WIN_PINGHU_ = 0x040000,	//胡  只是胡的标志  胡的类型不是以上几种
	_MJ_WIN_QIDUI_ = 0x080000,	//七对
	_MJ_WIN_MINGSIGUI_ = 0x100000,	//明四归
	_MJ_WIN_ANSIGUI_ = 0x200000,	//暗四归
	_MJ_WIN_SHOUZHUAYI_ = 0x400000,	//手抓1
	_MJ_WIN_LONGQIDUI_  = 0x800000,	//龙七对
	_MJ_WIN_SHUANGLONGQIDUI_ = 0x1000000,	//双龙七对
	_MJ_WIN_DASANYUAN_ = 0x2000000,	//大三元
	_MJ_WIN_XIAOSANYUAN_ = 0x4000000,	//小三元
	_MJ_WIN_HUNYISE_ = 0x8000000,	//混一色

}MJ_WIN_TYPE;


//放炮的类型
typedef enum
{
	_MJ_LOSE_FANGPAO_ = 0x01,	//正常打牌放炮
	_MJ_LOSE_GONG_,			//扛后出牌放炮或抢扛
	_MJ_LOSE_ZIMO_,			//自摸
}MJ_LOSE_TYPE;

typedef enum
{
	_MJ_TING_NULL_	=	0,
	_MJ_TING_MINGTING_	,
	_MJ_TING_TING_,
}MJ_TING_TYPE;


//游戏状态 可用于用户状态标记
typedef enum
{
	_MJ_PLAY_STATUS_FREE_ = 0,
	_MJ_PLAY_STATUS_JIABEI_,	//加倍
	_MJ_PLAY_STATUS_FAPAI_,	//游戏开始时发牌
	_MJ_PLAY_STATUS_BANK_,	//选择庄家
	_MJ_PLAY_STATUS_HUANPAI_,	//使用道具
	_MJ_PLAY_STATUS_DAPAI_,		//发牌状态
	_MJ_PLAY_STATUS_YAOPAI_,	//发牌给用户或发能碰/扛/胡消息给用户
	_MJ_PLAY_STATUS_HUPAI_,		//用户胡牌
	_MJ_PLAY_STATUS_HUANGPAI_,	//荒牌
	_MJ_PLAY_STATUS_HU_JIESHUAN_,	//最后胡牌的结算界面
	_MJ_PLAY_STATUS_PLAYER_END_		//玩家状态： 胡完牌后在桌子上的状态
}MJ_PLAY_STATUS;


//出牌类型
typedef enum
{
	_MJ_CHUPAI_NULL_ = 0,	//普通出牌
	_MJ_CHUPAI_MINGGONG_,	//扛
	_MJ_CHUPAI_GONG_CHUPAI_,	//扛后出牌
	_MJ_CHUPAI_GONG_,	//扛的状态(暗扛/点扛)
}MJ_CHUPAI_TYPE;


//玩家结算分数结构体
struct PLAYER_JIESUAN_DATA_STRUCT
{
	int32_t hutype;		//胡牌类型
	uint8_t fanshu;	//输赢翻数
	uint8_t chirdid;	//谁放炮  如果是自摸为传0
	uint8_t duihuanum;	//对花数量
	uint8_t bExist;		//客户端在用
	int32_t fpgold;		//放炮金币数
	int32_t ggold;		//扛的金币数
	int32_t hugold;		//胡牌的金币数如果没有胡则是查牌金币数
	int32_t totalgold;	//总的输赢金币
};

//花猪和查叫信息
#define _CHAPAI_NUM_	(10)
struct PLAYER_CHAPAI_DATA_STRUCT
{
	uint8_t type;			//类型  1:花猪 2: 查叫 0是无
	uint8_t wchaired;		//赢家椅子号
	uint8_t lchaired;		//输家椅子号
	uint8_t res;			//保留
	int32_t goldnum;		//输赢金币
};

//定义发牌规则
typedef enum
{
	SCRT_RAND,	//随机发
	SCRT_MANY,	//哪类牌多就多发哪类的牌
	SCRT_LESS,	//哪类牌少就多发哪类的牌
}SEND_CARD_RULE_TYPE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*		13张消息结构定义			*/
//开局桌子上最大人数和最小人数

#define  __MJ_PLAYER_MAX_NUM13__	(3)
#define  __MJ_PLAYER_MIN_NUM13__	(3)

#define __MAJING_NUM13__	(84)

//每人发的麻将个数
#define  __MJ_NUM13__	(13)
//手上牌总的张数 不算碰或扛的牌
#define  __MJ_TOTAL_NUM13__	(14)

#define  __MAX_OUTPAI_NUM13__ (16)

//消息定义
//所有游戏里面送发给客户端的消息都MainID: MSG_MDM_CGS_GAME   SUBID: SUB_GAME_CGS_GAME_MSG
//收到游戏消息以后要重新解析是什么消息 转换为 CMD_GF_GameFrameHead

//游戏开始发牌消息
#define		_MJ_MSG_GAME_START13_		(131)

//通知所有用户加倍和  玩家发送是否加倍
#define		_MJ_MSG_PLAYER_JIABEI13_		(132)

//广播所有用户选择加倍消息结果
#define		_MJ_MSG_GAME_START_RET13_	(133)

//广播用户换牌消息
#define		_MJ_MSG_PLAYER_HUANPAI13_	(134)

//广播用户使用道具换牌结果消息
#define		_MJ_MSG_PLAYER_HUANPAI13_RET13_	(135)

//玩家发送打牌给服务器 服务器发送打牌给玩家
#define		_MJ_MSG_PLAYER_DAPAI13_	(136)

//通知指定用户能碰扛胡牌等
#define		_MJ_MSG_PLAYER_YAOPAI13_	(137)

//通知指定用户能碰扛牌等
#define		_MJ_MSG_PLAYER_YAOPAI13_RET13_	(138)


//广播用户碰扛胡
#define _MJ_MSG_PLAYER_PGH13_	(139)

//通知指定用户名胡牌
#define		_MJ_MSG_PLAYER_HUPAI13_		(1310)


//其它用户抓牌  广播
#define		_MJ_MSG_PLAYER_ZHUAPAI13_	(1311)
//广播荒牌
#define _MJ_MSG_GAME_HUANGPAI13_	(1312)

//发送给玩家听/明听消息
#define 	_MJ_MSG_GAME_TING13_	(1313)
//玩家出牌消息
#define		_MJ_MSG_PLAYER_CHUAPAI13_	(1314)

//玩家听牌消息 二边互发
#define		_MJ_MSG_PLAYER_TINGPAI13_		(1315)
#define		_MJ_MSG_PLAYER_TINGPAI13_RET13_	(1316)
//翻数不够或过高的提示
#define		_MJ_MSG_HU_PROMPT13_	(1317)


//客户端发送错误的打牌消息过来  服务器把牌发送给当前客户端
#define	_MJ_MSG_PLAYER_SEND_ERROR_PAI13_	(1318)


//结算消息
#define	_MJ_MSG_GAME_JIESHUAN13_	(1319)

//游戏结束
#define		_MJ_MSG_PLAYER_GAME_END13_	(1350)


//用户断线处理  发送相应场景和数据给用户
#define _MJ_GAME_RECONNECT_SCENE13_		(1351)

//S->C	//广播听牌玩家可以胡的牌
//#define		_MJ_MSG_BROADCAST_TINGDATA13_		(1352)

#endif
