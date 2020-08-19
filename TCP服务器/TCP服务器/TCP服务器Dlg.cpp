
// TCP������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCP������.h"
#include "TCP������Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND hWnd;
SOCKET listensocket;
SOCKET clientsocket;
SOCKADDR_IN TCPClientAddr;

DWORD WINAPI TCPAcceptProc(LPVOID p);
DWORD WINAPI TCPRecvProc(LPVOID p);
void OnRecvMsg();

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTCP������Dlg �Ի���



CTCP������Dlg::CTCP������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCP������Dlg::IDD, pParent)
	, m_ServerIP(_T(""))
	, m_ServerName(_T(""))
	, m_Record(_T(""))
	, m_ServerPort()
	, m_ClientIP(_T(""))
	, m_ClientPort()
	, m_ClientName(_T(""))
	, m_Send(_T(""))
{
	char name[128];
	memset(name, 0, 128);
	gethostname(name, 128);
	m_ServerName = name;

	//����IP
	hostent* p = gethostbyname(name);
	char* str = inet_ntoa(*((in_addr*)p->h_addr));
	m_ServerIP.Format("%s", str);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCP������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IPADDRESS_SERVER, m_ServerIP);
	DDX_Text(pDX, IDC_EDIT_SERVER_NAME, m_ServerName);
	DDX_Text(pDX, IDC_EDIT_RECORD, m_Record);
	DDX_Control(pDX, IDC_EDIT_RECORD, m_CtrlRecord);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_ServerPort);
	DDX_Text(pDX, IDC_IPADDRESS_CLIENT, m_ClientIP);
	DDX_Text(pDX, IDC_EDIT_CLIENT_PORT, m_ClientPort);
	DDX_Text(pDX, IDC_EDIT_CLIENT_NAME, m_ClientName);
	DDX_Text(pDX, IDC_EDIT_SEND, m_Send);
}

BEGIN_MESSAGE_MAP(CTCP������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_RECVMSG, OnRecvMsg)
	ON_MESSAGE(UM_ACCEPTMSG, OnAcceptMsg)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CTCP������Dlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CTCP������Dlg::OnBnClickedButtonExit)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CTCP������Dlg ��Ϣ�������

BOOL CTCP������Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	::hWnd = this->m_hWnd;

	listensocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listensocket == INVALID_SOCKET)
	{
		AfxMessageBox("TCP�׽��ִ���ʧ�ܣ�");
		WSACleanup();
		return FALSE;
	}
	else m_Record += "TCP�׽��ִ����ɹ���\r\n";

	SOCKADDR_IN TCPServerAddr;
	memset(&TCPServerAddr, 0, sizeof(TCPServerAddr));
	TCPServerAddr.sin_family = AF_INET;
	TCPServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	TCPServerAddr.sin_port = htons(0);

	if (bind(listensocket, (SOCKADDR*)&TCPServerAddr, sizeof(TCPServerAddr)) == SOCKET_ERROR)
	{
		AfxMessageBox("TCP�׽��ְ�ʧ�ܣ�");
		closesocket(listensocket);
		WSACleanup();
		return FALSE;
	}
	else m_Record += "TCP�׽��ְ󶨳ɹ���\r\n";

	if (listen(listensocket, 1) == SOCKET_ERROR)
	{
		AfxMessageBox("TCP�׽��ּ���ʧ�ܣ�");
		closesocket(listensocket);
		WSACleanup();
		return FALSE;
	}
	else m_Record += "���ڼ���......\r\n";

	HANDLE hAccept = CreateThread(NULL, 0, TCPAcceptProc, NULL, 0, NULL);
	CloseHandle(hAccept);

	SOCKADDR_IN tempaddr;
	memset(&tempaddr, 0, sizeof(tempaddr));
	int addrlen = sizeof(SOCKADDR_IN);
	getsockname(listensocket, (sockaddr*)&tempaddr, &addrlen);
	m_ServerPort = ntohs(tempaddr.sin_port);
	
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SEND)->SetFocus();

	UpdateData(FALSE);

	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTCP������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTCP������Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTCP������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI TCPAcceptProc(LPVOID p)
{
	memset(&clientsocket, 0, sizeof(clientsocket));
	memset(&TCPClientAddr, 0, sizeof(TCPClientAddr));
	int len = sizeof(TCPClientAddr);
	clientsocket = accept(listensocket, (SOCKADDR*)&TCPClientAddr, &len);
	::PostMessage(hWnd, UM_ACCEPTMSG, 0, 0);

	HANDLE hAccept = CreateThread(NULL, 0, TCPRecvProc, (LPVOID)clientsocket, 0, NULL);
	CloseHandle(hAccept);

	return 0;
}

