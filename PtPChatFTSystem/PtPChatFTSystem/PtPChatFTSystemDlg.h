
// PtPChatFTSystemDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CPtPChatFTSystemDlg 对话框
class CPtPChatFTSystemDlg : public CDialogEx
{
// 构造
public:
	CPtPChatFTSystemDlg(CWnd* pParent = NULL);	// 标准构造函数

	//手写
public:
	void OnCancel();

// 对话框数据
	enum { IDD = IDD_PTPCHATFTSYSTEM_DIALOG };

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
	afx_msg LRESULT OnRecvMsg(WPARAM wParam, LPARAM lParam);		//接收消息
	UINT m_TCP;
	CString m_Name;
	CEdit m_CtrlSendEdit;
	CEdit m_CtrlName;
	CString m_SendEdit;
	CEdit m_CtrlRecordEdit;
	CString m_RecordEdit;
	CButton m_CtrlSend;
	CString m_IP;
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
