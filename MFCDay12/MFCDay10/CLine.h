#pragma once
class CLine:public CObject
{
	DECLARE_SERIAL(CLine)
public:
	CLine(){}
	CLine(CPoint ptFrom, CPoint ptTo, COLORREF iCol):m_ptFrom(ptFrom),m_ptTo(ptTo), m_crColor(iCol){}
private:
	CPoint m_ptFrom;
	CPoint m_ptTo;
public:
	void Draw(CDC* pDC, UINT iPensize);
	void Serialize(CArchive& ar);
private:
	COLORREF m_crColor;
};




