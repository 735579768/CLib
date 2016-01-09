// CLib.cpp : 定义 DLL 应用程序的导出函数。
//
#include "CLib.h"

namespace Ainiku {
	AINIKU_API char* echo() {
		return "这个是输出的内容";
	}

	// 这是已导出类的构造函数。
	// 有关类定义的信息，请参阅 CLib.h
	CCLib::CCLib()
	{
		return;
	}
}
