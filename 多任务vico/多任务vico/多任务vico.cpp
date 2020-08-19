// 多任务vico.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "多任务vico.h"
#include <process.h>
#include <time.h>

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcOne(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcTwo(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcThree(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcFour(HWND, UINT, WPARAM, LPARAM);
int Line(HWND hwnd, int cy, int fy, int line);
void One(PVOID pvoid);
void Two(PVOID pvoid);
void Three(PVOID pvoid);
void Four(PVOID pvoid);

typedef struct Data
{
	HWND hwnd;
	int cx;
	int cy;
	int fx;
	int fy;
	BOOL kill;
}DATA, *PDATA;

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
	LoadString(hInstance, IDC_VICO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VICO));

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



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VICO));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;// MAKEINTRESOURCE(IDC_VICO);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInst;
	WNDCLASS wc;
	static HWND hChild[4];
	static TCHAR* ChildClass[4] = { TEXT("One"), TEXT("Two"), TEXT("Three"), TEXT("Four")};
	static WNDPROC ChildProc[4] = { WndProcOne, WndProcTwo, WndProcThree, WndProcFour };
	int cx, cy, i;
	 
	switch (message)
	{
	case WM_CREATE:
		hInst = (HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE);

		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.hCursor = NULL;
		wc.hIcon = NULL;
		wc.hInstance = hInst;
		wc.lpszMenuName = NULL;
		wc.style = CS_HREDRAW | CS_VREDRAW;

		for (i = 0; i < 4; i++)
		{
			wc.lpfnWndProc = ChildProc[i];
			wc.lpszClassName = ChildClass[i];

			RegisterClass(&wc);

			hChild[i] = CreateWindow(ChildClass[i], NULL, WS_CHILDWINDOW | WS_BORDER | WS_VISIBLE,
				100, 100, 100, 100, hWnd, (HMENU)i, hInst, NULL);
		}
		break;
	case WM_SIZE:
		cx = LOWORD(lParam);
		cy = HIWORD(lParam);
		for (i = 0; i < 4; i++)
		{
			MoveWindow(hChild[i], (i % 2)*cx / 2, (i>1)*cy / 2, cx / 2, cy / 2, TRUE);
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			DestroyWindow(hWnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int Line(HWND hwnd,int cy,int fy,int line)
{
	if (line*fy + fy > cy)
	{
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);
		line = 0;
	}
	return line;
}

void One(PVOID pvoid)
{
	HDC hdc;
	PDATA pdata;
	TCHAR str[50];
	int line = 0;

	pdata = (PDATA)pvoid;

	while (!pdata->kill)
	{
		line = Line(pdata->hwnd, pdata->cy, pdata->fy, line);
		hdc = GetDC(pdata->hwnd);
		TextOut(hdc, pdata->cx / 2 - pdata->fx * lstrlen(L"请叫我嘴哥!!!") / 2, line*pdata->fy, str, wsprintf(str, L"%s", L"请叫我嘴哥!!!"));
		TextOut(hdc, pdata->cx / 4 * 1 - pdata->fx * lstrlen(L"请叫我嘴哥!!!") / 2, line*pdata->fy, str, wsprintf(str, L"%s", L"请叫我嘴哥!!!"));
		TextOut(hdc, pdata->cx / 4 * 3 - pdata->fx * lstrlen(L"请叫我嘴哥!!!") / 2, line*pdata->fy, str, wsprintf(str, L"%s", L"请叫我嘴哥!!!"));
		ReleaseDC(pdata->hwnd, hdc);
		line++;
	}

	_endthread();
}

LRESULT CALLBACK WndProcOne(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static DATA data;

	switch (message)
	{
	case WM_CREATE:
		data.hwnd = hWnd;
		data.fx = LOWORD(GetDialogBaseUnits());
		data.fy = HIWORD(GetDialogBaseUnits());
		_beginthread(One, 0, &data);
		break;
	case WM_SIZE:
		data.cy = HIWORD(lParam);
		data.cx = LOWORD(lParam);
		break;
	case WM_DESTROY:
		data.kill = TRUE;
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void Two(PVOID pvoid)
{
	HDC hdc;
	PDATA pdata;
	HPEN hPen;
	int x1, y1, x2, y2;
	int r, g, b;

	pdata = (PDATA)pvoid;

	while (!pdata->kill)
	{
		x1 = rand() % pdata->cx;
		y1 = rand() % pdata->cy;
		x2 = rand() % pdata->cx;
		y2 = rand() % pdata->cy;
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;

		InvalidateRect(pdata->hwnd, NULL, FALSE);
		UpdateWindow(pdata->hwnd);

		hdc = GetDC(pdata->hwnd);
		hPen = CreatePen(PS_SOLID, 5, RGB(r, g, b));
		SelectObject(hdc, hPen);
		MoveToEx(hdc, x2, y2, NULL);
		LineTo(hdc, x1, y1);
		DeleteObject(hPen);
		ReleaseDC(pdata->hwnd, hdc);

		Sleep(10);
	}

	_endthread();
}

LRESULT CALLBACK WndProcTwo(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static DATA data;

	switch (message)
	{
	case WM_CREATE:
		data.hwnd = hWnd;
		_beginthread(Two, 0, &data);
		break;
	case WM_SIZE:
		data.cy = HIWORD(lParam);
		data.cx = LOWORD(lParam);
		break;
	case WM_DESTROY:
		data.kill = TRUE;
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void Three(PVOID pvoid)
{
	HDC hdc;
	PDATA pdata;
	HBRUSH hBrush;
	int x, y, w, h;
	int r, g, b;

	pdata = (PDATA)pvoid;

	while (!pdata->kill)
	{
		x = rand() % pdata->cx;
		w = rand() % pdata->cx;
		y = rand() % pdata->cy;
		h = rand() % pdata->cy;
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;

		InvalidateRect(pdata->hwnd, NULL, FALSE);
		UpdateWindow(pdata->hwnd);

		hdc = GetDC(pdata->hwnd);
		hBrush = CreateSolidBrush(RGB(r, g, b));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, x, y, w, h);
		DeleteObject(hBrush);
		ReleaseDC(pdata->hwnd, hdc);

		Sleep(10);
	}

	_endthread();
}

LRESULT CALLBACK WndProcThree(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static DATA data;

	switch (message)
	{
	case WM_CREATE:
		srand((unsigned)time(NULL));
		data.hwnd = hWnd;
		_beginthread(Three, 0, &data);
		break;
	case WM_SIZE:
		data.cy = HIWORD(lParam);
		data.cx = LOWORD(lParam);
		break;
	case WM_DESTROY:
		data.kill = TRUE;
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void Four(PVOID pvoid)
{
	HDC hdc;
	HBRUSH hBrush;
	PDATA pdata;
	int R;
	int r, g, b;

	pdata = (PDATA)pvoid;	

	while (!pdata->kill)
	{
		R = rand() % min(pdata->cx, pdata->cy) / 2;
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;

		InvalidateRect(pdata->hwnd, NULL, TRUE);
		UpdateWindow(pdata->hwnd);

		hdc = GetDC(pdata->hwnd);
		hBrush = CreateSolidBrush(RGB(r, g, b));
		SelectObject(hdc, hBrush);
		Ellipse(hdc, pdata->cx / 2 - R, pdata->cy / 2 - R, pdata->cx / 2 + R, pdata->cy / 2 + R);
		DeleteObject(hBrush);
		ReleaseDC(pdata->hwnd, hdc);

		Sleep(10);
	}

	_endthread();
}

LRESULT CALLBACK WndProcFour(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static DATA data;

	switch (message)
	{
	case WM_CREATE:
		srand((unsigned)time(NULL));
		data.hwnd = hWnd;
		_beginthread(Four, 0, &data);
		break;
	case WM_SIZE:
		data.cy = HIWORD(lParam);
		data.cx = LOWORD(lParam);
		break;
	case WM_DESTROY:
		data.kill = TRUE;
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}