// CPaintDlg.cpp : implementation file
//

#include "pch.h"
#include "Graphics.h"
#include "afxdialogex.h"
#include "CPaintDlg.h"
#include "GraphicsDlg.h"
//#include "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.19041.0\\um\\wingdi.h"
// CPaintDlg dialog
//#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
const COLORREF CPaintDlg::m_crColor[8] =
{
	RGB(0, 0, 0 ),
	RGB( 0, 0, 255),
	RGB( 0, 255, 0),
	RGB( 0, 255, 255),
	RGB( 255, 0, 0),
	RGB( 255, 0, 255),
	RGB( 255, 255, 0),
	RGB( 255, 255, 255)
};
#define DEF_PEN(x) x,1,m_crColor[iColor] 
void CPaintDlg::DrawLine(CPaintDC* pdc, int iColor)
{

	CPen lSolidPen( DEF_PEN(PS_SOLID) );
	CPen lDotPen(   DEF_PEN(PS_DOT));
	CPen lDashPen(DEF_PEN(PS_DASH));
	CPen lDashDotPen(DEF_PEN(PS_DASHDOT));
	CPen lDashDotDotPen(DEF_PEN(PS_DASHDOTDOT));
	CPen lNullPen(DEF_PEN(PS_NULL));
	CPen lInsidePen(DEF_PEN(PS_INSIDEFRAME));

	CPen *vPenPtrArr[] = {&lSolidPen, &lDotPen, &lDashPen, &lDashDotPen, &lDashDotDotPen, &lNullPen, &lInsidePen};

	CRect lRect;
	GetClientRect(lRect);
	lRect.NormalizeRect();

	CPoint pStart;
	CPoint pEnd;
	int liDist = lRect.Height() / 8;
	CPen* lOldPen=nullptr;

	pStart.y = lRect.top;
	pStart.x = lRect.left;

	pEnd.y = pStart.y;
	pEnd.x = lRect.right;

	for (auto i = 0; i < 7; i++)
	{
		if (i == 0)
			lOldPen = pdc->SelectObject(vPenPtrArr[0]);// (vPenPtrArr[0]);
		else
		  pdc->SelectObject(vPenPtrArr[i]);
		pStart.y = pStart.y + liDist;
		pEnd.y = pStart.y;

		pdc->MoveTo(pStart);
		pdc->LineTo(pEnd);
	}
	if(lOldPen)
		pdc->SelectObject(lOldPen);
}


IMPLEMENT_DYNAMIC(CPaintDlg, CDialogEx)

CPaintDlg::CPaintDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAINT_DLG, pParent)
{

}

CPaintDlg::~CPaintDlg()
{
}

void CPaintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPaintDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPaintDlg message handlers


void CPaintDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
										 // TODO: Add your message handler code here
										 // Do not call CDialogEx::OnPaint() for painting messages
	CGraphicsDlg* pWnd = (CGraphicsDlg*)GetParent();
	if (pWnd)
	{
		if (pWnd->m_iTool == 2)
		{
			if (pWnd->m_sBitMap != "")
				ShowBitmap(&dc, pWnd);
		}
		else
		{
			if (pWnd->m_iShape == 0)
				DrawLine(&dc, pWnd->m_iColor);
			else
				DrawRegion(&dc, pWnd->m_iColor, pWnd->m_iTool, pWnd->m_iShape);
		}

	}
}

void CPaintDlg::DrawRegion(CPaintDC* pDC, int iColor, int iTool, int iShape)
{
	CPen lSolidPen(DEF_PEN(PS_SOLID));
	CPen lDotPen(DEF_PEN(PS_DOT));
	CPen lDashPen(DEF_PEN(PS_DASH));
	CPen lDashDotPen(DEF_PEN(PS_DASHDOT));
	CPen lDashDotDotPen(DEF_PEN(PS_DASHDOTDOT));
	CPen lNullPen(DEF_PEN(PS_NULL));
	CPen lInsidePen(DEF_PEN(PS_INSIDEFRAME));

	int vCol = m_crColor[iColor];
	CBrush lSolidBrush(vCol);
	CBrush lBDiagBrush(HS_BDIAGONAL, vCol);
	CBrush lCrossBrush(HS_CROSS, vCol);
	CBrush lDiagCrossBrush(HS_DIAGCROSS, vCol);
	CBrush lFDiagBrush(HS_FDIAGONAL, vCol);
	CBrush lHorizBrush(HS_HORIZONTAL, vCol);
	CBrush lVerBrush(HS_VERTICAL, vCol);
	CBrush lNullBrush(RGB(192, 192, 192));

	CRect lRect;
	GetClientRect(lRect);
	lRect.NormalizeRect();
	int liVert = lRect.Height() / 2;
	int liHeight = liVert - 10;
	int liHorz = lRect.Width() / 4;
	int liWidth = liHorz - 10;
	CRect lDrawRect;
	CPen* lOldPen = nullptr;
	CBrush* lOldBrush = nullptr;

	CPen* vPenPtrArr[] = { &lSolidPen, &lDotPen, &lDashPen, &lDashDotPen, &lDashDotDotPen, &lNullPen, &lInsidePen };
	CBrush* vBrushPtrArr[] = {&lSolidBrush, &lBDiagBrush, &lCrossBrush, &lDiagCrossBrush,
	                          &lFDiagBrush, &lHorizBrush, &lVerBrush, &lNullBrush};

	for (auto i = 0; i < 7; ++i)
	{
		if (i == 0)
		{
			lDrawRect.top = lRect.top + 5;
			lDrawRect.left = lRect.left + 5;
			lDrawRect.bottom = lDrawRect.top + liHeight;
			lDrawRect.right = lDrawRect.left + liWidth;
		}
		else if (i == 4)
		{
			lDrawRect.top = lDrawRect.top + liVert;
			lDrawRect.left = lRect.left + 5;
			lDrawRect.bottom = lDrawRect.top + liHeight;
			lDrawRect.right = lDrawRect.left + liWidth;
		}
		else
		{
			lDrawRect.left = lDrawRect.left + liHorz;
			lDrawRect.right = lDrawRect.right + liWidth;
		}
		if (i == 0)
		{
			lOldPen = pDC->SelectObject(vPenPtrArr[i]);
			lOldBrush = pDC->SelectObject(vBrushPtrArr[i]);
		}
		else
		{
			pDC->SelectObject(vPenPtrArr[i]);
			pDC->SelectObject(vBrushPtrArr[i]);
		}

		if (iTool == 0)
			pDC->SelectObject(lNullBrush);
		else
			pDC->SelectObject(lNullPen);

		if (iShape == 1)
			pDC->Ellipse(lDrawRect);
		else
			pDC->Rectangle(lDrawRect);


	}
	pDC->SelectObject(lOldPen);
	pDC->SelectObject(lOldBrush);
}

void CPaintDlg::ShowBitmap(CPaintDC* pDC, CWnd* pWnd)
{
	CGraphicsDlg* lpWnd = (CGraphicsDlg*)pWnd;
	BITMAP bm;
	lpWnd->m_bmpBitMap.GetBitmap(&bm);
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = (CBitmap*)dcMem.SelectObject(lpWnd->m_bmpBitMap);
	CRect lRect;
	GetClientRect(lRect);
	lRect.NormalizeRect();
	pDC->StretchBlt(10, 10, (lRect.Width() - 20), (lRect.Height() - 20), &dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
}