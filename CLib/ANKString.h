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
		char* WcharToChar(wchar_t* wc);//���ֽ�ת���ֽ�
		wchar_t* CharToWchar(char* c); //���ֽ�ת���ֽ�
		char* getChar();
		wchar_t* getWChar();
		ANKString* append(const char* c);
		//���ز�����
		ANKString& operator+=(char* c);
		ANKString& operator+=(ANKString* anks);
		ANKString& operator+=(const char* c);
		ANKString& operator+=(CString str);

		//ANKString operator=(char* c);
		//ANKString operator=(ANKString* anks);
		//ANKString operator=(const char* c);
		//ANKString operator=(CString str);
		//ANKString operator=(const ANKString ankstr);
		void Release();//�ͷ���Դ
	private:
		//����m_char�ַ���
		void ANKString::lianjie(char* c);
		char* m_char;
		wchar_t* m_wchar;
	};
}


