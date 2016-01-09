#ifndef __LIB_CLIB_H__
#define __LIB_CLIB_H__
#include "stdafx.h"
// 此类是从 CLib.dll 导出的
namespace Ainiku {
	class AINIKU_API CCLib {
	public:
		CCLib(void);
		// TODO:  在此添加您的方法。
	};

	AINIKU_API char* echo();
}
#endif
