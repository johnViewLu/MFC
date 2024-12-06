
// MFCDay2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCDay2.h"
#include "MFCDay2Dlg.h"
#include "afxdialogex.h"
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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}


// CMFCDay2Dlg dialog



CMFCDay2Dlg::CMFCDay2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDAY2_DIALOG, pParent)
  , m_strMessage(_T(""))
  , m_strProgToRun(_T(""))
  , m_bEnableMsg(FALSE)
  , m_bEnablePgm(FALSE)
  , m_bShowMsg(FALSE)
  , m_bShowPgm(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDay2Dlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_MSG, m_strMessage);
  DDX_CBString(pDX, IDC_PROGTORUN, m_strProgToRun);
  DDX_Check(pDX, IDC_CKENBLMSG, m_bEnableMsg);
  DDX_Check(pDX, IDC_CKENBLPGM, m_bEnablePgm);
  DDX_Check(pDX, IDC_CKSHWMSG, m_bShowMsg);
  DDX_Check(pDX, IDC_CKSHWPGM, m_bShowPgm);
}

BEGIN_MESSAGE_MAP(CMFCDay2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_EXIT, &CMFCDay2Dlg::OnBnClickedExit)
  ON_BN_CLICKED(IDC_BUTTON1, &CMFCDay2Dlg::OnShwmsg)
  ON_BN_CLICKED(IDC_CLRMSG, &CMFCDay2Dlg::OnClrmsg)
  ON_BN_CLICKED(IDC_CKENBLMSG, &CMFCDay2Dlg::OnCkenblmsg)
  ON_BN_CLICKED(IDC_CKSHWMSG, &CMFCDay2Dlg::OnCkshwmsg)
  ON_BN_CLICKED(IDC_RUNPGM, &CMFCDay2Dlg::OnRunpgm)
  ON_BN_CLICKED(IDC_DFLTMSG, &CMFCDay2Dlg::OnCKDfltmsg)
  ON_BN_CLICKED(IDC_CKSHWPGM, &CMFCDay2Dlg::OnCkshwpgm)
  ON_BN_CLICKED(IDC_CKENBLPGM, &CMFCDay2Dlg::OnCkenblpgm)
END_MESSAGE_MAP()


// CMFCDay2Dlg message handlers

BOOL CMFCDay2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
  m_strMessage = "Place a message here";
  m_bShowMsg = TRUE;
  m_bShowPgm = TRUE;
  m_bEnableMsg = TRUE;
  m_bEnablePgm = TRUE;

  UpdateData(FALSE);

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

void CMFCDay2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCDay2Dlg::OnPaint()
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
HCURSOR CMFCDay2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDay2Dlg::OnBnClickedExit()
{
  // TODO: Add your control notification handler code here
  OnOK();
}


void CMFCDay2Dlg::OnShwmsg()
{
  // TODO: Add your control notification handler code here
  UpdateData(true);
  MessageBox(m_strMessage);
}


void CMFCDay2Dlg::OnClrmsg()
{
  // TODO: Add your control notification handler code here
  m_strMessage = "";
  UpdateData(FALSE);
}


void CMFCDay2Dlg::OnCkenblmsg()
{
  // TODO: Add your control notification handler code here
  UpdateData(TRUE);
  int vE = (m_bEnableMsg == TRUE);
  unsigned vID[5] = { IDC_MSG, IDC_SHWMSG, IDC_DFLTMSG, IDC_CLRMSG, IDC_STATICMSG };

  for (auto x : vID)
    GetDlgItem(x)->EnableWindow(vE);
}


void CMFCDay2Dlg::OnCkshwmsg()
{
  // TODO: Add your control notification handler code here
  UpdateData(TRUE);
  int vE = (m_bShowMsg == TRUE);
  unsigned vID[5] = { IDC_MSG, IDC_SHWMSG, IDC_DFLTMSG, IDC_CLRMSG, IDC_STATICMSG };

  for (auto x : vID)
    GetDlgItem(x)->EnableWindow(vE);
}

std::string  wchar2char(const wchar_t* wideStr, CString &iStr)
{
  //setlocale(LC_ALL, "");

  // Sample wide character string
  //const wchar_t* wideStr = L"Hello, 你好";

  // Calculate the size of the required buffer for the converted string
  size_t len = wcslen(wideStr) + 1; // +1 for null terminator

  // Allocate memory for the converted string
  char* narrowStr = (char*)malloc(len);

  // Convert wide string to multibyte string
  size_t temp = 0;
  wcstombs_s(&temp, narrowStr, len, wideStr, len);

  //wcstombs(narrowStr, wideStr, len);

  // Print the converted string
  printf("Narrow String: %s\n", narrowStr);
  iStr = "NarrowString is ";
  iStr += narrowStr;
  
  std::string vRlt(narrowStr);
  // Don't forget to free allocated memory
  free(narrowStr);
  return vRlt;
}


void CMFCDay2Dlg::OnRunpgm()
{
  // TODO: Add your control notification handler code here
  UpdateData(TRUE);
  CString strPgmName;
  strPgmName = m_strProgToRun;
  strPgmName.MakeUpper();
  if (strPgmName == "PAINT")
  {
    WinExec("mspaint.exe", SW_SHOW);
    m_strMessage = "mspaint.exe";
  }
  else if (strPgmName == "NOTEPAD")
  {
    WinExec("notepad.exe", SW_SHOW);
    m_strMessage = "notepad.exe";
  }
  else if (strPgmName == "SOLITAIRE")
  {
    WinExec("sol.exe", SW_SHOW);
    m_strMessage = "sol.exe";
  }
  else
  {
    int sizeOfString = (strPgmName.GetLength() + 1);
    std::string vTemp = wchar2char((const wchar_t*)strPgmName, m_strMessage);
    WinExec(vTemp.data(), SW_SHOW);
  }
}


void CMFCDay2Dlg::OnCKDfltmsg()
{
  // TODO: Add your control notification handler code here
  //m_strMessage = "Enter a message here";
  UpdateData(FALSE);
}






void CMFCDay2Dlg::OnCkshwpgm()
{
  // TODO: Add your control notification handler code here

  UpdateData(TRUE);
  int vE = (m_bShowPgm == TRUE);
  unsigned vID[3] = { IDC_PROGTORUN, IDC_STATICPGM, IDC_RUNPGM};

  for (auto x : vID)
    GetDlgItem(x)->EnableWindow(vE);
}


void CMFCDay2Dlg::OnCkenblpgm()
{
  // TODO: Add your control notification handler code here
  UpdateData(TRUE);
  int vE = (m_bEnablePgm == TRUE);
  unsigned vID[3] = { IDC_PROGTORUN, IDC_STATICPGM, IDC_RUNPGM };

  for (auto x : vID)
    GetDlgItem(x)->EnableWindow(vE);
}
