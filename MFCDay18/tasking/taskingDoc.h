
// taskingDoc.h : interface of the CtaskingDoc class
//


#pragma once
#include "CSpinner.h"

class CtaskingDoc : public CDocument
{
protected: // create from serialization only
	CtaskingDoc() noexcept;
	DECLARE_DYNCREATE(CtaskingDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	void CalcPoint(int nID, CSpinner* pSpin);
	void InitSpinners();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CtaskingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	void DoSpin(int nIndex) { m_cSpin[nIndex].Draw(); }
#endif

   static  UINT ThreadFunc(LPVOID pParam);
 void SuspendSpinner(int nIndex, BOOL bSuspend);
protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
private:
	CSpinner m_cSpin[4];
	CWinThread* m_pSpinThread[4];

};
