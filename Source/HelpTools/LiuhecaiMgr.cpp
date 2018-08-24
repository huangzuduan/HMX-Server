#include "LiuhecaiMgr.h"



LiuhecaiMgr::LiuhecaiMgr():m_pDbConn(NULL), m_nYear(0), m_nType(0)
{
	m_pXml = new zXMLParser();
}


LiuhecaiMgr::~LiuhecaiMgr()
{
}

void LiuhecaiMgr::DoSomethings()
{
	if (m_pDbConn == NULL)
	{
		if (!ConnectDb())
		{
			ASSERT(0);
			return;
		}
	}

	//Load(TYPE_OPEN, 2017, "F:\\wwwroot\\liuhecai\\资料\\开奖记录\\2017年(鸡年)开奖记录(共154期).txt");
	//Load(TYPE_OPEN, 2016, "F:\\wwwroot\\liuhecai\\资料\\开奖记录\\2016年(猴年)开奖记录(共151期).txt");
	//Load(TYPE_OPEN, 2015, "F:\\wwwroot\\liuhecai\\资料\\开奖记录\\2015年(羊年)开奖记录(共152期).txt");
	//Load(TYPE_OPEN, 2014, "F:\\wwwroot\\liuhecai\\资料\\开奖记录\\2014年(马年)开奖记录(共152期).txt");
	//Load(TYPE_OPEN, 2013, "F:\\wwwroot\\liuhecai\\资料\\开奖记录\\2013年(蛇年)开奖记录(共152期).txt");
	//Load(TYPE_OPEN, 2012, "F:\\wwwroot\\liuhecai\\资料\\开奖记录\\2012年(龙年)开奖记录(共152期).txt");
	//Load(TYPE_OPEN, 2011, "F:\\wwwroot\\liuhecai\\资料\\开奖记录\\2011年(兔年)开奖记录(共154期).txt");
	//Load(TYPE_OPEN, 2010, "F:\\wwwroot\\liuhecai\\资料\\开奖记录\\2010年(虎年)开奖记录(共152期).txt");
	//Load(TYPE_TIANJISI, 2017, "F:\\wwwroot\\liuhecai\\资料\\特码诗\\天机诗.txt");
	//Load(TYPE_FUZUTIANSHU, 2017, "F:\\wwwroot\\liuhecai\\资料\\特码诗\\香港佛祖天書.txt");
	//Load(TYPE_NAOJINJIZHUANWAN, 2017, "F:\\wwwroot\\liuhecai\\资料\\特码诗\\脑筋急转弯.txt");
	//Load(TYPE_TEMASHI, 2017, "F:\\wwwroot\\liuhecai\\资料\\特码诗\\特码诗.txt");
	Load(TYPE_BAIXIAOJIE, 2017, "F:\\wwwroot\\liuhecai\\资料\\特码诗\\白姐正版先锋诗.txt");
	Load(TYPE_BAIDAJIE, 2017, "F:\\wwwroot\\liuhecai\\资料\\特码诗\\百大姐半句玄機诗.txt");
	Load(TYPE_JINGZHUI7WEI, 2017, "F:\\wwwroot\\liuhecai\\资料\\特码诗\\精准七尾.txt");
	Load(TYPE_ZENGSHIDONGWU, 2017, "F:\\wwwroot\\liuhecai\\资料\\特码诗\\曾女士成语动物.txt");
}

bool LiuhecaiMgr::ConnectDb()
{
	unsigned int readtimeout = 10;
	unsigned int writetimeout = 10;
	unsigned int conntimeout = 10;
	m_pDbConn = new db::DBConnection();
	m_pDbConn->setReadTimeout(readtimeout);
	m_pDbConn->setWriteTimeout(writetimeout);
	m_pDbConn->setConnectTimeout(conntimeout);
	bool ret = m_pDbConn->connect("127.0.0.1", "root", "123456", "liuhecai", 3306);
	return ret;
}

bool LiuhecaiMgr::Load(int32_t type,int32_t year, const char* cstrFileName)
{
	m_cFileStream.open(cstrFileName, std::ios::in);
	if (!m_cFileStream.is_open() ||
		m_cFileStream.fail() ||
		m_cFileStream.bad())
	{
		printf("[ERROR]:file open fail!\n");
		return false;
	}
	printf("正处理处理文件:%s\n", cstrFileName);
	m_nYear = year;
	m_nType = type;
	NextRow();
	return true;
}

