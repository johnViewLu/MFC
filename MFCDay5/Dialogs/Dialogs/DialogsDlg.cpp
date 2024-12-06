
// DialogsDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Dialogs.h"
#include "CMsgDlg.h"
#include "DialogsDlg.h"
#include "afxdialogex.h"
#include <map>
#include <string>

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


// CDialogsDlg dialog



CDialogsDlg::CDialogsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGS_DIALOG, pParent)
	, m_sResults(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDialogsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RESULTS, m_sResults);
	DDX_Control(pDX, IDC_BWHICHOPTION, m_cWhichOption);
}

BEGIN_MESSAGE_MAP(CDialogsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Yesnocancel, &CDialogsDlg::OnYesnocancel)
	ON_BN_CLICKED(IDC_FILEOPEN, &CDialogsDlg::OnFileopen)
	ON_BN_CLICKED(IDC_BCUSTOMDIALOG, &CDialogsDlg::OnBcustomdialog)
	ON_BN_CLICKED(IDC_BWHICHOPTION, &CDialogsDlg::OnBwhichoption)
END_MESSAGE_MAP()


// CDialogsDlg message handlers

BOOL CDialogsDlg::OnInitDialog()
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

void CDialogsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDialogsDlg::OnPaint()
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
HCURSOR CDialogsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDialogsDlg::OnYesnocancel()
{
	// TODO: Add your control notification handler code here
	int iResults = MessageBox(L"Press the Yes, No, or Cancel button", L"Yes, No, Cancel Dialog",
		MB_YESNOCANCEL | MB_ICONINFORMATION);
	switch (iResults)
	{
	case IDYES:
		m_sResults = "Yes! Yes! Yes!";
		break;
	case IDNO:
		m_sResults = "No! No! No!";
		break;
	case IDCANCEL:
		m_sResults = "Sorry, canceled";
		break;
	default:
		break;
	}
	UpdateData(FALSE);
}


void CDialogsDlg::OnFileopen()
{
	// TODO: Add your control notification handler code here
	CFileDialog m_ldFile(TRUE);
	if (m_ldFile.DoModal() == IDOK)
	{
		m_sResults = m_ldFile.GetFileName();
		UpdateData(FALSE);
	}
	else if (m_ldFile.DoModal() == IDCANCEL)
	{
		//m_sResults = L"Canceled";
		//UpdateData(FALSE);
	}
}


void CDialogsDlg::OnBcustomdialog()
{
	// TODO: Add your control notification handler code here
	if (m_dMsgDlg.DoModal() == IDOK)
	{
		m_sResults = m_dMsgDlg.m_sMessage;
		UpdateData(FALSE);
		m_cWhichOption.EnableWindow(TRUE);
	}
}


void CDialogsDlg::OnBwhichoption()
{
	// TODO: Add your control notification handler code here
	static std::map<int, std::wstring>   sMap{
		{0, L"first"}, { 1, L"second" }, { 2, L"third" }, { 3, L"fourth" }
	};
	switch (m_dMsgDlg.m_iOption)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	{
		m_sResults = "The ";
		m_sResults += sMap[m_dMsgDlg.m_iOption].data();
		m_sResults += " option was selected.";			
	}
	break;
	default:
		m_sResults = "No option was selected";
		break;
	}
	UpdateData(FALSE);
}
