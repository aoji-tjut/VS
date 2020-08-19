// 控件.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "控件.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明: 
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

 	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

	// 主消息循环: 
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
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
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
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 将实例句柄存储在全局变量中

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
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
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
		// 分析菜单选择: 
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
				MessageBox(hWnd, L"选择项改变", L"提示", MB_OK);
			}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  在此添加任意绘图代码...
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

// “关于”框的消息处理程序。
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
	CreateWindowEx(0, L"Button", L"分组框", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		50, 50, 1000, 200, hwnd, (HMENU)1001, hInst, NULL);//子窗口	可见的	分组框

	CreateWindowEx(0, L"Button", L"下压式按钮", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
		100, 100, 100, 100, hwnd, (HMENU)1002, hInst, NULL);//按钮

	CreateWindowEx(0, L"Button", L"2D复选框", WS_CHILD | WS_VISIBLE | BS_CHECKBOX |BS_AUTOCHECKBOX,
		300, 100, 100, 100, hwnd, (HMENU)1003, hInst, NULL);//系统自动维护选择框2d

	CreateWindowEx(0, L"Button", L"3D复选框", WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_AUTO3STATE,
		500, 100, 100, 100, hwnd, (HMENU)1004, hInst, NULL);//系统自动维护选择框3d

	CreateWindowEx(0, L"Button", L"单选框A1", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON,
		700, 100, 100, 50, hwnd, (HMENU)1005, hInst, NULL);//分组	系统自动维护按钮

	CreateWindowEx(0, L"Button", L"单选框A2", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		700, 150, 100, 50, hwnd, (HMENU)1006, hInst, NULL);
	
	CreateWindowEx(0, L"Button", L"单选框B1", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON,
		900, 100, 100, 50, hwnd, (HMENU)1007, hInst, NULL);

	CreateWindowEx(0, L"Button", L"单选框B2", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		900, 150, 100, 50, hwnd, (HMENU)1008, hInst, NULL);

	CreateWindowEx(WS_EX_CLIENTEDGE, L"Edit", L"多行文字编辑框", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE,
		100, 300, 300, 100, hwnd, (HMENU)1009, hInst, NULL);//有边框	横向滚动条	纵向滚动条	多行文字

	CreateWindowEx(WS_EX_CLIENTEDGE, L"Edit", L"密码编辑框", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_PASSWORD,
		500, 300, 300, 100, hwnd, (HMENU)1010, hInst, NULL);//密码文字
	
	//GetDlgItem()	根据ID得到句柄
	
	

	CreateWindowEx(0, L"STATIC", L"静态框", WS_CHILD | WS_VISIBLE | SS_NOTIFY,
		100, 450, 50 ,50, hwnd, (HMENU)1011, hInst, NULL);//静态框发送消息

	CreateWindowEx(0, L"STATIC", L"#130", WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_BITMAP,
		200, 450, 50, 50, hwnd, (HMENU)1012, hInst, NULL);//Bitmap（资源符号）

	CreateWindowEx(0, L"STATIC", L"#129", WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_ICON,
		300, 450, 50, 50, hwnd, (HMENU)1013, hInst, NULL);//ICON（资源符号）

	CreateWindow(L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST, 400, 450, 100, 300,hwnd, (HMENU)1014, hInst, NULL);

	TCHAR str[20];
	for (int i = 0; i < 10; i++)
	{
		memset(str, 0, 20);
		wsprintf(str, L"%d", i + 1);
		SendMessage(GetDlgItem(hwnd, 1014), CB_ADDSTRING, 0, (LPARAM)str);
	}
}