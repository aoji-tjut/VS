// socket.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	//初始化socket库
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	//准备插座
	//参数							协议簇		发送方式	TCP通信
	SOCKET hSocketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//创建socket失败
	if (hSocketClient == INVALID_SOCKET)
	{
		printf("socket error");
		getchar();
		return -1;
	}

	//准备结构体
	SOCKADDR_IN sockSvr = { 0 };
	//端口
	sockSvr.sin_port = htons(33297);
	//协议簇
	sockSvr.sin_family = AF_INET;
	//IP地址	把字符串转换成点分十进制
	sockSvr.sin_addr.S_un.S_addr = inet_addr("172.20.10.2");

	//客户端连接服务器
	//参数	socket描述符	结构体				结构体大小
	int n = connect(hSocketClient, (SOCKADDR*)&sockSvr, sizeof(sockSvr));
	if (n == SOCKET_ERROR)
	{
		printf("connect error\n");
		getchar();
		return -1;
	}

	/*****************************************************************/
	printf("TCP客户端与TCP服务器端连接成功......\n");
	/*****************************************************************/

	//发送消息
	char strsend[128] = { 0 };
	char strrecv[128] = { 0 };
	while (1)
	{
		memset(strrecv, 0, 128);
		//memset(strsend, 0, sizeof(strsend));
		//scanf("%s", strsend);
		////参数 socket描述符 数据缓冲	数据大小	默认0
		//send(hSocketClient, strsend, strlen(strsend), 0);
		recv(hSocketClient, strrecv, strlen(strrecv), 0);
		printf("%s", strrecv);
	}

	//关闭socket
	closesocket(hSocketClient);

	//释放socket库
	WSACleanup();

	system("pause");
	return 0;
}

