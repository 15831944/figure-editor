// ColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FigureEditor.h"
#include "ColorDlg.h"
#include "afxdialogex.h"


// CColorDlg dialog

IMPLEMENT_DYNAMIC(CColorDlg, CDialogEx)

CColorDlg::CColorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CColorDlg::IDD, pParent)
	, red(0)
	, green(0)
	, blue(0)
{

}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, color);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CColorDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CColorDlg message handlers


void CColorDlg::OnBnClickedOk()
{
	UpdateData();
	red = GetRValue(color.GetColor());
	green = GetGValue(color.GetColor());
	blue = GetBValue(color.GetColor());
	CDialogEx::OnOK();
}


BOOL CColorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	color.EnableOtherButton(_T("More"), 0, 0);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
