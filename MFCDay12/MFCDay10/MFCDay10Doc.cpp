
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
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "DebugLog.h"
// CMFCDay10Doc

IMPLEMENT_DYNCREATE(CToolbarDoc, CDocument)

BEGIN_MESSAGE_MAP(CToolbarDoc, CDocument)
	ON_COMMAND(ID_COLOR_BLACK, &CToolbarDoc::OnColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CToolbarDoc::OnUpdateColorBlack)
	ON_COMMAND(ID_COLOR_BLUE, &CToolbarDoc::OnColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CToolbarDoc::OnUpdateColorBlue)
	ON_COMMAND(ID_COLOR_CYAN, &CToolbarDoc::OnColorCyan)
	ON_UPDATE_COMMAND_UI(ID_COLOR_CYAN, &CToolbarDoc::OnUpdateColorCyan)
	ON_COMMAND(ID_COLOR_GREEN, &CToolbarDoc::OnColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CToolbarDoc::OnUpdateColorGreen)
	ON_COMMAND(ID_COLOR_MAGENTA, &CToolbarDoc::OnColorMagenta)
	ON_UPDATE_COMMAND_UI(ID_COLOR_MAGENTA, &CToolbarDoc::OnUpdateColorMagenta)
	ON_COMMAND(ID_COLOR_RED, &CToolbarDoc::OnColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CToolbarDoc::OnUpdateColorRed)
	ON_COMMAND(ID_COLOR_WHITE, &CToolbarDoc::OnColorWhite)
	ON_UPDATE_COMMAND_UI(ID_COLOR_WHITE, &CToolbarDoc::OnUpdateColorWhite)
	ON_COMMAND(ID_COLOR_YELLOW, &CToolbarDoc::OnColorYellow)
	ON_UPDATE_COMMAND_UI(ID_COLOR_YELLOW, &CToolbarDoc::OnUpdateColorYellow)
	ON_COMMAND_RANGE(ID_PENSIZE_VERYTHIN, ID_PENSIZE_VERYTHICK, &CToolbarDoc::OnPensizeCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_PENSIZE_VERYTHIN, ID_PENSIZE_VERYTHICK, &CToolbarDoc::OnUpdatePensizeCommand)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_COLOR, &CToolbarDoc::OnUpdateIndicatorColor)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_PENSIZE, &CToolbarDoc::OnUpdateIndicatorPenSize)
END_MESSAGE_MAP()

const COLORREF CToolbarDoc::m_crColors[8] = {
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

CToolbarDoc::CToolbarDoc() noexcept
{
	// TODO: add one-time construction code here
	m_nPenSize = 1;
	UpdateColorBar(0);
}

CToolbarDoc::~CToolbarDoc()
{
}

BOOL CToolbarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_nColor = ID_COLOR_BLACK - ID_COLOR_BLACK;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCDay10Doc serialization

void CToolbarDoc::Serialize(CArchive& ar)
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
void CToolbarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CToolbarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCDay10Doc commands


CLine* CToolbarDoc::AddLine(CPoint ptFrom, CPoint ptTo)
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


int CToolbarDoc::GetLineCount()
{
	// TODO: Add your implementation code here.
	//std::ofstream vFile;
	//vFile.open("debugRecord.txt", std::ofstream::app);	
	auto vCount = m_oaLines.GetSize();
	//vFile << "GetLineSize= " <<vCount << "\n";
	L_(linfo) << __FUNCTION__ << "vCount=" << vCount;
	return vCount;
}


CLine* CToolbarDoc::GetLine(int nIndex)
{
	// TODO: Add your implementation code here.
	return (CLine*)m_oaLines[nIndex];
	//return nullptr;
}


void CToolbarDoc::DeleteContents()
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


unsigned int CToolbarDoc::GetColor()
{
	// TODO: Add your implementation code here.
	return ID_COLOR_BLACK + m_nColor;
}


void CToolbarDoc::OnColorBlack()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_BLACK - ID_COLOR_BLACK;
}


void CToolbarDoc::OnUpdateColorBlack(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_BLACK ? 1 : 0);
}


