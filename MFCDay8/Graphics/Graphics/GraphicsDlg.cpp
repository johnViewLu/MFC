
// GraphicsDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Graphics.h"
#include "GraphicsDlg.h"
#include "afxdialogex.h"
#include "CPaintDlg.h"
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


// CGraphicsDlg dialog



CGraphicsDlg::CGraphicsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRAPHICS_DIALOG, pParent)
	, m_iColor(0)
	, m_iShape(0)
	, m_iTool(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGraphicsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RCBLACK, m_iColor);
	DDX_Radio(pDX, IDC_RSLINE, m_iShape);
	DDX_Radio(pDX, IDC_RTPEN, m_iTool);
}

BEGIN_MESSAGE_MAP(CGraphicsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BEXIT, &CGraphicsDlg::OnBnClickedBexit)
	ON_BN_CLICKED(IDC_RTPEN+1, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_RTPEN+2, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_RTPEN+3, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_RTPEN+4, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_RTPEN+5, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_RTPEN+6, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_RTPEN+7, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_RTPEN+8, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_RTPEN+9, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_RTPEN+10, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_RTPEN+11, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_RTPEN+12, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_RTPEN+13, &CGraphicsDlg::OnRSelection)
	ON_BN_CLICKED(IDC_BBITMAP, &CGraphicsDlg::OnBbitmap)
END_MESSAGE_MAP()


// CGraphicsDlg message handlers

BOOL CGraphicsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	m_iColor = 0;
	m_iShape = 0;
	m_iTool = 0;
	UpdateData(FALSE);

	m_dlgPaint.Create(IDD_PAINT_DLG, this);
	m_dlgPaint.ShowWindow(SW_SHOW);


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

void CGraphicsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGraphicsDlg::OnPaint()
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
HCURSOR CGraphicsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGraphicsDlg::OnBnClickedBexit()
{
	// TODO: Add your control notification handler code here
	OnOK();
}


void CGraphicsDlg::OnRSelection()
{
	// TODO: Add your implementation code here.
	UpdateData(TRUE);
	m_dlgPaint.Invalidate();
}


void CGraphicsDlg::OnBbitmap()
{
	// TODO: Add your control notification handler code here
	static TCHAR  szFilter[] = _T("Bitmap Files (*.bmp|*.bmp||");
	LPCTSTR lpszDefExt = _T(".bmp");
	TCHAR vFileName[256];
	CFileDialog m_ldFile(TRUE, _T(".bmp"), vFileName,  OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
	if (m_ldFile.DoModal() == IDOK)
	{
		m_sBitMap = m_ldFile.GetPathName();
		HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), m_sBitMap, 
			                                     IMAGE_BITMAP, 0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		if (hBitmap)
		{
			if (m_bmpBitMap.DeleteObject())
				m_bmpBitMap.Detach();
		  m_bmpBitMap.Attach(hBitmap);
		}
		m_dlgPaint.Invalidate();
	}
}
