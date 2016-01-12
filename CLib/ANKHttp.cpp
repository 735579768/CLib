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
		//连接到Http服务器
		CHttpConnection* myconn = (CHttpConnection*)m_interSession->GetHttpConnection(_T("www.baidu.com"));
		//打开Http请求：
		CHttpFile* htmlFile = (CHttpFile*)myconn->OpenRequest(CHttpConnection::HTTP_VERB_GET, _T("/index.html"));
		htmlFile->AddRequestHeaders(_T("User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)"));
		//发送Http请求：
		try {
			//发送请求到HTTP
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
		//连接到Http服务器
		CHttpConnection* myconn = (CHttpConnection*)m_interSession->GetHttpConnection(_T("www.baidu.com"));
		//打开Http请求：
		CHttpFile* htmlFile = (CHttpFile*)myconn->OpenRequest(CHttpConnection::HTTP_VERB_POST,_T( "/index.html"));
		htmlFile->AddRequestHeaders(_T("User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)"));
		//发送Http请求：
		try {
			//发送请求到HTTP
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
		TCHAR sRecv[1024];//定义一个缓冲区
		UINT CodePage = 65001;//CP_UTF8:65001 CP_ACP:0
		TRY
		{
		//获取网页编码
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
