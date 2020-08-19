
// PtPChatFTSystem.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

// CPtPChatFTSystemApp: 
// 有关此类的实现，请参阅 PtPChatFTSystem.cpp
//

class CPtPChatFTSystemApp : public CWinApp
{
public:
	CPtPChatFTSystemApp();
	//手写
	BOOL InitUDPSocket();
	BOOL InitTCPSocket();
// 重写
public:
	virtual BOOL InitInstance();
	//手写
	virtual BOOL ExitInstance();
// 实现

	DECLARE_MESSAGE_MAP()
};

extern CPtPChatFTSystemApp theApp;