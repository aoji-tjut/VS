
// PtPChatFTSystemDlg.cpp : ʵ���ļ�
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

DWORD WINAPI UDPThreadRecvProc(LPVOID lpParameter);					//UDP�߳�


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


// CPtPChatFTSystemDlg �Ի���



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
	//��д
	ON_MESSAGE(UM_RECVMSG, OnRecvMsg)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CPtPChatFTSystemDlg ��Ϣ�������

BOOL CPtPChatFTSystemDlg::OnInitDialog()
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

	//��д
	//��������
	char name[128];
	memset(name, 0, 128);
	int ret = gethostname(name, 128);
	m_Name = name;

	//����IP
	hostent* p = gethostbyname(name);
	char* str = inet_ntoa(*((in_addr*)p->h_addr));		//h_addr==h_addr_list[0]
	m_IP.Format("%s", str);

	//UDP�˿�
	SOCKADDR_IN temp;
	memset(&temp, 0, sizeof(temp));
	int addrlen = sizeof(SOCKADDR_IN);
	getsockname(socketTCP, (sockaddr*)&temp, &addrlen);
	m_TCP = ntohs(temp.sin_port);

	//��ʼ��Э����Ϣ
	Client = Server;


	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPtPChatFTSystemDlg::OnPaint()
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
HCURSOR CPtPChatFTSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPtPChatFTSystemDlg::OnBnClickedButtonExit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//this->EndDialog(TRUE);
	CPtPChatFTSystemDlg::OnCancel();
}

//�˳�
void CPtPChatFTSystemDlg::OnCancel()
{
	if (IDYES == MessageBox("�Ƿ��˳���", "��ʾ", MB_YESNO | MB_ICONQUESTION))
	{
		CDialog::OnCancel();
	}
}

//������Ϣ
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(s, (SOCKADDR*)&Client, sizeof(Client));

	if (m_SendEdit.GetLength() == 0)
	{
		MessageBox("������Ϣ����Ϊ��", "��ʾ", MB_OK | MB_ICONERROR);
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
		strerr.Format("����%d", ret);
		MessageBox(strerr, "��ʾ", MB_OK | MB_ICONERROR);
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

	// TODO:  �ڴ˴������Ϣ����������
	m_CtrlSendEdit.SetFocus();

	HANDLE hThreadUDP = ::CreateThread(NULL, 0, UDPThreadRecvProc, (LPVOID)(this->m_hWnd), 0, NULL);
	CloseHandle(hThreadUDP);
}
