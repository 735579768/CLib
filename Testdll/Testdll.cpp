// Testdll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace Ainiku;
using namespace std;
int main()
{
	CString str= Ainiku::getUrl("http://www.zhaokeli.com");
	setlocale(LC_TIME, "chs");
	cout << wstring2string(str.GetBuffer(0)).c_str() <<endl;
	wchar_t ch1[50] = L"abc";
	char ch2[50] = "abc";
	printf("%d",wcslen(ch1));
	printf("%d", strlen(ch2));
	getchar();
    return 0;
}

