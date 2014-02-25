#include "stdafx.h"
#include "StandardController.h"
#include "IController.h"


StandardController::StandardController(FigureSet* pModel) : currentCursor(0), model(pModel), NO_FIGURES_SELECTED(-1){}

StandardController::~StandardController() {}

void StandardController::DoubleClickOnFigure(UINT nFlags, int index)
{
	if (!(nFlags & MK_CONTROL))
		model->unselectFigures();
	if (index != NO_FIGURES_SELECTED)
		model->selectFigure(index);
	model->notifyObservers();
}

void StandardController::LButtonDown(UINT nFlags, CPoint point)
{
	currentCursor = point;
}

void StandardController::RButtonDown(UINT nFlags, CPoint point)
{
	currentCursor = point;
}

void StandardController::MouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON)
	{
		// here currentCursor is not current but contains mouse coordinates during click lButton
		if (fabs(double(point.x - currentCursor.x)) > fabs(double(point.y - currentCursor.y)))
		{
			if (point.x - currentCursor.x > 0)
				model->moveSelectedFigures(0.1, 0.0, 0.0);
			else
				model->moveSelectedFigures(-0.1, 0.0, 0.0);
		}
		else {
			if (point.y - currentCursor.y > 0)
				model->moveSelectedFigures(0.0, -0.1, 0.0);
			else
				model->moveSelectedFigures(0.0, 0.1, 0.0);
		}
		model->markIntersectedFigures();
		model->notifyObservers();
	}
	else if (nFlags & MK_RBUTTON)
	{
		// here currentCursor is not current but contains mouse coordinates during click lButton
		if (fabs(double(point.x - currentCursor.x)) > fabs(double(point.y - currentCursor.y)))
		{
			if (point.x - currentCursor.x > 0)
				model->rotateSelectedFiguresAroundOwnAxis(+1.0, false, true, false);
			else 
				model->rotateSelectedFiguresAroundOwnAxis(-1.0, false, true, false);
		}
		else {
			if (point.y - currentCursor.y > 0)
				model->rotateSelectedFiguresAroundOwnAxis(-1.0, true, false, false);
			else
				model->rotateSelectedFiguresAroundOwnAxis(+1.0, true, false, false);
		}
		model->notifyObservers();
	}
}

void StandardController::MouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (nFlags & MK_LBUTTON){		//we will change z-coordinate of picked figures
		if (zDelta > 0)
			model->moveSelectedFigures(0.0, 0.0, 0.2);
		else
			model->moveSelectedFigures(0.0, 0.0, -0.2);
		model->markIntersectedFigures();
	}
	else if (nFlags & MK_RBUTTON){	//we will rotate picked figures around z axis
		if (zDelta > 0)
			model->rotateSelectedFiguresAroundOwnAxis(2.0, false, false, true);
		else
			model->rotateSelectedFiguresAroundOwnAxis(-2.0, false, false, true);
	}
	else{							//we will scale picked figures
		if (zDelta > 0)
			model->scaleSelectedFigures(1.05);
		else
			model->scaleSelectedFigures(0.95);
	}
	model->notifyObservers();
}

void StandardController::AddCuboid(Cuboid* cuboid)
{
	model->addFigure(static_cast<Figure*>(cuboid));
	model->notifyObservers();
}

void StandardController::AddEllipsoid(Ellipsoid* ellipsoid)
{
	model->addFigure(static_cast<Figure*>(ellipsoid));
	model->notifyObservers();
}

void StandardController::UpdateFigure(int index, Figure* pNewFigure)
{
	model->updateFigure(index, pNewFigure);
	model->notifyObservers();
}

void StandardController::Rotate(double angle, bool ox, bool oy, bool oz)
{
	model->rotateSelectedFiguresAroundCoordAxis(angle, ox, oy, oz);
	model->notifyObservers();
}

void StandardController::ChangeColor(double red, double green, double blue)
{
	model->changeSelectedFiguresColor(red, green, blue);
	model->notifyObservers();
}

void StandardController::Project(bool xoy, bool yoz, bool xoz)
{
	model->projectSelectedFigures(xoy, yoz, xoz);
	model->notifyObservers();
}

void StandardController::Delete()
{
	model->deleteSelectedFigures();
	model->notifyObservers();
}

void StandardController::SaveDatabase()
{
	model->saveDatabase();
}

void StandardController::LoadDatabase()
{
	model->loadDatabase();
	model->notifyObservers();
}
