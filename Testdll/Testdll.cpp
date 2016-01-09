// Testdll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace Ainiku;
using namespace std;
int main()
{
	//CString str= Ainiku::getUrl("http://www.zhaokeli.com");
	//setlocale(LC_TIME, "chs");
	//cout << wstring2string(str.GetBuffer(0)).c_str() <<endl;
	CAnkLog::getInstance()->write("日志记录");
	getchar();
    return 0;
}

