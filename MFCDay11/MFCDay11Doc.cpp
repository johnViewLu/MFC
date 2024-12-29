
// MFCDay11Doc.cpp : implementation of the CMFCDay11Doc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCDay11.h"
#endif

#include "MFCDay11Doc.h"
#include "CLine.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCDay11Doc

IMPLEMENT_DYNCREATE(CMFCDay11Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCDay11Doc, CDocument)
	ON_COMMAND_RANGE(ID_PENSIZE_VERYTHIN, ID_PENSIZE_VERYTHICK, &CMFCDay11Doc::OnPensizeCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_PENSIZE_VERYTHIN, ID_PENSIZE_VERYTHICK, &CMFCDay11Doc::OnUpdatePensize)
	ON_COMMAND_RANGE(ID_COLOR_BLACK, ID_COLOR_WHITE, &CMFCDay11Doc::OnColorCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_COLOR_BLACK, ID_COLOR_WHITE, &CMFCDay11Doc::OnUpdateColor)
END_MESSAGE_MAP()


const COLORREF CMFCDay11Doc::m_crColors[8] = {
	RGB(0,		0,		  0),
	RGB(0,		0,		255),
	RGB(0,		255,	  0),
	RGB(0,		255,	255),
	RGB(255,	0,		  0),
	RGB(255,	0,		255),
	RGB(255,	255,	  0),
	RGB(255,	255,	255)
};


// CMFCDay11Doc construction/destruction

CMFCDay11Doc::CMFCDay11Doc() noexcept
{
	// TODO: add one-time construction code here
	m_nPenSize = 1;
	m_nColor = 0;
}

CMFCDay11Doc::~CMFCDay11Doc()
{
}

BOOL CMFCDay11Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCDay11Doc serialization

void CMFCDay11Doc::Serialize(CArchive& ar)
{
	m_oaLines.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCDay11Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMFCDay11Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCDay11Doc::SetSearchContent(const CString& value)
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

// CMFCDay11Doc diagnostics

#ifdef _DEBUG
void CMFCDay11Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCDay11Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCDay11Doc commands





void CMFCDay11Doc::OnColorCommand(UINT iID)
{
	// TODO: Add your command handler code here
	m_nColor = iID - ID_COLOR_BLACK;
}


void CMFCDay11Doc::OnUpdateColor(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_nColor + ID_COLOR_BLACK == pCmdUI->m_nID);

}

void CMFCDay11Doc::OnPensizeCommand(UINT iID)
{
	if (iID != ID_PENSIZE_VERYTHIN)
		m_nPenSize = 8*(iID - ID_PENSIZE_VERYTHIN);
	else
		m_nPenSize = 1;
}


void CMFCDay11Doc::OnUpdatePensize(CCmdUI* pCmdUI)
{
	if (pCmdUI->m_nID != ID_PENSIZE_VERYTHIN)
		pCmdUI->SetCheck(m_nPenSize == (pCmdUI->m_nID- ID_PENSIZE_VERYTHIN) * 8);
	else
		pCmdUI->SetCheck(m_nPenSize==1);

}

CLine* CMFCDay11Doc::AddLine(CPoint ptFrom, CPoint ptTo)
{
	// TODO: Add your implementation code here.
	CLine* pLine = new CLine(ptFrom, ptTo, m_crColors[m_nColor]);
	try {
		m_oaLines.Add(pLine);
		SetModifiedFlag();
	}
	catch (CMemoryException* perr)
	{
		AfxMessageBox(L"Out of memory", MB_ICONSTOP | MB_OK);
		if (pLine)
		{
			delete pLine;
			pLine = nullptr;
		}
		perr->Delete();
	}
	//L_(linfo) << __FUNCTION__;
	//L_(linfo) << "GetLineCount()=" << m_oaLines.GetSize();
	return pLine;
}



CLine* CMFCDay11Doc::GetLine(int nIndex)
{
	// TODO: Add your implementation code here.
	return (CLine*)m_oaLines[nIndex];
	//return nullptr;
}


void CMFCDay11Doc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	auto liCount = m_oaLines.GetSize();
	//L_(linfo) << __FUNCTION__;
	if (liCount)
	{
		for (auto ix = 0; ix < liCount; ++ix)
			delete m_oaLines[ix];
		m_oaLines.RemoveAll();
	}
	CDocument::DeleteContents();
}
