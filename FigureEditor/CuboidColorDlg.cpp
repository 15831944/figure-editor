// CuboidColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FigureEditor.h"
#include "CuboidColorDlg.h"
#include "afxdialogex.h"


// CCuboidColorDlg dialog

IMPLEMENT_DYNAMIC(CCuboidColorDlg, CDialogEx)

CCuboidColorDlg::CCuboidColorDlg(Cuboid* pCuboid, CWnd* pParent /*=NULL*/)
	: CDialogEx(CCuboidColorDlg::IDD, pParent)
	, pIn(pCuboid)
	, pOut(NULL)
{
	ASSERT(pCuboid != nullptr);
}

CCuboidColorDlg::~CCuboidColorDlg()
{
}

void CCuboidColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, face0);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, face1);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON3, face2);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON4, face3);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON5, face4);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON6, face5);
}


BEGIN_MESSAGE_MAP(CCuboidColorDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCuboidColorDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCuboidColorDlg message handlers


BOOL CCuboidColorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	face0.EnableOtherButton(_T("More"), 0, 0);
	face0.SetColor(RGB(pIn->faceColor[0][0], pIn->faceColor[0][1], pIn->faceColor[0][2]));

	face1.EnableOtherButton(_T("More"), 0, 0);
	face1.SetColor(RGB(pIn->faceColor[1][0], pIn->faceColor[1][1], pIn->faceColor[1][2]));

	face2.EnableOtherButton(_T("More"), 0, 0);
	face2.SetColor(RGB(pIn->faceColor[2][0], pIn->faceColor[2][1], pIn->faceColor[2][2]));

	face3.EnableOtherButton(_T("More"), 0, 0);
	face3.SetColor(RGB(pIn->faceColor[3][0], pIn->faceColor[3][1], pIn->faceColor[3][2]));

	face4.EnableOtherButton(_T("More"), 0, 0);
	face4.SetColor(RGB(pIn->faceColor[4][0], pIn->faceColor[4][1], pIn->faceColor[4][2]));

	face5.EnableOtherButton(_T("More"), 0, 0);
	face5.SetColor(RGB(pIn->faceColor[5][0], pIn->faceColor[5][1], pIn->faceColor[5][2]));

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CCuboidColorDlg::createCuboid()
{
	pOut = new Cuboid(*pIn);
	pOut->changeFaceColor(0, GetRValue(face0.GetColor()), GetGValue(face0.GetColor()), GetBValue(face0.GetColor()));
	pOut->changeFaceColor(1, GetRValue(face1.GetColor()), GetGValue(face1.GetColor()), GetBValue(face1.GetColor()));
	pOut->changeFaceColor(2, GetRValue(face2.GetColor()), GetGValue(face2.GetColor()), GetBValue(face2.GetColor()));
	pOut->changeFaceColor(3, GetRValue(face3.GetColor()), GetGValue(face3.GetColor()), GetBValue(face3.GetColor()));
	pOut->changeFaceColor(4, GetRValue(face4.GetColor()), GetGValue(face4.GetColor()), GetBValue(face4.GetColor()));
	pOut->changeFaceColor(5, GetRValue(face5.GetColor()), GetGValue(face5.GetColor()), GetBValue(face5.GetColor()));
}


void CCuboidColorDlg::OnBnClickedOk()
{
	UpdateData();
	createCuboid();
	CDialogEx::OnOK();
}
