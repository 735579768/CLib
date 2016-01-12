#pragma once
#include "stdafx.h"
namespace Ainiku {
	class AINIKU_API ANKHttp
	{
	public:
		CString getUrl(CString url);
		CString postUrl(CString url,CString postdata);
		ANKHttp();
		~ANKHttp();
	private:
		CString decode(CHttpFile* htmlFile);
		CInternetSession* m_interSession;
	};

}