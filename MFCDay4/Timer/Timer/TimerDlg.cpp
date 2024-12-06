
// TimerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Timer.h"
#include "TimerDlg.h"
#include "afxdialogex.h"

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


// CTimerDlg dialog



CTimerDlg::CTimerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIMER_DIALOG, pParent)
	, m_sTime(_T(""))
	, m_sCount(_T(""))
	, m_iInterval(1000)
	,m_iCount(0)
	, testInt(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Check(pDX, IDC_INTERVAL, m_iInterval);
	//DDX_Control(pDX, IDC_STATICTIME, m_sTime);
	DDX_Text(pDX, IDC_STATICTIME, m_sTime);
	//DDX_Control(pDX, IDC_STATICCOUNT, m_sCount);
	DDX_Text(pDX, IDC_STATICCOUNT, m_sCount);
	DDX_Control(pDX, IDC_STARTTIME, m_cStartTimer);
	DDX_Control(pDX, IDC_STOPTIMER, m_cStopTimer);
	DDX_Text(pDX, IDC_INTERVAL, m_iInterval);
	DDV_MinMaxInt(pDX, m_iInterval, 1, 10000);

	DDX_Text(pDX, IDC_EDIT1, testInt);
	DDV_MinMaxInt(pDX, testInt, 1, 1000);
}

BEGIN_MESSAGE_MAP(CTimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, &CTimerDlg::OnExit)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_INTERVAL, &CTimerDlg::OnChangeInterval)
	ON_BN_CLICKED(IDC_STARTTIME, &CTimerDlg::OnStarttime)
	ON_BN_CLICKED(IDC_STOPTIMER, &CTimerDlg::OnStoptimer)
	ON_EN_CHANGE(IDC_EDIT1, &CTimerDlg::OnChangeEdit1)
END_MESSAGE_MAP()


// CTimerDlg message handlers

BOOL CTimerDlg::OnInitDialog()
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
	//m_iInterval = 1000;
	UpdateData(FALSE);
	SetTimer(ID_CLOCK_TIMER, 1000, NULL);

	


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTimerDlg::OnPaint()
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
HCURSOR CTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CTimerDlg::OnExit()
{
	// TODO: Add your control notification handler code here
	OnOK();
}


void CTimerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CTime curTime = CTime::GetCurrentTime();

	switch (nIDEvent)
	{
	case ID_CLOCK_TIMER:
		m_sTime.Format(L"%d:%d:%d", curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond());
		break;
	case ID_COUNT_TIMER:
		m_iCount++;
		m_sCount.Format(L"%d", m_iCount);
		break;
	default:
		break;
	}

	
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


void CTimerDlg::OnChangeInterval()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
    // CDialog::OnInitDialog();
	// TODO:  Add your control notification handler code here
	 UpdateData(TRUE);
}


void CTimerDlg::OnStarttime()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_iCount = 0;
	m_sCount.Format(L"%d", m_iCount);

	UpdateData(FALSE);
	SetTimer(ID_COUNT_TIMER, m_iInterval, NULL);

	m_cStartTimer.EnableWindow(FALSE);
	m_cStopTimer.EnableWindow();
}


void CTimerDlg::OnStoptimer()
{
	// TODO: Add your control notification handler code here
	KillTimer(ID_COUNT_TIMER);
	m_cStartTimer.EnableWindow();
	m_cStopTimer.EnableWindow(FALSE);
}


void CTimerDlg::OnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	//CDialog::OnInitDialog();
	UpdateData(TRUE);
}
