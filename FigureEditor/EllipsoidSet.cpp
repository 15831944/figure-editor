// EllipsoidSet.h : Implementation of the CEllipsoidSet class



// CEllipsoidSet implementation

// code generated on 1 квітня 2014 р., 0:20

#include "stdafx.h"
#include "EllipsoidSet.h"
IMPLEMENT_DYNAMIC(CEllipsoidSet, CRecordset)

CEllipsoidSet::CEllipsoidSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_A = 0.0;
	m_B = 0.0;
	m_C = 0.0;
	m_MOVE_X = 0.0;
	m_MOVE_Y = 0.0;
	m_MOVE_Z = 0.0;
	m_ROTATE_X = 0.0;
	m_ROTATE_Y = 0.0;
	m_ROTATE_Z = 0.0;
	m_ZOOM = 0.0;
	m_COLOR_RED = 0.0;
	m_COLOR_GREEN = 0.0;
	m_COLOR_BLUE = 0.0;
	m_nFields = 13;
	m_nDefaultType = dynaset;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CEllipsoidSet::GetDefaultConnect()
{
	return _T("DRIVER={Microsoft ODBC for Oracle};UID=system;PWD=4880930;SERVER=MyDB;");
}

CString CEllipsoidSet::GetDefaultSQL()
{
	return _T("[PROJECTDB].[ELLIPSOIDS]");
}

void CEllipsoidSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Double(pFX, _T("[A]"), m_A);
	RFX_Double(pFX, _T("[B]"), m_B);
	RFX_Double(pFX, _T("[C]"), m_C);
	RFX_Double(pFX, _T("[MOVE_X]"), m_MOVE_X);
	RFX_Double(pFX, _T("[MOVE_Y]"), m_MOVE_Y);
	RFX_Double(pFX, _T("[MOVE_Z]"), m_MOVE_Z);
	RFX_Double(pFX, _T("[ROTATE_X]"), m_ROTATE_X);
	RFX_Double(pFX, _T("[ROTATE_Y]"), m_ROTATE_Y);
	RFX_Double(pFX, _T("[ROTATE_Z]"), m_ROTATE_Z);
	RFX_Double(pFX, _T("[ZOOM]"), m_ZOOM);
	RFX_Double(pFX, _T("[COLOR_RED]"), m_COLOR_RED);
	RFX_Double(pFX, _T("[COLOR_GREEN]"), m_COLOR_GREEN);
	RFX_Double(pFX, _T("[COLOR_BLUE]"), m_COLOR_BLUE);

}
/////////////////////////////////////////////////////////////////////////////
// CEllipsoidSet diagnostics

#ifdef _DEBUG
void CEllipsoidSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEllipsoidSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


