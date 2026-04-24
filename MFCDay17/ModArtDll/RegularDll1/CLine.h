
#pragma once
#include <stdlib.h>
#include <afxwin.h>




class  CLine:public CObject
{
	DECLARE_SERIAL(CLine)
public:
	CLine(){}
	CLine(CPoint ptFrom, CPoint ptTo, COLORREF iCol):m_ptFrom(ptFrom),m_ptTo(ptTo), m_iWidth(0), m_crColor(iCol){}
	CLine(CPoint ptFrom, CPoint ptTo, int iWidth, COLORREF iCol) :m_ptFrom(ptFrom), m_ptTo(ptTo), m_iWidth(iWidth), m_crColor(iCol) {}
	void Draw(CDC* pDC, UINT iPensize);
	void Serialize(CArchive& ar);
private:
	CPoint m_ptFrom;
	CPoint m_ptTo;
	COLORREF m_crColor;
	int m_iWidth;
};




