
// PtPChatFTSystemDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CPtPChatFTSystemDlg �Ի���
class CPtPChatFTSystemDlg : public CDialogEx
{
// ����
public:
	CPtPChatFTSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

	//��д
public:
	void OnCancel();

// �Ի�������
	enum { IDD = IDD_PTPCHATFTSYSTEM_DIALOG };

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
	afx_msg LRESULT OnRecvMsg(WPARAM wParam, LPARAM lParam);		//������Ϣ
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
