#pragma once
#include "FigureEditorView.h"

// CProjectionsDlg dialog

class CProjectionsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectionsDlg)

public:
	CProjectionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProjectionsDlg();

// Dialog Data
	enum { IDD = IDD_PROJECTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	BOOL xoy;
	BOOL yoz;
	BOOL xoz;
public:
	afx_msg void OnBnClickedOk();
};
