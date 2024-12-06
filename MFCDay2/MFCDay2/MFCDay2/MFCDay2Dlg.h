
// MFCDay2Dlg.h : header file
//

#pragma once


// CMFCDay2Dlg dialog
class CMFCDay2Dlg : public CDialogEx
{
// Construction
public:
	CMFCDay2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDAY2_DIALOG };
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
  afx_msg void OnBnClickedButton2();
  afx_msg void OnLbnSelchangeList2();
  afx_msg void OnBnClickedMfcday2Dialog();
  afx_msg void OnBnClickedCheck1();
  afx_msg void OnBnClickedCheck3();
private:
  CString m_strMessage;
  CString m_strProgToRun;
  BOOL m_bEnableMsg;
  BOOL m_bEnablePgm;
  BOOL m_bShowMsg;
public:
  BOOL m_bShowPgm;
  afx_msg void OnBnClickedExit();
  afx_msg void OnShwmsg();
  afx_msg void OnClrmsg();
  afx_msg void OnCkenblmsg();
  afx_msg void OnCkshwmsg();
  afx_msg void OnCbnSelchangeProgtorun();
  afx_msg void OnRunpgm();
  afx_msg void OnCKDfltmsg();
  afx_msg void OnCkshwpgm();
  afx_msg void OnCkenblpgm();
};