void CToolbarDoc::OnColorBlue()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_BLUE - ID_COLOR_BLACK;
}


void CToolbarDoc::OnUpdateColorBlue(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_BLUE ? 1 : 0);
}


void CToolbarDoc::OnColorCyan()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_CYAN - ID_COLOR_BLACK;
}


void CToolbarDoc::OnUpdateColorCyan(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_CYAN ? 1 : 0);
}


void CToolbarDoc::OnColorGreen()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_GREEN - ID_COLOR_BLACK;
}


void CToolbarDoc::OnUpdateColorGreen(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_GREEN ? 1 : 0);
}


void CToolbarDoc::OnColorMagenta()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_MAGENTA - ID_COLOR_BLACK;
}


void CToolbarDoc::OnUpdateColorMagenta(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_MAGENTA ? 1 : 0);
}


void CToolbarDoc::OnColorRed()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_RED - ID_COLOR_BLACK;
}


void CToolbarDoc::OnUpdateColorRed(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_RED ? 1 : 0);
}


void CToolbarDoc::OnColorWhite()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_WHITE - ID_COLOR_BLACK;
}


void CToolbarDoc::OnUpdateColorWhite(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_WHITE ? 1 : 0);
}


void CToolbarDoc::OnColorYellow()
{
	// TODO: Add your command handler code here
	m_nColor = ID_COLOR_YELLOW - ID_COLOR_BLACK;
}


void CToolbarDoc::OnUpdateColorYellow(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetColor() == ID_COLOR_YELLOW ? 1 : 0);
}


void CToolbarDoc::OnPensizeCommand(UINT iID)
{
	// TODO: Add your command handler code here
	UpdateColorBar(iID - ID_PENSIZE_VERYTHIN);

	auto vTemp = iID - ID_PENSIZE_VERYTHIN;

	if(iID!=ID_PENSIZE_VERYTHIN)
		m_nPenSize =8*vTemp;
	else
		m_nPenSize = 1;
		
}



void CToolbarDoc::OnUpdatePensizeCommand(CCmdUI* pCmdUI)
{
	UINT iID = pCmdUI->m_nID;
	UINT vTemp = iID - ID_PENSIZE_VERYTHIN;
	if (iID != ID_PENSIZE_VERYTHIN)
		vTemp *= 8;
	pCmdUI->SetCheck(m_nPenSize == vTemp);
}

void CToolbarDoc::OnUpdateIndicatorColor(CCmdUI* pCmdUI)
{
	static CString sColors[] = { L"BlackX", L"Blue",  L"Green",  L"Cyan", L"Red", L"Magenta", L"Yellow" , L"White"};
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(sColors[m_nColor]);

}


void CToolbarDoc::OnUpdateIndicatorPenSize(CCmdUI* pCmdUI)
{
	static CString sSize[] = { L"Very Thin", L"Thin",  L"Medium",  L"Thick", L"Very Thick"};
	pCmdUI->Enable(TRUE);
	auto vIndex = m_nPenSize;
	L_(linfo) << __FUNCTION__;
	L_(linfo) << "m_nPenSize=" << m_nPenSize;
	if (vIndex != 1)
		vIndex /= 8;
	else
		vIndex = 0;
	pCmdUI->SetText(sSize[vIndex]);

}

unsigned int CToolbarDoc::GetPenSize()
{
	// TODO: Add your implementation code here.
	return m_nPenSize;
}


void CToolbarDoc::UpdateColorBar(int ix)
{
	// TODO: Add your implementation code here.
	auto pos = GetFirstViewPosition();
	if(!pos)
		return;
	auto pView = GetNextView(pos);
	if (!pView)
		return;
	auto pFrame = (CMainFrame*)pView->GetTopLevelFrame();
	if (!pFrame)
		return;
	pFrame->UpdateWidthCB(ix);
}

void CToolbarDoc::SetPenSize(int nIndex)
{
	if (nIndex == 0)
		m_nPenSize = 1;
	else
		m_nPenSize = 8 * (nIndex);
}
