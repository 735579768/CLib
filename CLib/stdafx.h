// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//
#ifndef __LIB_STDAFX_H__
#define __LIB_STDAFX_H__
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
//#include <windows.h>
#define _AFXDLL
#include <afxinet.h>

#ifdef CLIB_EXPORTS
#define AINIKU_API __declspec(dllexport)
#else
#define AINIKU_API __declspec(dllimport)
#endif

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#endif