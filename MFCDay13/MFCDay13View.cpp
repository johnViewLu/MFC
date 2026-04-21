
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
#include "CPerson.h"
#include <sstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCDay13View

IMPLEMENT_DYNCREATE(CMFCDay13View, CFormView)

BEGIN_MESSAGE_MAP(CMFCDay13View, CFormView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_EN_CHANGE(IDC_ENAME, &CMFCDay13View::OnEnChangeEname)
	ON_EN_CHANGE(IDC_EAGE, &CMFCDay13View::OnEnChangeEage)
	ON_BN_CLICKED(IDC_CEMPLOYED, &CMFCDay13View::OnClickedCemployed)
	ON_BN_CLICKED(IDC_FIRST, &CMFCDay13View::OnClickedFirst)
	ON_BN_CLICKED(IDC_Previous, &CMFCDay13View::OnClickedPrevious)
	ON_BN_CLICKED(IDC_Next, &CMFCDay13View::OnClickedNext)
	ON_BN_CLICKED(IDC_Last, &CMFCDay13View::OnClickedLast)
	ON_BN_CLICKED(IDC_RSINGLE, &CMFCDay13View::OnClickedRsingle)
	ON_COMMAND(IDC_RMARRIED, &CMFCDay13View::OnRmarried)
	ON_COMMAND(IDC_RDIVORCED, &CMFCDay13View::OnRdivorced)
	ON_COMMAND(IDC_RWIDOW, &CMFCDay13View::OnRwidow)
	ON_BN_CLICKED(IDC_FEMALE, &CMFCDay13View::OnClickedFemale)
	ON_COMMAND(IDC_MALE, &CMFCDay13View::OnMale)
END_MESSAGE_MAP()

// CMFCDay13View construction/destruction

CMFCDay13View::CMFCDay13View() noexcept
	: CFormView(IDD_MFCDAY13_FORM)
	, m_iAge(0)
	, m_strName(_T(""))
	, m_sPosition(_T(""))
	, m_bEmployed(false)
	, m_iMaritalStatus(0)				
	, m_iSex(0)
{
	// TODO: add construction code here
	m_pCurPerson = nullptr;
}

CMFCDay13View::~CMFCDay13View()
{
}

void CMFCDay13View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ENAME, m_strName);
	DDX_Text(pDX, IDC_SPOSITION, m_sPosition);
	DDX_Check(pDX, IDC_CEMPLOYED, m_bEmployed);
	DDX_Radio(pDX, IDC_RSINGLE, m_iMaritalStatus);
	DDX_Radio(pDX, IDC_FEMALE, m_iSex);


	if (pDX->m_bSaveAndValidate)
	{
		// UI → variable
		CString str;
		DDX_Text(pDX, IDC_EAGE, str);

		if (str.IsEmpty())
			m_iAge = 0;
		else
			m_iAge = _ttoi(str);
	}
	else
	{
		// variable → UI
		if (m_iAge == 0)
		{
			SetDlgItemText(IDC_EAGE, _T(""));
		}
		else
		{
			DDX_Text(pDX, IDC_EAGE, m_iAge);
		}
	}
}

BOOL CMFCDay13View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMFCDay13View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CMFCDay13View printing

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

void CMFCDay13View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}


// CMFCDay13View diagnostics

