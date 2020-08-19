// �����.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "�����.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HWND hEdit;
HANDLE hand;
int ID;

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void SetEnv();
void ShowEnv();
void createprocess();
void getprocess();
void terminateprocess();
void openprocess();

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

	// ����Ϣѭ��: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		hEdit = CreateWindow(L"Edit", NULL, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_MULTILINE | ES_LEFT,
			0, 0, 0, 0, hWnd, NULL, hInst, NULL);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_SHOWENV:
			ShowEnv();
			break;
		case IDM_SETENV:
			SetEnv();
			break;
		case IDM_CREATEPROCESS:
			createprocess();
			break;
		case IDM_PROCESSINF:
			getprocess();
			break;
		case IDM_OPENPROCESS:
			openprocess();
			break;
		case IDM_EXITCHILDPROCESS:
			terminateprocess();
			break;
		case IDM_EXITCURPROCESS:
			ExitProcess(123);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_SETFOCUS:
		SetFocus(hEdit);
		break;
	case WM_SIZE:
		MoveWindow(hEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void ShowEnv()
{
	TCHAR* ps = (TCHAR*)GetEnvironmentStrings();
	TCHAR* temp = ps;
	while (ps[0])
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)ps);
		ps = ps + lstrlen(ps);
	}
	FreeEnvironmentStrings(temp);
}

void SetEnv()
{
	TCHAR str[128] = { 0 };
	SetEnvironmentVariable(L"123456", L"��������");
	GetEnvironmentVariable(L"123456", str, 128);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
}

void createprocess()
{
	STARTUPINFO sta = { 0 };
	PROCESS_INFORMATION pro = { 0 };
	CreateProcess(
		L"C:\\Windows\\System32\\calc.exe",		//��������·��
		NULL,									//������
		NULL,									//���̰�ȫ����
		NULL,									//�̰߳�ȫ����
		FALSE,									//���̾���̳�
		0,										//������ʽ
		NULL,									//������Ϣ
		NULL,									//��ǰĿ¼
		&sta,									//����ֵ����ʼ��Ϣ
		&pro									//����ֵ��������Ϣ
		);
	ID = pro.dwProcessId;

	TCHAR str[128] = { 0 };
	wsprintf(str, L"�ӽ��̾����%d\r\n�ӽ���ID��%d\r\n", pro.hProcess, pro.dwProcessId);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
}

void getprocess()
{
	TCHAR str[128] = { 0 };
	HANDLE hPro = GetCurrentProcess();
	DWORD ID = GetCurrentProcessId();
	wsprintf(str, L"��ǰ����(��)�����%d\r\n��ǰ����ID��%d\r\n", hPro, ID);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
}

void openprocess()
{
	TCHAR str[128] = { 0 };
	hand = OpenProcess(
		PROCESS_ALL_ACCESS,			//��Ȩ��
		FALSE,						//�Ƿ�̳�
		ID							//�ӽ���ID
		);
	if (!hand)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"��ʧ��");
	}
	else
	{
		wsprintf(str, L"��ǰ����(��)�����%d\r\n", hand);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
	}
}

void terminateprocess()
{
	TerminateProcess(
		hand,						//��ǰ���
		123							//�˳���
		);
	ID = 0;
}