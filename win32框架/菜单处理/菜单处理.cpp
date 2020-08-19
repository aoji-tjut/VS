// 菜单处理.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "菜单处理.h"

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
	wcex.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU1);
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

	//TopMenu(hWnd);
	//SystemMenu(hWnd);

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
	case WM_COMMAND://顶层菜单消息
		wmId    = LOWORD(wParam);//低字节菜单ID
		wmEvent = HIWORD(wParam);
		TCHAR str[100];
		wsprintf(str, L"ID：%d", wmId);
		MessageBox(NULL, str, L"提示", MB_OK);
		// 分析菜单选择: 
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
	//	wsprintf(str, L"ID：%d", wmId);
	//	MessageBox(NULL, str, L"提示", MB_OK);
	//	break;
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

void TopMenu(HWND hWnd)
{
	//创建顶层菜单
	HMENU hmenu = CreateMenu();
	//创建顶层弹出式菜单
	HMENU hFile = CreatePopupMenu();
	AppendMenu(hmenu, MF_POPUP, (int)hFile, L"文件");
	AppendMenu(hFile, MF_STRING, 1001, L"打开");
	AppendMenu(hFile, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFile, MF_STRING, 1002, L"保存");
	AppendMenu(hFile, MF_STRING, 1003, L"另存为");
	HMENU hEdit = CreatePopupMenu();
	AppendMenu(hmenu, MF_POPUP, (int)hEdit, L"编辑");
	AppendMenu(hEdit, MF_STRING, 2001, L"剪切");
	AppendMenu(hEdit, MF_STRING, 2002, L"复制");
	AppendMenu(hEdit, MF_STRING, 2003, L"粘贴");
	SetMenu(hWnd, hmenu);
}

void SystemMenu(HWND hWnd)
{
	HMENU SysMenu = GetSystemMenu(hWnd, FALSE);
	for (int i = 0; i < 6; i++)
	{
		DeleteMenu(SysMenu, 0, MF_BYPOSITION);
	}
	AppendMenu(SysMenu, MF_STRING, 4001, L"系统菜单");
}

void youjianMenu(HWND hWnd,LPARAM l)
{
	HMENU RMenu = CreatePopupMenu();
	HMENU hChildMenu = CreatePopupMenu();
	AppendMenu(RMenu, MF_POPUP, (int)hChildMenu, L"右键菜单");
	AppendMenu(hChildMenu, MF_STRING, 3001, L"子菜单");
	POINT p;
	p.x = LOWORD(l);
	p.y = HIWORD(l);
	ClientToScreen(hWnd, &p);//客户端坐标转换成屏幕坐标
	TrackPopupMenu(RMenu, NULL, p.x, p.y, 0, hWnd, NULL);
}
