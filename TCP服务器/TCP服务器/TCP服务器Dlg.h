
// TCP服务器Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CTCP服务器Dlg 对话框
class CTCP服务器Dlg : public CDialogEx
{
// 构造
public:
	CTCP服务器Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TCP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
