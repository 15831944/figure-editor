// EllipsoidDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FigureEditor.h"
#include "EllipsoidDlg.h"
#include "afxdialogex.h"


// CEllipsoidDlg dialog

IMPLEMENT_DYNAMIC(CEllipsoidDlg, CDialogEx)

CEllipsoidDlg::CEllipsoidDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEllipsoidDlg::IDD, pParent)
	, aEdit(0)
	, bEdit(0)
	, cEdit(0)
	, pOut(NULL)
{

}

CEllipsoidDlg::~CEllipsoidDlg()
{
}

void CEllipsoidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_A, aEdit);
	DDX_Text(pDX, IDC_B, bEdit);
	DDX_Text(pDX, IDC_C, cEdit);
	DDX_Control(pDX, IDC_COLORBUTTON, colorButton);
}


BEGIN_MESSAGE_MAP(CEllipsoidDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CEllipsoidDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEllipsoidDlg message handlers


void CEllipsoidDlg::OnBnClickedOk()
{
	UpdateData();
	createEllipsoid();
	CDialogEx::OnOK();
}

void CEllipsoidDlg::createEllipsoid()
{
	pOut = new Ellipsoid;
	pOut->a = aEdit;
	pOut->b = bEdit;
	pOut->c = cEdit;
	pOut->color[0] = GetRValue(colorButton.GetColor());
	pOut->color[1] = GetGValue(colorButton.GetColor());
	pOut->color[2] = GetBValue(colorButton.GetColor());
}

BOOL CEllipsoidDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	colorButton.EnableOtherButton(_T("More"), 0, 0);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
