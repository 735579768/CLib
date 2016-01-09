#include "AnkLog.h"
namespace Ainiku {
	CAnkLog* CAnkLog::m_pInstance = NULL;
	CAnkLog::CAnkLog() {
		filePath = "";
		CAnkLog::m_pInstance = NULL;
	}
	CAnkLog::~CAnkLog() {

	}
	bool CAnkLog::write(char *chr) {
		CAnkLog *log=CAnkLog::getInstance();
		//д��־
		CTime t = CTime::GetCurrentTime();
		CString t_str1 = t.Format("%Y-%m-%d %H:%M:%S");
		t_str1 += ":  ";
		CString t_str = t.Format("%Y-%m-%d");
		std::ofstream ofs(filePath+t_str+".log",std::ios::app);//����ofstream����
		if (ofs) {
			try {
				ANKString test=t_str1;
				test += chr;
				test += "\n";
				char* tem = test.getChar();
				ofs.write(tem, strlen(tem));//������д���ļ�
				ofs.close();//�ر�ofstream����
			}
			catch (...) {
				
			}
		}

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