#ifndef __STOCK_CRAWL_H_
#define __STOCK_CRAWL_H_

#include "Includes.h"
#include "DbIncludes.h"


/*------------------------------------------------------------------
 *
 * @Brief : 股票抓取程序，并抓取到的数据存放在内存和数据库中
 *
 * @Author: hzd 
 * @File  : StockCrawl.h
 * @Date  : 2016/01/03 22:01
 * @Copyright (c) 2016,hzd, All rights reserved.
 *-----------------------------------------------------------------*/
// stock_info
static const dbCol FieldInfoDefine[] = {
	{ "`id`",DB_DWORD,4 },
	{ "`stockid`",DB_STR,50 },
	{ "`name`",DB_STR,50 },
	{ NULL,0,0}
};

// stock_minute
static const dbCol FieldMinuteDefine[] = {
	{ "`stockid`",DB_STR,50 },
	{ "`onprice`",DB_FLOAT,4 },
	{ "`offprice`",DB_FLOAT,4 },
	{ "`curprice`",DB_FLOAT,4 },
	{ "`topprice`",DB_FLOAT,4 },
	{ "`lowprice`",DB_FLOAT,4 },
	{ "`buyprice`",DB_FLOAT,4 },
	{ "`sellprice`",DB_FLOAT,4 },
	{ "`dealnum`",DB_DWORD,4 },
	{ "`dealmoney`",DB_DWORD,4 },
	{ "`buy1num`",DB_DWORD,4 },
	{ "`buy1price`",DB_FLOAT,4 },
	{ "`buy2num`",DB_DWORD,4 },
	{ "`buy2price`",DB_FLOAT,4 },
	{ "`buy3num`",DB_DWORD,4 },
	{ "`buy3price`",DB_FLOAT,4 },
	{ "`buy4num`",DB_DWORD,4 },
	{ "`buy4price`",DB_FLOAT,4 },
	{ "`buy5num`",DB_DWORD,4 },
	{ "`buy5price`",DB_FLOAT,4 },
	{ "`sell1num`",DB_DWORD,4 },
	{ "`sell1price`",DB_FLOAT,4 },
	{ "`sell2num`",DB_DWORD,4 },
	{ "`sell2price`",DB_FLOAT,4 },
	{ "`sell3num`",DB_DWORD,4 },
	{ "`sell3price`",DB_FLOAT,4 },
	{ "`sell4num`",DB_DWORD,4 },
	{ "`sell4price`",DB_FLOAT,4 },
	{ "`sell5num`",DB_DWORD,4 },
	{ "`sell5price`",DB_FLOAT,4 },
	{ "`date`",DB_STR,50 },
	{ "`time`",DB_STR,50 },
	{ NULL,0,0}
};

#pragma pack(push,1)


struct StStockInfo
{
	int32 id;
	char stockid[50];
	char name[50];
	StStockInfo()
	{
		id = 0;
		memset(stockid,0,sizeof(stockid));
		memset(name,0,sizeof(name));
	}
};

struct StStockMinute
{
	char stockid[50];
	float onprice;
	float offprice;
	float curprice;
	float topprice;
	float lowprice;
	float buyprice;
	float sellprice;
	int32 dealnum;
	int32 dealmoney;
	int32 buy1num;
	float buy1price;
	int32 buy2num;
	float buy2price;
	int32 buy3num;
	float buy3price;
	int32 buy4num;
	float buy4price;
	int32 buy5num;
	float buy5price;
	int32 sell1num;
	float sell1price;
	int32 sell2num;
	float sell2price;
	int32 sell3num;
	float sell3price;
	int32 sell4num;
	float sell4price;
	int32 sell5num;
	float sell5price;
	char date[50];
	char time[50];
	StStockMinute()
	{
		onprice = offprice = curprice = topprice = lowprice =  0;
		buyprice = sellprice = 0;
		dealnum = dealmoney = buy1num = 0;
		buy1num = buy2num = buy3num = buy4num = buy4num = 0;
		buy1price = buy2price = buy3price = buy4price = buy5price = 0;
		memset(stockid,0,50);
		memset(date,0,50);
		memset(time,0,50);
	}
};

#pragma pack(pop)

class StockCrawl : public BaseSingle<StockCrawl>
{
public:
	StockCrawl(void);
	~StockCrawl(void);

	void UpdaeStockInfo(); 
	int32 HttpGet(const char* host,const char* path,std::string& o_reponse);
	void AddCode(const char* code); // 添加要抓取的股票代码 
	void Start(); // 开始抓取 
	void OnEnd(); // 抓取完毕 

private:

	bool CreateStockInfo(std::string& i_reponse,StStockInfo& o_stock);
	bool CreateStockMinute(std::string& i_reponse,StStockMinute& o_stock);

private:

	std::vector<const char*> m_vecCode; // 股票数据 
	
};


#endif


