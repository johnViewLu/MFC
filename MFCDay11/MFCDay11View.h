
// MFCDay11View.h : interface of the CMFCDay11View class
//

#pragma once


class CMFCDay11View : public CView
{
protected: // create from serialization only
	CMFCDay11View() noexcept;
	DECLARE_DYNCREATE(CMFCDay11View)

// Attributes
public:
	CMFCDay11Doc* GetDocument() const;

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
	virtual ~CMFCDay11View();
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	CPoint m_ptPrevPos;
};

#ifndef _DEBUG  // debug version in MFCDay11View.cpp
inline CMFCDay11Doc* CMFCDay11View::GetDocument() const
   { return reinterpret_cast<CMFCDay11Doc*>(m_pDocument); }
#endif

