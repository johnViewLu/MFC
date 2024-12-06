
// MenusDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Menus.h"
#include "MenusDlg.h"
#include "afxdialogex.h"
#include <iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMenusDlg dialog



CMenusDlg::CMenusDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MENUS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMenusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMenusDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, &CMenusDlg::OnExit)
	ON_COMMAND(IDM_FILE_HELLO, &CMenusDlg::OnFileHello)
	ON_COMMAND(IDM_FILE_EXIT, &CMenusDlg::OnFileExit)
//	ON_COMMAND(IDM_ABOUTBOX, &CMenusDlg::OnAboutbox)
//ON_COMMAND(ID_HELP_ABOUT, &CMenusDlg::OnHelpAbout)
ON_WM_CONTEXTMENU()
ON_BN_CLICKED(IDC_HELLO, &CMenusDlg::OnHello)
ON_COMMAND(ID_HELLO_ABOUT, &CMenusDlg::OnHelloAbout)
END_MESSAGE_MAP()


// CMenusDlg message handlers

BOOL CMenusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMenusDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMenusDlg::OnPaint()
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
HCURSOR CMenusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CMenusDlg::OnExit()
{
	// TODO: Add your control notification handler code here
	OnOK();
}


void CMenusDlg::OnFileHello()
{
	// TODO: Add your command handler code here
	MessageBox(L"Hello there", L"Hello");
}


void CMenusDlg::OnFileExit()
{
	// TODO: Add your command handler code here
	OnExit();
}


//void CMenusDlg::OnAboutbox()
//{
//	// TODO: Add your command handler code here
//	CAboutDlg dlgAbout;
//	dlgAbout.DoModal();
//}


void CMenusDlg::OnHelpAbout()
{
	// TODO: Add your command handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CMenusDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here
	
	CPoint m_pPoint = point;
	//ClientToScreen(&m_pPoint);
	CMenu* m_lMenu = GetMenu();
	//m_lMenu->GetMenuSate();
	CMenu* vTemp[2];
	for (auto ix = 0; ix != 2; ++ix)
	{
		vTemp[ix] = m_lMenu->GetSubMenu(ix);
	}

	m_lMenu = m_lMenu->GetSubMenu(0);
	//TPM_CENTERALIGN +
	m_lMenu->TrackPopupMenu( TPM_LEFTBUTTON,
		m_pPoint.x, m_pPoint.y, this, nullptr);




}





void CMenusDlg::OnHello()
{
	// TODO: Add your control notification handler code here
	OnFileHello();
}





void CMenusDlg::OnHelloAbout()
{
	// TODO: Add your command handler code here
	OnHelpAbout();
}
