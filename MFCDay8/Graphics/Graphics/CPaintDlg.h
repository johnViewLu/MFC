#pragma once
#include "afxdialogex.h"


// CPaintDlg dialog

class CPaintDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPaintDlg)

public:
	CPaintDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPaintDlg();
	static const COLORREF m_crColor[8];
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAINT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	void DrawLine(CPaintDC* pdc, int iColor);
	void DrawRegion(CPaintDC* pDC, int iColor, int iTool, int iShape);
	void ShowBitmap(CPaintDC* pDC, CWnd *pWnd);
public:
	afx_msg void OnPaint();
};
