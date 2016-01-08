// CLib.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "CLib.h"


// 这是导出变量的一个示例
CLIB_API int nCLib=0;

// 这是导出函数的一个示例。
CLIB_API int fnCLib(void)
{
    return 42;
}
CLIB_API char* echo() {
	return "这个是输出的内容";
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 CLib.h
CCLib::CCLib()
{
    return;
}
