#ifndef __LIB_CLIB_H__
#define __LIB_CLIB_H__
// �����Ǵ� CLib.dll ������
#include "stdafx.h"
namespace Ainiku {
	class AINIKU_API CCLib {
	public:
		CCLib(void);
		// TODO:  �ڴ�������ķ�����
	};

	extern AINIKU_API int nCLib;

	AINIKU_API int fnCLib(void);
	AINIKU_API char* echo();
}
#endif
