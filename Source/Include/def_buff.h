#ifndef __DEF_BUFF_H_
#define __DEF_BUFF_H_

#include <vector>
#include "ServerDefine.h"

#define MAX_BUFF_EFFECT_NUM 5

enum EffectAimType
{
	EFFECT_AIM_TYPE_FROM		= 1,	// 施法者 
	EFFECT_AIM_TYPE_TO			= 2,	// 被施法者 
	EFFECT_AIM_TYPE_FROM_RANGE	= 3,	// 施法者范围内 
	EFFECT_AIM_TYPE_TO_RANGE	= 4,	// 被施法者范围内 
};

enum EffectRangeType
{
	EFFECT_RANGE_TYPE_AROUND	= 1,	// 周围 
	EFFECT_RANGE_TYPE_Angle		= 2,	// 夹角 
};

enum BuffEffectType
{
	BUFF_EFFECT_TYPE_NULL,

	BUFF_EFFECT_TYPE_SHOUJI				= 1,	// 受击 
	BUFF_EFFECT_TYPE_JIDAO				= 2,	// 击倒 
	BUFF_EFFECT_TYPE_FUKONG				= 3,	// 浮空 
	BUFF_EFFECT_TYPE_JITUI				= 4,	// 击退 
	BUFF_EFFECT_TYPE_MIWU				= 5,	// 迷雾 
	BUFF_EFFECT_TYPE_CHENMO				= 6,	// 沉默 
	BUFF_EFFECT_TYPE_DINGSHEN			= 7,    // 定身 
	BUFF_EFFECT_TYPE_HUNLUAN			= 8,    // 混乱 
	BUFF_EFFECT_TYPE_XUANYUN			= 9,    // 眩晕 
	BUFF_EFFECT_TYPE_LIUXIE				= 10,    // 流血 
	BUFF_EFFECT_TYPE_HUANMAN			= 11,    // 缓慢 
	BUFF_EFFECT_TYPE_XIYIN				= 12,    // 吸引 
	BUFF_EFFECT_TYPE_KANGSHOUJI			= 13,    // 抗受击 
	BUFF_EFFECT_TYPE_KANGJIDAO			= 14,    // 抗击倒 
	BUFF_EFFECT_TYPE_KANGFUKONG			= 15,    // 抗浮空 
	BUFF_EFFECT_TYPE_KANGMIWU			= 16,    // 抗迷雾 
	BUFF_EFFECT_TYPE_KANGCHENMO			= 17,    // 抗沉默 
	BUFF_EFFECT_TYPE_KANGDINGSHEN		= 18,    // 抗定身 
	BUFF_EFFECT_TYPE_KANGHUNLUAN		= 19,    // 抗混乱 
	BUFF_EFFECT_TYPE_KANGXUANYUN		= 20,    // 抗眩晕 
	BUFF_EFFECT_TYPE_KANGHUANMAN		= 21,    // 抗缓慢 
	BUFF_EFFECT_TYPE_KANGLIUXIE			= 22,    // 抗流血 
	BUFF_EFFECT_TYPE_BAOJILV			= 23,    // 暴击率 
	BUFF_EFFECT_TYPE_SHANBILV			= 24,    // 闪避率 
	BUFF_EFFECT_TYPE_GEDANGLV			= 25,    // 格挡率 
	BUFF_EFFECT_TYPE_MINGZHONGLV		= 26,    // 命中率 
	BUFF_EFFECT_TYPE_BAOJIZHI			= 27,    // 暴击值 
	BUFF_EFFECT_TYPE_GEDANGZHI			= 28,    // 格挡值 
	BUFF_EFFECT_TYPE_WUGONG				= 29,    // 武攻 
	BUFF_EFFECT_TYPE_NEIGONG			= 30,    // 内攻 
	BUFF_EFFECT_TYPE_SHENGMING			= 31,    // 生命 
	BUFF_EFFECT_TYPE_WUFANG				= 32,    // 武防 
	BUFF_EFFECT_TYPE_NEIFANG			= 33,    // 内防 
	BUFF_EFFECT_TYPE_SHENGMINGXIUGUAI	= 34,    // 生命修改 
	BUFF_EFFECT_TYPE_DADUAN				= 35,    // 打断 

	BUFF_EFFECT_TYPE_KANGJITUI			= 36,    // 抗击退 
	BUFF_EFFECT_TYPE_MAX		 		// 最大数量 
};

enum BuffFlag
{
	BUFF_EFFECT_FLAG_MOMENTARY		= 0x00000001,	// 瞬时 
	BUFF_EFFECT_FLAG_REVERSIBLE		= 0x00000002,	// 可逆 
	BUFF_EFFECT_FLAG_STACKABLE		= 0x00000004,	// 可叠加 
	BUFF_EFFECT_FLAG_REPLACEABLE	= 0x00000008,	// 可替代 
	BUFF_EFFECT_FLAG_INTERRUPTIBLE	= 0x00000010,	// 可打断 
	BUFF_EFFECT_FLAG_SAVABLE		= 0x00000020,	// 需要保存 
};

class SceneNpc;
typedef void(*BuffEffectFunc)(SceneNpc* /* 施法者 */, SceneNpc* /* 被施法者 */, EffectAimType/* 目标类型 */, EffectRangeType/* 范围类型 */,
	int32/* 参数 */, int32/* 距离 */, float32/* 角度cos值 */,int32 nEffectNum/* 最多影响数量 */);

struct BuffEffect
{
	BuffEffectType		eType;					// 效果类型 
	//int32				nType;
	int32				nLimitFlag;				// 效果限制使用标记(BuffFlag二进制位运算值) 
	BuffEffectFunc		pCallBack;				// 效果函数 
};

struct BuffData
{
	int32		nBuffID;						// BuffID 
	int32		nLimitFlag;						// 使用标记 
	int32		nLifeTime;						// 生命周期(单位:毫秒) 
	int32		nEffectNum;						// 最多打到的生物体 
	struct Effect
	{
		BuffEffectType		nEffectID;			// 效果ID 
		int32				nProbability;		// 出现概率(0为一定出现) 
		EffectAimType		eAimType;			// 作用对象类型 
		EffectRangeType		eRangeType;			// 作用范围类型 
		int32				nDist;				// 距离 
		float32				fCosAngle;			// 角度(cos值) 
		int32				nParam;				// 参数值 
		int32				nTimePoint;			// 效果生效时间点(单位:毫秒) 
	}	arrEffect[MAX_BUFF_EFFECT_NUM];
};

struct DamageReduce
{
	int32 player_num;
	int32 reduce_param;
};

#endif


