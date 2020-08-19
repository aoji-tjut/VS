// GDI.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "GDI.h"

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
void OnPaint(HWND hwnd);
void DrawPoint(HWND hwnd);
void DrawLine(HWND hwnd);
void DrawCircle(HWND hwnd);
void DrawRect(HWND hwnd);
void Picture(HWND hwnd);
void Front(HWND hwnd);
void Paint(HWND hwnd);

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
	LoadString(hInstance, IDC_GDI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GDI));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDI));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_GDI);
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
int i;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case ID_POINT:
			DrawPoint(hWnd);
			i = 1;
			break;
		case ID_LINE:
			DrawLine(hWnd);
			i = 2;
			break;
		case ID_CIRCLE:
			DrawCircle(hWnd);
			i = 3;
			break;
		case ID_RECT:
			DrawRect(hWnd);
			i = 4;
			break;
		case ID_PICTURE:
			Picture(hWnd);
			i = 5;
			break;
		case ID_FRONT:
			Front(hWnd);
			i = 6;
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
	case WM_PAINT:
		ValidateRect(hWnd, NULL);
		Paint(hWnd);
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

void Paint(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);

	switch (i)
	{
	case 1:
		DrawPoint(hwnd);
		break;
	case 2:
		DrawLine(hwnd);
		break;
	case 3:
		DrawCircle(hwnd);
		break;
	case 4:
		DrawRect(hwnd);
		break;
	case 5:
		Picture(hwnd);
		break;
	case 6:
		Front(hwnd);
		break;
	}

	ReleaseDC(hwnd, hdc);
}

void DrawPoint(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			SetPixel(hdc, i, j, RGB(i, j, 0));
		}
	}
	ReleaseDC(hwnd, hdc);
}

void DrawLine(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	HPEN hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
	HGDIOBJ old = SelectObject(hdc, hPen);
	MoveToEx(hdc, 100, 100, NULL);//设置起点
	LineTo(hdc, 300, 300);
	LineTo(hdc, 300, 100);
	LineTo(hdc, 100, 300);
	LineTo(hdc, 100, 100);
	SelectObject(hdc, old);
	DeleteObject(hPen);
	ReleaseDC(hwnd, hdc);
}

void DrawCircle(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
	HGDIOBJ old = SelectObject(hdc, hBrush);
	Ellipse(hdc, 100, 100, 300, 300);
	SelectObject(hdc, old);
	DeleteObject(hBrush);
	ReleaseDC(hwnd, hdc);
}

void DrawRect(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	HBRUSH hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(0, 255, 0));
	HGDIOBJ old = SelectObject(hdc, hBrush);
	Rectangle(hdc, 100, 100, 300, 300);
	SelectObject(hdc, old);
	DeleteObject(hBrush);
	ReleaseDC(hwnd, hdc);
}

void Picture(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP hbitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP));
	HGDIOBJ old = SelectObject(memdc, hbitmap);
	BITMAP bitmap = { 0 };
	GetObject(hbitmap, sizeof(bitmap), &bitmap);
	BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, memdc, 0, 0, SRCCOPY);//等比例
	StretchBlt(hdc, 300, 300, bitmap.bmWidth * 2, bitmap.bmHeight * 2, memdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);//非等比例
	SelectObject(hdc, old);
	DeleteObject(hbitmap);
	DeleteDC(memdc);
	ReleaseDC(hwnd, hdc);
}

void Front(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkColor(hdc, RGB(0, 255, 0));
	//SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, 100, 100, L"哈哈", wcslen(L"哈哈"));
	RECT rect;
	rect.top = 300;
	rect.bottom = 600;
	rect.left = 300;
	rect.right = 600;
	DrawText(hdc, L"哈哈", wcslen(L"哈哈"), &rect, NULL);
	ReleaseDC(hwnd, hdc);
}
