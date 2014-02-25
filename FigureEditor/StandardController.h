#pragma once
#include "IController.h"
#include "FigureSet.h"
#include "Cuboid.h"
#include "Ellipsoid.h" 

class StandardController :
	public IController
{
protected:
	FigureSet* model;
	CPoint currentCursor;
	const int NO_FIGURES_SELECTED;
public:
	StandardController(FigureSet* pModel);
	virtual ~StandardController();
	virtual void DoubleClickOnFigure(UINT nFlags, int index);
	virtual void LButtonDown(UINT nFlags, CPoint point);
	virtual void RButtonDown(UINT nFlags, CPoint point);
	virtual void MouseMove(UINT nFlags, CPoint point);
	virtual void MouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual void AddCuboid(Cuboid* cuboid);
	virtual void AddEllipsoid(Ellipsoid* ellipsoid);
	virtual void UpdateFigure(int index, Figure* pNewFigure);
	virtual void Rotate(double angle, bool ox, bool oy, bool oz);
	virtual void ChangeColor(double red, double green, double blue);
	virtual void Project(bool xoy, bool yoz, bool xoz);
	virtual void Delete();
	virtual void SaveDatabase();
	virtual void LoadDatabase();	
};

