
// PtPChatFTSystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PtPChatFTSystem.h"
#include "PtPChatFTSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern SOCKET socketTCP;
extern SOCKADDR_IN Server;
extern SOCKADDR_IN Client;

DWORD WINAPI UDPThreadRecvProc(LPVOID lpParameter);					//UDP线程


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


// CPtPChatFTSystemDlg 对话框



CPtPChatFTSystemDlg::CPtPChatFTSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPtPChatFTSystemDlg::IDD, pParent)
	, m_TCP(0)
	, m_Name(_T(""))
	, m_SendEdit(_T(""))
	, m_RecordEdit(_T(""))
	, m_IP(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON);
}

void CPtPChatFTSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UDP, m_TCP);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Control(pDX, IDC_EDIT_SEND, m_CtrlSendEdit);
	DDX_Control(pDX, IDC_EDIT_NAME, m_CtrlName);
	DDX_Text(pDX, IDC_EDIT_SEND, m_SendEdit);
	DDX_Control(pDX, IDC_EDIT_RECORD, m_CtrlRecordEdit);
	DDX_Text(pDX, IDC_EDIT_RECORD, m_RecordEdit);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_CtrlSend);
	DDX_Text(pDX, IDC_EDIT_IP, m_IP);
}

BEGIN_MESSAGE_MAP(CPtPChatFTSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CPtPChatFTSystemDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CPtPChatFTSystemDlg::OnBnClickedButtonSend)
	//手写
	ON_MESSAGE(UM_RECVMSG, OnRecvMsg)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CPtPChatFTSystemDlg 消息处理程序

BOOL CPtPChatFTSystemDlg::OnInitDialog()
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

	//手写
	//本机名称
	char name[128];
	memset(name, 0, 128);
	int ret = gethostname(name, 128);
	m_Name = name;

	//本机IP
	hostent* p = gethostbyname(name);
	char* str = inet_ntoa(*((in_addr*)p->h_addr));		//h_addr==h_addr_list[0]
	m_IP.Format("%s", str);

	//UDP端口
	SOCKADDR_IN temp;
	memset(&temp, 0, sizeof(temp));
	int addrlen = sizeof(SOCKADDR_IN);
	getsockname(socketTCP, (sockaddr*)&temp, &addrlen);
	m_TCP = ntohs(temp.sin_port);

	//初始化协议信息
	Client = Server;


	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPtPChatFTSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPtPChatFTSystemDlg::OnPaint()
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
HCURSOR CPtPChatFTSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPtPChatFTSystemDlg::OnBnClickedButtonExit()
{
	// TODO:  在此添加控件通知处理程序代码
	//this->EndDialog(TRUE);
	CPtPChatFTSystemDlg::OnCancel();
}

//退出
void CPtPChatFTSystemDlg::OnCancel()
{
	if (IDYES == MessageBox("是否退出？", "提示", MB_YESNO | MB_ICONQUESTION))
	{
		CDialog::OnCancel();
	}
}

//接收消息
LRESULT CPtPChatFTSystemDlg::OnRecvMsg(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);
	
	char* p = (char*)lParam;
	CString tempstr = p;
	m_RecordEdit += tempstr;
	delete[] p;
	
	char* IP = inet_ntoa(Client.sin_addr);
	m_IP.Format("%s", IP);
	m_TCP = ntohs(Client.sin_port);
	UpdateData(FALSE);
	m_CtrlRecordEdit.LineScroll(m_CtrlRecordEdit.GetLineCount());

	return TRUE;
}


void CPtPChatFTSystemDlg::OnBnClickedButtonSend()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(s, (SOCKADDR*)&Client, sizeof(Client));

	if (m_SendEdit.GetLength() == 0)
	{
		MessageBox("发送信息不能为空", "提示", MB_OK | MB_ICONERROR);
		GetDlgItem(IDC_EDIT_SEND)->SetFocus();
		return;
	}

	SYSTEMTIME st;
	CString strDate, strTime;
	GetLocalTime(&st);
	strDate.Format("%d-%d-%d", st.wYear, st.wMonth, st.wDay);
	strTime.Format("%d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);

	SOCKADDR_IN temp;
	temp.sin_family = AF_INET;
	temp.sin_addr.S_un.S_addr = inet_addr(m_IP.GetBuffer(m_IP.GetLength()));
	temp.sin_port = ntohs(m_TCP);

	CString sendstr;
	sendstr.Format("[%s] %s %s\r\n%s\r\n", m_Name, strDate, strTime, m_SendEdit);
	int ret = send(socketTCP, sendstr, sizeof(sendstr), 0);

	if (ret == SOCKET_ERROR)
	{
		ret = WSAGetLastError();
		CString strerr;
		strerr.Format("错误：%d", ret);
		MessageBox(strerr, "提示", MB_OK | MB_ICONERROR);
		return;
	}

	CString tempstr;
	tempstr.Format("[%s] %s %s\r\n%s\r\n", m_Name, strDate, strTime, m_SendEdit);
	m_RecordEdit += tempstr;
	m_SendEdit = "";
	GetDlgItem(IDC_EDIT_SEND)->SetFocus();
	UpdateData(FALSE);
}

DWORD WINAPI UDPThreadRecvProc(LPVOID lpParameter)
{
	int len = sizeof(SOCKADDR);
	int recvval;
	char recvbuf[256];
	HWND mainWnd = (HWND)lpParameter;
	SOCKET s;

	while (TRUE)
	{
		int i = sizeof(Client);
		s = accept(socketTCP, (SOCKADDR*)&Client, &i);
		recvval = recv(s, recvbuf, sizeof(recvbuf), 0);
		if (recvval != SOCKET_ERROR)
		{
			if (mainWnd)
			{
				char* pmsg = new char[recvval];
				memcpy(pmsg, recvbuf, recvval);
				::PostMessage(mainWnd, UM_RECVMSG, 0, (LPARAM)pmsg);
			}
		}
		Sleep(200);
	}

	return 0;
}


void CPtPChatFTSystemDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO:  在此处添加消息处理程序代码
	m_CtrlSendEdit.SetFocus();

	HANDLE hThreadUDP = ::CreateThread(NULL, 0, UDPThreadRecvProc, (LPVOID)(this->m_hWnd), 0, NULL);
	CloseHandle(hThreadUDP);
}
