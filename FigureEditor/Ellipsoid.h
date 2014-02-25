#pragma once
#include "Figure.h"
class Ellipsoid :
	public Figure
{
	friend class CEllipsoidDlg;
	friend class CFigureEditorView;
	friend class FigureDatabaseEditor;
protected:
	GLUquadricObj* quadricObj;
	double a, b, c;
	GLfloat color[3];
// Methods:
public:
	Ellipsoid();
	~Ellipsoid();
	void changeColor(double red, double green, double blue);
	bool intersectsFigure(Figure* figure);
protected:
	bool isInside(vector<double> point);
};

