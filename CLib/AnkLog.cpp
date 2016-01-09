#include "AnkLog.h"
namespace Ainiku {
	CAnkLog::CAnkLog() {
		filePath = "./log";
		CAnkLog::m_pInstance = NULL;
	}
	CAnkLog::~CAnkLog() {

	}
	bool CAnkLog::write(char *chr) {
		CAnkLog *log=CAnkLog::getInstance();
		//写日志
		CTime t = CTime::GetCurrentTime();
		CString t_str = t.Format("%Y-%m-%d %H:%M:%S");
		std::ofstream ofs(t_str+".log");//建立ofstream对像。
		ofs.write(chr, strlen(chr));//将数据写入文件
		ofs.close();//关闭ofstream对象。
		return true;
	}
    CAnkLog* CAnkLog::getInstance() {
			if (m_pInstance == NULL)  //判断是否第一次调用  
				m_pInstance = new CAnkLog();
			return m_pInstance;
	}
	void CAnkLog::setPath(char *pfilePath) {
		filePath = pfilePath;
	}
}