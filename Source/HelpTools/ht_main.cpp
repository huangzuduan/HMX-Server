#include "HelpTools_PCH.h"
#include "StockCrawl.h"


/*
*
*  Detail: 程序主入口 936字符 
*
*  Created by hzd 2014-11-28
*
*/

char SQL_BUFFER[ MAX_SQL_BUFFER ];

DbConnectsMgr* gDbServerMgr = &DbConnectsMgr::getMe(); // db 

bool gIsRun = true;

int HttpGet(const char* host,const char* path,std::string& o_reponse);

bool Init();

void CreateNickData(IDbBase* pDb);

void SinaStock(const char* nCode);

int main(int argc, const char * argv[])
{

	//::protobuf::Character charter;
	//charter.set_char_id(100);

	//int32 bytesize = 0;
	//char bytes[1024];
	//memset(bytes, 0, sizeof(bytes));
	//bytesize = charter.ByteSize();
	//charter.SerializeWithCachedSizesToArray((::google::protobuf::uint8*)bytes);

	//::google::protobuf::io::CodedInputStream inputChar((::google::protobuf::uint8*)bytes,bytesize);

	//::protobuf::Character charter2;
	//charter2.MergePartialFromCodedStream(&inputChar);

	//printf("charid=%lld\n",charter2.char_id());

	// 初始化服务器所都要准备好的数据 
	bool bResult = Init();

	if(!bResult)
	{
		//FLOG_INFO("Init Fail");
		ASSERT(0);
		return 0;
	}

	return 0;
}

#pragma pack(push,1)

struct MixNumber
{
	int32 type;
	int64 value;
};

#pragma pack(pop)

bool Init()
{
	bool bResult = NetServerOpt::Instance()->LoadServerConfig("ht_cfg.xml",ESERVER_TYPE_DP);
	if(!bResult)
	{
		printf("Load cfg fail\n");
		return false;
	}

	// 连接数据库  
	DatabaseInfoOpt& rDbInfo = NetServerOpt::Instance()->GetDatabaseInfo();
	IDbBase* pDb = gDbServerMgr->AddConn(rDbInfo.strHost.c_str(),rDbInfo.strUser.c_str(),rDbInfo.strPass.c_str(),rDbInfo.strDbname.c_str());
	if(pDb == NULL)
	{
		printf("Connnect to Database fail!\n");
		return false;
	}

	//CreateNickData(pDb);

	static const dbCol count_define[] = {
		{ "`type`",DB_DWORD,sizeof(int32) },
		{ "`value`",DB_QWORD,sizeof(int64) },
		{ "`time`",DB_DWORD,sizeof(int32) },
		{ "`name`",DB_STR,32 },
		{ NULL,0,0}
	};

	//DbRecordSet recordset;
	//pDb->ExecSelect("mixitem_number_info",count_define,NULL,NULL,recordset);
	//for (int32 i = 0; i < recordset.CountRecord();++i)
	//{
	//	const MixNumber* num = static_cast<const MixNumber*>(recordset.GetRecordData(i));
	//	int32 aa = 1;
	//}

#pragma pack(push,1)

	struct StAAInsert
	{
		int32 nType;
		int64 nValue;
		int32 nTime;
		char name[32];
		StAAInsert()
		{
			memset(name,0,32);
		}
	};
#pragma pack(pop)

	// 本页面是GBK编码，所以需要转码，要不要转码，根据自己的实际情况来决定 
	//StAAInsert a;
	//a.nType = 7;
	//a.nValue = 10;
	//a.nTime = 1300001;

	//char arrUtf8[32];
	//memset(arrUtf8,0,32);
	//GBKToUTF8("中国",arrUtf8,32);
	//arrUtf8[31] = '\0';
	//memcpy(a.name,arrUtf8,32);

	//uint64 nID = pDb->ExecInsert("mixitem_number_info",count_define,(char*)&a);
	//std::string reponse;
	//	int32 n = HttpGet("hq.sinajs.cn","/list=sh601006",reponse);


	// 查出stock_info表中所有的股票代码，再遍历每分钟去检查 

	//SinaStock("601006");

	StockCrawl::Instance()->Start();
	StockCrawl::Instance()->UpdaeStockInfo();

	return true;

}

void CreateNickData(IDbBase* pDb)
{
	std::string arrXing[] = {"李","王","张","刘","陈","杨","赵","欧阳","上官","西门"};
	int32 nXingSize = sizeof(arrXing) / sizeof(arrXing[0]);

	std::string arrMing[] = {"辰逸","浩宇","瑾瑜","皓轩","致远","文博","英杰","貌才","雨泽","文昊",\
		"雅静","惠茜","梦璐","漫妮","语嫣","倩雪","灵芸","茹雪","美琳","莉姿"};
	int32 nMingSize = sizeof(arrMing) / sizeof(arrMing[0]);

	// 构建名字加入到数据库中 
	for (int32 i = 0 ; i < nXingSize; ++i)
	{
		for (int32 j = 0; j < nMingSize; ++j)
		{
			std::stringstream strName;
			strName << arrXing[i] << arrMing[j];
			char arrUtf8[32];
			memset(arrUtf8,0,32);
			GBKToUTF8(strName.str().c_str(),arrUtf8,32);
			arrUtf8[31] = '\0';
			memset(SQL_BUFFER,0,MAX_SQL_BUFFER);
			SPRINTF(SQL_BUFFER,"INSERT INTO `swa_data`.`names_info` (`name`) VALUES ('%s');",arrUtf8);
			SQL_BUFFER[ MAX_SQL_BUFFER - 1 ] = '\0';
			pDb->ResultSQL(SQL_BUFFER);
		}
	}

}

void SinaStock(const char* nCode)
{



}


