#include "stdafx.h"
#include <fstream>
#include "AnkChar.h"
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
			CAnkChar u;
			char* tem = u.WcharToChar(t_str1.GetBuffer(0));
			chr=strcat(tem,chr);
			chr = strcat(chr, "\n");
			ofs.write(chr, strlen(chr));//������д���ļ�
			ofs.close();//�ر�ofstream����
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