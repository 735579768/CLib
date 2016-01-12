#include "ANKHttp.h"
#include "Url.h"
#include "ANKString.h"
namespace Ainiku {
	CString ANKHttp::getUrl(CString url) {
		CString restr = "";
		if (m_interSession == NULL) {
			m_interSession = new CInternetSession(_T("ANKHTTP"), 0);
		}
		ANKString ustr = url;
		Url ur(ustr.getChar());
		//���ӵ�Http������
		CHttpConnection* myconn = (CHttpConnection*)m_interSession->GetHttpConnection(_T("www.baidu.com"));
		//��Http����
		CHttpFile* htmlFile = (CHttpFile*)myconn->OpenRequest(CHttpConnection::HTTP_VERB_GET, _T("/index.html"));
		htmlFile->AddRequestHeaders(_T("User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)"));
		//����Http����
		try {
			//��������HTTP
			htmlFile->SendRequest();
			restr = decode(htmlFile);
			//m_interSession->InternetGetCookie();
		}
		catch (CInternetException* pEx)
		{
			TCHAR szError[1024];
			pEx->GetErrorMessage(szError, 1024);
		}

		htmlFile->Close();
		myconn->Close();
		delete htmlFile;
		delete myconn;
		htmlFile = NULL;
		myconn = NULL;
		return restr;
	}
	CString ANKHttp::postUrl(CString url,CString postdata) {
		CString restr = "";
		if (m_interSession == NULL) {
		 m_interSession=new	CInternetSession();
		}
		//���ӵ�Http������
		CHttpConnection* myconn = (CHttpConnection*)m_interSession->GetHttpConnection(_T("www.baidu.com"));
		//��Http����
		CHttpFile* htmlFile = (CHttpFile*)myconn->OpenRequest(CHttpConnection::HTTP_VERB_POST,_T( "/index.html"));
		htmlFile->AddRequestHeaders(_T("User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)"));
		//����Http����
		try {
			//��������HTTP
			htmlFile->SendRequest(NULL, 0,(LPVOID)(LPCTSTR)postdata, postdata.GetLength());
			restr = decode(htmlFile);
			//htmlFile->SendRequest();
			//m_interSession->InternetGetCookie();
		}
		catch (CInternetException* pEx)
		{
			TCHAR szError[1024];
			pEx->GetErrorMessage(szError, 1024);
		}
		
		htmlFile->Close();
		myconn->Close();
		delete htmlFile;
		delete myconn;
		htmlFile = NULL;
		myconn = NULL;
		return restr;
	}
	CString ANKHttp::decode(CHttpFile* htmlFile) {
		CString strLine, strHtml;
		strHtml = _T("");
		TCHAR sRecv[1024];//����һ��������
		UINT CodePage = 65001;//CP_UTF8:65001 CP_ACP:0
		TRY
		{
		//��ȡ��ҳ����
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
	ANKHttp::ANKHttp()
	{
		m_interSession = NULL;
	}


	ANKHttp::~ANKHttp()
	{
		if (m_interSession) {
			delete m_interSession;
			m_interSession = NULL;
		}
	}
}
