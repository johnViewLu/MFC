
// TestAPPView.h : interface of the CTestAPPView class
//

#pragma once


class CTestAPPView : public CView
{
protected: // create from serialization only
	CTestAPPView() noexcept;
	DECLARE_DYNCREATE(CTestAPPView)

// Attributes
public:
	CTestAPPDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTestAPPView();
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
};

#ifndef _DEBUG  // debug version in TestAPPView.cpp
inline CTestAPPDoc* CTestAPPView::GetDocument() const
   { return reinterpret_cast<CTestAPPDoc*>(m_pDocument); }
#endif

