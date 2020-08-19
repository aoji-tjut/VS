// UDP客户端.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string.h>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	//										数据包方式
	SOCKET hSocketClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (hSocketClient == INVALID_SOCKET)
	{
		printf("socket error");
		getchar();
		return -1;
	}

	SOCKADDR_IN addrSvr = { 0 };
	addrSvr.sin_family = AF_INET;
	addrSvr.sin_port = htons(6666);
	addrSvr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	/*****************************************************************/
	printf("UDP客户端创建成功......\n");
	/*****************************************************************/

	//专用于UDP通信		非堵塞
	char buf[128] = "123456789";
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		printf("输入传输数据：\n");
		scanf("%s", buf);
		//参数 socket描述符 数据缓冲	数据大小	默认0
		sendto(hSocketClient, buf, strlen(buf), 0, (sockaddr*)&addrSvr, sizeof(addrSvr));
		printf("数据发送完成\n");
	}

	closesocket(hSocketClient);

	WSACleanup();
	

	system("pause");
	return 0;
}

