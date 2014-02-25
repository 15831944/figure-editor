#pragma once
#include "Figure.h"
class Cuboid :
	public Figure
{
	friend class CCuboidDlg;
	friend class CCuboidColorDlg;
	friend class CFigureEditorView;
	friend class FigureDatabaseEditor;
protected:
	double length, height, width;
	GLfloat faceColor[6][3];
public:
// Methods:
	Cuboid();
	~Cuboid();
	void changeColor(double red, double green, double blue);
	void changeFaceColor(unsigned int face, double red, double green, double blue);
	bool intersectsFigure(Figure* figure);
protected:
	bool isInside(vector<double> point);
};

