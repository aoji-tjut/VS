// �ؼ�.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "�ؼ�.h"

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
void CreateButton(HWND hwnd);

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

	CreateButton(hWnd);

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
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case 1014:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				MessageBox(hWnd, L"ѡ����ı�", L"��ʾ", MB_OK);
			}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
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

void CreateButton(HWND hwnd)
{
	CreateWindowEx(0, L"Button", L"�����", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		50, 50, 1000, 200, hwnd, (HMENU)1001, hInst, NULL);//�Ӵ���	�ɼ���	�����

	CreateWindowEx(0, L"Button", L"��ѹʽ��ť", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
		100, 100, 100, 100, hwnd, (HMENU)1002, hInst, NULL);//��ť

	CreateWindowEx(0, L"Button", L"2D��ѡ��", WS_CHILD | WS_VISIBLE | BS_CHECKBOX |BS_AUTOCHECKBOX,
		300, 100, 100, 100, hwnd, (HMENU)1003, hInst, NULL);//ϵͳ�Զ�ά��ѡ���2d

	CreateWindowEx(0, L"Button", L"3D��ѡ��", WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_AUTO3STATE,
		500, 100, 100, 100, hwnd, (HMENU)1004, hInst, NULL);//ϵͳ�Զ�ά��ѡ���3d

	CreateWindowEx(0, L"Button", L"��ѡ��A1", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON,
		700, 100, 100, 50, hwnd, (HMENU)1005, hInst, NULL);//����	ϵͳ�Զ�ά����ť

	CreateWindowEx(0, L"Button", L"��ѡ��A2", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		700, 150, 100, 50, hwnd, (HMENU)1006, hInst, NULL);
	
	CreateWindowEx(0, L"Button", L"��ѡ��B1", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON,
		900, 100, 100, 50, hwnd, (HMENU)1007, hInst, NULL);

	CreateWindowEx(0, L"Button", L"��ѡ��B2", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		900, 150, 100, 50, hwnd, (HMENU)1008, hInst, NULL);

	CreateWindowEx(WS_EX_CLIENTEDGE, L"Edit", L"�������ֱ༭��", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE,
		100, 300, 300, 100, hwnd, (HMENU)1009, hInst, NULL);//�б߿�	���������	���������	��������

	CreateWindowEx(WS_EX_CLIENTEDGE, L"Edit", L"����༭��", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_PASSWORD,
		500, 300, 300, 100, hwnd, (HMENU)1010, hInst, NULL);//��������
	
	//GetDlgItem()	����ID�õ����
	
	

	CreateWindowEx(0, L"STATIC", L"��̬��", WS_CHILD | WS_VISIBLE | SS_NOTIFY,
		100, 450, 50 ,50, hwnd, (HMENU)1011, hInst, NULL);//��̬������Ϣ

	CreateWindowEx(0, L"STATIC", L"#130", WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_BITMAP,
		200, 450, 50, 50, hwnd, (HMENU)1012, hInst, NULL);//Bitmap����Դ���ţ�

	CreateWindowEx(0, L"STATIC", L"#129", WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_ICON,
		300, 450, 50, 50, hwnd, (HMENU)1013, hInst, NULL);//ICON����Դ���ţ�

	CreateWindow(L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST, 400, 450, 100, 300,hwnd, (HMENU)1014, hInst, NULL);

	TCHAR str[20];
	for (int i = 0; i < 10; i++)
	{
		memset(str, 0, 20);
		wsprintf(str, L"%d", i + 1);
		SendMessage(GetDlgItem(hwnd, 1014), CB_ADDSTRING, 0, (LPARAM)str);
	}
}