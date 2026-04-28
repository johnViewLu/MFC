#pragma once
#include <afx.h>
class CSpinner :
    public CObject
{
public:
     BOOL * GetContinue() { return m_bContinue; }
     void SetContinue(BOOL *bContinue) { m_bContinue = bContinue; }
     CWnd * GetViewWnd() { return m_pViewWnd; }
     void SetViewWnd(CWnd * pWnd) { m_pViewWnd = pWnd; }
	 int GetLength() { return m_iRadius; }
     void SetLength(int iLength) { m_iRadius = iLength; }
     void SetPoint(CPoint pPoint){ m_pCenter = pPoint; }
     void Draw();
     CSpinner();
     virtual ~CSpinner() { ; }


private:

    int  m_iRadius;
    CPoint     m_pCenter;
    static COLORREF     m_crColors[8];
	int m_crColor;
    CWnd* m_pViewWnd;
    BOOL* m_bContinue;
    int m_nMinute;
};

