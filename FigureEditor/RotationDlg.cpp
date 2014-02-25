// RotationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FigureEditor.h"
#include "RotationDlg.h"
#include "Figure.h"
#include "afxdialogex.h"


// CRotationDlg dialog

IMPLEMENT_DYNAMIC(CRotationDlg, CDialogEx)

CRotationDlg::CRotationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRotationDlg::IDD, pParent)
	, m_Angle(0)
	, Ox(0)
	, Oy(0)
	, Oz(0)
{

}

CRotationDlg::~CRotationDlg()
{
}

void CRotationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ANGLE, m_Angle);
	DDX_Control(pDX, IDC_OX, m_Ox);
	DDX_Control(pDX, IDC_OY, m_Oy);
	DDX_Control(pDX, IDC_OZ, m_Oz);
}

BEGIN_MESSAGE_MAP(CRotationDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRotationDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRotationDlg message handlers


void CRotationDlg::OnBnClickedOk()
{
	UpdateData();
	Ox = m_Ox.GetCheck();
	Oy = m_Oy.GetCheck();
	Oz = m_Oz.GetCheck();
	CDialogEx::OnOK();
}
