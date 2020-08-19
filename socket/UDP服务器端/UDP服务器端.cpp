// UDP��������.cpp : �������̨Ӧ�ó������ڵ㡣
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
	printf("UDP�������˴����ɹ����ȴ��ͻ��˷���......\n");
	/*****************************************************************/

	char buf[128] = { 0 };
	SOCKADDR_IN addrClient = { 0 };
	int len = sizeof(addrClient);
	while (1)
	{
		recvfrom(hSocketSvr, buf, sizeof(buf), 0, (SOCKADDR*)&addrClient, &len);
		char* IP = inet_ntoa(addrClient.sin_addr);
		printf("�ͻ���(%s)�������ݣ�%s\n", IP, buf);
		memset(buf, 0, sizeof(buf));
		IP = NULL;
	}

	closesocket(hSocketSvr);

	WSACleanup();


	system("pause");
	return 0;
}

