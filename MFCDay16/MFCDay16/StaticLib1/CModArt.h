#pragma once

#include <stdlib.h>
#include <afxwin.h>
#include <afxtempl.h> // Include this header for COBArray

class CModArt :
    public CObject
{
public:
    static const COLORREF m_crColors[8];

    CModArt() 
    {
        srand((unsigned)time(NULL));
    }

    void SetRect(CRect rDrawArea)
    {
        m_rDrawArea = rDrawArea;
    }   
    void NewLine();
	void NewDrawing();
	void Draw(CDC* pDC);
    void ClearDrawing();
    void Serialize(CArchive& ar);
private:
    CRect m_rDrawArea;
    CObArray m_oaLines; // Corrected to CObArray
};
