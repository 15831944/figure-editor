#pragma once
#include "stdafx.h"

class Figure;
class Cuboid;
class Ellipsoid;

class IController
{

public:
	virtual ~IController(){}
	virtual void DoubleClickOnFigure(UINT nFlags, int index) = 0;
	virtual void LButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void RButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void MouseMove(UINT nFlags, CPoint point) = 0;
	virtual void MouseWheel(UINT nFlags, short zDelta, CPoint pt) = 0;
	virtual void AddCuboid(Cuboid* cuboid) = 0;
	virtual void AddEllipsoid(Ellipsoid* ellipsoid) = 0;
	virtual void UpdateFigure(int index, Figure* pNewFigure) = 0;
	virtual void Rotate(double angle, bool ox, bool oy, bool oz) = 0;
	virtual void ChangeColor(double red, double green, double blue) = 0;
	virtual void Project(bool xoy, bool yoz, bool xoz) = 0;
	virtual void Delete() = 0;
	virtual void SaveDatabase() = 0;
	virtual void LoadDatabase() = 0;
};

