// ���ԭ������˹����.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "���ԭ������˹����.h"
#include <stdio.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' "\
	"name='Microsoft.Windows.Common-Controls' "\
	"version='6.0.0.0' processorArchitecture='*' "\
	"publicKeyToken='6595b64144ccf1df' language='*'\"")

#define MAX_LOADSTRING	100
#define TIMERID			1
#define Difficult		100
#define SCORE			10
#define FONT_HEIGHT		20
#define FONT_WIDTH		10

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HWND hWnd;
char A[20][10];
char a[2][4];
char B[20][10];
char b[2][4];
int Time = 500;
int TimeFlag;
int i;
int Flag;
int NextFlag;
int Line, List;
int Score;
int MaxScore;
bool Game = FALSE;

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void OnCreate();
void OnTimer();
void OnPaint();
void OnUp();
void OnDown();
void OnLeft();
void OnRight();

void PaintSqare1(HDC MemDc);
void PaintSqare2(HDC MemDc);
void PaintSqare3(HDC MemDc);
void PaintSqare4(HDC MemDc);
void PaintSqare5(HDC MemDc);
void PaintSqare6(HDC MemDc);
void PaintSqare7(HDC MemDc);
void PaintScore(HDC MemDc);
void PaintOver(HDC MemDc);

void LeftMove();
void RightMove();
void DownMove();

bool JudgeLeftMove1();
bool JudgeLeftMove2();
bool JudgeRightMove1();
bool JudgeRightMove2();
bool JudgeDownMove1();
bool JudgeDownMove2();
bool JudgeChangeSqare();
bool JudgeChangeLong();

void ChangeNum();
void ChangeSqare();
void ChangeLong();
void ChangeDifficult();

void CreateRandomSqare();
void CopySqareToBack();
void DestroyOneLine();
void GameOver();


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

	// ����Ϣѭ��: 
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
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MY);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 659, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	::hWnd = hWnd;

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu,hSubMenu;
	PAINTSTRUCT ps;
	HDC hdc;
	static int wmId, wmEvent;
	static int Layered, Gwl;
	static int SelectMenu;
	static int flag = 0;

	switch (message)
	{
	case WM_CREATE:
		OnCreate();
		break;
	case WM_INITMENUPOPUP:
		if (lParam == 0)
		{
			EnableMenuItem((HMENU)wParam, IDM_BEGAIN, flag ? MF_GRAYED : MF_ENABLED);
			EnableMenuItem((HMENU)wParam, IDM_STOP, flag ? MF_ENABLED : MF_GRAYED);
		}
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_BEGAIN:
			PlaySound((LPCSTR)IDR_WAVE1, NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
			flag = 1;
			break;
		case IDM_STOP:
			PlaySound(NULL, NULL, SND_PURGE);
			flag = 0;
			break;
		case IDM_LAYERED0:
		case IDM_LAYERED10:
		case IDM_LAYERED20:
		case IDM_LAYERED30:
		case IDM_LAYERED40:
		case IDM_LAYERED50:
		case IDM_LAYERED60:
		case IDM_LAYERED70:
		case IDM_LAYERED80:
		case IDM_LAYERED90:
		case IDM_LAYERED100:
			Layered = wmId - IDM_LAYERED0;
			Gwl = (int)GetWindowLong(hWnd, GWL_EXSTYLE);
			SetWindowLong(hWnd, GWL_EXSTYLE, Gwl | WS_EX_LAYERED);
			SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), (10 - Layered) / 10.0 * 255, LWA_ALPHA);
			
			hMenu = GetMenu(hWnd);
			hSubMenu = GetSubMenu(hMenu, 1);
			CheckMenuItem(hSubMenu, SelectMenu, MF_UNCHECKED);
			SelectMenu = LOWORD(wParam);
			CheckMenuItem(hSubMenu, SelectMenu, MF_CHECKED);
			break;
		case IDM_LAYERED_USER:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG), hWnd, DlgProc);
			hMenu = GetMenu(hWnd);
			hSubMenu = GetSubMenu(hMenu, 1);
			CheckMenuItem(hSubMenu, SelectMenu, MF_UNCHECKED);
			SelectMenu = LOWORD(wParam);
			CheckMenuItem(hSubMenu, SelectMenu, MF_CHECKED);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  �ڴ���������ͼ����...
		OnPaint();
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		OnTimer();
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			if (!Game)
			{
				SetTimer(hWnd, TIMERID, Time, NULL);
				Game = TRUE;
			}
			else
			{
				KillTimer(hWnd, TIMERID);
				Game = FALSE;
			}
			break;
		case VK_UP:
			if (Game)
			{
				OnUp();
			}
			break;
		case VK_LEFT:
			if (Game)
			{
				OnLeft();
			}
			break;
		case VK_RIGHT:
			if (Game)
			{
				OnRight();
			}
			break;
		case VK_DOWN:
			if (Game)
			{
				OnDown();
			}
			break;
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, TIMERID);
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
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

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit, hButton;
	char buf[10] = { 0 };
	static int i = 0;

	switch (message)
	{
	case WM_INITDIALOG:
		hEdit = GetDlgItem(hDlg, IDC_EDIT);
		hButton = GetDlgItem(hDlg, IDC_BUTTON);
		SetFocus(hEdit);
		break;
	case WM_COMMAND:
		if (((HWND)lParam == hButton) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, 10);
			if (!buf[0])
			{
				MessageBox(hDlg, "δ����", "��ʾ", MB_OK | MB_ICONERROR);
				break;
			}
			i = atoi(buf);
			if (i > 255 || i < 0)
			{
				MessageBox(hDlg, "��������", "��ʾ", MB_OK | MB_ICONERROR);
				break;
			}
			else
			{
				SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
				SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), i, LWA_ALPHA);
				EndDialog(hDlg, 0);
			}
		}
	case WM_SYSCOMMAND:
		if (LOWORD(wParam) == SC_CLOSE)
		{
			EndDialog(hDlg, 0);
		}
		break;
	}

	return 0;
}

