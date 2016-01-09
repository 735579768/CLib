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
		//д��־
		CTime t = CTime::GetCurrentTime();
		CString t_str = t.Format("%Y-%m-%d %H:%M:%S");
		std::ofstream ofs(t_str+".log");//����ofstream����
		ofs.write(chr, strlen(chr));//������д���ļ�
		ofs.close();//�ر�ofstream����
		return true;
	}
    CAnkLog* CAnkLog::getInstance() {
			if (m_pInstance == NULL)  //�ж��Ƿ��һ�ε���  
				m_pInstance = new CAnkLog();
			return m_pInstance;
	}
	void CAnkLog::setPath(char *pfilePath) {
		filePath = pfilePath;
	}
}