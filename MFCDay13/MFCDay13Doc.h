
// MFCDay13Doc.h : interface of the CMFCDay13Doc class
//


#pragma once
#include <vector>
#include <memory>
class CPerson;

class CMFCDay13Doc : public CDocument
{
protected: // create from serialization only
	CMFCDay13Doc() noexcept;
	DECLARE_DYNCREATE(CMFCDay13Doc)

// Operations
public:
	CPerson* AddNewRecord();
	int GetTotalRecords();
	int GetCurRecordNbr();
	CPerson* GetCurRecord();
	CPerson* GetFirstRecord();
	CPerson* GetLastRecord();
	CPerson* GetNextRecord();
	CPerson* GetPrevRecord();
	void DeleteContents();
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
	virtual ~CMFCDay13Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

private:
	int m_iCurPosition;
	//CObArray m_oaPeople;

	//std::vector<std::unique_ptr<CPerson>> m_oaPeople;
	std::vector<std::unique_ptr<CPerson>> m_oaPeople;

};