void OnCreate()
{
	srand((unsigned int)time(NULL));

	i = 0;
	Time = 500;
	Score = 0;
	Game = FALSE;
	memset(A, 0, sizeof(A));
	memset(B, 0, sizeof(B));

	HANDLE hFile = CreateFile("��¼.txt", GENERIC_WRITE | GENERIC_READ, 
		FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	char buf[8];
	DWORD len = 0;
	ReadFile(hFile, buf, strlen(buf), &len, NULL);
	MaxScore = atoi(buf);
	CloseHandle(hFile);

	CreateRandomSqare();
	CopySqareToBack();
}

void OnTimer()
{
	if (JudgeDownMove1() && JudgeDownMove2())
	{
		DownMove();
		Line++;
	}
	else
	{
		ChangeNum();
		DestroyOneLine();
		ChangeDifficult();
		GameOver();
		CreateRandomSqare();
		CopySqareToBack();
	}

	OnPaint();
}

void OnPaint()
{
	HDC hdc = GetDC(hWnd);
	HDC MemDc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, 500, 659);
	HBRUSH hNewBrush, hOldBrush;
	HFONT hFont;

	SelectObject(MemDc, hBitmap);

	hFont = CreateFont(FONT_HEIGHT, FONT_WIDTH, NULL, NULL, FW_BOLD,
		NULL, NULL, NULL, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DRAFT_QUALITY, FIXED_PITCH | FF_SWISS, TEXT("������"));
	SelectObject(MemDc, hFont);

	SetBkMode(MemDc, TRANSPARENT);

	hNewBrush = CreateSolidBrush(RGB(128, 255, 255));
	hOldBrush = (HBRUSH)SelectObject(MemDc, hNewBrush);
	SelectObject(MemDc, hBitmap);
	Rectangle(MemDc, 0, 0, 300, 600);
	hNewBrush = (HBRUSH)SelectObject(MemDc, hOldBrush);
	DeleteObject(hNewBrush);

	hNewBrush = CreateSolidBrush(RGB(255, 255, 128));
	hOldBrush = (HBRUSH)SelectObject(MemDc, hNewBrush);
	Rectangle(MemDc, 300, 0, 484, 659);
	Rectangle(MemDc, 310, 260, 470, 340);
	hNewBrush = (HBRUSH)SelectObject(MemDc, hOldBrush);
	DeleteObject(hNewBrush);
	
	PaintSqare1(MemDc);
	PaintSqare2(MemDc);
	PaintSqare3(MemDc);
	PaintSqare4(MemDc);
	PaintSqare5(MemDc);
	PaintSqare6(MemDc);
	PaintSqare7(MemDc);
	PaintScore(MemDc);
	PaintOver(MemDc);

	BitBlt(hdc, 0, 0, 500, 659, MemDc, 0, 0, SRCCOPY);

	DeleteObject(hFont);
	DeleteObject(hBitmap);
	DeleteDC(MemDc);
	ReleaseDC(hWnd, hdc);
}

