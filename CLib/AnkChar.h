#pragma once
namespace Ainiku {
	class AINIKU_API CAnkChar
	{
	public:
		CAnkChar();
		virtual~CAnkChar();
		char* WcharToChar(wchar_t* wc);//���ֽ�ת���ֽ�    
		wchar_t* CharToWchar(char* c); //���ֽ�ת���ֽ�    
		void Release();//�ͷ���Դ    
	private:
		char* m_char;
		wchar_t* m_wchar;
	};
}
