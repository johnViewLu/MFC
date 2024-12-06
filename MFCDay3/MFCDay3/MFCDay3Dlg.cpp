
// MFCDay3Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCDay3.h"
#include "MFCDay3Dlg.h"
#include "afxdialogex.h"
#include <vector>
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


// CMFCDay3Dlg dialog



CMFCDay3Dlg::CMFCDay3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDAY3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDay3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCDay3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_WM_MOUSEMOVE()
  ON_WM_LBUTTONDOWN()
  ON_WM_KEYDOWN()
  ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CMFCDay3Dlg message handlers

BOOL CMFCDay3Dlg::OnInitDialog()
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
  m_bCursor = FALSE;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCDay3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCDay3Dlg::OnPaint()
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
HCURSOR CMFCDay3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDay3Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
    //if (!(nFlags & MK_LBUTTON))
  if ((nFlags & MK_LBUTTON) == MK_LBUTTON)
  {
    CClientDC dc(this);
    dc.MoveTo(m_iPrevX, m_iPrevY);
    dc.LineTo(point.x, point.y);
    m_iPrevX = point.x;
    m_iPrevY = point.y;
    //Draw pixel
    //dc.SetPixel(point.x, point.y, RGB(0, 0, 0));
  }
  CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCDay3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
  m_iPrevX = point.x;
  m_iPrevY = point.y;
  CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCDay3Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  // TODO: Add your message handler code here and/or call default
  char IsChar;
  HCURSOR lhCursor;
  std::vector<char> vChar =     { 'A',       'B',      'C',      'D' ,       'E',         'F', 
                                  'G',        'H',     'I',      'O',        'P',         'Q',
                                  'L',
    'X' };
  std::vector<LPWSTR> vCursor = { IDC_ARROW, IDC_IBEAM, IDC_WAIT, IDC_CROSS, IDC_UPARROW, IDC_SIZEALL, 
                        IDC_SIZENWSE, IDC_SIZENESW, IDC_SIZEWE,  IDC_SIZENS, IDC_NO,    IDC_APPSTARTING,
                        IDC_HELP,
    IDC_ARROW };
  IsChar = char(nChar);
  for(int ix=0; ix<vChar.size(); ++ix)
    if (vChar[ix] == IsChar)
    {
      lhCursor = AfxGetApp()->LoadStandardCursor(vCursor[ix]);
      SetCursor(lhCursor);
	  break;
    }

  if (IsChar == 'X')
    OnOK();
  else {
    m_bCursor = true;
    //SetCursor(lhCursor);
  }


  CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CMFCDay3Dlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
  // TODO: Add your message handler code here and/or call default
  if (m_bCursor)
    return true;
  return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}
