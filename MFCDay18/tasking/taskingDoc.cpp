
// taskingDoc.cpp : implementation of the CtaskingDoc class
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
#include "CSpinner.h"




#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CtaskingDoc

IMPLEMENT_DYNCREATE(CtaskingDoc, CDocument)

BEGIN_MESSAGE_MAP(CtaskingDoc, CDocument)
END_MESSAGE_MAP()


// CtaskingDoc construction/destruction

CtaskingDoc::CtaskingDoc() noexcept
{
	// TODO: add one-time construction code here
	m_pSpinThread[0] = nullptr;
	m_pSpinThread[1] = nullptr;

}

CtaskingDoc::~CtaskingDoc()
{
}



void CtaskingDoc::CalcPoint(int nID, CSpinner* pSpin)
{
	RECT lWndRect;
	CPoint pPos;
	int iLength;
	CtaskingView* pWnd;

	// Get a pointer to the view window
	pWnd = (CtaskingView*)pSpin->GetViewWnd();
	// Get the display area rectangle
	pWnd->GetClientRect(&lWndRect);
	// Calculate the size of the spinners
	iLength = lWndRect.right / 12/2;
	// Which spinner are we placing?
	switch (nID)
	{
	case 0:    // Position the first spinner
		pPos.x = (lWndRect.right / 6) - iLength;
		pPos.y = (lWndRect.bottom / 6*3) - iLength;
		break;
	case 1:    // Position the second spinner
		pPos.x = ((lWndRect.right / 6) * 3) - iLength;
		pPos.y = (lWndRect.bottom / 6*3) - iLength;
		break;
	case 2:    // Position the third spinner
		pPos.x = (lWndRect.right / 6) - iLength;
		pPos.y = ((lWndRect.bottom / 6) * 6) - (iLength * 1.25);
		break;
	case 3:    // Position the fourth spinner
		pPos.x = ((lWndRect.right / 6) * 3) - iLength;
		pPos.y = ((lWndRect.bottom / 6) * 6) - (iLength * 1.25);
		break;
	}
	// Set the size of the spinner
	pSpin->SetLength(iLength);
	// Set the location of the spinner
	pSpin->SetPoint(pPos);
}


BOOL CtaskingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	InitSpinners();

	return TRUE;
}




// CtaskingDoc serialization

void CtaskingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CtaskingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CtaskingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CtaskingDoc::SetSearchContent(const CString& value)
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

// CtaskingDoc diagnostics

#ifdef _DEBUG
void CtaskingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CtaskingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


 void CtaskingDoc::InitSpinners()
 {
	 int i=0;
	
	    // Get the position of the view
	 POSITION pos = GetFirstViewPosition();
	     // Did we get a valid position?
	 if (pos != NULL)
	 {
		         // Get a pointer to the view
		CView * pView = GetNextView(pos);
		CtaskingView* pView2 = static_cast<CtaskingView*>(pView);
		         // Loop through the spinners
		 for (i = 0; i < 4; i++)
		 {
			             // Set the pointer to the view
			 m_cSpin[i].SetViewWnd(pView);
			             // Initialize the pointer to the continuation indicator
			 m_cSpin[i].SetContinue(NULL);
			 switch (i)
		     {
				case 1:    // Set the pointer to the first thread 
						// continuation indicator
					m_cSpin[i].SetContinue(&(pView2->m_bThread1));
						break;
			    case 3:    // Set the pointer to the second thread 
					// continuation indicator
				    m_cSpin[i].SetContinue(&(pView2->m_bThread2));
					break;
				default:
					break;
		    }
			             // Calculate the location of the spinner
			CalcPoint(i, &m_cSpin[i]);
		 }
	 }
 }




  UINT CtaskingDoc::ThreadFunc(LPVOID pParam)
     {
	    // Convert the argument to a pointer to the
	    // spinner for this thread
		  CSpinner * lpSpin = (CSpinner*)pParam;
	     // Get a pointer to the continuation flag
	      BOOL * pbContinue = lpSpin->GetContinue();
	 
	      // Loop while the continue flag is true
		  while (*pbContinue)
			  lpSpin->Draw();
	      return 0;
	  }


  void CtaskingDoc::SuspendSpinner(int nIndex, BOOL bSuspend)
  {
	  // if suspending the thread

	  if (!bSuspend)
	  {
		  // Is the pointer for the thread valid?
		  if (m_pSpinThread[nIndex])
		  {
			  // Get the handle for the thread
			  HANDLE hThread = m_pSpinThread[nIndex]->m_hThread;
			  // Wait for the thread to die
			  ::WaitForSingleObject(hThread, INFINITE);
			  m_pSpinThread[nIndex] = nullptr;	
		  }
	  }
	  else    // We are running the thread
	  {
		  if (m_pSpinThread[nIndex] != nullptr) return;
		  int iSpnr = (nIndex == 0) ? 1 : 3;
		  m_pSpinThread[nIndex] = AfxBeginThread(ThreadFunc, (LPVOID) & (CtaskingDoc::m_cSpin[iSpnr]));
	  }
  }
  