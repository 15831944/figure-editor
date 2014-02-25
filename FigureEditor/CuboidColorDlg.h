#pragma once
#include "afxcolorbutton.h"
#include "Cuboid.h"


// CCuboidColorDlg dialog

class CCuboidColorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCuboidColorDlg)

public:
	CCuboidColorDlg(Cuboid* pCuboid, CWnd* pParent = NULL);   // standard constructor
	virtual ~CCuboidColorDlg();

// Dialog Data
	enum { IDD = IDD_CUBOID_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CMFCColorButton face0;
	CMFCColorButton face1;
	CMFCColorButton face2;
	CMFCColorButton face3;
	CMFCColorButton face4;
	CMFCColorButton face5;
	Cuboid* pIn;
public:
	Cuboid* pOut;
	virtual BOOL OnInitDialog();
protected:
	void createCuboid();
public:
	afx_msg void OnBnClickedOk();
};