void OnUp()
{
	switch (Flag)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		if (JudgeChangeSqare())
		{
			ChangeSqare();
		}
		break;
	case 7:
		if (JudgeChangeLong())
		{
			ChangeLong();
		}
		break;
	default:
		break;
	}

	OnPaint();
}

void OnDown()
{
	OnTimer();
}

void OnLeft()
{
	if (JudgeLeftMove1() && JudgeLeftMove2())
	{
		LeftMove();
		List--;
		OnPaint();
	}
}

void OnRight()
{
	if (JudgeRightMove1() && JudgeRightMove2())
	{
		RightMove();
		List++;
		OnPaint();
	}
}

void PaintSqare1(HDC MemDc)
{
	static int i = 0, j = 0;
	HBRUSH hNewBrush, hOldBrush;

	hNewBrush = CreateSolidBrush(RGB(255, 0, 0));
	hOldBrush = (HBRUSH)SelectObject(MemDc, hNewBrush);

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (1 == A[i][j] || 10 == A[i][j])
			{
				Rectangle(MemDc, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
			if (1 == B[i][j])
			{
				Rectangle(MemDc, j * 30 + 315, i * 30 - 30, j * 30 + 30 + 315, i * 30);
			}
		}
	}

	hNewBrush = (HBRUSH)SelectObject(MemDc, hOldBrush);
	DeleteObject(hNewBrush);
}

void PaintSqare2(HDC MemDc)
{
	static int i = 0, j = 0;
	HBRUSH hNewBrush, hOldBrush;

	hNewBrush = CreateSolidBrush(RGB(255, 128, 0));
	hOldBrush = (HBRUSH)SelectObject(MemDc, hNewBrush);

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (2 == A[i][j] || 20 == A[i][j])
			{
				Rectangle(MemDc, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
			if (2 == B[i][j])
			{
				Rectangle(MemDc, j * 30 + 315, i * 30 - 30, j * 30 + 30 + 315, i * 30);
			}
		}
	}

	hNewBrush = (HBRUSH)SelectObject(MemDc, hOldBrush);
	DeleteObject(hNewBrush);
}

void PaintSqare3(HDC MemDc)
{
	static int i = 0, j = 0;
	HBRUSH hNewBrush, hOldBrush;

	hNewBrush = CreateSolidBrush(RGB(255, 255, 0));
	hOldBrush = (HBRUSH)SelectObject(MemDc, hNewBrush);

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (3 == A[i][j] || 30 == A[i][j])
			{
				Rectangle(MemDc, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
			if (3 == B[i][j])
			{
				Rectangle(MemDc, j * 30 + 315, i * 30 - 30, j * 30 + 30 + 315, i * 30);
			}
		}
	}

	hNewBrush = (HBRUSH)SelectObject(MemDc, hOldBrush);
	DeleteObject(hNewBrush);
}

void PaintSqare4(HDC MemDc)
{
	static int i = 0, j = 0;
	HBRUSH hNewBrush, hOldBrush;

	hNewBrush = CreateSolidBrush(RGB(0, 255, 0));
	hOldBrush = (HBRUSH)SelectObject(MemDc, hNewBrush);

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (4 == A[i][j] || 40 == A[i][j])
			{
				Rectangle(MemDc, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
			if (4 == B[i][j])
			{
				Rectangle(MemDc, j * 30 + 315, i * 30 - 30, j * 30 + 30 + 315, i * 30);
			}
		}
	}

	hNewBrush = (HBRUSH)SelectObject(MemDc, hOldBrush);
	DeleteObject(hNewBrush);
}

