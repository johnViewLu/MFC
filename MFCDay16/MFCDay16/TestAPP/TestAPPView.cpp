
// TestAPPView.cpp : implementation of the CTestAPPView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TestAPP.h"
#endif

#include "TestAPPDoc.h"
#include "TestAPPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestAPPView

IMPLEMENT_DYNCREATE(CTestAPPView, CView)

BEGIN_MESSAGE_MAP(CTestAPPView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestAPPView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CTestAPPView construction/destruction

CTestAPPView::CTestAPPView() noexcept
{
	// TODO: add construction code here

}

CTestAPPView::~CTestAPPView()
{
}

BOOL CTestAPPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}


// CTestAPPView printing


void CTestAPPView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestAPPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestAPPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestAPPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTestAPPView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestAPPView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestAPPView diagnostics

#ifdef _DEBUG
void CTestAPPView::AssertValid() const
{
	CView::AssertValid();
}

void CTestAPPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestAPPDoc* CTestAPPView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestAPPDoc)));
	return (CTestAPPDoc*)m_pDocument;
}
#endif //_DEBUG


void CTestAPPView::OnDraw(CDC* pDC)
{
	CTestAPPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

		 // Get the drawing object
	CModArt* m_maDrawing = pDoc->GetDrawing();
	// Draw the drawing
	m_maDrawing->Draw(pDC);
}

// CTestAPPView message handlers
