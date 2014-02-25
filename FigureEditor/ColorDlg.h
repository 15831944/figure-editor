#pragma once
#include "afxcolorbutton.h"


// CColorDlg dialog

class CColorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CColorDlg();

// Dialog Data
	enum { IDD = IDD_COLOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CMFCColorButton color;
public:
	afx_msg void OnBnClickedOk();
	double red;
	double green;
	double blue;
	virtual BOOL OnInitDialog();
};
