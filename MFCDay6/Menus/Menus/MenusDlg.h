
// MenusDlg.h : header file
//

#pragma once


// CMenusDlg dialog
class CMenusDlg : public CDialogEx
{
// Construction
public:
	CMenusDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENUS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnExit();
	afx_msg void OnFileHello();
	afx_msg void OnFileExit();
//	afx_msg void OnAboutbox();
	afx_msg void OnHelpAbout();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	
	afx_msg void OnHello();
	afx_msg void OnHelpAbout2();
	afx_msg void OnHelloAbout();
};
