
// MFCDay10Doc.h : interface of the CMFCDay10Doc class
//


#pragma once
class CLine;

class CMFCDay10Doc : public CDocument
{
protected: // create from serialization only
	CMFCDay10Doc() noexcept;
	DECLARE_DYNCREATE(CMFCDay10Doc)

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
	virtual ~CMFCDay10Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
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
	CObArray m_oaLines;
public:
	CLine* AddLine(CPoint ptFrom, CPoint ptTo);
	int GetLineCount();
	CLine* GetLine(int nIndex);
	virtual void DeleteContents();
	static const COLORREF m_crColors[8];
private:
	unsigned int m_nColor;
	unsigned int m_nPenSize;
public:
	unsigned int GetColor();
	afx_msg void OnColorBlack();
	afx_msg void OnUpdateColorBlack(CCmdUI* pCmdUI);
	afx_msg void OnColorBlue();
	afx_msg void OnUpdateColorBlue(CCmdUI* pCmdUI);
	afx_msg void OnColorCyan();
	afx_msg void OnUpdateColorCyan(CCmdUI* pCmdUI);
	afx_msg void OnColorGreen();
	afx_msg void OnUpdateColorGreen(CCmdUI* pCmdUI);
	afx_msg void OnColorMagenta();
	afx_msg void OnUpdateColorMagenta(CCmdUI* pCmdUI);
	afx_msg void OnColorRed();
	afx_msg void OnUpdateColorRed(CCmdUI* pCmdUI);
	afx_msg void OnColorWhite();
	afx_msg void OnUpdateColorWhite(CCmdUI* pCmdUI);
	afx_msg void OnColorYellow();
	afx_msg void OnUpdateColorYellow(CCmdUI* pCmdUI);
	afx_msg void OnPensizeCommand(UINT iID);
	afx_msg void OnUpdatePensizeCommand(CCmdUI* pCmdUI);
	unsigned int GetPenSize();
};
