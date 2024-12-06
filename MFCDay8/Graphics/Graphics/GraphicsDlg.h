
// GraphicsDlg.h : header file
//

#pragma once

#include "CPaintDlg.h"
// CGraphicsDlg dialog
class CGraphicsDlg : public CDialogEx
{
// Construction
public:
	CGraphicsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPHICS_DIALOG };
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
//	afx_msg void OnBnClickedRsline();
//	afx_msg void OnBnClickedRadio6();
	int m_iColor;
	int m_iShape;
	int m_iTool;
	CString m_sBitMap;
	CBitmap m_bmpBitMap;
	CPaintDlg m_dlgPaint;
	afx_msg void OnBnClickedBexit();
	afx_msg void OnRSelection();
	afx_msg void OnBbitmap();
};
