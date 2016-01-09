#include "functions.h"
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
		lpwsz[iWLen] = L'/0';
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

	char* wCharToChar(LPWSTR a1)
	{
		
		int nLen = WideCharToMultiByte(CP_ACP, 0, a1, -1, NULL, 0, NULL, NULL);
		char *s = new char[nLen + 1];
		WideCharToMultiByte(CP_ACP, 0, a1, -1, s, nLen, NULL, NULL);
		char *l;
		l = s;
		delete s;
		return l;
	}
}