
// MFCDay2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCDay2App:
// See MFCDay2.cpp for the implementation of this class
//

class CMFCDay2App : public CWinApp
{
public:
	CMFCDay2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCDay2App theApp;
