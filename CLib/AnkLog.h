#ifndef __LIB_ANKLOG_H__
#define __LIB_ANKLOG_H_
#pragma once
#include "stdafx.h"
#include <fstream>
#include "ANKString.h"
namespace Ainiku {
	class AINIKU_API CAnkLog {
	public:
		static CAnkLog * getInstance();
		bool write(char* chr);
		void setPath(char* pfilePath);
	private:
		static CAnkLog *m_pInstance;
		char *filePath;
		CAnkLog(void);
		~CAnkLog(void);
	};
}
#endif