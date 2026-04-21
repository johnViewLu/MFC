
// MFCDay13View.cpp : implementation of the CMFCDay13View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCDay13.h"
#endif

#include "MFCDay13Doc.h"
#include "MFCDay13View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDay13View

IMPLEMENT_DYNCREATE(CMFCDay13View, CView)

BEGIN_MESSAGE_MAP(CMFCDay13View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCDay13View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCDay13View construction/destruction

CMFCDay13View::CMFCDay13View() noexcept
{
	// TODO: add construction code here

}

CMFCDay13View::~CMFCDay13View()
{
}

BOOL CMFCDay13View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCDay13View drawing

void CMFCDay13View::OnDraw(CDC* /*pDC*/)
{
	CMFCDay13Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCDay13View printing


void CMFCDay13View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCDay13View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCDay13View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCDay13View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCDay13View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCDay13View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCDay13View diagnostics

#ifdef _DEBUG
void CMFCDay13View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDay13View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDay13Doc* CMFCDay13View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDay13Doc)));
	return (CMFCDay13Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDay13View message handlers