void PaintSqare5(HDC MemDc)
{
	static int i = 0, j = 0;
	HBRUSH hNewBrush, hOldBrush;

	hNewBrush = CreateSolidBrush(RGB(255, 0, 255));
	hOldBrush = (HBRUSH)SelectObject(MemDc, hNewBrush);

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (5 == A[i][j] || 50 == A[i][j])
			{
				Rectangle(MemDc, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
			if (5 == B[i][j])
			{
				Rectangle(MemDc, j * 30 + 315, i * 30 - 30, j * 30 + 30 + 315, i * 30);
			}
		}
	}

	hNewBrush = (HBRUSH)SelectObject(MemDc, hOldBrush);
	DeleteObject(hNewBrush);
}

void PaintSqare6(HDC MemDc)
{
	static int i = 0, j = 0;
	HBRUSH hNewBrush, hOldBrush;

	hNewBrush = CreateSolidBrush(RGB(0, 0, 255));
	hOldBrush = (HBRUSH)SelectObject(MemDc, hNewBrush);

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (6 == A[i][j] || 60 == A[i][j])
			{
				Rectangle(MemDc, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
			if (6 == B[i][j])
			{
				Rectangle(MemDc, j * 30 + 300, i * 30 - 30, j * 30 + 30 + 300, i * 30);
			}
		}
	}

	hNewBrush = (HBRUSH)SelectObject(MemDc, hOldBrush);
	DeleteObject(hNewBrush);
}

void PaintSqare7(HDC MemDc)
{
	static int i = 0, j = 0;
	HBRUSH hNewBrush, hOldBrush;

	hNewBrush = CreateSolidBrush(RGB(128, 0, 128));
	hOldBrush = (HBRUSH)SelectObject(MemDc, hNewBrush);

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (7 == A[i][j] || 70 == A[i][j])
			{
				Rectangle(MemDc, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
			if (7 == B[i][j])
			{
				Rectangle(MemDc, j * 30 + 300, i * 30 - 30, j * 30 + 30 + 300, i * 30);
			}
		}
	}

	hNewBrush = (HBRUSH)SelectObject(MemDc, hOldBrush);
	DeleteObject(hNewBrush);
}

void PaintScore(HDC MemDc)
{
	char strScore[8] = { 0 };
	char difficulty[8] = { 0 };
	char strMaxScore[8] = { 0 };

	sprintf(strScore, "%d", Score);
	sprintf(difficulty, "%dms", Time);
	sprintf(strMaxScore, "%d", MaxScore);

	SetTextColor(MemDc, RGB(0, 0, 0));
	TextOut(MemDc, 310, 20, "���ƣ�", strlen("���ƣ�"));
	TextOut(MemDc, 310, 50, "��ʼ/��ͣ���ո�", strlen("��ʼ/��ͣ���ո�"));
	TextOut(MemDc, 310, 80, "��ת����", strlen("��ת��	��"));
	TextOut(MemDc, 310, 110, "���٣���", strlen("���٣�	��"));
	TextOut(MemDc, 310, 140, "���ƣ���", strlen("���ƣ�	��"));
	TextOut(MemDc, 310, 170, "���ƣ���", strlen("���ƣ�	��"));
	SetTextColor(MemDc, RGB(0, 0, 255));
	TextOut(MemDc, 310, 230, "��һ����", strlen("��һ����"));
	SetTextColor(MemDc, RGB(255, 0, 0));
	TextOut(MemDc, 310, 370, "��ǰ������", strlen("��ǰ������"));
	TextOut(MemDc, 410, 370, strScore, strlen(strScore));
	TextOut(MemDc, 310, 400, "��ǰ�Ѷȣ�", strlen("��ǰ�Ѷȣ�"));
	TextOut(MemDc, 410, 400, difficulty, strlen(difficulty));
	TextOut(MemDc, 310, 430, "��߷�����", strlen("��߷�����"));
	TextOut(MemDc, 410, 430, strMaxScore, strlen(strMaxScore));
	SetTextColor(MemDc, RGB(0, 255, 0));
	TextOut(MemDc, 310, 500, "���ԭ������ؾ�", strlen("���ԭ������ؾ�"));
	TextOut(MemDc, 310, 530, "QQ��245611640", strlen("QQ��245611640"));
	TextOut(MemDc, 310, 560, "ôô��~~~~~~~", strlen("ôô��~~~~~~~"));
}

