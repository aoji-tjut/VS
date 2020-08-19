#include <Windows.h>
#include <deque>
#include <time.h>
using namespace std;

#define R	40
#define D	50

union CH
{
	BOOL up, down, left, right;
};

struct Circle
{
	UINT left, top, right, bottom;
	RECT rect;
	CH ch;
};

HWND hWnd;
deque<Circle> Q;
deque<Circle>::iterator itemove;
deque<Circle>::iterator itepaint;
HANDLE hEvent1;
HANDLE hEvent2;
int i = 1;

LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
DWORD CALLBACK MoveThread(LPVOID p);
DWORD CALLBACK NewThread(LPVOID p);
DWORD CALLBACK DeleteThread(LPVOID p);
void OnCreate();
void OnPaint();
void NewCircle();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex;
	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.hCursor = NULL;
	wcex.hIcon = NULL;
	wcex.hIconSm = NULL;
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"游戏";
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"注册失败", L"提示", MB_OK | MB_ICONERROR);
		return -1;
	}

	HWND hWnd;
	hWnd = CreateWindow(L"游戏", NULL, WS_SYSMENU,
		CW_USEDEFAULT, 0, 816, 239, NULL, NULL, hInstance, NULL);
	
	if (!hWnd)
	{
		MessageBox(NULL, L"创建失败", L"提示", MB_OK | MB_ICONERROR);
		return -1;
	}
	::hWnd = hWnd;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	switch (nMsg)
	{
	case WM_CREATE:
		OnCreate();
		break;
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		OnPaint();
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
		{
						 HANDLE h1 = CreateThread(0, 0, MoveThread, NULL, 0, 0);
						 CloseHandle(h1);
						 HANDLE h2 = CreateThread(0, 0, NewThread, NULL, 0, 0);
						 CloseHandle(h2);
						 HANDLE h3 = CreateThread(0, 0, DeleteThread, NULL, 0, 0);
						 CloseHandle(h3);
		}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

void OnCreate()  
{
	srand((UINT)time(NULL));
	hEvent1 = CreateEvent(NULL, FALSE, FALSE, NULL);
	hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
	NewCircle();
}

void NewCircle()
{
	Circle* C = new Circle;
	memset(C, 0, sizeof(C));
	C->left = 800;
	C->top = 0;
	C->right = 1000;
	C->bottom = 200;

	switch (rand() % 4)
	{
	case 0:
		C->ch.up = TRUE;
		C->rect.left = (C->right + C->left) / 2 - R / 2;
		C->rect.top = C->top;
		C->rect.right = (C->right + C->left) / 2 + R / 2;
		C->rect.bottom = C->top + D;
		break;
	case 1:
		C->ch.down = TRUE;
		C->rect.left = (C->right + C->left) / 2 - R / 2;
		C->rect.top = C->bottom - D;
		C->rect.right = (C->right + C->left) / 2 + R / 2;
		C->rect.bottom = C->bottom;
		break;
	case 2:
		C->ch.left = TRUE;
		C->rect.left = C->left;
		C->rect.top = (C->bottom + C->top) / 2 - R / 2;
		C->rect.right = C->left + D;
		C->rect.bottom = (C->bottom + C->top) / 2 + R / 2;
		break;
	case 3:
		C->ch.right = TRUE;
		C->rect.left = C->right - D;
		C->rect.top = (C->bottom + C->top) / 2 - R / 2;
		C->rect.right = C->right;
		C->rect.bottom = (C->bottom + C->top) / 2 + R / 2;
		break;
	}
	Q.push_back(*C);
}

void OnPaint()
{
	HDC hdc = GetDC(hWnd);
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, 800, 200);
	SelectObject(memdc, hBitmap);
	HBRUSH hBrush;

	for (itepaint = Q.begin(); itepaint != Q.end(); itepaint++)
	{
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		SelectObject(memdc, hBrush);

		Ellipse(memdc, itepaint->left, itepaint->top, itepaint->right, itepaint->bottom);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(memdc, hBrush);
		Rectangle(memdc, itepaint->rect.left, itepaint->rect.top, itepaint->rect.right, itepaint->rect.bottom);
		Ellipse(memdc, itepaint->left + R, itepaint->top + R, itepaint->right - R, itepaint->bottom - R);
		DeleteObject(hBrush);
	}

	BitBlt(hdc, 0, 0, 800, 200, memdc, 0, 0, SRCCOPY);

	DeleteObject(hBitmap);
	DeleteDC(memdc);
	ReleaseDC(hWnd, hdc);
}

DWORD CALLBACK MoveThread(LPVOID p)
{
	while (1)
	{
		haha:
		for (itemove = Q.begin(); itemove != Q.end(); itemove++)
		{
			if (i)
			{
				itemove->left -= 50;
				itemove->right -= 50;
				itemove->rect.left -= 50;
				itemove->rect.right -= 50;
			}
			else goto haha;
		}
		Sleep(100);
		InvalidateRect(hWnd, NULL, TRUE);
	}

	return 0;
}

DWORD CALLBACK NewThread(LPVOID p)
{
	while (1)
	{
		if (Q.back().right < 800)
		{
			i = 0;
			NewCircle();
			i = 1;
		}
	}
}

DWORD CALLBACK DeleteThread(LPVOID p)
{
	while (1)
	{
		if (Q.front().left < 50)
		{
			i = 0;
			delete &Q.front();
			Q.pop_front();
			i = 1;
		}
	}

	return 0;
}