bool LiuhecaiMgr::NextRow()
{
	for (;;)
	{
		if (std::getline(m_cFileStream, m_strLine))
		{
			if (m_strLine.empty())
			{
				return false;
			}
			else
			{
				if (strlen(m_strLine.c_str()) == 0 || strcmp(m_strLine.c_str(), "\n") == 0 || strcmp(m_strLine.c_str(), "\t") == 0 || strcmp(m_strLine.c_str(), "\r") == 0)
				{
					return false;
				}
				AnalyseLine(m_strLine);
			}
			m_strLine.clear();
		}
		else
		{
			m_cFileStream.close();
			return false;
		}
	}

	return true;
}


void LiuhecaiMgr::AnalyseLine(const std::string& i_strLine)
{
	if (m_nType == TYPE_OPEN)
	{
		::liuhc::OpenInfo proto;
		if (m_nYear >= 2010 && m_nYear <= 2017)
		{
			AnalyseLine2010_2017(m_nYear, i_strLine, proto);
		}
		else if (m_nYear >= 2005 && m_nYear <= 2009)
		{
			AnalyseLine2005_2009(m_nYear, i_strLine, proto);
		}
		else
		{
			return;
		}

		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_open", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_TIANJISHI)
	{
		::liuhc::TianJiShiInfo proto;
		TianJiShi(i_strLine,proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_tianjishi", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_FUZUTIANSHU)
	{
		::liuhc::FuzutianshuInfo proto;
		HKfuzutianshu(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_fuzutianshu", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_NAOJINJIZHUANWAN)
	{
		::liuhc::NaojinjizhuanwanInfo proto;
		NaoJingJiZhuanWan(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_naojinjizhuanwan", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_TEMASHI)
	{
		::liuhc::TemashiInfo proto;
		Temashi(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_temashi", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_BAIXIAOJIE)
	{
		::liuhc::BaiXiaoJieInfo proto;
		BaiXiaoJieXianFeng(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_baixiaojie", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_BAIDAJIE)
	{
		::liuhc::BaiDaJieInfo proto;
		BaiDaJieBanJu(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_baidajie", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_JINGZHUI7WEI)
	{
		::liuhc::JingZhui7WeiInfo proto;
		JingZhui7Wei(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_jingzhui7wei", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_ZENGSHIDONGWU)
	{
		::liuhc::ZengshiChengYuDongWuInfo proto;
		ZhengShiChengYuDongWu(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_zengshichengyudongwu", proto);
		if (ret == 0)
		{
			return;
		}
	}
	

	//2004
	//2004年01月20日007期:05-32-28-31-09-06 特玛:19(牛)
	//2004年01月27日008期:40-41-13-18-10-29 特玛:04(蛇)(2004年新生宵)

	//2003
	//01月23日丙申火第007期36-06-38-27-14-23特49。总分193。马 
	//01月28日辛丑土第008期30-10-25-46-05-41特48。总分205。羊新春金多宝
	//04月15日戊午火第030期37-39-15-28-27-09特33。总分188。猪复活节金多宝

	//2002
	//07月02日(辛未土日)052期04-26-31-33-36-38特28。 总分196。 
	//07月04日(癸酉金日)053期05-32-34-38-39-49特08。 总分205。(开始增加48、49号)

	//2001
	//2001年01月02日(乙丑金日)001期13-20-35-38-44-45特05。 总分200。

	//2000
	//2000年10月17日092期:44-41-18-12-09-02特24。 总分:150。
}


void LiuhecaiMgr::AnalyseLine2010_2017(int32_t year, const std::string& i_strLine, ::liuhc::OpenInfo& proto)
{
	//2017 085期:36-04-06-27-47-49T03羊/蓝/金
	//2016 151期:09-08-28-17-15-12T33鼠/绿/金
	//2015 152期:22-24-11-25-02-12T03蛇/蓝/水
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/.");
	if (vecD.size() >= 10)
	{
		proto.set_year(year);
		proto.set_date(0);
		proto.set_week(0);
		proto.set_qi(atoi(vecD[0].c_str()));
		proto.set_pm1(atoi(vecD[1].c_str()));
		proto.set_pm2(atoi(vecD[2].c_str()));
		proto.set_pm3(atoi(vecD[3].c_str()));
		proto.set_pm4(atoi(vecD[4].c_str()));
		proto.set_pm5(atoi(vecD[5].c_str()));
		proto.set_pm6(atoi(vecD[6].c_str()));
		proto.set_tema(atoi(vecD[7].c_str()));
		proto.set_tema_shangx((char*)m_pXml->charConv((BYTE*)(vecD[7].c_str() + 2), "GBK", "UTF-8"));
		proto.set_tema_bose((char*)m_pXml->charConv((BYTE*)vecD[8].c_str(), "GBK", "UTF-8"));
		proto.set_tema_wuxing((char*)m_pXml->charConv((BYTE*)vecD[9].c_str(), "GBK", "UTF-8"));

		if (proto.tema() % 2 == 1)
			proto.set_tema_dans((char*)m_pXml->charConv((BYTE*)"单", "GBK", "UTF-8"));
		else
			proto.set_tema_dans((char*)m_pXml->charConv((BYTE*)"双", "GBK", "UTF-8"));
	}
	else
	{
		printf("数据有误:%s\n", i_strLine.c_str());
	}
}

void LiuhecaiMgr::AnalyseLine2005_2009(int32_t year, const std::string& i_strLine, ::liuhc::OpenInfo& proto)
{
	//2009
	//010期01月25星期日:44 40 47 04 12 19 特49鼠绿单土
	//011期01月27星期二:42 13 07 21 17 45 特36虎蓝双水 新肖
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/ ");

	proto.set_year(2017);
	proto.set_date(0);
	proto.set_week(0);
	proto.set_qi(atoi(vecD[0].c_str()));
	proto.set_pm1(atoi(vecD[1].c_str()));
	proto.set_pm2(atoi(vecD[2].c_str()));
	proto.set_pm3(atoi(vecD[3].c_str()));
	proto.set_pm4(atoi(vecD[4].c_str()));
	proto.set_pm5(atoi(vecD[5].c_str()));
	proto.set_pm6(atoi(vecD[6].c_str()));
	proto.set_tema(atoi(vecD[7].c_str()));
	proto.set_tema_shangx((char*)m_pXml->charConv((BYTE*)(vecD[7].c_str() + 2), "GBK", "UTF-8"));
	proto.set_tema_bose((char*)m_pXml->charConv((BYTE*)vecD[8].c_str(), "GBK", "UTF-8"));
	proto.set_tema_wuxing((char*)m_pXml->charConv((BYTE*)vecD[9].c_str(), "GBK", "UTF-8"));

	if (proto.tema() % 2 == 1)
		proto.set_tema_dans((char*)m_pXml->charConv((BYTE*)"单", "GBK", "UTF-8"));
	else
		proto.set_tema_dans((char*)m_pXml->charConv((BYTE*)"双", "GBK", "UTF-8"));

}

void LiuhecaiMgr::NaoJingJiZhuanWan(const std::string& i_strLine, ::liuhc::NaojinjizhuanwanInfo& proto)
{
	//2015年第018期:林老生大手术后换了一个人工心脏。病好了后, 她的女友却马上提出分手, 为什么会这样 ? -- - 答案 : 没有真心爱她
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/ ");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 8));

		stringstream ss;
		if (vecD.size() >= 2)
			ss << vecD[1];
		if(vecD.size() >= 3)
			ss << vecD[2];
		if (vecD.size() >= 4)
			ss << vecD[3];

		proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::TianJiShi(const std::string& i_strLine, ::liuhc::TianJiShiInfo& proto)
{
	//第001期:暗渡陈仓三六计,一五单门做主彩,送:晨一曲准时唱。
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/ ");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::BaiXiaoJieXianFeng(const std::string& i_strLine, ::liuhc::BaiXiaoJieInfo& proto)
{
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::BaiDaJieBanJu(const std::string& i_strLine, ::liuhc::BaiDaJieInfo& proto)
{
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::HKfuzutianshu(const std::string& i_strLine, ::liuhc::FuzutianshuInfo& proto)
{
	//第112期:马后来羊特玛中, 守株待兔最理智(龙虎蛇羊)
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::Temashi(const std::string& i_strLine, ::liuhc::TemashiInfo& proto)
{
	//第001期:憧憬偏美好,现实击人倒; 沉浮若有备,小舟过惊涛。
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::JingZhui7Wei(const std::string& i_strLine, ::liuhc::JingZhui7WeiInfo& proto)
{
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::ZhengShiChengYuDongWu(const std::string& i_strLine, ::liuhc::ZengshiChengYuDongWuInfo& proto)
{
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}



