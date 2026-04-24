#include "pch.h"
#include "CModArt.h"
#include "CLine.h"




	 
	 extern "C" void PASCAL EXPORT ModArtNewDrawing(CRect pRect, CObArray* poaLines)
	 {
		 AFX_MANAGE_STATE(AfxGetStaticModuleState());
		 // normal function body here
		 int lNumLines;
		 int lCurLine;

		 // Initialize the random number generator
		 srand((unsigned)time(NULL));
		 // Determine how many lines to create
		 lNumLines = rand() % 50;
		 // Are there any lines to create?
		 if (lNumLines > 0)
		 {
			 // Loop through the number of lines
			 for (lCurLine = 0; lCurLine < lNumLines; lCurLine++)
			 {
				 // Create the new line
				 NewLine(pRect, poaLines);
			 }
		 }
	 }


     void NewLine(CRect pRect, CObArray* poaLines)
     {
         int lNumLines;
         int lCurLine;
         //  int nCurColor;
         UINT nCurWidth;
         CPoint pTo;
         CPoint pFrom;
         int cRed;
         int cBlue;
         int cGreen;

         // Normalize the rectangle before determining the width and

         pRect.NormalizeRect();
         // get the area width and height
         int lWidth = pRect.Width();
         int lHeight = pRect.Height();

         // Determine the number of parts to this squiggle
         lNumLines = rand() % 200;
         // Are there any parts to this squiggle?
         if (lNumLines > 0)
         {
             // Determine the color
     //      nCurColor = rand() % 8;
             cRed = rand() % 256;
             cBlue = rand() % 256;
             cGreen = rand() % 256;
             // Determine the pen width
             nCurWidth = (rand() % 8) + 1;
             // Determine the starting point for the squiggle
             pFrom.x = (rand() % lWidth) + pRect.left;
             pFrom.y = (rand() % lHeight) + pRect.top;
             // Loop through the number of segments
             for (lCurLine = 0; lCurLine < lNumLines; lCurLine++)
             {
                 // Determine the end point of the segment
                 pTo.x = ((rand() % 20) - 10) + pFrom.x;
                 pTo.y = ((rand() % 20) - 10) + pFrom.y;
                 // Create a new CLine object
                 CLine* pLine = new CLine(pFrom, pTo, nCurWidth,
                     RGB(cRed, cGreen, cBlue));
                 try
                 {
                     // Add the new line to the object array
                     poaLines->Add(pLine);
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
                 // Set the starting point to the end point
                 pFrom = pTo;
             }
         }
     }


     extern "C" void PASCAL EXPORT ModArtDraw(CDC* pDC, CObArray* poaLines)  
     {  
         AFX_MANAGE_STATE(AfxGetStaticModuleState());  
         // Get the number of lines in the object array  
         int liCount = poaLines->GetSize();  
         int liPos;  

         // Are there any objects in the array?  
         if (liCount)  
         {  
             // Loop through the array, drawing each object  
             for (liPos = 0; liPos < liCount; liPos++)  
             {  
                 CLine* pLine = dynamic_cast<CLine*>(poaLines->GetAt(liPos));  
                 if (pLine != nullptr)  
                 {
					 int vPensize = rand() % 8 + 1; // Random pen size between 1 and 8
                     pLine->Draw(pDC, vPensize);  
                 }  
             }  
         }  
     }


     extern "C" void PASCAL EXPORT ModArtClearDrawing(CObArray* poaLines)
           {
               AFX_MANAGE_STATE(AfxGetStaticModuleState());
              // Normal function body here
              // Get the number of lines in the object array
              int liCount = poaLines->GetSize();
              int liPos;
              
         
              // Are there any objects in the array?
             if (liCount)
             {
                         // Loop through the array, deleting each object
                 for (liPos = 0; liPos < liCount; liPos++)
                 {
                     CLine* pLine = dynamic_cast<CLine*>(poaLines->GetAt(liPos));
                     if (pLine != nullptr)
                         delete pLine;
                 }
                          // Reset the array
                  poaLines->RemoveAll();
             }
          }
     extern "C" void PASCAL EXPORT ModArtSerialize(CArchive & ar,
         CObArray * poaLines)
     {
         AFX_MANAGE_STATE(AfxGetStaticModuleState());
         // normal function body here
        // Pass the archive object on to the array
         poaLines->Serialize(ar);
     }