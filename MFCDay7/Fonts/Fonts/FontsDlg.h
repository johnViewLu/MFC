
// FontsDlg.h : header file
//

#pragma once

int CALLBACK EnumFontFamProc(LPENUMLOGFONT lpelf, 
	                         LPNEWTEXTMETRIC lpntm, 
	                         DWORD nFontType,
	                         long lParam);

// CFontsDlg dialog
class CFontsDlg : public CDialogEx
{
// Construction
public:
	CFontsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FONTS_DIALOG };
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
	CStatic m_ctrlDisplayText;
	CString m_strDisplayText;
	CListBox m_ctrlFontList;
private:
	CString m_strFontName;
	CString m_strSampleText;
	void FillFontList();
public:
	afx_msg void OnChangeEsampletxt();
private:
	void SetMyFont();
	CFont m_fSampFont;
public:
	afx_msg void OnSelchangeLfonts();
};
