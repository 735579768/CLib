// Testdll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace Ainiku;
using namespace std;
int main()
{
	CString str= Ainiku::getUrl("http://www.ruzhouba.com");
	wcout << (LPCTSTR)str <<endl;
	printf("\S", (LPCTSTR)str);
	cout << Ainiku::echo()<<endl;
	wchar_t ch1[50] = L"abc";
	char ch2[50] = "abc";
	printf("%s",ch1);
	printf("%s", ch1);
	getchar();
    return 0;
}

