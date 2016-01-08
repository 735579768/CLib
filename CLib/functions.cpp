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
		TCHAR sRecv[1024];
		UINT CodePage = 65001;//CP_UTF8:65001 CP_ACP:0
		TRY
		{
			htmlFile = (CHttpFile*)mySession.OpenURL(url);//������
														  //��ȡ��ҳ����
		while (htmlFile->ReadString(sRecv,1024))
		{
			//����UTF8������ת�������htmlҳ�������gbk��gb2312��ת���������ַ�Ϊ
			//���룬��Ӣ���ַ���ʾ�����������ж�htmlҳ����룬ͨ��Ѱ��Ӣ�ľͿ�����
			int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)sRecv, -1, NULL, 0);
			wchar_t *pBuffer = new wchar_t[nBufferSize + 1];
			memset(pBuffer,0,(nBufferSize + 1)*sizeof(wchar_t));
			MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)sRecv, -1 , pBuffer, nBufferSize*sizeof(wchar_t));
			strHtml = pBuffer;
			if (-1 != strHtml.Find(_T("charset=gbk")))
			{
				CodePage = 0;
				delete pBuffer;
				break;
			}
			if (-1 != strHtml.Find(_T("charset=GBK")))//http://www.sohu.com
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
		strHtml = _T("");
		//��ȡ��ҳԴ��
		htmlFile = (CHttpFile*)mySession.OpenURL(url);//���´�����
		while (htmlFile->ReadString(sRecv,1024))
		{
			// ����ת�����ɽ��������������
			//gb2312תΪunicode,����CP_ACP
			//gbkתΪunicode,Ҳ��CP_ACP
			//utf-8תΪunicode,����CP_UTF8
			int nBufferSize = MultiByteToWideChar(CodePage, 0, (LPCSTR)sRecv, -1, NULL, 0);
			wchar_t *pBuffer = new wchar_t[nBufferSize + 1];
			memset(pBuffer,0,(nBufferSize + 1)*sizeof(wchar_t));
			//gb2312תΪunicode,����CP_ACP
			//gbkתΪunicode,Ҳ��CP_ACP
			//utf-8תΪunicode,����CP_UTF8
			MultiByteToWideChar(CodePage, 0, (LPCSTR)sRecv, -1 , pBuffer, nBufferSize*sizeof(wchar_t));
			strHtml += pBuffer;
			strHtml += "\r\n";
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
}