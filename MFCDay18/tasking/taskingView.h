
// taskingView.h : interface of the CtaskingView class
//

#pragma once
#include "CSpinner.h"

class CtaskingView : public CFormView
{
protected: // create from serialization only
	CtaskingView() noexcept;
	DECLARE_DYNCREATE(CtaskingView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_TASKING_FORM };
#endif

// Attributes
public:
	CtaskingDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CtaskingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	BOOL m_bOnIdle1;
	BOOL m_bOnIdle2;
	BOOL m_bThread1;
	BOOL m_bThread2;

	afx_msg void OnBnClickedCbonidle1();
	afx_msg void OnBnClickedCbthread1();
	afx_msg void OnBnClickedCbthread2();
};

#ifndef _DEBUG  // debug version in taskingView.cpp
inline CtaskingDoc* CtaskingView::GetDocument() const
   { return reinterpret_cast<CtaskingDoc*>(m_pDocument); }
#endif

