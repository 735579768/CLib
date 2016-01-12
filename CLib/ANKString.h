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
		char* WcharToChar(wchar_t* wc,int codepage);//���ֽ�ת���ֽ�
		wchar_t* CharToWchar(char* c, int codepage); //���ֽ�ת���ֽ�
		char* getChar();
		wchar_t* getWChar();
		ANKString* append(const char* c);
		//�滻�ַ���
		char* replace(char* findstr, char* replacestr);

		//�����ַ���
		int find(char* findstr);
		int find(const char* findstr);
		int find(ANKString findstr);
		int find(CString findstr);
		//���ز�����
		ANKString& operator+=(char* c);
		ANKString& operator+=(ANKString &anks);
		ANKString& operator+=(const char* c);
		ANKString& operator+=(CString &str);

		ANKString& operator+(char* c);
		ANKString& operator+(const char* c);
		ANKString& operator+(ANKString &anks);
		ANKString& operator+(CString &str);

		void Release();//�ͷ���Դ
	private:
		//��ʼ������
		void init();
		//����m_char�ַ���
		void ANKString::lianjie(char* c);
		char* m_char;
		wchar_t* m_wchar;
		//���建����
		char* m_buff;
		wchar_t* m_wbuff;

	};
}
#endif

