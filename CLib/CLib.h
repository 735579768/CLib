#ifndef __LIB_CLIB_H__
#define __LIB_CLIB_H__
// 此类是从 CLib.dll 导出的
#include "stdafx.h"
namespace Ainiku {
	class AINIKU_API CCLib {
	public:
		CCLib(void);
		// TODO:  在此添加您的方法。
	};

	AINIKU_API char* echo();
}
#endif
