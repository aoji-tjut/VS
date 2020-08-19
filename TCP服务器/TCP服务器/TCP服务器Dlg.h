
// TCP������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CTCP������Dlg �Ի���
class CTCP������Dlg : public CDialogEx
{
// ����
public:
	CTCP������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TCP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_ServerIP;
	CString m_ClientIP;
	CString m_ServerName;
	CString m_ClientName;
	UINT m_ServerPort;
	UINT m_ClientPort;
	CString m_Record;
	CEdit m_CtrlRecord;
	CString m_Send;
	afx_msg LRESULT OnRecvMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAcceptMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonExit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
