#include "functions.h"
#include "assert.h"
namespace Ainiku {
	AINIKU_API char* postUrl() {
		return "这个是post输出的内容";
	}
	AINIKU_API CString getUrl(CString url) {
		if (url == "") { return ""; }
		CInternetSession mySession((LPCTSTR)"aaa", 0);//如果不指定aaa(随便的一个字符串)的话debug模式下会报错
		CHttpFile* htmlFile = NULL;
		CString strLine, strHtml;
		strHtml = _T("");
		TCHAR sRecv[1024];//定义一个缓冲区
		UINT CodePage = 65001;//CP_UTF8:65001 CP_ACP:0
		TRY
		{
			htmlFile = (CHttpFile*)mySession.OpenURL(url);//打开连接
		//CString str;
		//htmlFile->ReadString(str);											  //获取网页编码
		while (htmlFile->ReadString(sRecv,1024))
		{
			//先用UTF8来进行转换，如果html页面编码是gbk或gb2312，转换后中文字符为
			//乱码，但英文字符显示正常，我们判断html页码编码，通过寻找英文就可以了
			//保存临时文本
			int nBufferSize = MultiByteToWideChar(CodePage, 0, (LPCSTR)sRecv, -1, NULL, 0);
			wchar_t *pBuffer = new wchar_t[nBufferSize + 1];
			memset(pBuffer,0,(nBufferSize + 1)*sizeof(wchar_t));
			MultiByteToWideChar(CodePage, 0, (LPCSTR)sRecv, -1 , pBuffer, nBufferSize*sizeof(wchar_t));
			strHtml += pBuffer;
			if (-1 != strHtml.Find(_T("charset=gbk")))
			{
				CodePage = 0;
				delete pBuffer;
				break;
			}
			if (-1 != strHtml.Find(_T("charset=GBK")))
			{
				CodePage = 0;
				delete pBuffer;
				break;
			}
			if (-1 != strHtml.Find(_T("charset=gb2312")))
			{
				CodePage = 0;
				delete pBuffer;
				break;
			}
			if (-1 != strHtml.Find(_T("charset=GB2312")))
			{
				CodePage = 0;
				delete pBuffer;
				break;
			}
			if (-1 != strHtml.Find(_T("charset=utf-8")))
			{
				CodePage = 65001;
				delete pBuffer;
				break;
			}
			if (-1 != strHtml.Find(_T("charset=UTF-8")))
			{
				CodePage = 65001;
				delete pBuffer;
				break;
			}
			delete pBuffer;
		}
		//获取网页源码
		//转换上面临时取出的文本为正确的编码
		if (CodePage != 65001) {
			int nLength = strHtml.GetLength();
			int nBytes = WideCharToMultiByte(CodePage, 0, strHtml, nLength, NULL, 0, NULL, NULL);
			char* VoicePath = new char[nBytes + 1];
			memset(VoicePath, 0, nLength + 1);
			WideCharToMultiByte(CodePage, 0, strHtml, nLength, VoicePath, nBytes, NULL, NULL);
			strHtml = VoicePath;
			delete VoicePath;
		}

		while (htmlFile->ReadString(sRecv,1024))
		{
			// 编码转换，可解决中文乱码问题
			//gb2312转为unicode,则用CP_ACP
			//gbk转为unicode,也用CP_ACP
			//utf-8转为unicode,则用CP_UTF8
			int nBufferSize = MultiByteToWideChar(CodePage, 0, (LPCSTR)sRecv, -1, NULL, 0);
			wchar_t *pBuffer = new wchar_t[nBufferSize + 1];
			memset(pBuffer,0,(nBufferSize + 1)*sizeof(wchar_t));
			MultiByteToWideChar(CodePage, 0, (LPCSTR)sRecv, -1 , pBuffer, nBufferSize*sizeof(wchar_t));
			strHtml += pBuffer;
			delete pBuffer;
		}
		htmlFile->Close();
		mySession.Close();
		delete htmlFile;
		return strHtml;
		}
			CATCH(CException, e)
		{
			TCHAR err[1024];
			e->GetErrorMessage(err, 1024);
			return "";
		}
		END_CATCH
	}

