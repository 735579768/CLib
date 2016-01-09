#ifndef __LIB_FUNCTIONS_H__
#define __LIB_FUNCTIONS_H__
#pragma once
#include "stdafx.h"
#include <iostream>
using namespace std;
namespace Ainiku {
	AINIKU_API char* postUrl();
	AINIKU_API CString getUrl(CString url);
	AINIKU_API CString getUrl2(CString url);
	AINIKU_API wstring string2Wstring(string sToMatch);
	AINIKU_API string wstring2string(wstring sToMatch);
	AINIKU_API char* wCharToChar(LPWSTR a1);
}
#endif