// socket.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	//��ʼ��socket��
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	//׼������
	//����							Э���		���ͷ�ʽ	TCPͨ��
	SOCKET hSocketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//����socketʧ��
	if (hSocketClient == INVALID_SOCKET)
	{
		printf("socket error");
		getchar();
		return -1;
	}

	//׼���ṹ��
	SOCKADDR_IN sockSvr = { 0 };
	//�˿�
	sockSvr.sin_port = htons(33297);
	//Э���
	sockSvr.sin_family = AF_INET;
	//IP��ַ	���ַ���ת���ɵ��ʮ����
	sockSvr.sin_addr.S_un.S_addr = inet_addr("172.20.10.2");

	//�ͻ������ӷ�����
	//����	socket������	�ṹ��				�ṹ���С
	int n = connect(hSocketClient, (SOCKADDR*)&sockSvr, sizeof(sockSvr));
	if (n == SOCKET_ERROR)
	{
		printf("connect error\n");
		getchar();
		return -1;
	}

	/*****************************************************************/
	printf("TCP�ͻ�����TCP�����������ӳɹ�......\n");
	/*****************************************************************/

	//������Ϣ
	char strsend[128] = { 0 };
	char strrecv[128] = { 0 };
	while (1)
	{
		memset(strrecv, 0, 128);
		//memset(strsend, 0, sizeof(strsend));
		//scanf("%s", strsend);
		////���� socket������ ���ݻ���	���ݴ�С	Ĭ��0
		//send(hSocketClient, strsend, strlen(strsend), 0);
		recv(hSocketClient, strrecv, strlen(strrecv), 0);
		printf("%s", strrecv);
	}

	//�ر�socket
	closesocket(hSocketClient);

	//�ͷ�socket��
	WSACleanup();

	system("pause");
	return 0;
}

