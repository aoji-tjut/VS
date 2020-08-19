// 多文档UI.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "多文档UI.h"

#define MAX_LOADSTRING	100
#define INIT_MENU_POS	0
#define	TEXT_MENU_POS	1
#define RECT_MENU_POS	2
#define IDM_FIRSTCHILD	1000


HINSTANCE hInst;
HMENU hMenuInit, hMenuText, hMenuRect;
HMENU hMenuInitWindow, hMenuTextWindow, hMenuRectWindow;
TCHAR szWindowClass[] = L"UI";
TCHAR szTitle[] = L"多文档UI";
TCHAR szTextClass[] = L"TextChild";
TCHAR szRectClass[] = L"RectChild";


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK		CloseMenuProc(HWND, LPARAM);
LRESULT CALLBACK	TextWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	RectWndProc(HWND, UINT, WPARAM, LPARAM);

typedef struct Text
{
	UINT iColor;
	COLORREF clrText;
}TEXTDATA,*LPTEXTDATA;

typedef struct Rect
{
	short cxClient;
	short cyClient;
}RECTDATA,*LPRECTDATA;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	HWND hWnd;
	HWND hClient;
	MSG msg;
	HACCEL hAccelTable;
	WNDCLASS wc;

	hInst = hInstance;

	/**************************父窗口*****************************/
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = TextWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)3;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENUINIT);
	wc.lpszClassName = szWindowClass;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, L"注册失败", L"提示", MB_OK);
		return -1;
	}
	/**************************文本窗口*****************************/
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = TextWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof(HANDLE);//子窗口内存
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szTextClass;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, L"注册失败", L"提示", MB_OK);
		return -1;
	}
	/**************************矩形窗口*****************************/
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = RectWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof(HANDLE);//子窗口内存
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szRectClass;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, L"注册失败", L"提示", MB_OK);
		return -1;
	}
	/**************************菜单显示*****************************/
	hMenuInit = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENUINIT));
	hMenuText = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENUTEXT));
	hMenuRect = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENURECT));
	hMenuInitWindow = GetSubMenu(hMenuInit, INIT_MENU_POS);
	hMenuTextWindow = GetSubMenu(hMenuText, TEXT_MENU_POS);
	hMenuRectWindow = GetSubMenu(hMenuRect, RECT_MENU_POS);

	hAccelTable = LoadAccelerators(hInst, szTitle);

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	hClient = GetWindow(hWnd, GW_CHILD);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateMDISysAccel(hClient, &msg) &&
			!TranslateAccelerator(hWnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	DestroyMenu(hMenuText);
	DestroyMenu(hMenuRect);

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CLIENTCREATESTRUCT ccs;
	MDICREATESTRUCT mcs;
	static HWND hClient;
	static HWND hChild;

	switch (message)
	{
	case WM_CREATE:
		ccs.hWindowMenu = hMenuInitWindow;
		ccs.idFirstChild = IDM_FIRSTCHILD;
		hClient = CreateWindow(L"MDICLIENT", NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)1, hInst, (PSTR)&ccs);
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefFrameProc(hWnd, hClient, message, wParam, lParam);//返回多文档
	}
	return 0;
}

BOOL CALLBACK CloseMenuProc(HWND hWnd, LPARAM)
{
	if (GetWindow(hWnd, GW_OWNER))
	{
		return TRUE;
	}

	SendMessage(GetParent(hWnd), WM_MDIRESTORE, (WPARAM)hWnd, 0);

	if (!SendMessage(hWnd, WM_QUERYENDSESSION, 0, 0))
	{
		return TRUE;
	}

	SendMessage(GetParent(hWnd), WM_MDIDESTROY, (WPARAM)hWnd, 0);

	return TRUE;
}

LRESULT CALLBACK TextWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static COLORREF clrTextArray[] = { RGB(0, 0, 0), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255) };
	static HWND hClient, hFrame;
	HDC hdc;
	HMENU hMenu;
	LPTEXTDATA pTextData;
	PAINTSTRUCT ps;
	RECT rect;

	switch (message)
	{
	case WM_CREATE:
		pTextData = (LPTEXTDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(LPTEXTDATA));
		pTextData->iColor = IDM_COLOR_BLACK;
		pTextData->clrText = RGB(0, 0, 0);
		SetWindowLong(hWnd, 0, (long)pTextData);
		hClient = GetParent(hWnd);
		hFrame = GetParent(hClient);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_COLOR_BLACK:
		case IDM_COLOR_RED:
		case IDM_COLOR_GREEN:
		case IDM_COLOR_BLUE:
			pTextData = (LPTEXTDATA)GetWindowLong(hWnd, 0);
			hMenu = GetMenu(hFrame);
			CheckMenuItem(hMenu, pTextData->iColor, MF_UNCHECKED);
			pTextData->iColor = wParam;
			CheckMenuItem(hMenu, pTextData->iColor, MF_CHECKED);
			pTextData->clrText = clrTextArray[wParam - IDM_COLOR_BLACK];
			InvalidateRect(hWnd, NULL, FALSE);
		default:
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		pTextData = (LPTEXTDATA)GetWindowLong(hWnd, 0);
		SetTextColor(hdc, pTextData->clrText);
		DrawText(hdc, L"嘴哥V5", -1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		EndPaint(hWnd, &ps);
		break;
	case WM_MDIACTIVATE:
		if (lParam == (LPARAM)hWnd)
		{
			SendMessage(hClient, WM_MDISETMENU, 
				(WPARAM)hMenuText, (LPARAM)hMenuTextWindow);
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return DefMDIChildProc(hWnd, message, wParam, lParam);//返回子窗口
}

LRESULT CALLBACK RectWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	

	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return DefMDIChildProc(hWnd, message, wParam, lParam);//返回子窗口
}