// 多线程.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

int i;
CRITICAL_SECTION cs;
HANDLE hEvent;
HANDLE hMutex;

void duoxiancheng();
DWORD CALLBACK ThreadProc1(LPVOID lpvoid);
DWORD CALLBACK ThreadProc2(LPVOID lpvoid);
void linjiequ();
DWORD CALLBACK ThreadProc3(LPVOID p);
DWORD CALLBACK ThreadProc4(LPVOID lpvoid);
void shijian();
DWORD CALLBACK ThreadProc5(LPVOID lpvoid);
DWORD CALLBACK ThreadProc6(LPVOID lpvoid);
void huchi();
DWORD CALLBACK ThreadProc7(LPVOID lpvoid);
DWORD CALLBACK ThreadProc8(LPVOID lpvoid);

/***************************************************/
int _tmain(int argc, _TCHAR* argv[])
{
//	duoxiancheng();

//	linjiequ();

//	shijian();

	huchi();

	CloseHandle(hEvent);
	CloseHandle(hMutex);

	system("pause");
	return 0;
}
/***************************************************/

void duoxiancheng()
{
	DWORD ID;
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, ThreadProc1, NULL, 0, &ID);
	hThread[1] = CreateThread(NULL, 0, ThreadProc2, NULL, 0, &ID);

	WaitForSingleObject(hThread[0], INFINITE);//等待线程结束
	TerminateThread(hThread[0], 123);//终止指定线程
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);	//等待多个线程结束
	//TRUE等待所有线程结束
	//FALSE等待任一线程结束
	CloseHandle(hThread[0]);//释放句柄
	CloseHandle(hThread[1]);

	ExitThread(123);//终止主线程
}

DWORD CALLBACK ThreadProc1(LPVOID lpvoid)
{
	while (1)
	{
		printf("%d\n", i++);
		Sleep(500);
	}
	return 0;
}

DWORD CALLBACK ThreadProc2(LPVOID lpvoid)
{
	while (1)
	{
		printf("%d\n", i++);
		Sleep(500);
	}
	return 0;
}

void linjiequ()
{
	int i = 10;
	DWORD ID;
	HANDLE hThread[2] = { 0 };

	InitializeCriticalSection(&cs);//初始化临界区

	hThread[0] = CreateThread(NULL, 0, ThreadProc3, (LPVOID*)&i, 0, &ID);
	hThread[1] = CreateThread(NULL, 0, ThreadProc4, NULL, 0, &ID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
}

DWORD CALLBACK ThreadProc3(LPVOID p)
{
	//传入参数
	//int* pi = (int*)p;
	//printf("%d\n", *pi);
	while (1)
	{
		EnterCriticalSection(&cs);//进入临界区
		printf("%d\n", i++);
		Sleep(500);
		LeaveCriticalSection(&cs);//离开临界区
	}
	return 0;
}

DWORD CALLBACK ThreadProc4(LPVOID lpvoid)
{
	while (1)
	{
		EnterCriticalSection(&cs);//进入临界区
		printf("%d\n", i++);
		Sleep(500);
		LeaveCriticalSection(&cs);//离开临界区
	}
	return 0;
}

void shijian()
{
	DWORD ID;
	HANDLE hThread[2] = { 0 };
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);//创建
	
	hThread[0] = CreateThread(NULL, 0, ThreadProc5, NULL, 0, &ID);
	hThread[1] = CreateThread(NULL, 0, ThreadProc6, NULL, 0, &ID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
}

DWORD CALLBACK ThreadProc5(LPVOID lpvoid)
{
	while (1)
	{
		WaitForSingleObject(hEvent, INFINITE);
		printf("%d\n", i++);
		Sleep(500);
		ResetEvent(hEvent);
	}
	return 0;
}

DWORD CALLBACK ThreadProc6(LPVOID lpvoid)
{
	while (1)
	{
		SetEvent(hEvent);
		printf("%d\n", i++);
		Sleep(500);
	}
	return 0;
}

void huchi()
{
	DWORD ID;
	HANDLE hThread[2] = { 0 };
	hMutex = CreateMutex(NULL, TRUE, NULL);

	hThread[0] = CreateThread(NULL, 0, ThreadProc5, NULL, 0, &ID);
	hThread[1] = CreateThread(NULL, 0, ThreadProc6, NULL, 0, &ID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
}

DWORD CALLBACK ThreadProc7(LPVOID lpvoid)
{
	while (1)
	{
		WaitForSingleObject(hMutex, INFINITE);
		printf("%d\n", i++);
		Sleep(500);
		ReleaseMutex(hMutex);
	}
	return 0;
}

DWORD CALLBACK ThreadProc8(LPVOID lpvoid)
{
	while (1)
	{
		OpenMutex(MUTEX_ALL_ACCESS, FALSE, NULL);
		printf("%d\n", i++);
		Sleep(500);
	}
	return 0;
}