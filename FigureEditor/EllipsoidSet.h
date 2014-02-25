// EllipsoidSet.h : Declaration of the CEllipsoidSet

#pragma once

// code generated on 1 квітня 2014 р., 0:20

class CEllipsoidSet : public CRecordset
{
public:
	CEllipsoidSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEllipsoidSet)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	double	m_A;
	double	m_B;
	double	m_C;
	double	m_MOVE_X;
	double	m_MOVE_Y;
	double	m_MOVE_Z;
	double	m_ROTATE_X;
	double	m_ROTATE_Y;
	double	m_ROTATE_Z;
	double	m_ZOOM;
	double	m_COLOR_RED;
	double	m_COLOR_GREEN;
	double	m_COLOR_BLUE;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