	AINIKU_API CString getUrl2(CString url) {
		if (url == "") { return ""; }
		CInternetSession mySession((LPCTSTR)"aaa", 0);//如果不指定aaa(随便的一个字符串)的话debug模式下会报错
		CHttpFile* htmlFile = NULL;
		CString str, strHtml;
		TRY{
			htmlFile = (CHttpFile*)mySession.OpenURL(url);//打开连接
		while (htmlFile->ReadString(str)) {
			char *pStr = (char*)str.GetBuffer(str.GetLength()); //取得str对象的原始字符串
			int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, pStr, -1, NULL, 0); //取得所需缓存的多少
			wchar_t *pBuffer = (wchar_t*)malloc(nBufferSize * sizeof(wchar_t));//申请缓存空间
			MultiByteToWideChar(CP_UTF8, 0, pStr, -1, pBuffer, nBufferSize*sizeof(wchar_t));//转码
			strHtml += pBuffer;
			free(pBuffer); //释放缓存	
		}
		return strHtml;
		}CATCH(CException, e){
			TCHAR err[1024];
			e->GetErrorMessage(err, 1024);
			return "";
		}
		END_CATCH
	}
	//把字符串转换成宽字符串  
	AINIKU_API wstring string2Wstring(string sToMatch)
	{
#ifdef _A_LINUX 
		setlocale(LC_CTYPE, ""); // 很重要，没有这一句，转换会失败。  
		int iWLen = mbstowcs(NULL, sToMatch.c_str(), sToMatch.length()); // 计算转换后宽字符串的长度。（不包含字符串结束符）  
		wchar_t *lpwsz = new wchar_t[iWLen + 1];
		int i = mbstowcs(lpwsz, sToMatch.c_str(), sToMatch.length()); // 转换。（转换后的字符串有结束符）  
		wstring wsToMatch(lpwsz);
		delete[]lpwsz;
#else 
		int iWLen = MultiByteToWideChar(CP_ACP, 0, sToMatch.c_str(), sToMatch.size(), 0, 0); // 计算转换后宽字符串的长度。（不包含字符串结束符）  
		wchar_t *lpwsz = new wchar_t[iWLen + 1];
		MultiByteToWideChar(CP_ACP, 0, sToMatch.c_str(), sToMatch.size(), lpwsz, iWLen); // 正式转换。  
		lpwsz[iWLen] = L'\0';
		wstring wsToMatch(lpwsz);
		delete[]lpwsz;
#endif  
		return wsToMatch;
	}
	//把宽字符串转换成字符串，输出使用  
	AINIKU_API string wstring2string(wstring sToMatch)
	{
#ifdef _A_LINUX   
		int iLen = wcstombs(NULL, sToMatch.c_str(), 0); // 计算转换后字符串的长度。（不包含字符串结束符）  
		char *lpsz = new char[iLen + 1];
		int i = wcstombs(lpsz, sToMatch.c_str(), iLen); // 转换。（没有结束符）  
		lpsz[iLen] = '/0';
		string sResult(lpsz);
		delete[]lpsz;
#else 
		string sResult;
		int iLen = WideCharToMultiByte(CP_ACP, NULL, sToMatch.c_str(), -1, NULL, 0, NULL, FALSE); // 计算转换后字符串的长度。（包含字符串结束符）  
		char *lpsz = new char[iLen];
		WideCharToMultiByte(CP_OEMCP, NULL, sToMatch.c_str(), -1, lpsz, iLen, NULL, FALSE); // 正式转换。  
		sResult.assign(lpsz, iLen - 1); // 对string对象进行赋值。  
		delete[]lpsz;
#endif  
		return sResult;
	}

	AINIKU_API char* WcharToChar(wchar_t* wc)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), NULL, 0, NULL, NULL);
		char* m_char = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		char* rechar = m_char;
		delete[]m_char;
		return rechar;
	}
	AINIKU_API wchar_t* CharToWchar(char* c)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, c, strlen(c), NULL, 0);
		wchar_t* m_wchar = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, c, strlen(c), m_wchar, len);
		m_wchar[len] = '\0';
		wchar_t* rewchar = m_wchar;
		delete[]m_wchar;
		return rewchar;
	}
	/*从字符串的左边截取n个字符*/
	AINIKU_API char * left(char *dst, char *src, int n)
	{
		char *p = src;
		char *q = dst;
		int len = strlen(src);
		if (n>len) n = len;
		while (n--) *(q++) = *(p++);
		*(q++) = '\0'; /*有必要吗？很有必要*/
		return dst;
	}

	/*从字符串的中间截取n个字符*/
	AINIKU_API char * mid(char *dst, char *src, int n, int m) /*n为长度，m为位置*/
	{
		char *p = src;
		char *q = dst;
		int len = strlen(src);
		if (n>len) n = len - m;    /*从第m个到最后*/
		if (m<0) m = 0;    /*从第一个开始*/
		if (m>len) return NULL;
		p += m;
		while (n--) *(q++) = *(p++);
		*(q++) = '\0'; /*有必要吗？很有必要*/
		return dst;
	}

	/*从字符串的右边截取n个字符*/
	AINIKU_API char * right(char *dst, char *src, int n)
	{
		char *p = src;
		char *q = dst;
		int len = strlen(src);
		if (n>len) n = len;
		p += (len - n);   /*从右边第n个字符开始，到0结束，很巧啊*/
		while (*(q++) = *(p++));
		return dst;
	}
	AINIKU_API unsigned char ToHex(unsigned char x)
	{
		return  x > 9 ? x + 55 : x + 48;
	}

	AINIKU_API unsigned char FromHex(unsigned char x)
	{
		unsigned char y;
		if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
		else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
		else if (x >= '0' && x <= '9') y = x - '0';
		else assert(0);
		return y;
	}

	AINIKU_API std::string UrlEncode(const std::string& str)
	{
		std::string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++)
		{
			if (isalnum((unsigned char)str[i]) ||
				(str[i] == '-') ||
				(str[i] == '_') ||
				(str[i] == '.') ||
				(str[i] == '~'))
				strTemp += str[i];
			else if (str[i] == ' ')
				strTemp += "+";
			else
			{
				strTemp += '%';
				strTemp += ToHex((unsigned char)str[i] >> 4);
				strTemp += ToHex((unsigned char)str[i] % 16);
			}
		}
		return strTemp;
	}

	AINIKU_API std::string UrlDecode(const std::string& str)
	{
		std::string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++)
		{
			if (str[i] == '+') strTemp += ' ';
			else if (str[i] == '%')
			{
				assert(i + 2 < length);
				unsigned char high = FromHex((unsigned char)str[++i]);
				unsigned char low = FromHex((unsigned char)str[++i]);
				strTemp += high * 16 + low;
			}
			else strTemp += str[i];
		}
		return strTemp;
	}
}