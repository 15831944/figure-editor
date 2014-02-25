
// FigureEditorDoc.h : interface of the CFigureEditorDoc class
//


#pragma once
#include "CuboidSet.h"
#include "EllipsoidSet.h"


class CFigureEditorDoc : public CDocument
{
protected: // create from serialization only
	CFigureEditorDoc();
	DECLARE_DYNCREATE(CFigureEditorDoc)

// Attributes
public:
	CCuboidSet m_CuboidSet;
	CEllipsoidSet m_EllipsoidSet;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CFigureEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
