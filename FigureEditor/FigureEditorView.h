// FigureEditorView.h : interface of the CFigureEditorView class

#pragma once
#include "FigureEditorDoc.h"
#include "FigureSet.h"
#include "Cuboid.h"
#include "Ellipsoid.h"
#include "IController.h"
#include "StandardController.h"

class CCuboidSet;
class CEllipsoidSet;

class CFigureEditorView : public CRecordView, public IObserver
{
protected: // create from serialization only
	CFigureEditorView();
	DECLARE_DYNCREATE(CFigureEditorView)

public:
	enum{ IDD = IDD_FIGUREEDITOR_FORM };

// Attributes
public: 
	CFigureEditorDoc* GetDocument() const;
protected:
	FigureSet* model;
	IController* controller;

	HGLRC m_hrc;
	HDC m_hdc;
	GLsizei glnWidth, glnHeight;
	GLdouble gldAspect;
	CPoint currentCursor;
	double angleX, angleY, zoomZ;
	bool light, menu;


// Operations
protected:
	void getHGLRC(HWND hWnd);
	void drawAxes();
	void drawFigures(GLenum mode);
	void drawFigure(Figure* figure);
	void drawCuboid(Cuboid* cuboid);
	void drawEllipsoid(Ellipsoid* ellipsoid);
	void drawProjection(Figure* figure);
	void drawCuboidProjection(Cuboid* cuboid);
	void drawEllipsoidProjection(Ellipsoid* ellipsoid);
	void lightInit();
	void graphicsInit();

// Overrides
public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void update();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CFigureEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	afx_msg void OnAddcuboid();
	afx_msg void OnAddEllipsoid();
	afx_msg void OnDrawprojection();
	afx_msg void OnChangeColor();
	afx_msg void OnChangeFaceColor();
	afx_msg void OnRotate();
	afx_msg void OnDelete();

	afx_msg void OnFileSavetodatabase();
	afx_msg void OnLoadFromDatabase();
};

#ifndef _DEBUG  // debug version in FigureEditorView.cpp
inline CFigureEditorDoc* CFigureEditorView::GetDocument() const
   { return reinterpret_cast<CFigureEditorDoc*>(m_pDocument); }
#endif

