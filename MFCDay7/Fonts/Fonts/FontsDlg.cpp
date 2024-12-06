
// FontsDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Fonts.h"
#include "FontsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int CALLBACK EnumFontFamProc(LPENUMLOGFONT lpelf,
	LPNEWTEXTMETRIC lpntm,
	DWORD nFontType,
	long lParam)
{
	CFontsDlg* pWnd = (CFontsDlg*)lParam;
	pWnd->m_ctrlFontList.AddString(lpelf->elfLogFont.lfFaceName);
	return 1;
}



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
public:
	afx_msg void OnSelchangeLfonts();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LFONTS, &CAboutDlg::OnSelchangeLfonts)
END_MESSAGE_MAP()


// CFontsDlg dialog



CFontsDlg::CFontsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FONTS_DIALOG, pParent)
	, m_strDisplayText(_T(""))
	, m_strFontName(_T(""))
	, m_strSampleText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFontsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_DISPLAYTEXT, m_ctrlDisplayText);
	DDX_Text(pDX, ID_DISPLAYTEXT, m_strDisplayText);
	DDX_Control(pDX, IDC_LFONTS, m_ctrlFontList);
	DDX_LBString(pDX, IDC_LFONTS, m_strFontName);
	DDX_Text(pDX, IDC_ESAMPLETXT, m_strSampleText);
}

BEGIN_MESSAGE_MAP(CFontsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_ESAMPLETXT, &CFontsDlg::OnChangeEsampletxt)
	ON_LBN_SELCHANGE(IDC_LFONTS, &CFontsDlg::OnSelchangeLfonts)
END_MESSAGE_MAP()


// CFontsDlg message handlers

BOOL CFontsDlg::OnInitDialog()
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

	FillFontList();

	m_strSampleText = L"Testing";
	m_strDisplayText = m_strSampleText;
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFontsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFontsDlg::OnPaint()
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
HCURSOR CFontsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFontsDlg::FillFontList()
{
	// TODO: Add your implementation code here.
	LOGFONT lf;
	lf.lfCharSet = DEFAULT_CHARSET;
	//strcpy(lf.lfFaceName, "");
	lstrcpy(lf.lfFaceName, L"");
	m_ctrlFontList.ResetContent();
	CClientDC dc(this);
	::EnumFontFamiliesEx((HDC)dc, &lf,
		(FONTENUMPROC)EnumFontFamProc, (LPARAM)this, 0);
	auto iCount = m_ctrlFontList.GetCount();
	CString strPreFont = L"";
	for (auto iCurCount = iCount; iCurCount > 0; iCurCount--)
	{
		CString strCurFont;
		m_ctrlFontList.GetText((iCurCount - 1), strCurFont);
		if (strCurFont == strPreFont)
			m_ctrlFontList.DeleteString(iCurCount - 1);
		strPreFont = strCurFont;
	}
}


void CFontsDlg::OnChangeEsampletxt()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	//CDialogEx::OnInitDialog();
	UpdateData(TRUE);

	m_strDisplayText = m_strSampleText;
	UpdateData(FALSE);
}


void CFontsDlg::SetMyFont()
{
	CRect rRect;
	int iHeight;
	if (m_strFontName != L"")
	{
		m_ctrlDisplayText.GetWindowRect(&rRect);
		iHeight = rRect.top - rRect.bottom;
		if (iHeight < 0)
			iHeight = 0 - iHeight;
		m_fSampFont.Detach();
		m_fSampFont.CreateFontW((iHeight - 5), 0, 0, 0, FW_NORMAL,
			0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
			CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH |
			FF_DONTCARE, m_strFontName);
		m_ctrlDisplayText.SetFont(&m_fSampFont);

	}
}


void CAboutDlg::OnSelchangeLfonts()
{
	// TODO: Add your control notification handler code here
}


void CFontsDlg::OnSelchangeLfonts()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SetMyFont();
}
