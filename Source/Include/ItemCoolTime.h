//sky 新增物品冷却管理类
#pragma once
#include <zebra/csCommon.h>

#include <zebra/srvEngine.h>

struct SceneUser;
class zObject;

typedef struct stCoolTimeType
{
	DWORD TimeType;  //冷却类型
	QWORD StartTime; //冷却开始时间
};

class CItmeCoolTime
{
public:
	CItmeCoolTime();
	~CItmeCoolTime();

	//冷却管理器(记录拉各个冷却类型的开始时间)
	std::vector<stCoolTimeType> vCoolTimeType;

public:
	//检测该物品是否可以使用(冷却时间已经结束)
	bool IsCoolTimeOver(zObject* obj);
	//向管理器里添加一个冷却类型的冷却开始
	bool AddCoolTimeStar(zObject* obj);
	//初始化管理器
	bool InitCoolTimeType();
};