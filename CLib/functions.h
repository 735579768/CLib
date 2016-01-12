#ifndef __LIB_FUNCTIONS_H__
#define __LIB_FUNCTIONS_H__
#pragma once
#include "stdafx.h"
#include <iostream>
namespace Ainiku {
	using namespace std;
	AINIKU_API char* postUrl();
	AINIKU_API CString getUrl(CString url);
	AINIKU_API CString getUrl2(CString url);
	AINIKU_API wstring string2Wstring(string sToMatch);
	AINIKU_API string wstring2string(wstring sToMatch);
	AINIKU_API char* WcharToChar(wchar_t* wc);
	AINIKU_API wchar_t* CharToWchar(char* c);
	/*���ַ�������߽�ȡn���ַ�*/
	AINIKU_API char * left(char *dst, char *src, int n);
	/*���ַ������м��ȡn���ַ�*/
	AINIKU_API char * mid(char *dst, char *src, int n, int m); /*nΪ���ȣ�mΪλ��*/
	/*���ַ������ұ߽�ȡn���ַ�*/
	AINIKU_API char * right(char *dst, char *src, int n);
	AINIKU_API unsigned char ToHex(unsigned char x);
	AINIKU_API unsigned char FromHex(unsigned char x);
	AINIKU_API std::string UrlEncode(const std::string& str);
	AINIKU_API std::string UrlDecode(const std::string& str);


}
#endif