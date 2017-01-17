#include "HelpTools_PCH.h"
#include "StockCrawl.h"


extern DbConnectsMgr* gDbServerMgr;

StockCrawl::StockCrawl(void)
{
}

StockCrawl::~StockCrawl(void)
{
}

void StockCrawl::UpdaeStockInfo()
{

// 600000
// 002000
	for (int32 i = 0; i < 10; i++)
	{
		std::ostringstream ss;
		std::ostringstream ssCode;
		ssCode << "600";
		ssCode << (100 + i);
		ss << "/list=sh";
		ss << ssCode.str();

		std::string reponse;
		if (HttpGet("hq.sinajs.cn", ss.str().c_str(), reponse) == 0)
		{
			StStockInfo stockTmp;
			CreateStockInfo(reponse, stockTmp);
			memcpy(stockTmp.stockid, ssCode.str().c_str(), 6);
			gDbServerMgr->mainDB->ExecInsert("stock_info", FieldInfoDefine, (char*)&stockTmp);
		}
	}

}


void StockCrawl::AddCode(const char* code)
{
	m_vecCode.push_back(code);
}

bool StockCrawl::CreateStockMinute(std::string& i_reponse,StStockMinute& o_stock)
{
	std::vector<std::string> vs;
	my_stringtok(vs,i_reponse,"=");
	if(vs.size() != 2)
	{
		return false;
	}
	std::string& strComent = vs[1];
	strComent = strComent.substr(1,strComent.length() - 2);
	std::vector<std::string> vsComent;
	my_stringtok(vsComent, strComent,",");
	if(vsComent.size() < 32 )
	{
		return false;
	}
	o_stock.onprice = atof(vsComent[1].c_str());
	o_stock.offprice = atof(vsComent[2].c_str());
	o_stock.curprice = atof(vsComent[3].c_str());
	o_stock.topprice = atof(vsComent[4].c_str());
	o_stock.lowprice = atof(vsComent[5].c_str());
	o_stock.buyprice = atof(vsComent[6].c_str());
	o_stock.sellprice = atof(vsComent[7].c_str());
	o_stock.dealnum = atoi(vsComent[8].c_str());
	o_stock.dealmoney = atoi(vsComent[9].c_str());
	o_stock.buy1num = atoi(vsComent[10].c_str());
	o_stock.buy1price = atof(vsComent[11].c_str());
	o_stock.buy2num = atoi(vsComent[12].c_str());
	o_stock.buy2price = atof(vsComent[13].c_str());
	o_stock.buy3num = atoi(vsComent[14].c_str());
	o_stock.buy3price = atof(vsComent[15].c_str());
	o_stock.buy4num = atoi(vsComent[16].c_str());
	o_stock.buy4price = atof(vsComent[17].c_str());
	o_stock.buy5num = atoi(vsComent[18].c_str());
	o_stock.buy5price = atof(vsComent[19].c_str());
	o_stock.sell1num = atoi(vsComent[20].c_str());
	o_stock.sell1price = atof(vsComent[21].c_str());
	o_stock.sell2num = atoi(vsComent[22].c_str());
	o_stock.sell2price = atof(vsComent[23].c_str());
	o_stock.sell3num = atoi(vsComent[24].c_str());
	o_stock.sell3price = atof(vsComent[25].c_str());
	o_stock.sell4num = atoi(vsComent[26].c_str());
	o_stock.sell4price = atof(vsComent[27].c_str());
	o_stock.sell5num = atoi(vsComent[28].c_str());
	o_stock.sell5price = atof(vsComent[29].c_str());
	memcpy(o_stock.date,vsComent[30].c_str(),vsComent[30].length());
	memcpy(o_stock.time,vsComent[31].c_str(),vsComent[31].length());
	return true;
}

bool StockCrawl::CreateStockInfo(std::string& i_reponse,StStockInfo& o_stock)
{
	std::vector<std::string> vs;
	my_stringtok(vs,i_reponse,"=");
	if(vs.size() != 2)
	{
		return false;
	}
	std::string& strComent = vs[1];
	strComent = strComent.substr(1,strComent.length() - 2);
	std::vector<std::string> vsComent;
	my_stringtok(vsComent, strComent,",");
	if(vsComent.size() < 32 )
	{
		return false;
	}
	//memcpy(o_stock.stockid,nCode,6);
	memcpy(o_stock.name,vsComent[1].c_str(),vsComent[1].length());
	return true;
}

void StockCrawl::Start()
{

	// 连接数据库  
	DatabaseInfoOpt& rDbInfo = NetServerOpt::Instance()->GetDatabaseInfo();
	IDbBase* pDb = gDbServerMgr->AddConn(rDbInfo.strHost.c_str(),rDbInfo.strUser.c_str(),rDbInfo.strPass.c_str(),"stock_data");
	if(pDb == NULL)
	{
		printf("Connnect to Database fail!\n");
		return ;
	}

	// 
	std::vector<const char*>::iterator it = m_vecCode.begin();
	std::vector<const char*>::iterator itEnd = m_vecCode.end();
	for (;it != itEnd; ++it)
	{
		const char* nCode = *it;
		std::stringstream ss;
		ss << "/list=";
		if(strcmp(nCode,"600") > -1) //sh
		{
			ss << "sh";
		}
		else if(strcmp(nCode,"002") > -1) // sz
		{
			ss << "sz";
		}
		ss << nCode ;

		std::string reponse;
		if(HttpGet("hq.sinajs.cn",ss.str().c_str(),reponse) == 0)
		{
			StStockMinute stockTmp;
			CreateStockMinute(reponse,stockTmp);
			pDb->ExecInsert("stock_minute",FieldMinuteDefine,(char*)&stockTmp);
		}
	}

}

void StockCrawl::OnEnd()
{

}

int32 StockCrawl::HttpGet(const char* host,const char* pathArgs,std::string& o_reponse)
{
	try
	{
		boost::asio::io_service io_service;
		// Get a list of endpoints corresponding to the server name.
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(host, "http");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		// Try each endpoint until we successfully establish a connection.
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET "<< pathArgs <<" HTTP/1.0\r\n";
		request_stream << "Host: " << host << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		// Read the response status line. The response streambuf will automatically
		// grow to accommodate the entire line. The growth may be limited by passing
		// a maximum size to the streambuf constructor.
		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");
		// Check that response is OK.
		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			std::cout << "Invalid response\n";
			return 1;
		}
		if (status_code != 200)
		{
			std::cout << "Response returned with status code " << status_code << "\n";
			return 1;
		}

		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Process the response headers.
		std::string header;
		while (std::getline(response_stream, header) && header != "\r")
			std::cout << header << "\n";
		std::cout << "\n";

		// Read until EOF, writing data to output as we go.
		boost::system::error_code error;
		while (boost::asio::read(socket, response,
			boost::asio::transfer_at_least(1), error))
		{
			//std::cout << &response;
		}

		if (error != boost::asio::error::eof)
			throw boost::system::system_error(error);

		int size = response.size();
		char* buffer = new char[size + 1];
		response.sgetn(buffer,size);
		buffer[size] = '0';
		o_reponse.append(buffer);
		std::cout << o_reponse.c_str() << "\n";;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
		return -1;
	}

	return 0;

}