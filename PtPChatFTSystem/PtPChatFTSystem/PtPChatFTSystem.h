
// PtPChatFTSystem.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CPtPChatFTSystemApp: 
// �йش����ʵ�֣������ PtPChatFTSystem.cpp
//

class CPtPChatFTSystemApp : public CWinApp
{
public:
	CPtPChatFTSystemApp();
	//��д
	BOOL InitUDPSocket();
	BOOL InitTCPSocket();
// ��д
public:
	virtual BOOL InitInstance();
	//��д
	virtual BOOL ExitInstance();
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPtPChatFTSystemApp theApp;