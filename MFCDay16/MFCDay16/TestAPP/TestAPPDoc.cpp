
// TestAPPDoc.cpp : implementation of the CTestAPPDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TestAPP.h"
#endif

#include "TestAPPDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTestAPPDoc

IMPLEMENT_DYNCREATE(CTestAPPDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestAPPDoc, CDocument)
END_MESSAGE_MAP()


// CTestAPPDoc construction/destruction

CTestAPPDoc::CTestAPPDoc() noexcept
{
	// TODO: add one-time construction code here

}

CTestAPPDoc::~CTestAPPDoc()
{
}

BOOL CTestAPPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	POSITION pos = GetFirstViewPosition();
	// Did we get a valid position?
	if (pos != NULL)
	{
		// Get a pointer to the view
		CView* pView = GetNextView(pos);
		RECT lWndRect;
		// Get the display area rectangle
		pView->GetClientRect(&lWndRect);
		// Set the drawing area
		m_maDrawing.SetRect(lWndRect);
		// Create a new drawing
		m_maDrawing.NewDrawing();
	}
	return TRUE;
}

// CTestAPPDoc serialization

void CTestAPPDoc::Serialize(CArchive& ar)
{
	m_maDrawing.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CTestAPPDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CTestAPPDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CTestAPPDoc::SetSearchContent(const CString& value)
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

// CTestAPPDoc diagnostics

#ifdef _DEBUG
void CTestAPPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestAPPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG



 // Fix for E0276 and C2653 errors: Ensure the class name matches the declaration in the header file.  
 // The class name in the .cpp file should be consistent with the class name in the .h file.  

 void CTestAPPDoc::DeleteContents()  
 {  
     // TODO: Add your specialized code here and/or call the base class  
     // Delete the drawing  
     m_maDrawing.ClearDrawing();  

     CDocument::DeleteContents();  
 }

 