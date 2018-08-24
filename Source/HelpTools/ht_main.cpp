#include <fstream>
#include <string>
#include <iostream>
#include "SrvEngine.h"
#include "DBConnection.h"
#include "LiuhecaiMgr.h"
#include "FileSystem.h"


// 读取次数，存放到数据库中
int main(int argc, const char * argv[])
{

	//获取目录名

	//构造类对象
	CFileSystem statdir;

	//设置要遍历的目录
	if (!statdir.SetInitDir("F:\\wwwroot\\liuhecai\\资料"))
	{
		puts("目录不存在。");
		return 0;
	}

	//开始遍历
	statdir.BeginBrowse("正版*.*");
	printf("文件总数: %d\n子目录总数:%d\n", statdir.GetFileCount(), statdir.GetSubdirCount());

	//LiuhecaiMgr* liuMgr = new LiuhecaiMgr();
	//liuMgr->DoSomethings();
	return 0;
}