void PaintOver(HDC MemDc)
{
	static int i = 0, j = 0;
	HBRUSH hNewBrush, hOldBrush;

	hNewBrush = CreateSolidBrush(RGB(128, 128, 128));
	hOldBrush = (HBRUSH)SelectObject(MemDc, hNewBrush);

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (100 == A[i][j])
			{
				Rectangle(MemDc, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
		}
	}

	hNewBrush = (HBRUSH)SelectObject(MemDc, hOldBrush);
	DeleteObject(hNewBrush);
}

void LeftMove()
{
	static int i = 0, j = 0;

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (Flag == A[i][j])
			{
				A[i][j - 1] = A[i][j];
				A[i][j] = 0;
			}
		}
	}
}

void RightMove()
{
	static int i = 0, j = 0;

	for (i = 0; i < 20; i++)
	{
		for (j = 9; j >= 0; j--)
		{
			if (Flag == A[i][j])
			{
				A[i][j + 1] = A[i][j];
				A[i][j] = 0;
			}
		}
	}
}

void DownMove()
{
	static int i = 0, j = 0;

	for (i = 19; i >= 0; i--)
	{
		for (j = 0; j < 10; j++)
		{
			if (Flag == A[i][j])
			{
				A[i + 1][j] = A[i][j];
				A[i][j] = 0;
			}
		}
	}
}

bool JudgeLeftMove1()
{
	static int i = 0;

	for (i = 0; i < 20; i++)
	{
		if (A[i][0] == Flag)
		{
			return FALSE;
		}
	}

	return TRUE;
}

