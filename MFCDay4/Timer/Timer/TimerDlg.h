
// TimerDlg.h : header file
//

#pragma once


// CTimerDlg dialog
class CTimerDlg : public CDialogEx
{
// Construction
public:
	CTimerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMER_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_sTime;
	CString m_sCount;
	int m_iCount;
//	int m_iInterval;
	CButton m_cStartTimer;
	CButton m_cStopTimer;
	afx_msg void OnChangeInterval();
	afx_msg void OnStarttime();
	afx_msg void OnStoptimer();
private:
	int m_iInterval;
public:
	int testInt;
	afx_msg void OnChangeEdit1();
	afx_msg void OnStnClickedStatictime();
};
