// CuboidDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FigureEditor.h"
#include "CuboidDlg.h"
#include "afxdialogex.h"


// CCuboidDlg dialog

IMPLEMENT_DYNAMIC(CCuboidDlg, CDialogEx)

CCuboidDlg::CCuboidDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCuboidDlg::IDD, pParent)
	, lengthEdit(0)
	, heightEdit(0)
	, widthEdit(0)
	, pOut(NULL)
{
}

CCuboidDlg::~CCuboidDlg()
{
}

void CCuboidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LENGTH, lengthEdit);
	DDX_Text(pDX, IDC_HEIGHT, heightEdit);
	DDX_Text(pDX, IDC_WIDTH, widthEdit);
	DDX_Control(pDX, IDC_COLORBUTTON, colorButton);
}


BEGIN_MESSAGE_MAP(CCuboidDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCuboidDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CCuboidDlg::createCuboid()
{
	pOut = new Cuboid;
	pOut->length = lengthEdit;
	pOut->height = heightEdit;
	pOut->width = widthEdit;
	for (int i = 0; i < 6; i++)
	{
		pOut->faceColor[i][0] = GetRValue(colorButton.GetColor());
		pOut->faceColor[i][1] = GetGValue(colorButton.GetColor());
		pOut->faceColor[i][2] = GetBValue(colorButton.GetColor());
	}
}
// CCuboidDlg message handlers

void CCuboidDlg::OnBnClickedOk()
{
	UpdateData();
	createCuboid();
	CDialogEx::OnOK();
}

BOOL CCuboidDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	colorButton.EnableOtherButton(_T("More"),0,0);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
