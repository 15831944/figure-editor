#pragma once
#include "afxwin.h"
#include "FigureEditorView.h"


// CRotationDlg dialog

class CRotationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRotationDlg)
public:
	CRotationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRotationDlg();

// Dialog Data
	enum { IDD = IDD_ROTATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

	CButton m_Ox;
	CButton m_Oy;
	CButton m_Oz;
public:
	double m_Angle;
	bool Ox;
	bool Oy;
	bool Oz;

public:
	afx_msg void OnBnClickedOk();
};
