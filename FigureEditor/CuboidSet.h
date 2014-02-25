
// CuboidSet.h: interface of the CCuboidSet class
//


#pragma once

// code generated on 1 квітня 2014 р., 0:14

class CCuboidSet : public CRecordset
{
public:
	CCuboidSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCuboidSet)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	double	m_LENGTH;
	double	m_HEIGHT;
	double	m_WIDTH;
	double	m_MOVE_X;
	double	m_MOVE_Y;
	double	m_MOVE_Z;
	double	m_ROTATE_X;
	double	m_ROTATE_Y;
	double	m_ROTATE_Z;
	double	m_ZOOM;
	double	m_TOP_RED;
	double	m_TOP_GREEN;
	double	m_TOP_BLUE;
	double	m_BOTTOM_RED;
	double	m_BOTTOM_GREEN;
	double	m_BOTTOM_BLUE;
	double	m_FRONT_RED;
	double	m_FRONT_GREEN;
	double	m_FRONT_BLUE;
	double	m_BACK_RED;
	double	m_BACK_GREEN;
	double	m_BACK_BLUE;
	double	m_LEFT_RED;
	double	m_LEFT_GREEN;
	double	m_LEFT_BLUE;
	double	m_RIGHT_RED;
	double	m_RIGHT_GREEN;
	double	m_RIGHT_BLUE;

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

