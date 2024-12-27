
// MFCDay10View.h : interface of the CMFCDay10View class
//

#pragma once


class CMFCDay10View : public CView
{
protected: // create from serialization only
	CMFCDay10View() noexcept;
	DECLARE_DYNCREATE(CMFCDay10View)

// Attributes
public:
	CMFCDay10Doc* GetDocument() const;

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
	virtual ~CMFCDay10View();
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
private:
	CPoint m_ptPrevPos;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in MFCDay10View.cpp
inline CMFCDay10Doc* CMFCDay10View::GetDocument() const
   { return reinterpret_cast<CMFCDay10Doc*>(m_pDocument); }
#endif

