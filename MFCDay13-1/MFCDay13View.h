
// MFCDay13View.h : interface of the CMFCDay13View class
//

#pragma once


class CMFCDay13View : public CView
{
protected: // create from serialization only
	CMFCDay13View() noexcept;
	DECLARE_DYNCREATE(CMFCDay13View)

// Attributes
public:
	CMFCDay13Doc* GetDocument() const;

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
	virtual ~CMFCDay13View();
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

#ifndef _DEBUG  // debug version in MFCDay13View.cpp
inline CMFCDay13Doc* CMFCDay13View::GetDocument() const
   { return reinterpret_cast<CMFCDay13Doc*>(m_pDocument); }
#endif

