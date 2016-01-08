#include "functions.h"
namespace Ainiku {
	AINIKU_API char* postUrl() {
		return "这个是post输出的内容";
	}
	AINIKU_API CString getUrl(CString url) {
		if (url == "") { return ""; }
		CInternetSession mySession((LPCTSTR)"aaa", 0);//如果不指定aaa(随便的一个字符串)的话debug模式下会报错
		CHttpFile* htmlFile = NULL;
		CString strLine, strHtml;
		TCHAR sRecv[1024];
		UINT CodePage = 65001;//CP_UTF8:65001 CP_ACP:0
		TRY
		{
			htmlFile = (CHttpFile*)mySession.OpenURL(url);//打开连接
														  //获取网页编码
		while (htmlFile->ReadString(sRecv,1024))
		{
			//先用UTF8来进行转换，如果html页面编码是gbk或gb2312，转换后中文字符为
			//乱码，但英文字符显示正常，我们判断html页码编码，通过寻找英文就可以了
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
		//获取网页源码
		htmlFile = (CHttpFile*)mySession.OpenURL(url);//重新打开连接
		while (htmlFile->ReadString(sRecv,1024))
		{
			// 编码转换，可解决中文乱码问题
			//gb2312转为unicode,则用CP_ACP
			//gbk转为unicode,也用CP_ACP
			//utf-8转为unicode,则用CP_UTF8
			int nBufferSize = MultiByteToWideChar(CodePage, 0, (LPCSTR)sRecv, -1, NULL, 0);
			wchar_t *pBuffer = new wchar_t[nBufferSize + 1];
			memset(pBuffer,0,(nBufferSize + 1)*sizeof(wchar_t));
			//gb2312转为unicode,则用CP_ACP
			//gbk转为unicode,也用CP_ACP
			//utf-8转为unicode,则用CP_UTF8
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
}