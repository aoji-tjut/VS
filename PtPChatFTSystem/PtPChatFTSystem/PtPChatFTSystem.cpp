
// PtPChatFTSystem.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "PtPChatFTSystem.h"
#include "PtPChatFTSystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//��д
SOCKET socketTCP;				//UDP������

SOCKADDR_IN Server;				//����UDP��������ַ

SOCKADDR_IN Client;		//�Է�UDP��ַ


// CPtPChatFTSystemApp

BEGIN_MESSAGE_MAP(CPtPChatFTSystemApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPtPChatFTSystemApp ����

CPtPChatFTSystemApp::CPtPChatFTSystemApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPtPChatFTSystemApp ����

CPtPChatFTSystemApp theApp;


// CPtPChatFTSystemApp ��ʼ��

BOOL CPtPChatFTSystemApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	//��д
	if (!InitUDPSocket())
	{
		return FALSE;
	}

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CPtPChatFTSystemDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


BOOL CPtPChatFTSystemApp::InitUDPSocket()		//UDP������
{
	socketTCP = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);		//����socket(UDP���ݱ�)
	if (socketTCP == INVALID_SOCKET)
	{
		AfxMessageBox("UDP�׽��ִ���ʧ�ܣ������¼�飡");
		return FALSE;
	}


	Server.sin_addr.S_un.S_addr = INADDR_ANY;
	Server.sin_family = AF_INET;
	Server.sin_port = htons(0);
	
	if (bind(socketTCP, (SOCKADDR*)&Server, sizeof(Server)) == SOCKET_ERROR)		//��
	{
		closesocket(socketTCP);
		WSACleanup();
		AfxMessageBox("UDP�׽��ְ�ʧ�ܣ������¼�飡");
		return FALSE;
	}

	listen(socketTCP, 1);

	return TRUE;
}


int CPtPChatFTSystemApp::ExitInstance()
{
	if (socketTCP)
	{
		closesocket(socketTCP);
	}

	WSACleanup();
	
	return CWinApp::ExitInstance();
}