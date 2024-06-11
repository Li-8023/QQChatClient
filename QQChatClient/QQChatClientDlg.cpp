
// QQChatClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "QQChatClient.h"
#include "QQChatClientDlg.h"
#include "afxdialogex.h"
#include "CClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQQChatClientDlg dialog



CQQChatClientDlg::CQQChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QQCHATCLIENT_DIALOG, pParent)
	, m_strSendMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pClientSocket = NULL;
}

void CQQChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_strSendMsg);
}

BEGIN_MESSAGE_MAP(CQQChatClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CQQChatClientDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CQQChatClientDlg message handlers

BOOL CQQChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_pClientSocket = new CClientSocket;

	//创建套接字
	if (FALSE == m_pClientSocket->Create()) {
		MessageBox(L"创建套接字失败");
		delete m_pClientSocket;
		m_pClientSocket = NULL;

		EndDialog(IDOK);
		return TRUE;
	}

	//连接服务器
	if (FALSE == m_pClientSocket->Connect(L"10.16.1.196", 10086)) {
		MessageBox(L"连接服务器失败");
		delete m_pClientSocket;
		m_pClientSocket = NULL;

		EndDialog(IDOK);
		return TRUE;
	}
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQQChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQQChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//发送消息
void CQQChatClientDlg::OnBnClickedBtnSend()
{
	
	UpdateData(TRUE);

	if (m_strSendMsg.IsEmpty()) {
		MessageBox(L"不能发送空消息");
		return;
	}

	if (m_strSendMsg.GetLength() > 1024) {
		MessageBox(L"您的消息过长，请分条发送");
		return;
	}

	//发送消息给服务器
	//我们采用Unicode编码
	//一个字符占用俩个字节
	m_pClientSocket->Send(m_strSendMsg, m_strSendMsg.GetLength()*2); //字符长度，字符个数
	
}
