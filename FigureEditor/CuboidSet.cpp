
// CuboidSet.cpp : implementation of the CCuboidSet class
//

#include "stdafx.h"
#include "FigureEditor.h"
#include "CuboidSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCuboidSet implementation

// code generated on 1 квітня 2014 р., 0:14

IMPLEMENT_DYNAMIC(CCuboidSet, CRecordset)

CCuboidSet::CCuboidSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_LENGTH = 0.0;
	m_HEIGHT = 0.0;
	m_WIDTH = 0.0;
	m_MOVE_X = 0.0;
	m_MOVE_Y = 0.0;
	m_MOVE_Z = 0.0;
	m_ROTATE_X = 0.0;
	m_ROTATE_Y = 0.0;
	m_ROTATE_Z = 0.0;
	m_ZOOM = 0.0;
	m_TOP_RED = 0.0;
	m_TOP_GREEN = 0.0;
	m_TOP_BLUE = 0.0;
	m_BOTTOM_RED = 0.0;
	m_BOTTOM_GREEN = 0.0;
	m_BOTTOM_BLUE = 0.0;
	m_FRONT_RED = 0.0;
	m_FRONT_GREEN = 0.0;
	m_FRONT_BLUE = 0.0;
	m_BACK_RED = 0.0;
	m_BACK_GREEN = 0.0;
	m_BACK_BLUE = 0.0;
	m_LEFT_RED = 0.0;
	m_LEFT_GREEN = 0.0;
	m_LEFT_BLUE = 0.0;
	m_RIGHT_RED = 0.0;
	m_RIGHT_GREEN = 0.0;
	m_RIGHT_BLUE = 0.0;
	m_nFields = 28;
	m_nDefaultType = dynaset;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CCuboidSet::GetDefaultConnect()
{
	return _T("DRIVER={Microsoft ODBC for Oracle};UID=system;PWD=4880930;SERVER=MyDB;");
}

CString CCuboidSet::GetDefaultSQL()
{
	return _T("[PROJECTDB].[CUBOIDS]");
}

void CCuboidSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Double(pFX, _T("[LENGTH]"), m_LENGTH);
	RFX_Double(pFX, _T("[HEIGHT]"), m_HEIGHT);
	RFX_Double(pFX, _T("[WIDTH]"), m_WIDTH);
	RFX_Double(pFX, _T("[MOVE_X]"), m_MOVE_X);
	RFX_Double(pFX, _T("[MOVE_Y]"), m_MOVE_Y);
	RFX_Double(pFX, _T("[MOVE_Z]"), m_MOVE_Z);
	RFX_Double(pFX, _T("[ROTATE_X]"), m_ROTATE_X);
	RFX_Double(pFX, _T("[ROTATE_Y]"), m_ROTATE_Y);
	RFX_Double(pFX, _T("[ROTATE_Z]"), m_ROTATE_Z);
	RFX_Double(pFX, _T("[ZOOM]"), m_ZOOM);
	RFX_Double(pFX, _T("[TOP_RED]"), m_TOP_RED);
	RFX_Double(pFX, _T("[TOP_GREEN]"), m_TOP_GREEN);
	RFX_Double(pFX, _T("[TOP_BLUE]"), m_TOP_BLUE);
	RFX_Double(pFX, _T("[BOTTOM_RED]"), m_BOTTOM_RED);
	RFX_Double(pFX, _T("[BOTTOM_GREEN]"), m_BOTTOM_GREEN);
	RFX_Double(pFX, _T("[BOTTOM_BLUE]"), m_BOTTOM_BLUE);
	RFX_Double(pFX, _T("[FRONT_RED]"), m_FRONT_RED);
	RFX_Double(pFX, _T("[FRONT_GREEN]"), m_FRONT_GREEN);
	RFX_Double(pFX, _T("[FRONT_BLUE]"), m_FRONT_BLUE);
	RFX_Double(pFX, _T("[BACK_RED]"), m_BACK_RED);
	RFX_Double(pFX, _T("[BACK_GREEN]"), m_BACK_GREEN);
	RFX_Double(pFX, _T("[BACK_BLUE]"), m_BACK_BLUE);
	RFX_Double(pFX, _T("[LEFT_RED]"), m_LEFT_RED);
	RFX_Double(pFX, _T("[LEFT_GREEN]"), m_LEFT_GREEN);
	RFX_Double(pFX, _T("[LEFT_BLUE]"), m_LEFT_BLUE);
	RFX_Double(pFX, _T("[RIGHT_RED]"), m_RIGHT_RED);
	RFX_Double(pFX, _T("[RIGHT_GREEN]"), m_RIGHT_GREEN);
	RFX_Double(pFX, _T("[RIGHT_BLUE]"), m_RIGHT_BLUE);

}
/////////////////////////////////////////////////////////////////////////////
// CCuboidSet diagnostics

#ifdef _DEBUG
void CCuboidSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCuboidSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

