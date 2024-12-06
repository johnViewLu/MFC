
// Fonts.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFontsApp:
// See Fonts.cpp for the implementation of this class
//

class CFontsApp : public CWinApp
{
public:
	CFontsApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFontsApp theApp;
