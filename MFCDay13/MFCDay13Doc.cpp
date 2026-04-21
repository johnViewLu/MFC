
// MFCDay13Doc.cpp : implementation of the CMFCDay13Doc class
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

#include <propkey.h>

#include "CPerson.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CMFCDay13Doc

IMPLEMENT_DYNCREATE(CMFCDay13Doc, CDocument)
BEGIN_MESSAGE_MAP(CMFCDay13Doc, CDocument)
//	//ON_COMMAND(IDC_FIRST, &CMFCDay13Doc::OnFirst)
//	//ON_COMMAND(IDC_BUTTON2, &CMFCDay13Doc::OnPrevious)
//	//ON_COMMAND(IDC_BUTTON3, &CMFCDay13Doc::OnNext)
//	//ON_COMMAND(IDC_BUTTON4, &CMFCDay13Doc::OnLast)
END_MESSAGE_MAP()


// CMFCDay13Doc construction/destruction

CMFCDay13Doc::CMFCDay13Doc() noexcept
{
	// TODO: add one-time construction code here
}

CMFCDay13Doc::~CMFCDay13Doc()
{
}


void CMFCDay13Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		int size = (int)m_oaPeople.size();
		ar << size;

		for (auto& p : m_oaPeople)
		{
			p->Serialize(ar);
		}
	}
	else
	{
		int size;
		ar >> size;

		m_oaPeople.clear();

		for (int i = 0; i < size; ++i)
		{
			auto p= std::make_unique<CPerson>();
			p->Serialize(ar);
			m_oaPeople.push_back(std::move(p));
		}
	}
}


#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCDay13Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCDay13Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCDay13Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCDay13Doc diagnostics

#ifdef _DEBUG
void CMFCDay13Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCDay13Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCDay13Doc commands

CPerson* CMFCDay13Doc::AddNewRecord()
{
	m_oaPeople.push_back(std::make_unique<CPerson>());

	m_iCurPosition = static_cast<int>(m_oaPeople.size()) - 1;
	SetModifiedFlag(TRUE);

	return m_oaPeople.back().get();
}


int CMFCDay13Doc::GetTotalRecords()
{
	// TODO: Add your implementation code here.
	return static_cast<int>(m_oaPeople.size());
}

int CMFCDay13Doc::GetCurRecordNbr()
{
	// TODO: Add your implementation code here.
	return m_iCurPosition+1;
}

CPerson* CMFCDay13Doc::GetCurRecord()
{
	// TODO: Add your implementation code here.
	if (m_iCurPosition >= 0 && m_iCurPosition < m_oaPeople.size())
	{
		return m_oaPeople[m_iCurPosition].get();
	}
	return nullptr;
}

CPerson* CMFCDay13Doc::GetFirstRecord()
{
	// TODO: Add your implementation code here.
	if (m_oaPeople.size() > 0)
	{
		m_iCurPosition = 0;
		return m_oaPeople[m_iCurPosition].get();
	}
	return nullptr;
}

CPerson* CMFCDay13Doc::GetLastRecord()
{
	// TODO: Add your implementation code here.
	if (m_oaPeople.size() > 0)
	{
		m_iCurPosition = static_cast<int>(m_oaPeople.size()) - 1;
		return m_oaPeople[m_iCurPosition].get();
	}
	return nullptr;
}

CPerson* CMFCDay13Doc::GetNextRecord()
{
	// TODO: Add your implementation code here.
	if(++m_iCurPosition< m_oaPeople.size())
	{
		return m_oaPeople[m_iCurPosition].get();
	}
	else
	{
		return AddNewRecord();
	}
}

CPerson* CMFCDay13Doc::GetPrevRecord()
{
	// TODO: Add your implementation code here.
	if(m_oaPeople.size()>0 && --m_iCurPosition >= 0)
	{
		return m_oaPeople[m_iCurPosition].get();
	}
	return nullptr;
}

void CMFCDay13Doc::DeleteContents()
{
	// TODO: Add your implementation code here.
    m_oaPeople.clear();
    m_iCurPosition = -1;
	CDocument::DeleteContents();
}


BOOL CMFCDay13Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
	{
		return false;
	}

	if (!AddNewRecord())
		return false;

	POSITION pos = GetFirstViewPosition();
	CMFCDay13View* pView = (CMFCDay13View*)GetNextView(pos);
	if(pView)
	{
		pView->NewDataSet();
	}
	return TRUE;
}


BOOL CMFCDay13Doc::OnOpenDocument(LPCTSTR pszPathName)
{
	if (!CDocument::OnOpenDocument(pszPathName))
		return FALSE;
	POSITION pos = GetFirstViewPosition();
	CMFCDay13View* pView = (CMFCDay13View*)GetNextView(pos);
	if (pView)
	{
		pView->NewDataSet();
	}
	return TRUE;
}
