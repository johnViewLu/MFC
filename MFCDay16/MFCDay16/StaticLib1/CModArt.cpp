#include "pch.h"
#include "CModArt.h"
#include "../StaticLib2/CLine.h"



const COLORREF CModArt::m_crColors[8] = {
   RGB(0,   0,   0),    // Black
   RGB(0,   0, 255),    // Blue
   RGB(0, 255,   0),    // Green
   RGB(0, 255, 255),    // Cyan
   RGB(255,   0,   0),    // Red
   RGB(255,   0, 255),    // Magenta
   RGB(255, 255,   0),    // Yellow
   RGB(255, 255, 255)     // White
};





void CModArt::NewLine()
{
	int lNumLines;
	int lCurLine = 0;
	int nCurColor;
	UINT nCurWidth;


	CPoint pTo;
	CPoint pFrom;
	
	     // Normalize the rectangle before determining the width and height
     m_rDrawArea.NormalizeRect();
	     // get the area width and height
	 int lWidth = m_rDrawArea.Width();
	 int lHeight = m_rDrawArea.Height();
	
	  // Determine the number of parts to this squiggle
	lNumLines = rand() % 100;
	     // Are there any parts to this squiggle?
	 if (lNumLines > 0)
	 {
		         // Determine the color
		 nCurColor = rand() % 8;
		         // Determine the pen width
		 nCurWidth = (rand() % 8) + 1;
		         // Determine the starting point for the squiggle
		 pFrom.x = (rand() % lWidth) + m_rDrawArea.left;
         pFrom.y = (rand() % lHeight) + m_rDrawArea.top;
		         // Loop through the number of segments
		 for (lCurLine = 0; lCurLine < lNumLines; lCurLine++)
		 {
			            // Determine the end point of the segment
			pTo.x = ((rand() % 20) - 10) + pFrom.x;
			pTo.y = ((rand() % 20) - 10) + pFrom.y;
			           // Create a new CLine object
		    CLine * pLine = new CLine(pFrom, pTo, m_crColors[nCurColor]);
			try
			{
								// Add the new line to the object array
				m_oaLines.Add(pLine);
			}
						// Did we run into a memory exception?
			catch (CMemoryException* perr)
			{
							// Display a message for the user, giving him the
							// bad news
				AfxMessageBox(_T("Out of memory"), MB_ICONSTOP | MB_OK);
						// Did we create a line object?
				if (pLine)
				{
										// Delete it
					delete pLine;
					pLine = NULL;
					}
									// Delete the exception object
					perr->Delete();
				}
			            // Set the starting point to the end poin
				pFrom = pTo;
		    }
	  }
	
}


void CModArt::NewDrawing()
{
	int lNumLines;
	int lCurLine = 0;

	lNumLines = rand() % 10;
	if (lNumLines > 0)
	{
		for (lCurLine = 0; lCurLine < lNumLines; lCurLine++)
		{
			NewLine();
		}
	}
}

void CModArt::Draw(CDC* pDC)  
{  
    int lNumLines = m_oaLines.GetSize();  
    int lCurLine = 0;  
    CLine* pLine = NULL;  

    for (lCurLine = 0; lCurLine < lNumLines; lCurLine++)  
    {  
        pLine = (CLine*)m_oaLines.GetAt(lCurLine);  
        if (pLine)  
        {  
            // Assuming the missing argument is the pen size, you can pass a default or calculated value.  
			UINT penSize = rand() % 5;
            //UINT penSize = 1; // Replace with appropriate logic if needed.  	       
            pLine->Draw(pDC, penSize);  
        }  
    }  
}


  void CModArt::ClearDrawing()
 {
      // Get the number of lines in the object array
	 int liCount = m_oaLines.GetSize();
	 int liPos;
	
	// Are there any objects in the array?
	if (liCount)
	{
			// Loop through the array, deleting each object
		for (liPos = 0; liPos < liCount; liPos++)
			delete m_oaLines[liPos];
				// Reset the array
		m_oaLines.RemoveAll();
	}
}



void CModArt::Serialize(CArchive & ar)
{
	// Pass the archive object on to the array
	m_oaLines.Serialize(ar);
}