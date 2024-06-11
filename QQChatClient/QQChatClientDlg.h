
// QQChatClientDlg.h : header file
//

#pragma once

class CClientSocket;

// CQQChatClientDlg dialog
class CQQChatClientDlg : public CDialogEx
{
// Construction
public:
	CQQChatClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QQCHATCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CClientSocket* m_pClientSocket;
	CString m_strSendMsg;
	afx_msg void OnBnClickedBtnSend();
};
