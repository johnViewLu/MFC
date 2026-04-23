#include "../ModArtDll/ModArtDll/CModArt.h" // Ensure this include is correct and provides the definition for CModArt

class CTestAPPDoc : public CDocument
{
protected: // create from serialization only
    CTestAPPDoc() noexcept;
    DECLARE_DYNCREATE(CTestAPPDoc)

// Operations
public:

            // m_maDrawing
    CModArt m_maDrawing; // Ensure this member variable is declared

// Overrides

    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    CModArt* GetDrawing() { return &m_maDrawing; } // Corrected the typo from m_maDrawin to m_maDrawing
	void OnDraw(CDC* pDC); // Added declaration for OnDraw function
    void DeleteContents();
#ifdef SHARED_HANDLERS
    virtual void InitializeSearchContent();
    virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

    virtual ~CTestAPPDoc();
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
};
//    #include "TestAPPDoc.h" // Ensure this include is present to reference the header file