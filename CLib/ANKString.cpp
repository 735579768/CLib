#include "ANKString.h"
namespace Ainiku {
	/**
	*C++多字节与宽字节间的转换(wchar_t与char转换)
	使用方法
	WCHAR* wc=findData.cFileName;
	ANKString u;
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
	ANKString::ANKString()
		:m_char(NULL)
		, m_wchar(NULL)
	{
	}
	ANKString::ANKString(const ANKString& ankstr) {
		m_char = ankstr.m_char;
	}
	ANKString::ANKString(char* c)
	{
		m_char = c;
	}
	ANKString::ANKString(std::string str)
	{
		ANKString(str.c_str());
	}
	ANKString::ANKString(const char* c)
	{
		m_char = new char[strlen(c) + 1];
		strcpy(m_char, c);
	}
	ANKString::ANKString(CString str)
	{
	#ifdef _UNICODE
			m_char = WcharToChar(str.GetBuffer(0));
	#else
			m_char = (char*)str.GetBuffer(0);
	#endif
	}
	ANKString::~ANKString()
	{
		Release();
	}
	char* ANKString::WcharToChar(wchar_t* wc)
	{
		//Release();
		int len = WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), NULL, 0, NULL, NULL);
		m_char = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		return m_char;
	}
	wchar_t* ANKString::CharToWchar(char* c)
	{
		//Release();
		int len = MultiByteToWideChar(CP_ACP, 0, c, strlen(c), NULL, 0);
		m_wchar = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, c, strlen(c), m_wchar, len);
		m_wchar[len] = '\0';
		return m_wchar;
	}
	void ANKString::Release()
	{
		if (m_char)
		{
			delete[] m_char;
			m_char = NULL;
		}
		if (m_wchar)
		{
			delete[] m_wchar;
			m_wchar = NULL;
		}
	}
	char* ANKString::getChar() {
		return m_char;
	}
	wchar_t* ANKString::getWChar() {
		m_wchar = CharToWchar(m_char);
		return m_wchar;
	}
	ANKString* ANKString::append(const char* c) {
		char* tembuff = new char[strlen(c) + 1];
		strcpy(tembuff, c);
		strcat(m_char, tembuff);
		delete[] tembuff;
		tembuff = NULL;
		return this;
	}
	//char*赋值给对象
	ANKString& ANKString::operator+=(char*  c){
		strcat(m_char,c);
		return *this;
	}
	ANKString& ANKString::operator+=(ANKString*  anks) {
		strcat(m_char,anks->m_char);
		return *this;
	}
	ANKString& ANKString::operator+=(const char* c) {
		char* tembuff = new char[strlen(c) + 1];
		strcpy(tembuff, c);
		strcat(m_char,tembuff);
		delete[] tembuff;
		tembuff = NULL;
		return *this;
	}
	ANKString& ANKString::operator+=(CString str) {
		#ifdef _UNICODE
				strcat(m_char,WcharToChar(str.GetBuffer(0)));
		#else
				strcat(m_char,(char*)str.GetBuffer(0));
		#endif
		return *this;
	}
	//char*赋值给对象
//	ANKString ANKString::operator=(char*  c) {
//		strcat(m_char, c);
//		return *this;
//	}
//	ANKString ANKString::operator=(ANKString*  anks) {
//		strcat(m_char, anks->m_char);
//		return *this;
//	}
//	ANKString ANKString::operator=(const char* c) {
//		m_char = new char[strlen(c) + 1];
//		return *this;
//	}
//	ANKString ANKString::operator=(const ANKString ankstr) {
//		if (ankstr.m_char != m_char) {
//			m_char = new char[strlen(ankstr.m_char) + 1];
//			strcpy(m_char,ankstr.m_char);
//		}
//		return *this;
//	}
//	ANKString ANKString::operator=(CString str) {
//#ifdef _UNICODE
//		strcpy(m_char, WcharToChar(str.GetBuffer(0)));
//#else
//		strcpy(m_char, (char*)str.GetBuffer(0));
//#endif
//		return *this;
//	}
}