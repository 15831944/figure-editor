#pragma once
#include "stdafx.h"
#include "Figure.h"
#include "IObserver.h"
#include "FigureDatabaseEditor.h"

class Observable
{
protected:
	vector<IObserver*> observers;
public:
	Observable();
	virtual ~Observable();

	virtual void attach(IObserver* observer);
	virtual void detach(IObserver* observer);
	virtual void notifyObservers();
};

class FigureSet : public Observable
{
	friend class CFigureEditorView;
	friend class FigureDatabaseEditor;
protected:
	FigureDatabaseEditor* m_pDBEditor;
	vector<Figure*> m_Figures;
public:
	FigureSet();
	virtual ~FigureSet();
	void addFigure(Figure* pFigure);
	void updateFigure(int index, Figure* pNewFigure);
	void selectFigure(int index);
	void unselectFigures();
	void moveSelectedFigures(double moveX, double moveY, double moveZ);
	void scaleSelectedFigures(double zoom);
	void rotateSelectedFiguresAroundOwnAxis(double angle, bool x, bool y, bool z);
	void rotateSelectedFiguresAroundCoordAxis(double angle, bool ox, bool oy, bool oz);
	void changeSelectedFiguresColor(double red, double green, double blue);
	void projectSelectedFigures(bool xoy, bool yoz, bool xoz);
	void deleteSelectedFigures();
	int getSelectedFiguresNumber() const;
	Figure* getSelectedFigure(int& index) const;
	void markIntersectedFigures();
	void setDBEditor(FigureDatabaseEditor* pDBEditor);
	void saveDatabase();
	void loadDatabase();
};