bool JudgeLeftMove2()
{
	static int i = 0, j = 0;

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (A[i][j] == Flag && A[i][j - 1] >= 10)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

bool JudgeRightMove1()
{
	static int i = 0;

	for (i = 0; i < 20; i++)
	{
		if (A[i][9] == Flag)
		{
			return FALSE;
		}
	}

	return TRUE;
}

bool JudgeRightMove2()
{
	static int i = 0, j = 0;

	for (i = 0; i < 20; i++)
	{
		for (j = 9; j >= 0; j--)
		{
			if (A[i][j] == Flag && A[i][j + 1] >= 10)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

bool JudgeDownMove1()
{
	static int i = 0;

	for (i = 0; i < 10; i++)
	{
		if (A[19][i] == Flag)
		{
			return FALSE;
		}
	}

	return TRUE;
}

bool JudgeDownMove2()
{
	static int i = 0, j = 0;

	for (i = 19; i >= 0; i--)
	{
		for (j = 0; j < 10; j++)
		{
			if (Flag == A[i][j] && A[i + 1][j] >= 10)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

bool JudgeChangeSqare()
{
	static int i = 0, j = 0;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (A[Line + i][List + j] >= 10)
			{
				return FALSE;
			}
		}
	}

	if (List < 0)
	{
		List = 0;
	}
	else if (List + 2 > 9)
	{
		List = 7;
	}

	return TRUE;
}

bool JudgeChangeLong()
{
	static int i = 0, j = 0;

	for (i = 1; i <= 3; i++)
	{
		if (A[Line][List + i] >= 10 || List + i > 9)
		{
			break;
		}
	}

	for (j = 1; j <= 3; j++)
	{
		if (A[Line][List - j] >= 10 || List - j < 0)
		{
			break;
		}
	}

	if (((i - 1) + (j - 1)) < 3)
	{
		return FALSE;
	}

	if (0 == Line)
	{
		return FALSE;
	}


	return TRUE;
}

void ChangeNum()
{
	static int i = 0, j = 0;

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (Flag == A[i][j])
			{
				A[i][j] = Flag * 10;
			}
		}
	}
}

void ChangeSqare()
{
	static int i = 0, j = 0, k = 0;
	char temp[3][3] = { 0 };

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			temp[i][j] = A[Line + i][List + j];
		}
	}

	for (i = 0; i < 3; i++)
	{
		k = 2;
		for (j = 0; j < 3; j++)
		{
			A[Line + i][List + j] = temp[k][i];
			k--;
		}
	}
}

void ChangeLong()
{
	if (7 == A[Line][List - 1])
	{
		A[Line][List - 1] = 0;
		A[Line][List + 1] = 0;
		A[Line][List + 2] = 0;

		if (A[Line + 1][List] >= 10 || Line == 19)
		{
			A[Line - 1][List] = 7;
			A[Line - 2][List] = 7;
			A[Line - 3][List] = 7;
			Line -= 2;
		}
		else if (A[Line + 2][List] >= 10 || Line == 18)
		{
			A[Line + 1][List] = 7;
			A[Line - 1][List] = 7;
			A[Line - 2][List] = 7;
			Line -= 1;
		}
		else
		{
			A[Line - 1][List] = 7;
			A[Line + 1][List] = 7;
			A[Line + 2][List] = 7;
		}

	}
	else
	{
		A[Line - 1][List] = 0;
		A[Line + 1][List] = 0;
		A[Line + 2][List] = 0;

		if (A[Line][List - 1] >= 10 || 0 == List)
		{
			A[Line][List + 1] = 7;
			A[Line][List + 2] = 7;
			A[Line][List + 3] = 7;
			List += 1;
		}
		else if (A[Line][List + 1] >= 10 || 9 == List)
		{
			A[Line][List - 1] = 7;
			A[Line][List - 2] = 7;
			A[Line][List - 3] = 7;
			List -= 2;
		}
		else if (A[Line][List + 2] >= 10 || 8 == List)
		{
			A[Line][List + 1] = 7;
			A[Line][List - 1] = 7;
			A[Line][List - 2] = 7;
			List -= 1;
		}
		else
		{
			A[Line][List - 1] = 7;
			A[Line][List + 1] = 7;
			A[Line][List + 2] = 7;
		}
	}
}

void ChangeDifficult()
{
	TimeFlag = Score;
	TimeFlag = Score - Difficult * i;

	if (TimeFlag >= Difficult)
	{
		i++;

		if (Time > 100)
		{
			Time -= 100;
			SetTimer(hWnd, TIMERID, Time, NULL);
		}
	}
}

void CreateRandomSqare()
{
	static int flag = 0, nextflag = 0;
	static int i = 1;

	flag = NextFlag;
	Flag = flag;

	while (i)
	{
		flag = rand() % 7 + 1;
		Flag = flag;
		i = 0;
	}

	nextflag = rand() % 7 + 1;
	NextFlag = nextflag;

	switch (flag)
	{
	case 1:
		a[0][1] = 1, a[1][0] = 1, a[1][1] = 1, a[1][2] = 1;
		a[0][0] = 0, a[0][2] = 0, a[0][3] = 0, a[1][3] = 0;
		Line = 0, List = 3;
		break;
	case 2:
		a[0][0] = 2, a[1][0] = 2, a[1][1] = 2, a[1][2] = 2;
		a[0][1] = 0, a[0][2] = 0, a[0][3] = 0, a[1][3] = 0;
		Line = 0, List = 3;
		break;
	case 3:
		a[0][2] = 3, a[1][0] = 3, a[1][1] = 3, a[1][2] = 3;
		a[0][0] = 0, a[0][1] = 0, a[0][3] = 0, a[1][3] = 0;
		Line = 0, List = 3;
		break;
	case 4:
		a[0][1] = 4, a[0][2] = 4, a[1][0] = 4, a[1][1] = 4;
		a[0][0] = 0, a[0][3] = 0, a[1][2] = 0, a[1][3] = 0;
		Line = 0, List = 3;
		break;
	case 5:
		a[0][0] = 5, a[0][1] = 5, a[1][1] = 5, a[1][2] = 5;
		a[0][2] = 0, a[0][3] = 0, a[1][0] = 0, a[1][3] = 0;
		Line = 0, List = 3;
		break;
	case 6:
		a[0][1] = 6, a[0][2] = 6, a[1][1] = 6, a[1][2] = 6;
		a[0][0] = 0, a[0][3] = 0, a[1][0] = 0, a[1][3] = 0;
		break;
	case 7:
		a[0][0] = 7, a[0][1] = 7, a[0][2] = 7, a[0][3] = 7;
		a[1][0] = 0, a[1][1] = 0, a[1][2] = 0, a[1][3] = 0;
		Line = 0, List = 4;
		break;
	default:
		break;
	}

	switch (nextflag)
	{
	case 1:
		b[0][1] = 1, b[1][0] = 1, b[1][1] = 1, b[1][2] = 1;
		b[0][0] = 0, b[0][2] = 0, b[0][3] = 0, b[1][3] = 0;
		break;
	case 2:
		b[0][0] = 2, b[1][0] = 2, b[1][1] = 2, b[1][2] = 2;
		b[0][1] = 0, b[0][2] = 0, b[0][3] = 0, b[1][3] = 0;
		break;
	case 3:
		b[0][2] = 3, b[1][0] = 3, b[1][1] = 3, b[1][2] = 3;
		b[0][0] = 0, b[0][1] = 0, b[0][3] = 0, b[1][3] = 0;
		break;
	case 4:
		b[0][1] = 4, b[0][2] = 4, b[1][0] = 4, b[1][1] = 4;
		b[0][0] = 0, b[0][3] = 0, b[1][2] = 0, b[1][3] = 0;
		break;
	case 5:
		b[0][0] = 5, b[0][1] = 5, b[1][1] = 5, b[1][2] = 5;
		b[0][2] = 0, b[0][3] = 0, b[1][0] = 0, b[1][3] = 0;
		break;
	case 6:
		b[0][1] = 6, b[0][2] = 6, b[1][1] = 6, b[1][2] = 6;
		b[0][0] = 0, b[0][3] = 0, b[1][0] = 0, b[1][3] = 0;
		break;
	case 7:
		b[0][0] = 7, b[0][1] = 7, b[0][2] = 7, b[0][3] = 7;
		b[1][0] = 0, b[1][1] = 0, b[1][2] = 0, b[1][3] = 0;
		break;
	default:
		break;
	}
}

void CopySqareToBack()
{
	static int i = 0, j = 0;

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 4; j++)
		{
			A[i][j + 3] = a[i][j];
		}
	}

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 4; j++)
		{
			B[i + 10][j + 1] = b[i][j];
		}
	}
}