LRESULT CTCP������Dlg::OnAcceptMsg(WPARAM wParam, LPARAM lParam)
{
	m_Record += "�ͻ������ӳɹ����ɷ�����Ϣ��\r\n";

	char* IP = inet_ntoa(TCPClientAddr.sin_addr);
	m_ClientIP.Format("%s", IP);
	m_ClientPort = ntohs(TCPClientAddr.sin_port);
	hostent* p = gethostbyaddr((char*)&TCPClientAddr.sin_addr, 4, AF_INET);
	m_ClientName.Format("%s", p->h_name);

	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SEND)->SetFocus();

	UpdateData(FALSE);

	return 0;
}

DWORD WINAPI TCPRecvProc(LPVOID p)
{
	SOCKET newsocket = (SOCKET)p;
	char recvbuf[1024];
	int recvval;

	while (1)
	{
		recvval = recv(newsocket, recvbuf, 1024, 0);
		if (recvval != SOCKET_ERROR)
		{
			if (hWnd)
			{
				char* pmsg = new char[recvval];
				memcpy(pmsg, recvbuf, recvval);
				::PostMessage(hWnd, UM_RECVMSG, 0, (LPARAM)pmsg);
			}
		}
		Sleep(200);
	}

	return 0;
}

LRESULT CTCP������Dlg::OnRecvMsg(WPARAM wParam, LPARAM lParam)
{
	char* p = (char*)lParam;
	CString tempstr = p;
	m_Record += tempstr;
	delete[] p;

	UpdateData(FALSE);

	return TRUE;
}

void CTCP������Dlg::OnBnClickedButtonSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SYSTEMTIME st;
	CString strDate, strTime;
	GetLocalTime(&st);
	strDate.Format("%d-%d-%d", st.wYear, st.wMonth, st.wDay);
	strTime.Format("%d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);

	UpdateData(TRUE);

	if (m_Send.GetLength() == 0)
	{
		MessageBox("������Ϣ����Ϊ��", "��ʾ", MB_OK | MB_ICONERROR);
		GetDlgItem(IDC_EDIT_SEND)->SetFocus();
		return;
	}

	CString sendstr;
	sendstr.Format("[%s]  %s  %s\r\n%s\r\n", m_ServerName, strDate, strTime, m_Send);
	
	int ret = send(clientsocket, sendstr.GetBuffer(sendstr.GetLength()), sendstr.GetLength() + 1, 0);

	if (ret == SOCKET_ERROR)
	{
		ret = WSAGetLastError();
		CString strerr;
		strerr.Format("%d", ret);
		MessageBox(strerr, "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}

	CString tempstr;
	tempstr.Format("[%s]  %s  %s\r\n%s\r\n", m_ServerName, strDate, strTime, m_Send);
	m_Record += tempstr;
	m_Send = "";

	GetDlgItem(IDC_EDIT_SEND)->SetFocus();

	UpdateData(FALSE);

	m_CtrlRecord.LineScroll(m_CtrlRecord.GetLineCount());
}

void CTCP������Dlg::OnBnClickedButtonExit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (IDYES == MessageBox("�Ƿ��˳���", "��ʾ", MB_YESNO | MB_ICONQUESTION))
	{
		if (listensocket)
		{
			closesocket(listensocket);
		}
		if (clientsocket)
		{
			closesocket(clientsocket);
		}

		WSACleanup();

		CDialog::OnCancel();
	}
}

BOOL CTCP������Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN && GetDlgItem(IDC_BUTTON_SEND)->IsWindowEnabled())
		{
			CTCP������Dlg::OnBnClickedButtonSend();
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
