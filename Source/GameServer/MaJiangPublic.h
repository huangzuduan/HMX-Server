#ifndef		___DEF_H_DDZ_MAJING_H_DEF__
#define		___DEF_H_DDZ_MAJING_H_DEF__

#include "GamePublic.h"

enum eZoneType
{
	E_ZONE_T_NONE = 0,
	E_ZONE_T_PN = 1,	// 平南
	E_ZONE_T_MZ = 2,	// 梅州
	//E_ZONE_T_GG = 3,	// 贵港
};

enum eCardType
{
	eCardType_Zi	= 0, //东南西北中发白(1~7)
	eCardType_Tong	= 1, //筒(11~19)
	eCardType_Tiao	= 2, //条(21~29)
	eCardType_Wan	= 3, //万(31~39)
	eCardType_Hua	= 4, //梅兰竹菊春夏秋冬(41~48)
};

/*
0xab: a:类型  b:大小
a: 0: 字	1: 筒	2: 条	3：万
*/
//136张牌
const uint16_t g_majing_data[__MAJING_NUM__] =
{
	1,2,3,4,5,6,7,				//eCardType_Zi
	11,12,13,14,15,16,17,18,19,	//eCardType_Tong
	21,22,23,24,25,26,27,28,29,	//eCardType_Tiao
	31,32,33,34,35,36,37,38,39,	//eCardType_Wan
	1,2,3,4,5,6,7,				//eCardType_Zi
	11,12,13,14,15,16,17,18,19,	//eCardType_Tong
	21,22,23,24,25,26,27,28,29,	//eCardType_Tiao
	31,32,33,34,35,36,37,38,39,	//eCardType_Wan
	1,2,3,4,5,6,7,				//eCardType_Zi
	11,12,13,14,15,16,17,18,19,	//eCardType_Tong
	21,22,23,24,25,26,27,28,29,	//eCardType_Tiao
	31,32,33,34,35,36,37,38,39,	//eCardType_Wan
	1,2,3,4,5,6,7,				//eCardType_Zi
	11,12,13,14,15,16,17,18,19,	//eCardType_Tong
	21,22,23,24,25,26,27,28,29,	//eCardType_Tiao
	31,32,33,34,35,36,37,38,39,	//eCardType_Wan
};

//十三幺牌
const uint16_t g_majing_13yao[__13_YAO_NUM__] =
{
	1,2,3,4,5,6,7,11,19,21,29,31,39,
};


//花牌4
const uint16_t g_majing_hua_4[__HUA_NUM_4__] =
{
	41,42,43,44,
};

//花牌8
const uint16_t g_majing_hua_8[__HUA_NUM_8__] =
{
	41,42,43,44,45,46,47,48,
};

struct stEventPai
{
	uint16_t usEventType;
	uint16_t usPai;
	stEventPai()
	{
		usEventType = 0;
		usPai = 0;
	}
};
typedef std::vector<stEventPai> vecEventPai;

struct stCheckPai
{
	uint16_t usPai;
	uint16_t usNum;
	stCheckPai()
	{
		usPai = 0;
		usNum = 0;
	}
};
typedef std::vector<stCheckPai> vecCheckPai;




#endif
