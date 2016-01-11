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
	ofstream ofs( "test", std::ios::binary);//建立ofstream对像。
	ofs.write("aaa",strlen("aaa"));
	ofs.close();
	ANKString str = "aaabbb我爱你";
	str.replace("b","a");
	str.replace("我爱","你");
	CString chr = "你";
	//查找字符串
	cout << str.find(chr) << endl;
	cout << str.getChar() << endl;
	getchar();
    return 0;
}

