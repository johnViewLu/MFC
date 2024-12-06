
// MFCDay3Dlg.h : header file
//

#pragma once


// CMFCDay3Dlg dialog
class CMFCDay3Dlg : public CDialogEx
{
// Construction
public:
	CMFCDay3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDAY3_DIALOG };
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
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
  int m_iPrevY;
  int m_iPrevX;
public:
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
  bool m_bCursor;
public:
  afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
