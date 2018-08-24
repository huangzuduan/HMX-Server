#ifndef __LIUHECAI_H_
#define __LIUHECAI_H_

#include "SrvEngine.h"
#include "liuhecai.pb.h"
#include "DBConnection.h"
#include "MysqlProtobufHelper.h"

/*
 * 彩票数据处理类
 *
 */

enum 
{
	TYPE_OPEN = 1,			// 开奖记录
	TYPE_TIANJISHI,			// 天机诗
	TYPE_FUZUTIANSHU,		// 佛祖天书
	TYPE_NAOJINJIZHUANWAN,	//
	TYPE_TEMASHI,
	TYPE_BAIXIAOJIE,
	TYPE_BAIDAJIE,
	TYPE_ZENGSHIDONGWU,
	TYPE_JINGZHUI7WEI,
};

class LiuhecaiMgr
{
public:
	LiuhecaiMgr();
	~LiuhecaiMgr();
	void DoSomethings();

private:
	bool ConnectDb();
	bool Load(int32_t type,int32_t year,const char* cstrFileName);
	bool NextRow();
	void AnalyseLine(const std::string& i_strLine);
	void AnalyseLine2010_2017(int32_t year, const std::string& i_strLine, ::liuhc::OpenInfo& proto);
	void AnalyseLine2005_2009(int32_t year, const std::string& i_strLine, ::liuhc::OpenInfo& proto);

	void NaoJingJiZhuanWan(const std::string& i_strLine, ::liuhc::NaojinjizhuanwanInfo& proto);
	void TianJiShi(const std::string& i_strLine, ::liuhc::TianJiShiInfo& proto);
	void BaiXiaoJieXianFeng(const std::string& i_strLine, ::liuhc::BaiXiaoJieInfo& proto);
	void BaiDaJieBanJu(const std::string& i_strLine, ::liuhc::BaiDaJieInfo& proto);
	void HKfuzutianshu(const std::string& i_strLine, ::liuhc::FuzutianshuInfo& proto);
	void Temashi(const std::string& i_strLine, ::liuhc::TemashiInfo& proto);
	void JingZhui7Wei(const std::string& i_strLine, ::liuhc::JingZhui7WeiInfo& proto);
	void ZhengShiChengYuDongWu(const std::string& i_strLine, ::liuhc::ZengshiChengYuDongWuInfo& proto);

private:

	std::ifstream		m_cFileStream;
	int32_t				m_nYear;
	int32_t				m_nType;
	std::string			m_strLine;
	zXMLParser*			m_pXml;
	db::DBConnection*	m_pDbConn;
};


#endif


