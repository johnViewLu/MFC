
// MFCDay10Doc.cpp : implementation of the CMFCDay10Doc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCDay10.h"
#endif

#include "MFCDay10Doc.h"
#include <fstream>
#include <propkey.h>
#include "CLine.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "DebugLog.h"
// CMFCDay10Doc

IMPLEMENT_DYNCREATE(CMFCDay10Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCDay10Doc, CDocument)
	ON_COMMAND(ID_COLOR_BLACK, &CMFCDay10Doc::OnColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CMFCDay10Doc::OnUpdateColorBlack)
	ON_COMMAND(ID_COLOR_BLUE, &CMFCDay10Doc::OnColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CMFCDay10Doc::OnUpdateColorBlue)
	ON_COMMAND(ID_COLOR_CYAN, &CMFCDay10Doc::OnColorCyan)
	ON_UPDATE_COMMAND_UI(ID_COLOR_CYAN, &CMFCDay10Doc::OnUpdateColorCyan)
	ON_COMMAND(ID_COLOR_GREEN, &CMFCDay10Doc::OnColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CMFCDay10Doc::OnUpdateColorGreen)
	ON_COMMAND(ID_COLOR_MAGENTA, &CMFCDay10Doc::OnColorMagenta)
	ON_UPDATE_COMMAND_UI(ID_COLOR_MAGENTA, &CMFCDay10Doc::OnUpdateColorMagenta)
	ON_COMMAND(ID_COLOR_RED, &CMFCDay10Doc::OnColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CMFCDay10Doc::OnUpdateColorRed)
	ON_COMMAND(ID_COLOR_WHITE, &CMFCDay10Doc::OnColorWhite)
	ON_UPDATE_COMMAND_UI(ID_COLOR_WHITE, &CMFCDay10Doc::OnUpdateColorWhite)
	ON_COMMAND(ID_COLOR_YELLOW, &CMFCDay10Doc::OnColorYellow)
	ON_UPDATE_COMMAND_UI(ID_COLOR_YELLOW, &CMFCDay10Doc::OnUpdateColorYellow)
	ON_COMMAND_RANGE(ID_PENSIZE_VERYTHIN, ID_PENSIZE_VERYTHICK, &CMFCDay10Doc::OnPensizeCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_PENSIZE_VERYTHIN, ID_PENSIZE_VERYTHICK, &CMFCDay10Doc::OnUpdatePensizeCommand)
END_MESSAGE_MAP()

const COLORREF CMFCDay10Doc::m_crColors[8] = {
	RGB(0,		0,		  0),
	RGB(0,		0,		255),
	RGB(0,		255,	  0),
	RGB(0,		255,	255),
	RGB(255,	0,		  0),
	RGB(255,	0,		255),
	RGB(255,	255,	  0),
	RGB(255,	255,	255)
};


// CMFCDay10Doc construction/destruction

CMFCDay10Doc::CMFCDay10Doc() noexcept
{
	// TODO: add one-time construction code here
	m_nPenSize = 32;

}

CMFCDay10Doc::~CMFCDay10Doc()
{
}

BOOL CMFCDay10Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_nColor = ID_COLOR_BLACK - ID_COLOR_BLACK;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCDay10Doc serialization

void CMFCDay10Doc::Serialize(CArchive& ar)
{
	m_oaLines.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCDay10Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMFCDay10Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCDay10Doc::SetSearchContent(const CString& value)
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

// CMFCDay10Doc diagnostics

#ifdef _DEBUG
void CMFCDay10Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCDay10Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCDay10Doc commands


CLine* CMFCDay10Doc::AddLine(CPoint ptFrom, CPoint ptTo)
{
	// TODO: Add your implementation code here.
	CLine* pLine = new CLine(ptFrom, ptTo,m_crColors[m_nColor]);
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
	L_(linfo) << __FUNCTION__;
	L_(linfo) << "GetLineCount()=" << m_oaLines.GetSize();
	return pLine;
}


int CMFCDay10Doc::GetLineCount()
{
	// TODO: Add your implementation code here.
	//std::ofstream vFile;
	//vFile.open("debugRecord.txt", std::ofstream::app);	
	auto vCount = m_oaLines.GetSize();
	//vFile << "GetLineSize= " <<vCount << "\n";
	L_(linfo) << __FUNCTION__ << "vCount=" << vCount;
	return vCount;
}


CLine* CMFCDay10Doc::GetLine(int nIndex)
{
	// TODO: Add your implementation code here.
	return (CLine*)m_oaLines[nIndex];
	//return nullptr;
}


void CMFCDay10Doc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	auto liCount = m_oaLines.GetSize();
	L_(linfo) << __FUNCTION__;
	if (liCount)
	{
		for (auto ix = 0; ix < liCount; ++ix)
			delete m_oaLines[ix];
		m_oaLines.RemoveAll();
	}
	CDocument::DeleteContents();
}


unsigned int CMFCDay10Doc::GetColor()
{
	// TODO: Add your implementation code here.
	return ID_COLOR_BLACK + m_nColor;
}


void CMFCDay10Doc::OnColorBlack()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_BLACK - ID_COLOR_BLACK;
}


void CMFCDay10Doc::OnUpdateColorBlack(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_BLACK ? 1 : 0);
}


void CMFCDay10Doc::OnColorBlue()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_BLUE - ID_COLOR_BLACK;
}


void CMFCDay10Doc::OnUpdateColorBlue(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_BLUE ? 1 : 0);
}


void CMFCDay10Doc::OnColorCyan()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_CYAN - ID_COLOR_BLACK;
}


void CMFCDay10Doc::OnUpdateColorCyan(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_CYAN ? 1 : 0);
}


void CMFCDay10Doc::OnColorGreen()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_GREEN - ID_COLOR_BLACK;
}


void CMFCDay10Doc::OnUpdateColorGreen(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_GREEN ? 1 : 0);
}


void CMFCDay10Doc::OnColorMagenta()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_MAGENTA - ID_COLOR_BLACK;
}


void CMFCDay10Doc::OnUpdateColorMagenta(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_MAGENTA ? 1 : 0);
}


void CMFCDay10Doc::OnColorRed()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_RED - ID_COLOR_BLACK;
}


void CMFCDay10Doc::OnUpdateColorRed(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_RED ? 1 : 0);
}


void CMFCDay10Doc::OnColorWhite()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_WHITE - ID_COLOR_BLACK;
}


void CMFCDay10Doc::OnUpdateColorWhite(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_WHITE ? 1 : 0);
}


void CMFCDay10Doc::OnColorYellow()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_YELLOW - ID_COLOR_BLACK;
}


void CMFCDay10Doc::OnUpdateColorYellow(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_YELLOW ? 1 : 0);
}


void CMFCDay10Doc::OnPensizeCommand(UINT iID)
{
	// TODO: Add your command handler code here
	m_nPenSize = iID - ID_PENSIZE_VERYTHIN + 1;
	if(iID!=ID_PENSIZE_VERYTHIN)
		m_nPenSize *=8;
}



void CMFCDay10Doc::OnUpdatePensizeCommand(CCmdUI* pCmdUI)
{
	UINT iID = pCmdUI->m_nID;
	UINT vTemp = iID - ID_PENSIZE_VERYTHIN + 1;
	if (iID != ID_PENSIZE_VERYTHIN)
		vTemp *= 8;
	pCmdUI->SetCheck(m_nPenSize == vTemp);
}

unsigned int CMFCDay10Doc::GetPenSize()
{
	// TODO: Add your implementation code here.
	return m_nPenSize;
}
