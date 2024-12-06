
// Graphics.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CGraphicsApp:
// See Graphics.cpp for the implementation of this class
//

class CGraphicsApp : public CWinApp
{
public:
	CGraphicsApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CGraphicsApp theApp;
