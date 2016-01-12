// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//
#ifndef __LIB_STDAFX_H__
#define __LIB_STDAFX_H__
#pragma once

// 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。
// 如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将
// 将 _WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。
#include <SDKDDKVer.h>


#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
//#include <windows.h>
#define _AFXDLL
#include <afxinet.h>

#ifdef CLIB_EXPORTS
#define AINIKU_API __declspec(dllexport)
#else
#define AINIKU_API __declspec(dllimport)
#endif

// TODO:  在此处引用程序需要的其他头文件
#endif