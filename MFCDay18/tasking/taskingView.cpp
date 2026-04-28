
// taskingView.cpp : implementation of the CtaskingView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "tasking.h"
#endif

#include "taskingDoc.h"
#include "taskingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtaskingView

IMPLEMENT_DYNCREATE(CtaskingView, CFormView)

BEGIN_MESSAGE_MAP(CtaskingView, CFormView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CtaskingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_CBONIDLE1, &CtaskingView::OnBnClickedCbonidle1)
	ON_BN_CLICKED(IDC_CBTHREAD1, &CtaskingView::OnBnClickedCbthread1)
	ON_BN_CLICKED(IDC_CBTHREAD2, &CtaskingView::OnBnClickedCbthread2)
END_MESSAGE_MAP()

// CtaskingView construction/destruction

CtaskingView::CtaskingView() noexcept
	: CFormView(IDD_TASKING_FORM)
	, m_bOnIdle1(FALSE)
	, m_bOnIdle2(FALSE)
	, m_bThread1(FALSE)
	, m_bThread2(FALSE)
{
	// TODO: add construction code here

}

CtaskingView::~CtaskingView()
{
}

void CtaskingView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CBONIDLE1, m_bOnIdle1);
	DDX_Check(pDX, IDC_CBONIDLE2, m_bOnIdle2);
	DDX_Check(pDX, IDC_CBTHREAD1, m_bThread1);
	DDX_Check(pDX, IDC_CBTHREAD2, m_bThread2);
}

BOOL CtaskingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CtaskingView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}


// CtaskingView printing


void CtaskingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CtaskingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CtaskingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CtaskingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CtaskingView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

void CtaskingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CtaskingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CtaskingView diagnostics

#ifdef _DEBUG
void CtaskingView::AssertValid() const
{
	CFormView::AssertValid();
}

void CtaskingView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CtaskingDoc* CtaskingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtaskingDoc)));
	return (CtaskingDoc*)m_pDocument;
}
#endif //_DEBUG


// CtaskingView message handlers

void CtaskingView::OnBnClickedCbonidle1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CtaskingView::OnBnClickedCbthread1()
{
	// TODO: Add your control notification handler code here

		// TODO: Add your control notification handler code here

			///////////////////////
			// MY CODE STARTS HERE
			///////////////////////
			 // Sync the variables with the dialog
	UpdateData(TRUE);
	// Get a pointer to the document
	auto* pDocWnd = (CtaskingDoc*)GetDocument();
	// Did we get a valid pointer?
	ASSERT_VALID(pDocWnd);
	// Suspend or start the spinner thread
	pDocWnd->SuspendSpinner(0, m_bThread1);

	//////////////////////
}
void CtaskingView::OnBnClickedCbthread2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// Get a pointer to the document
	auto* pDocWnd = (CtaskingDoc*)GetDocument();
	// Did we get a valid pointer?
	ASSERT_VALID(pDocWnd);
	// Suspend or start the spinner thread
	pDocWnd->SuspendSpinner(1, m_bThread2);

}
