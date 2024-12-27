#include "pch.h"
#include "CLine.h"



IMPLEMENT_SERIAL(CLine, CObject, 1)


void CLine::Draw(CDC* pDC, UINT iPenSize)
{
	// TODO: Add your implementation code here.
	CPen lpen(PS_SOLID, iPenSize, m_crColor);
	CPen* pOldPen = pDC->SelectObject(&lpen);
	pDC->MoveTo(m_ptFrom);
	pDC->LineTo(m_ptTo);
	pDC->SelectObject(pOldPen);
}

void CLine::Serialize(CArchive& ar)
{
	// TODO: Add your implementation code here.
	CObject::Serialize(ar);
	if (ar.IsStoring())
		ar << m_ptFrom << m_ptTo << (DWORD)m_crColor;
	else
		ar >> m_ptFrom >> m_ptTo >> (DWORD)m_crColor;
}
