// �ļ�Ŀ¼����.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "�ļ�Ŀ¼����.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HWND hEdit;

// �˴���ģ���а����ĺ�����ǰ������: 
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

 	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
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

	return (int) msg.wParam;
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

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
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
		// TODO:  �ڴ���������ͼ����...
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


void GetCurrent()
{
	TCHAR buf[128] = { 0 };
	TCHAR temp[128] = { 0 };
	GetCurrentDirectory(128, buf);
	wsprintf(temp, L"��ǰĿ¼��%s", buf);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)temp);
}

void GetSystem()
{
	TCHAR buf[128] = { 0 };
	TCHAR temp[128] = { 0 };
	GetSystemDirectory(buf, 128);
	wsprintf(temp, L"ϵͳĿ¼��%s", buf);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)temp);
}

void GetWindows()
{
	TCHAR buf[128] = { 0 };
	TCHAR temp[128] = { 0 };
	GetWindowsDirectory(buf, 128);
	wsprintf(temp, L"WindowsĿ¼��%s", buf);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)temp);
}

void GetTemp()
{
	TCHAR buf[128] = { 0 };
	TCHAR temp[128] = { 0 };
	GetTempPath(128, buf);
	wsprintf(temp, L"tempĿ¼��%s", buf);
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
		//�����Ŀ¼
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//�õ��ļ���
			lstrcat(allpath, wfd.cFileName);
			lstrcat(allpath, L"��Ŀ¼��\r\n");
		}
		else
		{
			lstrcat(allpath, wfd.cFileName);
			lstrcat(allpath, L"���ļ���\r\n");
		//	wcscat(allpath, wfd.cFileName);
		//	wcscat(allpath, L"���ļ���\r\n");
		}
		flag = FindNextFile(hFind, &wfd);
	}
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)allpath);
}

void CreateF()
{
	HANDLE hFile = CreateFile(L"C:\\Users\\acer\\Desktop\\�ļ�.txt", GENERIC_WRITE,
		FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"�����ɹ�");
	}
	CloseHandle(hFile);
}

void WriteF()
{
	HANDLE hFile = CreateFile(L"C:\\Users\\acer\\Desktop\\�ļ�.txt", GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	char* text = "����������������������������������������������������������������"; 
	DWORD len = 0;
	BOOL write = WriteFile(hFile, text, strlen(text), &len, NULL);
	if (write)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"д��ɹ�");
	}
	CloseHandle(hFile);
}

void ReadF()
{
	HANDLE hFile = CreateFile(L"C:\\Users\\acer\\Desktop\\�ļ�.txt", GENERIC_ALL,
		FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	char text[1024] = { 0 };
	DWORD len = 0;
	DWORD high = 0;
	DWORD low = GetFileSize(hFile, &high);
	BOOL read = WriteFile(hFile, text, low, &len, NULL);
	if (read)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"��ȡ�ɹ�");
	}
	CloseHandle(hFile);
}

void FileMap()
{
	//�����ļ�
	HANDLE hFile = CreateFile(L"C:\\Users\\acer\\Desktop\\�ļ�.txt", GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!hFile)
	{
		TCHAR error[100];
		wsprintf(error, L"error:%s", GetLastError());
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)error);
		exit(0);
	}
	//�����ļ�ӳ�䵽�ڴ�
	HANDLE hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 1024 * 1024, L"���");
	if (!hMap)
	{
		TCHAR error[100];
		wsprintf(error, L"error:%s", GetLastError());
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)error);
		exit(0);
	}
	//�����ڴ�ӳ��
	TCHAR* map = (TCHAR*)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 64 * 1024, 0);
	if (!map)
	{
		TCHAR error[100];
		wsprintf(error, L"error:%s", GetLastError());
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)error);
		exit(0);
	}
	//�ڴ�ʹ��
	lstrcpy(map, L"���");
	TCHAR str[100];
	wsprintf(str, L"map = %s", map);
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
	//ж��ӳ��
	UnmapViewOfFile(map);
	CloseHandle(hMap);
	CloseHandle(hFile);
}