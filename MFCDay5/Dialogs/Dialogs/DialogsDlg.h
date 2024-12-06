
// DialogsDlg.h : header file
//

#pragma once
#include "CMsgDlg.h"

// CDialogsDlg dialog
class CDialogsDlg : public CDialogEx
{
// Construction
public:
	CDialogsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGS_DIALOG };
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
private:
	CString m_sResults;
	CButton m_cWhichOption;
public:
	afx_msg void OnYesnocancel();
	afx_msg void OnFileopen();
private:
	// custome dialog
	CMsgDlg m_dMsgDlg;
public:
	afx_msg void OnBcustomdialog();
	afx_msg void OnBwhichoption();
};
