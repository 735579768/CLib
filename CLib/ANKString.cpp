#include "ANKString.h"
namespace Ainiku {
	/**
	*C++���ֽ�����ֽڼ��ת��(wchar_t��charת��)
	ʹ�÷���
	WCHAR* wc=findData.cFileName;
	ANKString u;
	char* c=u.WcharToChar(wc);
	cout<<c<<endl;
	*/
	/////////////////////////////////////////////////////////////////////////////////////
	/*�ַ�����        wchar_t     char
	/*��ȡ�ַ�����    wcslen()    strlen()
	/*���������ַ���  wcscat()    strcpy()
	/*�����ַ���      wcscpy()    strcpy()
	/*�Ƚ������ַ���  wcscmp()    strcmp()
	/*����������www.linuxidc.com*/
	////////////////////////////////////////////////////////////////////////////////////
	ANKString::ANKString()
		:m_char(NULL)
		, m_wchar(NULL)
	{
	}
	ANKString::ANKString(const ANKString& ankstr) {
		Release();
		m_char = ankstr.m_char;
	}
	ANKString::ANKString(char* c)
	{
		Release();
		m_char = c;
	}
	ANKString::ANKString(std::string str)
	{
		Release();
		ANKString(str.c_str());
	}
	ANKString::ANKString(const char* c)
	{
		Release();
		m_char = new char[strlen(c) + 1];
		strcpy(m_char, c);
	}
	ANKString::ANKString(CString str)
	{
		Release();
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
		int len = WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), NULL, 0, NULL, NULL);
		m_char = new char[len + 10];
		WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		return m_char;
	}
	wchar_t* ANKString::CharToWchar(char* c)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, c, strlen(c), NULL, 0);
		m_wchar = new wchar_t[len + 10];
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
		int bytelen = strlen(c)  + 10;
		char* tembuff = new char[bytelen];
		strcpy(tembuff,c);
		lianjie(tembuff);
		delete[] tembuff;
		tembuff = NULL;
		return this;
	}
	//char*��ֵ������
	ANKString& ANKString::operator+=(char*  c){
		lianjie(c);
		return *this;
	}
	ANKString& ANKString::operator+=(ANKString*  anks) {
		int bytelen = strlen(anks->m_char) + 10;
		char* tembuff = new char[bytelen];
		strcpy(tembuff, anks->m_char);
		lianjie(tembuff);
		delete[] tembuff;
		tembuff = NULL;
		return *this;
	}
	ANKString& ANKString::operator+=(const char* c) {
		int bytelen = strlen(c) +1;
		char* tembuff = new char[bytelen];
		strcpy(tembuff,c);
		lianjie(tembuff);
		delete[] tembuff;
		tembuff = NULL;
		return *this;
	}
	ANKString& ANKString::operator+=(CString str) {
		int bytelen = 0;
		#ifdef _UNICODE
			char* chr1 = WcharToChar(str.GetBuffer(0));
			lianjie(chr1);
		#else
			lianjie((char*)str.GetBuffer(0));
		#endif
		return *this;
	}
	/**
	 *�����ַ���
	 */
	void ANKString::lianjie(char* c) {
		int bytelen = strlen(c) + strlen(m_char) + 10;
		char* tembuff = new char[bytelen];
		strcpy(tembuff, m_char);
		strcat(tembuff, c);
		//����m_charָ��,�����������������ͷ�
		Release();
		m_char = new char[bytelen];
		strcpy(m_char, tembuff);
		delete[] tembuff;
		tembuff = NULL;
	}
	//char*��ֵ������
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