#pragma once
#include "Cuboid.h"
#include "FigureEditorView.h"
#include "afxcolorbutton.h"


// CCuboidDlg dialog

class CCuboidDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCuboidDlg)

public:
	CCuboidDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCuboidDlg();

// Dialog Data
	enum { IDD = IDD_CUBOID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
private:
//	CFigureEditorView* m_pView;
	double lengthEdit;
	double heightEdit;
	double widthEdit;
	CMFCColorButton colorButton;
public:
	Cuboid* pOut;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
private:
	void createCuboid();
};
