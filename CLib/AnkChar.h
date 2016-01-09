#pragma once
namespace Ainiku {
	class AINIKU_API CAnkChar
	{
	public:
		CAnkChar();
		virtual~CAnkChar();
		char* WcharToChar(wchar_t* wc);//宽字节转单字节    
		wchar_t* CharToWchar(char* c); //单字节转宽字节    
		void Release();//释放资源    
	private:
		char* m_char;
		wchar_t* m_wchar;
	};
}
