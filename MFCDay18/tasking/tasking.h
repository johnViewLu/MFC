
// tasking.h : main header file for the tasking application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CtaskingApp:
// See tasking.cpp for the implementation of this class
//

class CtaskingApp : public CWinAppEx
{
public:
	CtaskingApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	BOOL OnIdle(LONG lCount);


// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CtaskingApp theApp;
