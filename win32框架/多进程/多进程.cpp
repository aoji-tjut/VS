// 多进程.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "多进程.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND hEdit;
HANDLE hand;
int ID;

// 此代码模块中包含的函数的前向声明: 
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
	case WM_CREATE:
		hEdit = CreateWindow(L"Edit", NULL, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_MULTILINE | ES_LEFT,
			0, 0, 0, 0, hWnd, NULL, hInst, NULL);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
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
	SetEnvironmentVariable(L"123456", L"哈哈哈哈");
	GetEnvironmentVariable(L"123456", str, 128);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
}

void createprocess()
{
	STARTUPINFO sta = { 0 };
	PROCESS_INFORMATION pro = { 0 };
	CreateProcess(
		L"C:\\Windows\\System32\\calc.exe",		//进程名、路径
		NULL,									//命令行
		NULL,									//进程安全属性
		NULL,									//线程安全属性
		FALSE,									//进程句柄继承
		0,										//创建方式
		NULL,									//环境信息
		NULL,									//当前目录
		&sta,									//传入值、起始信息
		&pro									//传出值、进程消息
		);
	ID = pro.dwProcessId;

	TCHAR str[128] = { 0 };
	wsprintf(str, L"子进程句柄：%d\r\n子进程ID：%d\r\n", pro.hProcess, pro.dwProcessId);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
}

void getprocess()
{
	TCHAR str[128] = { 0 };
	HANDLE hPro = GetCurrentProcess();
	DWORD ID = GetCurrentProcessId();
	wsprintf(str, L"当前进程(假)句柄：%d\r\n当前进程ID：%d\r\n", hPro, ID);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
}

void openprocess()
{
	TCHAR str[128] = { 0 };
	hand = OpenProcess(
		PROCESS_ALL_ACCESS,			//打开权限
		FALSE,						//是否继承
		ID							//子进程ID
		);
	if (!hand)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"打开失败");
	}
	else
	{
		wsprintf(str, L"当前进程(真)句柄：%d\r\n", hand);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
	}
}

void terminateprocess()
{
	TerminateProcess(
		hand,						//当前句柄
		123							//退出码
		);
	ID = 0;
}