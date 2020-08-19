// ��������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")


int _tmain(int argc, _TCHAR* argv[])
{
	//��ʼ��socket��
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	//����socket
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
	sockSvr.sin_addr.S_un.S_addr = INADDR_ANY;//�����������пͻ���
	
	//socket�ͽṹ���
	//socket������	�ṹ��ָ��		�ṹ���С
	bind(hSocketSvr, (SOCKADDR*)&sockSvr, sizeof(sockSvr));

	/*****************************************************************/
	printf("TCP�ͻ�����TCP�������˴����ɹ����ȴ��ͻ�������......\n");
	/*****************************************************************/

	//����	ֱ�Ӱѿͻ�����Ϣת��accept
	//socket������	������ɶ��ٿͻ���
	listen(hSocketSvr, 5);//�����5���ͻ��˿�����

	//accept	���ͻ���������֮�����̽������
	SOCKADDR_IN sockClient = { 0 };
	int len = sizeof(sockClient);
	SOCKET hSocketClient = accept(hSocketSvr, (SOCKADDR*)&sockClient, &len);
	printf("�пͻ������ӣ��ȴ����ݽ���......\n");

	//���ݷ��ͽ���
	char buf[128] = { 0 };
	while (1)
	{
		recv(hSocketClient, buf, sizeof(buf), 0);
		printf("�ͻ������ݣ�%s\n", buf);
		memset(buf, 0, sizeof(buf));
	}

	//�ر�socket
	closesocket(hSocketSvr);
	closesocket(hSocketClient);

	//�ͷ�socket��
	WSACleanup();

	system("pause");
	return 0;
}
