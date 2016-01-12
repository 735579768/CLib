#ifndef __LIB_ANKSTRING_H__
#define __LIB_ANKSTRING_H__
#pragma once
#include "stdafx.h"
#include <string>
namespace Ainiku {
	class AINIKU_API ANKString
	{
	public:
		ANKString();
		ANKString(const ANKString& ankstr);
		ANKString(char* c);
		ANKString(const char* c);
		ANKString(CString str);
		ANKString(std::string str);
		virtual~ANKString();
		char* WcharToChar(wchar_t* wc,int codepage);//宽字节转单字节
		wchar_t* CharToWchar(char* c, int codepage); //单字节转宽字节
		char* getChar();
		wchar_t* getWChar();
		ANKString* append(const char* c);
		//替换字符串
		char* replace(char* findstr, char* replacestr);

		//查找字符串
		int find(char* findstr);
		int find(const char* findstr);
		int find(ANKString findstr);
		int find(CString findstr);
		//重载操作符
		ANKString& operator+=(char* c);
		ANKString& operator+=(ANKString &anks);
		ANKString& operator+=(const char* c);
		ANKString& operator+=(CString &str);

		ANKString& operator+(char* c);
		ANKString& operator+(const char* c);
		ANKString& operator+(ANKString &anks);
		ANKString& operator+(CString &str);

		void Release();//释放资源
	private:
		//初始化数据
		void init();
		//连接m_char字符串
		void ANKString::lianjie(char* c);
		char* m_char;
		wchar_t* m_wchar;
		//定义缓冲区
		char* m_buff;
		wchar_t* m_wbuff;

	};
}
#endif

