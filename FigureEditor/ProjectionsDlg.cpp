// ProjectionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FigureEditor.h"
#include "ProjectionsDlg.h"
#include "FigureEditorView.h"
#include "afxdialogex.h"


// CProjectionsDlg dialog

IMPLEMENT_DYNAMIC(CProjectionsDlg, CDialogEx)

CProjectionsDlg::CProjectionsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProjectionsDlg::IDD, pParent)
	, xoy(FALSE)
	, yoz(FALSE)
	, xoz(FALSE)
{

}

CProjectionsDlg::~CProjectionsDlg()
{
}

void CProjectionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, xoy);
	DDX_Check(pDX, IDC_CHECK2, yoz);
	DDX_Check(pDX, IDC_CHECK3, xoz);
}

BEGIN_MESSAGE_MAP(CProjectionsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CProjectionsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CProjectionsDlg message handlers


void CProjectionsDlg::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}
