#pragma once
#include "CMsgDlg.h"
class CDialogsDlg : public CDialogEx
{
	// Construction
public:
	CDialogsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGS_DIALOG };
#endif
	BOOL OnInitDialog();
	HCURSOR OnQueryDragIcon();
	void OnYesnocancel();
	void OnFileopen();
	void OnBcustomdialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void OnSysCommand(UINT nID, LPARAM lParam);
	virtual void OnPaint();
	DECLARE_MESSAGE_MAP();

// Implementation
protected:
	HICON m_hIcon;
	CString m_sResults;

private:
	CMsgDlg m_dMsgDlg;
	CButton m_cWhichOption;
};
