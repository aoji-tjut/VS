
// TCP服务器.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#pragma comment(linker,"\"/manifestdependency:type='win32' "\
	"name='Microsoft.Windows.Common-Controls' "\
	"version='6.0.0.0' processorArchitecture='*' "\
	"publicKeyToken='6595b64144ccf1df' language='*'\"")

// CTCP服务器App: 
// 有关此类的实现，请参阅 TCP服务器.cpp
//

class CTCP服务器App : public CWinApp
{
public:
	CTCP服务器App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CTCP服务器App theApp;