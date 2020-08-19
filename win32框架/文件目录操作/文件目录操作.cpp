// 文件目录操作.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "文件目录操作.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND hEdit;

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void GetCurrent();
void GetSystem();
void GetWindows();
void GetTemp();
void FindAllFile();
void CreateF();
void ReadF();
void WriteF();
void FileMap();

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

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_CURDIR:
			GetCurrent();
			break;
		case IDM_SYSDIR:
			GetSystem();
			break;
		case IDM_WINDIR:
			GetWindows();
			break;
		case IDM_TEMPDIR:
			GetTemp();
			break;
		case IDM_ALLFILE:
			FindAllFile();
			break;
		case IDM_CREATE:
			CreateF();
			break;
		case IDM_READWRITE:
			WriteF();
			break;
		case IDM_COPY:
			break;
		case IDM_DELETE:
			break;
		case IDM_MOVE:
			break;
		case IDM_SIZE:
			break;
		case IDM_FILEMAP:
			FileMap();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		MoveWindow(hEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
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


void GetCurrent()
{
	TCHAR buf[128] = { 0 };
	TCHAR temp[128] = { 0 };
	GetCurrentDirectory(128, buf);
	wsprintf(temp, L"当前目录：%s", buf);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)temp);
}

void GetSystem()
{
	TCHAR buf[128] = { 0 };
	TCHAR temp[128] = { 0 };
	GetSystemDirectory(buf, 128);
	wsprintf(temp, L"系统目录：%s", buf);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)temp);
}

void GetWindows()
{
	TCHAR buf[128] = { 0 };
	TCHAR temp[128] = { 0 };
	GetWindowsDirectory(buf, 128);
	wsprintf(temp, L"Windows目录：%s", buf);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)temp);
}

void GetTemp()
{
	TCHAR buf[128] = { 0 };
	TCHAR temp[128] = { 0 };
	GetTempPath(128, buf);
	wsprintf(temp, L"temp目录：%s", buf);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)temp);
}

void FindAllFile()
{
	TCHAR *path = L"c:/*.*";
	TCHAR allpath[1024] = { 0 };
	WIN32_FIND_DATA wfd = { 0 };
	HANDLE hFind = FindFirstFile(path, &wfd);
	BOOL flag = TRUE;
	while (flag)
	{
		//如果是目录
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//得到文件名
			lstrcat(allpath, wfd.cFileName);
			lstrcat(allpath, L"（目录）\r\n");
		}
		else
		{
			lstrcat(allpath, wfd.cFileName);
			lstrcat(allpath, L"（文件）\r\n");
		//	wcscat(allpath, wfd.cFileName);
		//	wcscat(allpath, L"（文件）\r\n");
		}
		flag = FindNextFile(hFind, &wfd);
	}
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)allpath);
}

void CreateF()
{
	HANDLE hFile = CreateFile(L"C:\\Users\\acer\\Desktop\\文件.txt", GENERIC_WRITE,
		FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"创建成功");
	}
	CloseHandle(hFile);
}

void WriteF()
{
	HANDLE hFile = CreateFile(L"C:\\Users\\acer\\Desktop\\文件.txt", GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	char* text = "啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦"; 
	DWORD len = 0;
	BOOL write = WriteFile(hFile, text, strlen(text), &len, NULL);
	if (write)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"写入成功");
	}
	CloseHandle(hFile);
}

void ReadF()
{
	HANDLE hFile = CreateFile(L"C:\\Users\\acer\\Desktop\\文件.txt", GENERIC_ALL,
		FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	char text[1024] = { 0 };
	DWORD len = 0;
	DWORD high = 0;
	DWORD low = GetFileSize(hFile, &high);
	BOOL read = WriteFile(hFile, text, low, &len, NULL);
	if (read)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"读取成功");
	}
	CloseHandle(hFile);
}

void FileMap()
{
	//创建文件
	HANDLE hFile = CreateFile(L"C:\\Users\\acer\\Desktop\\文件.txt", GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!hFile)
	{
		TCHAR error[100];
		wsprintf(error, L"error:%s", GetLastError());
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)error);
		exit(0);
	}
	//创建文件映射到内存
	HANDLE hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 1024 * 1024, L"嘴哥");
	if (!hMap)
	{
		TCHAR error[100];
		wsprintf(error, L"error:%s", GetLastError());
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)error);
		exit(0);
	}
	//加载内存映射
	TCHAR* map = (TCHAR*)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 64 * 1024, 0);
	if (!map)
	{
		TCHAR error[100];
		wsprintf(error, L"error:%s", GetLastError());
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)error);
		exit(0);
	}
	//内存使用
	lstrcpy(map, L"嘴哥");
	TCHAR str[100];
	wsprintf(str, L"map = %s", map);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
	//卸载映射
	UnmapViewOfFile(map);
	CloseHandle(hMap);
	CloseHandle(hFile);
}