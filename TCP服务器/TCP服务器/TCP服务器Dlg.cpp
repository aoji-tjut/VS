
// TCP服务器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TCP服务器.h"
#include "TCP服务器Dlg.h"
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTCP服务器Dlg 对话框



CTCP服务器Dlg::CTCP服务器Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCP服务器Dlg::IDD, pParent)
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

	//本机IP
	hostent* p = gethostbyname(name);
	char* str = inet_ntoa(*((in_addr*)p->h_addr));
	m_ServerIP.Format("%s", str);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCP服务器Dlg::DoDataExchange(CDataExchange* pDX)
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

BEGIN_MESSAGE_MAP(CTCP服务器Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_RECVMSG, OnRecvMsg)
	ON_MESSAGE(UM_ACCEPTMSG, OnAcceptMsg)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CTCP服务器Dlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CTCP服务器Dlg::OnBnClickedButtonExit)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CTCP服务器Dlg 消息处理程序

BOOL CTCP服务器Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	::hWnd = this->m_hWnd;

	listensocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listensocket == INVALID_SOCKET)
	{
		AfxMessageBox("TCP套接字创建失败！");
		WSACleanup();
		return FALSE;
	}
	else m_Record += "TCP套接字创建成功！\r\n";

	SOCKADDR_IN TCPServerAddr;
	memset(&TCPServerAddr, 0, sizeof(TCPServerAddr));
	TCPServerAddr.sin_family = AF_INET;
	TCPServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	TCPServerAddr.sin_port = htons(0);

	if (bind(listensocket, (SOCKADDR*)&TCPServerAddr, sizeof(TCPServerAddr)) == SOCKET_ERROR)
	{
		AfxMessageBox("TCP套接字绑定失败！");
		closesocket(listensocket);
		WSACleanup();
		return FALSE;
	}
	else m_Record += "TCP套接字绑定成功！\r\n";

	if (listen(listensocket, 1) == SOCKET_ERROR)
	{
		AfxMessageBox("TCP套接字监听失败！");
		closesocket(listensocket);
		WSACleanup();
		return FALSE;
	}
	else m_Record += "正在监听......\r\n";

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

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTCP服务器Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTCP服务器Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTCP服务器Dlg::OnQueryDragIcon()
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

LRESULT CTCP服务器Dlg::OnAcceptMsg(WPARAM wParam, LPARAM lParam)
{
	m_Record += "客户端连接成功！可发送消息！\r\n";

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

LRESULT CTCP服务器Dlg::OnRecvMsg(WPARAM wParam, LPARAM lParam)
{
	char* p = (char*)lParam;
	CString tempstr = p;
	m_Record += tempstr;
	delete[] p;

	UpdateData(FALSE);

	return TRUE;
}

void CTCP服务器Dlg::OnBnClickedButtonSend()
{
	// TODO:  在此添加控件通知处理程序代码
	SYSTEMTIME st;
	CString strDate, strTime;
	GetLocalTime(&st);
	strDate.Format("%d-%d-%d", st.wYear, st.wMonth, st.wDay);
	strTime.Format("%d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);

	UpdateData(TRUE);

	if (m_Send.GetLength() == 0)
	{
		MessageBox("发送信息不能为空", "提示", MB_OK | MB_ICONERROR);
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
		MessageBox(strerr, "提示", MB_OK | MB_ICONERROR);
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

void CTCP服务器Dlg::OnBnClickedButtonExit()
{
	// TODO:  在此添加控件通知处理程序代码
	if (IDYES == MessageBox("是否退出？", "提示", MB_YESNO | MB_ICONQUESTION))
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

BOOL CTCP服务器Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN && GetDlgItem(IDC_BUTTON_SEND)->IsWindowEnabled())
		{
			CTCP服务器Dlg::OnBnClickedButtonSend();
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
