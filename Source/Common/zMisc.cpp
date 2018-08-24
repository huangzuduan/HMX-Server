
#include "SrvEngine.h"

namespace DareDef
{
  /// 状态描述
  char str_state[9][20]={"DARE_READY","DARE_READY_QUESTION","DARE_READY_ACTIVE","DARE_RETURN_GOLD",
    "DARE_ACTIVE","DARE_DATAPROCESS","DARE_READY_OVER","DARE_WAIT_BOUNTY","DARE_OVER"};

  char str_type[7][30] = {"UNION_DARE","SCHOOL_DARE","SEPT_DARE","SEPT_NPC_DARE","UNION_CITY_DARE","COUNTRY_FORMAL_DARE","COUNTRY_FORMAL_ANTI_DARE"};

}

namespace QuizDef
{
  /// 状态描述
  char str_state[9][30]={"QUIZ_READY","QUIZ_READY_QUESTION","QUIZ_SEND_QUESTION","QUIZ_ACTIVE_QUESTION",
    "QUIZ_END_QUESTION","QUIZ_READY_OVER","QUIZ_READ_SORT","QUIZ_RETURN_GOLD","QUIZ_OVER"};
  char str_type[2][20] = {"WORLD_QUIZ","PERSONAL_QUIZ"};

}

namespace H
{
	volatile uint64_t qwGameTime = 0;

	zLogger *logger = NULL;

	zProperties global;

	/**
	* \brief 初始化一些全局变量
	*
	*/
	//static void initGlobal()  __attribute__ ((constructor));
	static void initGlobal();
	void initGlobal()
	{
		global["threadPoolClient"] = "512";
		global["threadPoolServer"] = "2048";
		global["server"] = "127.0.0.1";
		global["port"] = "10000";
		global["ifname"] = "127.0.0.1";
		global["mysql"] = "mysql://zebra:zebra@127.0.0.1:3306/zebra";
		global["log"] = "error";
	}
	/**
	* \brief 释放一些全局变量
	*
	*/
	//static void finalGlobal() __attribute__ ((destructor));
	static void finalGlobal();
	void finalGlobal()
	{
		if (NULL != logger) { delete (logger); (logger) = NULL; }
	}
};

//随机产生min~max之间的数字，包裹min和max
int randBetween(int min,int max)
{
	srand((unsigned)time(NULL));
	if (min == max)
		return min;
	else if (min > max)
		return max + (int)(((double)min - (double)max + 1.0) * rand() / (RAND_MAX + 1.0));
	else
		return min + (int)(((double)max - (double)min + 1.0) * rand() / (RAND_MAX + 1.0));
}

//获取几分之的几率
bool selectByOdds(const DWORD upNum,const DWORD downNum)
{
  DWORD m_rand;
  if (downNum < 1) return false;
  if (upNum < 1) return false;
  if (upNum > downNum - 1) return true;
  m_rand = 1 + (DWORD) ((double)downNum * rand() / (RAND_MAX + 1.0));
  return (m_rand <= upNum);
}

//获取几分之几的几率
bool selectByt_Odds(const odds_t &odds)
{
  return selectByOdds(odds.upNum,odds.downNum);
}

//获取百分之的几率
bool selectByPercent(const DWORD percent)
{
  return selectByOdds(percent,100);
}

//获取万分之的几率
bool selectByTenTh(const DWORD tenth)
{
  return selectByOdds(tenth,10000);
}

//获取十万分之的几率
bool selectByLakh(const DWORD lakh)
{
  return selectByOdds(lakh,100000);
}

//获取亿分之之的几率
bool selectByOneHM(const DWORD lakh)
{
  return selectByOdds(lakh,100000000);
}

//获取当前时间字符串，需要给定格式
void getCurrentTimeString(char *buffer,const int bufferlen,const char *format)
{
  time_t now;
  time(&now);
  strftime(buffer,bufferlen,format,localtime(&now));
}

char *getTimeString(time_t t,char *buffer,const int bufferlen,const char *format)
{
  strftime(buffer,bufferlen,format,localtime(&t));
  return buffer;
}

char *getTimeString(time_t t,char *buffer,const int bufferlen)
{
  return getTimeString(t,buffer,bufferlen,"%C/%m/%d %T");
}

