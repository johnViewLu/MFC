#pragma once

#include <stdlib.h>
#include <afxwin.h>
#include <afxtempl.h> // Include this header for COBArray



#ifdef MODARTDLL_EXPORTS
#define MODARTDLL_API __declspec(dllexport)
#else
#define MODARTDLL_API __declspec(dllimport)
#endif

class MODARTDLL_API CModArt :
    public CObject
{
public:
    CModArt();
    ~CModArt();
    void SetRect(CRect rDrawArea);

    void NewLine();
	void NewDrawing();
	void Draw(CDC* pDC);
    void ClearDrawing();
    void Serialize(CArchive& ar);
private:
    CRect m_rDrawArea;
    CObArray m_oaLines; // Corrected to CObArray
};