void DestroyOneLine()
{
	static int i = 0, j = 0, sum = 0, temp = 0, flag = 0;

	for (i = 19; i >= 0; i--)
	{
		flag = 1;

		for (j = 0; j < 10; j++)
		{
			if (A[i][j] == 0)
			{
				flag = 0;
				break;
			}
		}

		if (flag)
		{
			for (temp = i - 1; temp >= 0; temp--)
			{
				for (j = 0; j < 10; j++)
				{
					A[temp + 1][j] = A[temp][j];
				}
			}

			Score += SCORE;
			i = 20;
		}
	}
}

void GameOver()
{
	static int i = 0, j = 0;

	for (i = 0; i < 10; i++)
	{
		if (A[0][i] >= 10)
		{
			KillTimer(hWnd, TIMERID);

			for (i = 0; i < 20; i++)
			{
				for (j = 0; j < 10; j++)
				{
					if (A[i][j])
					{
						A[i][j] = 100;
					}
				}
			}

			OnPaint();

			if (Score>MaxScore)
			{
				HANDLE hFile = CreateFile("��¼.txt", GENERIC_WRITE | GENERIC_READ,
					FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				char buf[8];
				sprintf(buf, "%d", Score);
				DWORD len = 0;
				WriteFile(hFile, buf, strlen(buf), &len, NULL);
				CloseHandle(hFile);
			}

			int flag = MessageBox(hWnd, "��Ϸ�������Ƿ����¿�ʼ��", "��ʾ", MB_YESNO | MB_ICONQUESTION);

			if (flag == IDNO)
			{
				SendMessage(hWnd, WM_DESTROY, 0, 0);
			}
			else SendMessage(hWnd, WM_CREATE, 0, 0);
		}
	}
}