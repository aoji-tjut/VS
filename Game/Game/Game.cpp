#include "stdafx.h"
#include "Game.h"
#include <process.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' "\
	"name='Microsoft.Windows.Common-Controls' "\
	"version='6.0.0.0' processorArchitecture='*' "\
	"publicKeyToken='6595b64144ccf1df' language='*'\"")

#define MAX_LOADSTRING 100
#define MOVE	1;

struct CH
{
	bool up;
	bool down;
	bool left;
	bool right;
};

struct DATA
{
	RECT rect;
	CH ch;
};

HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND hWnd;
DATA data[4];
RECT limit;
COORD mouse;
DWORD sleep;
DWORD start, end;
BOOL paint;
UINT msg;

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD CALLBACK One(LPVOID p);
DWORD CALLBACK Two(LPVOID p);
DWORD CALLBACK Three(LPVOID p);
DWORD CALLBACK Four(LPVOID p);
DWORD CALLBACK Paint(LPVOID p);
DWORD CALLBACK ChangeSleep(LPVOID p);
void OnCreate();
void OnPaint();
void Over();
void Limit();

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
	LoadString(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));

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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 将实例句柄存储在全局变量中

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 716, 739, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	::hWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool flag = TRUE;

	switch (message)
	{
	case WM_CREATE:
		OnCreate();
		break;
	case WM_MOUSEMOVE:
		mouse.X = LOWORD(lParam);
		mouse.Y = HIWORD(lParam);
		Limit();
		break;
	case WM_LBUTTONDOWN:
		if (flag && mouse.X + 20 < 650 && mouse.X - 20 > 50 && mouse.Y + 20 < 650 && mouse.Y - 20 > 50)
		{
			ShowCursor(FALSE);
			msg = WM_LBUTTONDOWN;

			HANDLE h[5] = { 0 };
			h[0] = CreateThread(NULL, 0, One, NULL, 0, NULL);
			h[1] = CreateThread(NULL, 0, Two, NULL, 0, NULL);
			h[2] = CreateThread(NULL, 0, Three, NULL, 0, NULL);
			h[3] = CreateThread(NULL, 0, Four, NULL, 0, NULL);
			h[4] = CreateThread(NULL, 0, ChangeSleep, NULL, 0, NULL);

			start = GetTickCount();

			for (int i = 0; i < 5; i++)
			{
				CloseHandle(h[i]);
			}

			flag = FALSE;
		}
		break;
	case WM_LBUTTONUP:
		if (!flag)
		{
			msg = NULL;
			Over();
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			break;
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

DWORD CALLBACK One(LPVOID p)
{
	while (msg == WM_LBUTTONDOWN)
	{
		if (data[0].rect.left < 0)
		{
			data[0].ch.left = FALSE;
			data[0].ch.right = TRUE;
		}
		if (data[0].rect.right > 700)
		{
			data[0].ch.left = TRUE;
			data[0].ch.right = FALSE;
		}
		if (data[0].rect.top < 0)
		{
			data[0].ch.up = FALSE;
			data[0].ch.down = TRUE;
		}
		if (data[0].rect.bottom > 700)
		{
			data[0].ch.up = TRUE;
			data[0].ch.down = FALSE;
		}

		if (data[0].ch.up)
		{
			data[0].rect.top -= MOVE;
			data[0].rect.bottom -= MOVE;
		}
		if (data[0].ch.down)
		{
			data[0].rect.top += MOVE;
			data[0].rect.bottom += MOVE;
		}
		if (data[0].ch.left)
		{
			data[0].rect.left -= MOVE;
			data[0].rect.right -= MOVE;
		}
		if (data[0].ch.right)
		{
			data[0].rect.left += MOVE;
			data[0].rect.right += MOVE;
		}

		if ((mouse.X + 20 > data[0].rect.left && mouse.Y + 20 > data[0].rect.top &&
			mouse.X + 20 < data[0].rect.right && mouse.Y + 20 < data[0].rect.bottom) ||
			(mouse.X - 20 < data[0].rect.right && mouse.Y + 20 > data[0].rect.top &&
			mouse.X - 20 > data[0].rect.left && mouse.Y + 20 < data[0].rect.bottom) ||
			(mouse.X + 20 > data[0].rect.left && mouse.Y - 20 < data[0].rect.bottom &&
			mouse.X + 20 < data[0].rect.right && mouse.Y - 20 > data[0].rect.top) ||
			(mouse.X - 20 < data[0].rect.right && mouse.Y - 20 < data[0].rect.bottom &&
			mouse.X - 20 > data[0].rect.left && mouse.Y - 20 > data[0].rect.top))
		{
			Over();
			return 0;
		}
		
		Sleep(sleep);
	}

	return 0;
}

DWORD CALLBACK Two(LPVOID p)
{
	while (msg == WM_LBUTTONDOWN)
	{
		if (data[1].rect.left <= 0)
		{
			data[1].ch.left = FALSE;
			data[1].ch.right = TRUE;
		}
		if (data[1].rect.right >= 700)
		{
			data[1].ch.left = TRUE;
			data[1].ch.right = FALSE;
		}
		if (data[1].rect.top <= 0)
		{
			data[1].ch.up = FALSE;
			data[1].ch.down = TRUE;
		}
		if (data[1].rect.bottom >= 700)
		{
			data[1].ch.up = TRUE;
			data[1].ch.down = FALSE;
		}

		if (data[1].ch.up)
		{
			data[1].rect.top -= MOVE;
			data[1].rect.bottom -= MOVE;
		}
		if (data[1].ch.down)
		{
			data[1].rect.top += MOVE;
			data[1].rect.bottom += MOVE;
		}
		if (data[1].ch.left)
		{
			data[1].rect.left -= MOVE;
			data[1].rect.right -= MOVE;
		}
		if (data[1].ch.right)
		{
			data[1].rect.left += MOVE;
			data[1].rect.right += MOVE;
		}

		if ((mouse.X + 20 > data[1].rect.left && mouse.Y + 20 > data[1].rect.top &&
			mouse.X + 20 < data[1].rect.right && mouse.Y + 20 < data[1].rect.bottom) ||
			(mouse.X - 20 < data[1].rect.right && mouse.Y + 20 > data[1].rect.top &&
			mouse.X - 20 > data[1].rect.left && mouse.Y + 20 < data[1].rect.bottom) ||
			(mouse.X + 20 > data[1].rect.left && mouse.Y - 20 < data[1].rect.bottom &&
			mouse.X + 20 < data[1].rect.right && mouse.Y - 20 > data[1].rect.top) ||
			(mouse.X - 20 < data[1].rect.right && mouse.Y - 20 < data[1].rect.bottom &&
			mouse.X - 20 > data[1].rect.left && mouse.Y - 20 > data[1].rect.top))
		{
			Over();
			return 0;
		}

		Sleep(sleep + 1);
	}

	return 0;
}

DWORD CALLBACK Three(LPVOID p)
{
	while (msg == WM_LBUTTONDOWN)
	{
		if (data[2].rect.left <= 0)
		{
			data[2].ch.left = FALSE;
			data[2].ch.right = TRUE;
		}
		if (data[2].rect.right >= 700)
		{
			data[2].ch.left = TRUE;
			data[2].ch.right = FALSE;
		}
		if (data[2].rect.top <= 0)
		{
			data[2].ch.up = FALSE;
			data[2].ch.down = TRUE;
		}
		if (data[2].rect.bottom >= 700)
		{
			data[2].ch.up = TRUE;
			data[2].ch.down = FALSE;
		}

		if (data[2].ch.up)
		{
			data[2].rect.top -= MOVE;
			data[2].rect.bottom -= MOVE;
		}
		if (data[2].ch.down)
		{
			data[2].rect.top += MOVE;
			data[2].rect.bottom += MOVE;
		}
		if (data[2].ch.left)
		{
			data[2].rect.left -= MOVE;
			data[2].rect.right -= MOVE;
		}
		if (data[2].ch.right)
		{
			data[2].rect.left += MOVE;
			data[2].rect.right += MOVE;
		}

		if ((mouse.X + 20 > data[2].rect.left && mouse.Y + 20 > data[2].rect.top &&
			mouse.X + 20 < data[2].rect.right && mouse.Y + 20 < data[2].rect.bottom) ||
			(mouse.X - 20 < data[2].rect.right && mouse.Y + 20 > data[2].rect.top &&
			mouse.X - 20 > data[2].rect.left && mouse.Y + 20 < data[2].rect.bottom) ||
			(mouse.X + 20 > data[2].rect.left && mouse.Y - 20 < data[2].rect.bottom &&
			mouse.X + 20 < data[2].rect.right && mouse.Y - 20 > data[2].rect.top) ||
			(mouse.X - 20 < data[2].rect.right && mouse.Y - 20 < data[2].rect.bottom &&
			mouse.X - 20 > data[2].rect.left && mouse.Y - 20 > data[2].rect.top))
		{
			Over();
			return 0;
		}

		Sleep(sleep + 2);
	}

	return 0;
}

DWORD CALLBACK Four(LPVOID p)
{
	while (msg == WM_LBUTTONDOWN)
	{
		if (data[3].rect.left <= 0)
		{
			data[3].ch.left = FALSE;
			data[3].ch.right = TRUE;
		}
		if (data[3].rect.right >= 700)
		{
			data[3].ch.left = TRUE;
			data[3].ch.right = FALSE;
		}
		if (data[3].rect.top <= 0)
		{
			data[3].ch.up = FALSE;
			data[3].ch.down = TRUE;
		}
		if (data[3].rect.bottom >= 700)
		{
			data[3].ch.up = TRUE;
			data[3].ch.down = FALSE;
		}

		if (data[3].ch.up)
		{
			data[3].rect.top -= MOVE;
			data[3].rect.bottom -= MOVE;
		}
		if (data[3].ch.down)
		{
			data[3].rect.top += MOVE;
			data[3].rect.bottom += MOVE;
		}
		if (data[3].ch.left)
		{
			data[3].rect.left -= MOVE;
			data[3].rect.right -= MOVE;
		}
		if (data[3].ch.right)
		{
			data[3].rect.left += MOVE;
			data[3].rect.right += MOVE;
		}

		if ((mouse.X + 20 > data[3].rect.left && mouse.Y + 20 > data[3].rect.top &&
			mouse.X + 20 < data[3].rect.right && mouse.Y + 20 < data[3].rect.bottom) ||
			(mouse.X - 20 < data[3].rect.right && mouse.Y + 20 > data[3].rect.top &&
			mouse.X - 20 > data[3].rect.left && mouse.Y + 20 < data[3].rect.bottom) ||
			(mouse.X + 20 > data[3].rect.left && mouse.Y - 20 < data[3].rect.bottom &&
			mouse.X + 20 < data[3].rect.right && mouse.Y - 20 > data[3].rect.top) ||
			(mouse.X - 20 < data[3].rect.right && mouse.Y - 20 < data[3].rect.bottom &&
			mouse.X - 20 > data[3].rect.left && mouse.Y - 20 > data[3].rect.top))
		{
			Over();
			return 0;
		}

		Sleep(sleep);
	}

	return 0;
}

DWORD CALLBACK ChangeSleep(LPVOID p)
{
	while (sleep)
	{
		Sleep(10000);
		sleep -= 1;
		if (sleep == 1)
		{
			break;
		}
	}

	return 0;
}

DWORD CALLBACK Paint(LPVOID p)
{
	while (paint)
	{
		OnPaint();
	}

	return 0;
}

void OnCreate()
{
	srand((unsigned int)time(NULL));

	paint = TRUE;
	sleep = 3;

	limit.left = 50;
	limit.top = 50;
	limit.right = 650;
	limit.bottom = 650;

	while (1)
	{
		data[0].rect.left = rand() % 350;
		data[0].rect.top = rand() % 350;
		data[0].rect.right = rand() % 350;
		data[0].rect.bottom = rand() % 350;

		if (data[0].rect.right - data[0].rect.left > 50 && data[0].rect.bottom - data[0].rect.top > 50 &&
			data[0].rect.right - data[0].rect.left < 200 && data[0].rect.bottom - data[0].rect.top < 200)
		{
			break;
		}
	}
	data[0].ch.left = TRUE;
	data[0].ch.up = TRUE;

	while (1)
	{
		data[1].rect.left = rand() % 350 + 350;
		data[1].rect.top = rand() % 350;
		data[1].rect.right = rand() % 350 + 350;
		data[1].rect.bottom = rand() % 350;

		if (data[1].rect.right - data[1].rect.left > 50 && data[1].rect.bottom - data[1].rect.top > 50 &&
			data[1].rect.right - data[1].rect.left < 200 && data[1].rect.bottom - data[1].rect.top < 200)
		{
			break;
		}
	}
	data[1].ch.right = TRUE;
	data[1].ch.up = TRUE;

	while (1)
	{
		data[2].rect.left = rand() % 350;
		data[2].rect.top = rand() % 350 + 350;
		data[2].rect.right = rand() % 350;
		data[2].rect.bottom = rand() % 350 + 350;

		if (data[2].rect.right - data[2].rect.left > 50 && data[2].rect.bottom - data[2].rect.top > 50 &&
			data[2].rect.right - data[2].rect.left < 200 && data[2].rect.bottom - data[2].rect.top < 200)
		{
			break;
		}
	}
	data[2].ch.left = TRUE;
	data[2].ch.down = TRUE;

	while (1)
	{
		data[3].rect.left = rand() % 350 + 350;
		data[3].rect.top = rand() % 350 + 350;
		data[3].rect.right = rand() % 350 + 350;
		data[3].rect.bottom = rand() % 350 + 350;

		if (data[3].rect.right - data[3].rect.left > 50 && data[3].rect.bottom - data[3].rect.top > 50 &&
			data[3].rect.right - data[3].rect.left < 200 && data[3].rect.bottom - data[3].rect.top < 200)
		{
			break;
		}
	}
	data[3].ch.right = TRUE;
	data[3].ch.down = TRUE;

	HANDLE h = CreateThread(NULL, 0, Paint, NULL, 0, NULL);
	CloseHandle(h);
}

void OnPaint()
{
	HDC hDc = GetDC(hWnd);
	HDC hMemdc = CreateCompatibleDC(hDc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDc, 700, 700);
	SelectObject(hMemdc, hBitmap);
	HBRUSH hBrush;

	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	SelectObject(hMemdc, hBrush);
	Rectangle(hMemdc, 0, 0, 700, 700);
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(RGB(0, 0, 255));
	SelectObject(hMemdc, hBrush);
	Rectangle(hMemdc, limit.left, limit.top, limit.right, limit.bottom);
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(RGB(0, 255, 0));
	SelectObject(hMemdc, hBrush);
	for (int i = 0; i < 4; i++)
	{
		Rectangle(hMemdc, data[i].rect.left, data[i].rect.top, data[i].rect.right, data[i].rect.bottom);
	}
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(RGB(255, 0, 255));
	SelectObject(hMemdc, hBrush);
	Rectangle(hMemdc, mouse.X - 20, mouse.Y - 20, mouse.X + 20, mouse.Y + 20);
	DeleteObject(hBrush);

	BitBlt(hDc, 0, 0, 700, 700, hMemdc, 0, 0, SRCCOPY);

	DeleteObject(hBitmap);
	DeleteDC(hMemdc);
	ReleaseDC(hWnd, hDc);
}

void Limit()
{
	if (msg)
	{
		if (mouse.X - 20 <= limit.left || mouse.X + 20 >= limit.right ||
			mouse.Y - 20 <= limit.top || mouse.Y + 20 >= limit.bottom)
		{
			Over();
		}
	}
}

void Over()
{
	paint = FALSE;
	msg = NULL;
	end = GetTickCount();
	ShowCursor(TRUE);
	TCHAR str[64] = { 0 };
	wsprintf(str, L"Game Over!\n坚持%ld秒!", (end - start) / 1000);
	MessageBox(hWnd, str, L"提示", MB_OK | MB_ICONINFORMATION);
	SendMessage(hWnd, WM_DESTROY, 0, 0);
}
