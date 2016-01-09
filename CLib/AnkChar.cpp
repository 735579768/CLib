#include "AnkChar.h"
namespace Ainiku {
	/**
	 *C++多字节与宽字节间的转换(wchar_t与char转换)
	 使用方法
	 WCHAR* wc=findData.cFileName;
	 CAnkChar u;
	 char* c=u.WcharToChar(wc);
	 cout<<c<<endl;
	 */
	/////////////////////////////////////////////////////////////////////////////////////    
	/*字符类型        wchar_t     char
	/*获取字符长度    wcslen()    strlen()
	/*连接两个字符串  wcscat()    strcpy()
	/*复制字符串      wcscpy()    strcpy()
	/*比较两个字符串  wcscmp()    strcmp()
	/*具体参数详见www.linuxidc.com*/
	////////////////////////////////////////////////////////////////////////////////////    
	CAnkChar::CAnkChar()
		:m_char(NULL)
		, m_wchar(NULL)
	{
	}
	CAnkChar::~CAnkChar()
	{
		Release();
	}
	char* CAnkChar::WcharToChar(wchar_t* wc)
	{
		Release();
		int len = WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), NULL, 0, NULL, NULL);
		m_char = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		return m_char;
	}
	wchar_t* CAnkChar::CharToWchar(char* c)
	{
		Release();
		int len = MultiByteToWideChar(CP_ACP, 0, c, strlen(c), NULL, 0);
		m_wchar = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, c, strlen(c), m_wchar, len);
		m_wchar[len] = '\0';
		return m_wchar;
	}
	void CAnkChar::Release()
	{
		if (m_char)
		{
			delete m_char;
			m_char = NULL;
		}
		if (m_wchar)
		{
			delete m_wchar;
			m_wchar = NULL;
		}
	}
}