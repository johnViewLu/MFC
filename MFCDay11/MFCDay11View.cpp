
// MFCDay11View.cpp : implementation of the CMFCDay11View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCDay11.h"
#endif

#include "MFCDay11Doc.h"
#include "MFCDay11View.h"
#include "CLine.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDay11View

IMPLEMENT_DYNCREATE(CMFCDay11View, CView)

BEGIN_MESSAGE_MAP(CMFCDay11View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCDay11View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFCDay11View construction/destruction

CMFCDay11View::CMFCDay11View() noexcept
{
	// TODO: add construction code here

}

CMFCDay11View::~CMFCDay11View()
{
}

BOOL CMFCDay11View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCDay11View drawing

void CMFCDay11View::OnDraw(CDC* pDC)
{
	CMFCDay11Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//L_(linfo) << __FUNCTION__;
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


// CMFCDay11View printing


void CMFCDay11View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCDay11View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCDay11View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCDay11View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCDay11View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCDay11View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif

	CMenu menu;
	//menu.loadMenuW(IDR_CONTEXTMENU);
    menu.LoadMenuW(IDR_CONTEXTMENU);
	auto ptr = menu.GetSubMenu(0);
	ptr->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());


}


// CMFCDay11View diagnostics

#ifdef _DEBUG
void CMFCDay11View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDay11View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDay11Doc* CMFCDay11View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDay11Doc)));
	return (CMFCDay11Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDay11View message handlers


void CMFCDay11View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	m_ptPrevPos = point;
	CView::OnLButtonDown(nFlags, point);
}


void CMFCDay11View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (GetCapture() == this)
		ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}


void CMFCDay11View::OnMouseMove(UINT nFlags, CPoint point)
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
