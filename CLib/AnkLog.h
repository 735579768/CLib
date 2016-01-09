#pragma once
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