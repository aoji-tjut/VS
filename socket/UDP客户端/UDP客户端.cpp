// UDP�ͻ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<string.h>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	//										���ݰ���ʽ
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
	printf("UDP�ͻ��˴����ɹ�......\n");
	/*****************************************************************/

	//ר����UDPͨ��		�Ƕ���
	char buf[128] = "123456789";
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		printf("���봫�����ݣ�\n");
		scanf("%s", buf);
		//���� socket������ ���ݻ���	���ݴ�С	Ĭ��0
		sendto(hSocketClient, buf, strlen(buf), 0, (sockaddr*)&addrSvr, sizeof(addrSvr));
		printf("���ݷ������\n");
	}

	closesocket(hSocketClient);

	WSACleanup();
	

	system("pause");
	return 0;
}

