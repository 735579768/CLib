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
	ANKString::ANKString():m_char(NULL),m_wchar(NULL)
	{
	}
	ANKString::ANKString(const ANKString& ankstr) {
		init();
		m_char = ankstr.m_char;
	}
	ANKString::ANKString(char* c)
	{
		init();
		m_char = c;
	}
	ANKString::ANKString(std::string str)
	{
		init();
		ANKString(str.c_str());
	}
	ANKString::ANKString(const char* c)
	{
		init();
		m_char = new char[strlen(c) + 1];
		strcpy(m_char, c);
	}
	ANKString::ANKString(CString str)
	{
		init();
	#ifdef _UNICODE
			char* tem=WcharToChar(str.GetBuffer(0));
			int bytelen = strlen(tem) + 10;
			m_char = new char[bytelen] {0};
			strcpy(m_char,tem);

	#else
			char* tem = (char*)str.GetBuffer(0);
			int bytelen = strlen(tem) + 10;
			m_char = new char[bytelen] {0};
			strcpy(m_char, tem);
	#endif
	}
	void ANKString::init() {
		m_char = NULL;
		m_wchar = NULL;
		m_buff = NULL;
		m_wbuff = NULL;
	}
	ANKString::~ANKString()
	{
		Release();
	}
	char* ANKString::WcharToChar(wchar_t* wc)
	{
		delete[] m_buff;
		m_buff = NULL;
		int len = WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), NULL, 0, NULL, NULL);
		m_buff = new char[len + 10]{0};
		WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), m_buff, len, NULL, NULL);
		m_buff[len] = '\0';
		return m_buff;
	}
	wchar_t* ANKString::CharToWchar(char* c)
	{
		delete[] m_wbuff;
		m_wbuff = NULL;
		int len = MultiByteToWideChar(CP_ACP, 0, c, strlen(c), NULL, 0);
		m_wbuff = new wchar_t[len + 10]{0};
		MultiByteToWideChar(CP_ACP, 0, c, strlen(c), m_wbuff, len);
		m_wbuff[len] = '\0';
		return m_wbuff;
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
		if (m_buff) {
			delete[] m_buff;
			m_buff = NULL;
		}
		if (m_wbuff) {
			delete[] m_wbuff;
			m_wbuff = NULL;
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
		char* tembuff = new char[bytelen] {0};
		strcpy(tembuff,c);
		lianjie(tembuff);
		delete[] tembuff;
		tembuff = NULL;
		return this;
	}
	//char*赋值给对象
	ANKString& ANKString::operator+=(char*  c){
		lianjie(c);
		return *this;
	}
	ANKString& ANKString::operator+=(ANKString  &anks) {
		int bytelen = strlen(anks.m_char) + 10;
		char* tembuff = new char[bytelen] {0};
		strcpy(tembuff, anks.m_char);
		lianjie(tembuff);
		delete[] tembuff;
		tembuff = NULL;
		return *this;
	}
	ANKString& ANKString::operator+=(const char* c) {
		int bytelen = strlen(c) +1;
		char* tembuff = new char[bytelen] {0};
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
	 *连接字符串
	 */
	ANKString& ANKString::operator+(const char* c) {
		int bytelen = strlen(c) + 1;
		char* tembuff = new char[bytelen] {0};
		strcpy(tembuff, c);
		lianjie(tembuff);
		delete[] tembuff;
		tembuff = NULL;
		return *this;
	}
	ANKString& ANKString::operator+(CString str) {
		int bytelen = 0;
#ifdef _UNICODE
		char* chr1 = WcharToChar(str.GetBuffer(0));
		lianjie(chr1);
#else
		lianjie((char*)str.GetBuffer(0));
#endif
		return *this;
	}
	ANKString& ANKString::operator+(ANKString  &anks) {
		int bytelen = strlen(anks.m_char) + 10;
		char* tembuff = new char[bytelen] {0};
		strcpy(tembuff, anks.m_char);
		lianjie(tembuff);
		delete[] tembuff;
		tembuff = NULL;
		return *this;
	}
	ANKString& ANKString::operator+(char*  c) {
		lianjie(c);
		return *this;
	}
	void ANKString::lianjie(char* c) {
		int bytelen = strlen(c) + strlen(m_char) + 10;
		char* tembuff = new char[bytelen]{0};
		strcpy(tembuff, m_char);
		strcat(tembuff, c);
		//重置m_char指针,否则析构函数不能释放
		Release();
		m_char = new char[bytelen] {0};
		strcpy(m_char, tembuff);
		delete[] tembuff;
		tembuff = NULL;
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