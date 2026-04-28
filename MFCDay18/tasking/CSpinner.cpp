#include "pch.h"
#include "CSpinner.h"


COLORREF CSpinner::m_crColors[8] = {
	RGB(0,   0,   0),    // Black
	RGB(0,   0, 255),    // Blue
	RGB(0, 255,   0),    // Green
	RGB(0, 255, 255),    // Cyan
	RGB(255,   0,   0),    // Red
	RGB(255,   0, 255),    // Magenta
	RGB(255, 255,   0),    // Yellow
	RGB(255, 255, 255)        // White
};



CSpinner::CSpinner()
{
	// Initialize the position, size, and color
	m_iRadius = 0;
	m_nMinute = 0;
	m_crColor = 0;
	// Nullify the pointers
	m_pViewWnd = NULL;
	m_bContinue = NULL;
}


void CSpinner::Draw()
{
	// Get a pointer to the device context
	CDC* pDC = m_pViewWnd->GetDC();
	// Set the mapping mode
	pDC->SetMapMode(MM_LOENGLISH);
	// Copy the spinner center
	CPoint org = m_pCenter;
	CPoint pStartPoint;
	// Set the starting point
	pStartPoint.x = (m_iRadius / 2);
	pStartPoint.y = (m_iRadius / 2);
	// Set the origination point
	org.x = m_pCenter.x + (m_iRadius / 2);
	org.y = m_pCenter.y + m_iRadius;
	    // Set the viewport origination point
	pDC->SetViewportOrg(org.x, org.y);
	
	 CPoint pEndPoint;
	     // Calculate the angle of the next line
	double nRadians = (double)(m_nMinute * 6) * 0.017453292;
	    // Set the end point of the line
	 pEndPoint.x = (int)(m_iRadius * sin(nRadians));
	     pEndPoint.y = (int)(m_iRadius * cos(nRadians));
	
			     // Create the pen to use
     CPen pen(PS_SOLID, 0, m_crColors[m_crColor]);
	     // Select the pen for use
	 CPen * pOldPen = pDC->SelectObject(&pen);
	
	     // Move to the starting point
     pDC->MoveTo(pEndPoint);
	    // Draw the line to the end point
	 pDC->LineTo(pStartPoint);
	
	     // Reselect the previous pen
	pDC->SelectObject(&pOldPen);
	
	     // Release the device context
	 m_pViewWnd->ReleaseDC(pDC);
	
	    // Increment the minute
	 if (++m_nMinute == 60)
	 {
	         // If the minutes have gone full circle, reset to 0
		 m_nMinute = 0;
				 // Increment the color
		 if (++m_crColor == 8)
					 // If we’ve gone through all colors, start again
		 m_crColor = 0;
	 }
}