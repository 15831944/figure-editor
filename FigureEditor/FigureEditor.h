
// FigureEditor.h : main header file for the FigureEditor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CFigureEditorApp:
// See FigureEditor.cpp for the implementation of this class
//

class CFigureEditorApp : public CWinApp
{
public:
	CFigureEditorApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFigureEditorApp theApp;
