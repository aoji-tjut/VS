// UDP服务器端.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string.h>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET hSocketSvr = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (hSocketSvr == INVALID_SOCKET)
	{
		printf("socket error");
		getchar();
		return -1;
	}

	SOCKADDR_IN addrSvr = { 0 };
	addrSvr.sin_family = AF_INET;
	addrSvr.sin_port = htons(6666);
	addrSvr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(hSocketSvr, (SOCKADDR*)&addrSvr, sizeof(addrSvr));

	/*****************************************************************/
	printf("UDP服务器端创建成功，等待客户端发送......\n");
	/*****************************************************************/

	char buf[128] = { 0 };
	SOCKADDR_IN addrClient = { 0 };
	int len = sizeof(addrClient);
	while (1)
	{
		recvfrom(hSocketSvr, buf, sizeof(buf), 0, (SOCKADDR*)&addrClient, &len);
		char* IP = inet_ntoa(addrClient.sin_addr);
		printf("客户端(%s)发送数据：%s\n", IP, buf);
		memset(buf, 0, sizeof(buf));
		IP = NULL;
	}

	closesocket(hSocketSvr);

	WSACleanup();


	system("pause");
	return 0;
}

