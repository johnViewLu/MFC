
// MFCDay10View.cpp : implementation of the CMFCDay10View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCDay10.h"
#endif

#include "MFCDay10Doc.h"
#include "MFCDay10View.h"
#include "CLine.h"
#include "DebugLog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDay10View

IMPLEMENT_DYNCREATE(CMFCDay10View, CView)

BEGIN_MESSAGE_MAP(CMFCDay10View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCDay10View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFCDay10View construction/destruction

CMFCDay10View::CMFCDay10View() noexcept
{
	// TODO: add construction code here

}

CMFCDay10View::~CMFCDay10View()
{
}

BOOL CMFCDay10View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCDay10View drawing

void CMFCDay10View::OnDraw(CDC* pDC)
{
	CMFCDay10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	L_(linfo) << __FUNCTION__;
	// TODO: add draw code for native data here
	auto liCount = pDoc->GetLineCount();
	if (liCount)
	{
		for (auto liPos = 0; liPos < liCount; ++liPos)
		{
			auto lptLine = pDoc->GetLine(liPos);
			lptLine->Draw(pDC, GetDocument()->GetPenSize());
		}
	}
}


// CMFCDay10View printing


void CMFCDay10View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCDay10View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCDay10View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCDay10View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCDay10View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCDay10View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCDay10View diagnostics

#ifdef _DEBUG
void CMFCDay10View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDay10View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDay10Doc* CMFCDay10View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDay10Doc)));
	return (CMFCDay10Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDay10View message handlers


void CMFCDay10View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	m_ptPrevPos = point;
	CView::OnLButtonDown(nFlags, point);
}


void CMFCDay10View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (GetCapture() == this)
		ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}


void CMFCDay10View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON)
	{
		if (GetCapture() == this)
		{
			CClientDC dc(this);
			CLine* pLine = GetDocument()->AddLine(m_ptPrevPos, point);
			pLine->Draw(&dc, GetDocument()->GetPenSize());
			m_ptPrevPos = point;
		}
	}

	CView::OnMouseMove(nFlags, point);
}
