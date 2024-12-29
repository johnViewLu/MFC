
// MFCDay11Doc.h : interface of the CMFCDay11Doc class
//


#pragma once

class CLine;
class CMFCDay11Doc : public CDocument
{
protected: // create from serialization only
	CMFCDay11Doc() noexcept;
	DECLARE_DYNCREATE(CMFCDay11Doc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMFCDay11Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	static const COLORREF m_crColors[8];
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
private:
	unsigned int m_nColor;
	unsigned int m_nPenSize;
	CObArray m_oaLines;
public:
	afx_msg void OnPensizeCommand(UINT iID);
	afx_msg void OnColorCommand(UINT iID);
	afx_msg void OnUpdateColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePensize(CCmdUI* pCmdUI);
	inline unsigned int GetColor() { return m_nColor; }
	inline auto GetPenSize() { return m_nPenSize; }
	CLine* AddLine(CPoint ptFrom, CPoint ptTo);
	inline auto GetLineCount() { return m_oaLines.GetSize(); }
	CLine* GetLine(int nIndex);
	virtual void DeleteContents();
};
