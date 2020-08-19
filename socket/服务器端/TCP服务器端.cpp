// 服务器端.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")


int _tmain(int argc, _TCHAR* argv[])
{
	//初始化socket库
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	//创建socket
	SOCKET hSocketSvr = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hSocketSvr == INVALID_SOCKET)
	{
		printf("socket error");
		getchar();
		return -1;
	}
	SOCKADDR_IN sockSvr = { 0 };
	sockSvr.sin_family = AF_INET;
	sockSvr.sin_port = htons(8888);
	sockSvr.sin_addr.S_un.S_addr = INADDR_ANY;//可以连接所有客户端
	
	//socket和结构体绑定
	//socket描述符	结构体指针		结构体大小
	bind(hSocketSvr, (SOCKADDR*)&sockSvr, sizeof(sockSvr));

	/*****************************************************************/
	printf("TCP客户端与TCP服务器端创建成功，等待客户端连接......\n");
	/*****************************************************************/

	//监听	直接把客户端信息转给accept
	//socket描述符	最多容纳多少客户端
	listen(hSocketSvr, 5);//最多有5个客户端可连接

	//accept	当客户端连接上之后立刻解除堵塞
	SOCKADDR_IN sockClient = { 0 };
	int len = sizeof(sockClient);
	SOCKET hSocketClient = accept(hSocketSvr, (SOCKADDR*)&sockClient, &len);
	printf("有客户端连接，等待数据接收......\n");

	//数据发送接收
	char buf[128] = { 0 };
	while (1)
	{
		recv(hSocketClient, buf, sizeof(buf), 0);
		printf("客户端数据：%s\n", buf);
		memset(buf, 0, sizeof(buf));
	}

	//关闭socket
	closesocket(hSocketSvr);
	closesocket(hSocketClient);

	//释放socket库
	WSACleanup();

	system("pause");
	return 0;
}
