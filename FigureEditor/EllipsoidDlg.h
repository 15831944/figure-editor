#pragma once
#include "Ellipsoid.h"
#include "FigureEditorView.h"
#include "afxcolorbutton.h"

// CEllipsoidDlg dialog

class CEllipsoidDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEllipsoidDlg)

public:
	CEllipsoidDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEllipsoidDlg();

// Dialog Data
	enum { IDD = IDD_ELLIPSOID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	Ellipsoid* pOut;
private:
	double aEdit;
	double bEdit;
	double cEdit;
	CMFCColorButton colorButton;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
private:
	void createEllipsoid();

};
