// �˵�����.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "�˵�����.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void TopMenu(HWND hWnd);
void SystemMenu(HWND hWnd);
void youjianMenu(HWND hWnd,LPARAM l);

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
	wcex.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU1);
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

	//TopMenu(hWnd);
	//SystemMenu(hWnd);

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
	case WM_COMMAND://����˵���Ϣ
		wmId    = LOWORD(wParam);//���ֽڲ˵�ID
		wmEvent = HIWORD(wParam);
		TCHAR str[100];
		wsprintf(str, L"ID��%d", wmId);
		MessageBox(NULL, str, L"��ʾ", MB_OK);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_RBUTTONUP:
		youjianMenu(hWnd, lParam);
		break;
	//case WM_SYSCOMMAND:
	//	wmId = LOWORD(wParam);
	//	wsprintf(str, L"ID��%d", wmId);
	//	MessageBox(NULL, str, L"��ʾ", MB_OK);
	//	break;
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

void TopMenu(HWND hWnd)
{
	//��������˵�
	HMENU hmenu = CreateMenu();
	//�������㵯��ʽ�˵�
	HMENU hFile = CreatePopupMenu();
	AppendMenu(hmenu, MF_POPUP, (int)hFile, L"�ļ�");
	AppendMenu(hFile, MF_STRING, 1001, L"��");
	AppendMenu(hFile, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFile, MF_STRING, 1002, L"����");
	AppendMenu(hFile, MF_STRING, 1003, L"���Ϊ");
	HMENU hEdit = CreatePopupMenu();
	AppendMenu(hmenu, MF_POPUP, (int)hEdit, L"�༭");
	AppendMenu(hEdit, MF_STRING, 2001, L"����");
	AppendMenu(hEdit, MF_STRING, 2002, L"����");
	AppendMenu(hEdit, MF_STRING, 2003, L"ճ��");
	SetMenu(hWnd, hmenu);
}

void SystemMenu(HWND hWnd)
{
	HMENU SysMenu = GetSystemMenu(hWnd, FALSE);
	for (int i = 0; i < 6; i++)
	{
		DeleteMenu(SysMenu, 0, MF_BYPOSITION);
	}
	AppendMenu(SysMenu, MF_STRING, 4001, L"ϵͳ�˵�");
}

void youjianMenu(HWND hWnd,LPARAM l)
{
	HMENU RMenu = CreatePopupMenu();
	HMENU hChildMenu = CreatePopupMenu();
	AppendMenu(RMenu, MF_POPUP, (int)hChildMenu, L"�Ҽ��˵�");
	AppendMenu(hChildMenu, MF_STRING, 3001, L"�Ӳ˵�");
	POINT p;
	p.x = LOWORD(l);
	p.y = HIWORD(l);
	ClientToScreen(hWnd, &p);//�ͻ�������ת������Ļ����
	TrackPopupMenu(RMenu, NULL, p.x, p.y, 0, hWnd, NULL);
}
