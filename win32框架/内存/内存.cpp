// 内存.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "内存.h"


#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND hEdit;
HANDLE hHeap;
char* p;
char* q;

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void ShowVirtual();
void AllocVirtual();
void FreeVirtual();
void ShowHeap();
void AllocHeap();
void FreeHeap();

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
	if (!InitInstance(hInstance, nCmdShow))
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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

	RECT rect;
	GetClientRect(hWnd, &rect);
	hEdit = CreateWindow(L"Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN,
		0, 0, rect.right, rect.bottom, hWnd, NULL, hInst, NULL);

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
	HFONT hFont;

	switch (message)
	{
	case WM_CREATE:

		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_SHOWVIRTUAL:
			ShowVirtual();
			break;
		case IDM_APPLYVIRTUAL:
			AllocVirtual();
			break;
		case IDM_FREEVIRTUAL:
			FreeVirtual();
			break;
		case IDM_SHOWHEAP:
			ShowHeap();
			break;
		case IDM_APPLYHEAP:
			AllocHeap();
			break;
		case IDM_FREEHEAP:
			FreeHeap();
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
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
		//DeleteObject(hFont);
		//ReleaseDC(hEdit, hdc);
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

void ShowVirtual()
{
	TCHAR str[1024];
	MEMORYSTATUS mms = { 0 };
	mms.dwLength = sizeof(mms);
	GlobalMemoryStatus(&mms);
	wsprintf(str, L"结构体大小：%d\r\n当前系统内存的使用率：%d%%\r\n总的物理内存大小：%X\r\n可用的物理内存大小：%X\r\n可以存在页面文件中的字节数：%X\r\n可用的页面文件大小：%X\r\n全部可用虚拟地址空间：%X\r\n实际自由可用的虚拟地址空间：%X\r\n",
		mms.dwLength, mms.dwMemoryLoad, mms.dwTotalPhys, mms.dwAvailPhys, mms.dwTotalPageFile, mms.dwAvailPageFile, mms.dwTotalVirtual, mms.dwAvailVirtual);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
}

void AllocVirtual()
{
	p = (char*)VirtualAlloc(NULL, 1024 * 1024 * 1024, MEM_COMMIT, PAGE_READWRITE);
	if (!p)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"申请失败");
	}
	else
	{
		strcpy(p, "哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈");
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"申请成功");
	}
}

void FreeVirtual()
{
	//0代表全部释放
	BOOL flag = VirtualFree(p, 0, MEM_RELEASE);
	if (flag)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"释放成功");
	}
	else SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"释放失败");
}

void ShowHeap()
{
	HANDLE hHeap = GetProcessHeap();//第一个堆
	TCHAR str[1024] = { 0 };
	TCHAR s[32] = { 0 };
	wsprintf(str, L"第一个堆内存：%d\r\n", hHeap);
	HANDLE hArr[128] = { 0 };
	DWORD count = GetProcessHeaps(128, hArr);//所有堆
	wcscat(str, L"所有堆内存：\r\n");
	for (int i = 0; i < count; i++)
	{
		memset(s, 0, sizeof(s));
		wsprintf(s, L"hArr[%d] = %d\r\n", i, hArr[i]);
		wcscat(str, s);
	}
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
}

void AllocHeap()
{
	hHeap = HeapCreate(0, 1024 * 1024, 0);
	q = (char*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, 2 * 1024 * 1024);
	if (!q)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"创建失败");
	}
	else
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"创建成功");
		strcpy(q, "哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈");
	}
}

void FreeHeap()
{
	//0代表全部释放
	BOOL flag = HeapFree(hHeap,0,q);
	if (!flag)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"释放失败");
	}
	else SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"释放成功");
	HeapDestroy(hHeap);
}