#ifdef _DEBUG
void CMFCDay13View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCDay13View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCDay13Doc* CMFCDay13View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDay13Doc)));
	return (CMFCDay13Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDay13View message handlers



void CMFCDay13View::NewDataSet()
{
	// TODO: Add your implementation code here.
	OnBfirst();
}

void CMFCDay13View::OnBfirst()
{
	// TODO: Add your implementation code here.
	CMFCDay13Doc* pDoc = (CMFCDay13Doc*)GetDocument();
	if (pDoc)
	{
		m_pCurPerson = pDoc->GetFirstRecord();
		if (m_pCurPerson)
		{
			PopulateView();
		}
		else
		{
			AfxMessageBox(_T("No data!"));
		}
	}
}

void CMFCDay13View::PopulateView()
{
	// TODO: Add your implementation code here.
	CMFCDay13Doc* pDoc = (CMFCDay13Doc*)GetDocument();
	if (pDoc)
	{
		std::ostringstream os;
		os << "Record " << pDoc->GetCurRecordNbr() << " of " << pDoc->GetTotalRecords();
		m_sPosition = os.str().c_str();

		//m_sPosition.Format("Record %d of %d", pDoc->GetCurRecordNbr(), pDoc->GetTotalRecords());
		if (m_pCurPerson)
		{
			m_bEmployed = m_pCurPerson->IsEmployed();
			m_iAge = m_pCurPerson->GetAge();
			m_strName = m_pCurPerson->GetName();
			m_iMaritalStatus = m_pCurPerson->GetMaritalStatus();
			m_iSex = static_cast<int>(m_pCurPerson->GetSex());
		}
		UpdateData(FALSE);
	}

}


void CMFCDay13View::OnClickedCemployed()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_pCurPerson)
	{
		m_pCurPerson->SetEmployed(m_bEmployed);
	}
}

void CMFCDay13View::OnEnChangeEname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	if (m_pCurPerson)
	{
		m_pCurPerson->SetName(m_strName);
	}

}

void CMFCDay13View::OnEnChangeEage()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	if (m_pCurPerson)
	{
		m_pCurPerson->SetAge(m_iAge);
	}


}
void CMFCDay13View::OnClickedFirst()
{
	// TODO: Add your control notification handler code here
	OnBfirst();
}

void CMFCDay13View::OnClickedPrevious()
{
	// TODO: Add your control notification handler code here
	CMFCDay13Doc* pDoc = (CMFCDay13Doc*)GetDocument();
	if (pDoc)
	{
		m_pCurPerson = pDoc->GetPrevRecord();
		if (m_pCurPerson)
		{
			PopulateView();
		}
		else
		{
			AfxMessageBox(_T("No data!"));
		}
	}
}

void CMFCDay13View::OnClickedNext()
{
	// TODO: Add your control notification handler code here
	CMFCDay13Doc* pDoc = (CMFCDay13Doc*)GetDocument();
	if (pDoc)
	{
		m_pCurPerson = pDoc->GetNextRecord();
		if (m_pCurPerson)
		{
			PopulateView();
		}
		else
		{
			AfxMessageBox(_T("No data!"));
		}
	}
}

void CMFCDay13View::OnClickedLast()
{
	// TODO: Add your control notification handler code here
	CMFCDay13Doc* pDoc = (CMFCDay13Doc*)GetDocument();
	if (pDoc)
	{
		m_pCurPerson = pDoc->GetLastRecord();
		if (m_pCurPerson)
		{
			PopulateView();
		}
		else
		{
			AfxMessageBox(_T("No data!"));
		}
	}
}



void CMFCDay13View::OnClickedRsingle()
{
	// TODO: Add your control notification handler code here
	RadioButtonCheck(ClsMaritalStatus::eSingle);
}

void CMFCDay13View::OnRmarried()
{
	// TODO: Add your command handler code here
	RadioButtonCheck(ClsMaritalStatus::eMarried);
}

void CMFCDay13View::OnRdivorced()
{
	// TODO: Add your command handler code here
	RadioButtonCheck(ClsMaritalStatus::eDivorced);
}

void CMFCDay13View::OnRwidow()
{
	// TODO: Add your command handler code here
	RadioButtonCheck(ClsMaritalStatus::eWidow);
}

void CMFCDay13View::RadioButtonCheck(ClsMaritalStatus iOption)
{
	UpdateData(TRUE);
	if (m_pCurPerson)
	{
		m_pCurPerson->SetMaritalStatus(static_cast<int>(iOption) );
	}
}

void CMFCDay13View::OnClickedFemale()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_pCurPerson)
    {
		m_pCurPerson->SetSex(sex::Female);
	}	
}

void CMFCDay13View::OnMale()
{
	// TODO: Add your command handler code here
	UpdateData(TRUE);
	if (m_pCurPerson)
	{
		m_pCurPerson->SetSex(sex::Male);
	}
}
