#include "functions.h"
#include "assert.h"
namespace Ainiku {
	AINIKU_API char* postUrl() {
		return "�����post���������";
	}
	AINIKU_API CString getUrl(CString url) {
		if (url == "") { return ""; }
		CInternetSession mySession((LPCTSTR)"aaa", 0);//�����ָ��aaa(����һ���ַ���)�Ļ�debugģʽ�»ᱨ��
		CHttpFile* htmlFile = NULL;
		CString strLine, strHtml;
		strHtml = _T("");
		TCHAR sRecv[1024];//����һ��������
		UINT CodePage = 65001;//CP_UTF8:65001 CP_ACP:0
		TRY
		{
			htmlFile = (CHttpFile*)mySession.OpenURL(url);//������
		//CString str;
		//htmlFile->ReadString(str);											  //��ȡ��ҳ����
		while (htmlFile->ReadString(sRecv,1024))
		{
			//����UTF8������ת�������htmlҳ�������gbk��gb2312��ת���������ַ�Ϊ
			//���룬��Ӣ���ַ���ʾ�����������ж�htmlҳ����룬ͨ��Ѱ��Ӣ�ľͿ�����
			//������ʱ�ı�
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
		//��ȡ��ҳԴ��
		//ת��������ʱȡ�����ı�Ϊ��ȷ�ı���
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
			// ����ת�����ɽ��������������
			//gb2312תΪunicode,����CP_ACP
			//gbkתΪunicode,Ҳ��CP_ACP
			//utf-8תΪunicode,����CP_UTF8
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
		CInternetSession mySession((LPCTSTR)"aaa", 0);//�����ָ��aaa(����һ���ַ���)�Ļ�debugģʽ�»ᱨ��
		CHttpFile* htmlFile = NULL;
		CString str, strHtml;
		TRY{
			htmlFile = (CHttpFile*)mySession.OpenURL(url);//������
		while (htmlFile->ReadString(str)) {
			char *pStr = (char*)str.GetBuffer(str.GetLength()); //ȡ��str�����ԭʼ�ַ���
			int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, pStr, -1, NULL, 0); //ȡ�����軺��Ķ���
			wchar_t *pBuffer = (wchar_t*)malloc(nBufferSize * sizeof(wchar_t));//���뻺��ռ�
			MultiByteToWideChar(CP_UTF8, 0, pStr, -1, pBuffer, nBufferSize*sizeof(wchar_t));//ת��
			strHtml += pBuffer;
			free(pBuffer); //�ͷŻ���	
		}
		return strHtml;
		}CATCH(CException, e){
			TCHAR err[1024];
			e->GetErrorMessage(err, 1024);
			return "";
		}
		END_CATCH
	}
	//���ַ���ת���ɿ��ַ���  
	AINIKU_API wstring string2Wstring(string sToMatch)
	{
#ifdef _A_LINUX 
		setlocale(LC_CTYPE, ""); // ����Ҫ��û����һ�䣬ת����ʧ�ܡ�  
		int iWLen = mbstowcs(NULL, sToMatch.c_str(), sToMatch.length()); // ����ת������ַ����ĳ��ȡ����������ַ�����������  
		wchar_t *lpwsz = new wchar_t[iWLen + 1];
		int i = mbstowcs(lpwsz, sToMatch.c_str(), sToMatch.length()); // ת������ת������ַ����н�������  
		wstring wsToMatch(lpwsz);
		delete[]lpwsz;
#else 
		int iWLen = MultiByteToWideChar(CP_ACP, 0, sToMatch.c_str(), sToMatch.size(), 0, 0); // ����ת������ַ����ĳ��ȡ����������ַ�����������  
		wchar_t *lpwsz = new wchar_t[iWLen + 1];
		MultiByteToWideChar(CP_ACP, 0, sToMatch.c_str(), sToMatch.size(), lpwsz, iWLen); // ��ʽת����  
		lpwsz[iWLen] = L'\0';
		wstring wsToMatch(lpwsz);
		delete[]lpwsz;
#endif  
		return wsToMatch;
	}
	//�ѿ��ַ���ת�����ַ��������ʹ��  
	AINIKU_API string wstring2string(wstring sToMatch)
	{
#ifdef _A_LINUX   
		int iLen = wcstombs(NULL, sToMatch.c_str(), 0); // ����ת�����ַ����ĳ��ȡ����������ַ�����������  
		char *lpsz = new char[iLen + 1];
		int i = wcstombs(lpsz, sToMatch.c_str(), iLen); // ת������û�н�������  
		lpsz[iLen] = '/0';
		string sResult(lpsz);
		delete[]lpsz;
#else 
		string sResult;
		int iLen = WideCharToMultiByte(CP_ACP, NULL, sToMatch.c_str(), -1, NULL, 0, NULL, FALSE); // ����ת�����ַ����ĳ��ȡ��������ַ�����������  
		char *lpsz = new char[iLen];
		WideCharToMultiByte(CP_OEMCP, NULL, sToMatch.c_str(), -1, lpsz, iLen, NULL, FALSE); // ��ʽת����  
		sResult.assign(lpsz, iLen - 1); // ��string������и�ֵ��  
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
	/*���ַ�������߽�ȡn���ַ�*/
	AINIKU_API char * left(char *dst, char *src, int n)
	{
		char *p = src;
		char *q = dst;
		int len = strlen(src);
		if (n>len) n = len;
		while (n--) *(q++) = *(p++);
		*(q++) = '\0'; /*�б�Ҫ�𣿺��б�Ҫ*/
		return dst;
	}

	/*���ַ������м��ȡn���ַ�*/
	AINIKU_API char * mid(char *dst, char *src, int n, int m) /*nΪ���ȣ�mΪλ��*/
	{
		char *p = src;
		char *q = dst;
		int len = strlen(src);
		if (n>len) n = len - m;    /*�ӵ�m�������*/
		if (m<0) m = 0;    /*�ӵ�һ����ʼ*/
		if (m>len) return NULL;
		p += m;
		while (n--) *(q++) = *(p++);
		*(q++) = '\0'; /*�б�Ҫ�𣿺��б�Ҫ*/
		return dst;
	}

	/*���ַ������ұ߽�ȡn���ַ�*/
	AINIKU_API char * right(char *dst, char *src, int n)
	{
		char *p = src;
		char *q = dst;
		int len = strlen(src);
		if (n>len) n = len;
		p += (len - n);   /*���ұߵ�n���ַ���ʼ����0���������ɰ�*/
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