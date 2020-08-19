// �ڴ�.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "�ڴ�.h"


#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HWND hEdit;
HANDLE hHeap;
char* p;
char* q;

// �˴���ģ���а����ĺ�����ǰ������: 
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
		// �����˵�ѡ��: 
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
		// TODO:  �ڴ���������ͼ����...
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

void ShowVirtual()
{
	TCHAR str[1024];
	MEMORYSTATUS mms = { 0 };
	mms.dwLength = sizeof(mms);
	GlobalMemoryStatus(&mms);
	wsprintf(str, L"�ṹ���С��%d\r\n��ǰϵͳ�ڴ��ʹ���ʣ�%d%%\r\n�ܵ������ڴ��С��%X\r\n���õ������ڴ��С��%X\r\n���Դ���ҳ���ļ��е��ֽ�����%X\r\n���õ�ҳ���ļ���С��%X\r\nȫ�����������ַ�ռ䣺%X\r\nʵ�����ɿ��õ������ַ�ռ䣺%X\r\n",
		mms.dwLength, mms.dwMemoryLoad, mms.dwTotalPhys, mms.dwAvailPhys, mms.dwTotalPageFile, mms.dwAvailPageFile, mms.dwTotalVirtual, mms.dwAvailVirtual);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
}

void AllocVirtual()
{
	p = (char*)VirtualAlloc(NULL, 1024 * 1024 * 1024, MEM_COMMIT, PAGE_READWRITE);
	if (!p)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"����ʧ��");
	}
	else
	{
		strcpy(p, "������������������������������");
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"����ɹ�");
	}
}

void FreeVirtual()
{
	//0����ȫ���ͷ�
	BOOL flag = VirtualFree(p, 0, MEM_RELEASE);
	if (flag)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"�ͷųɹ�");
	}
	else SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"�ͷ�ʧ��");
}

void ShowHeap()
{
	HANDLE hHeap = GetProcessHeap();//��һ����
	TCHAR str[1024] = { 0 };
	TCHAR s[32] = { 0 };
	wsprintf(str, L"��һ�����ڴ棺%d\r\n", hHeap);
	HANDLE hArr[128] = { 0 };
	DWORD count = GetProcessHeaps(128, hArr);//���ж�
	wcscat(str, L"���ж��ڴ棺\r\n");
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
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"����ʧ��");
	}
	else
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"�����ɹ�");
		strcpy(q, "������������������������������");
	}
}

void FreeHeap()
{
	//0����ȫ���ͷ�
	BOOL flag = HeapFree(hHeap,0,q);
	if (!flag)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"�ͷ�ʧ��");
	}
	else SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"�ͷųɹ�");
	HeapDestroy(hHeap);
}