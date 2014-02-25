#pragma once
using namespace std;

class Figure
{
	friend class CFigureEditorView;
	friend class CProjectionsDlg;
	friend class CRotationDlg;
	friend class FigureSet;
protected:
	double	moveX, moveY, moveZ,
		rotateX, rotateY, rotateZ,
		zoom;
	mutable GLfloat visibility;
	mutable bool picked, intersected, projectedXOY, projectedYOZ, projectedXOZ;
public:
	// Methods:
	Figure();
	virtual ~Figure();
	virtual void scale(double zoom);
	virtual void move(double x, double y, double z);
	virtual void rotate(double angle, bool x, bool y, bool z);
	virtual void pick();
	virtual void unpick();
	virtual void changeColor(double red, double green, double blue) = 0;
	virtual bool intersectsFigure(Figure* figure) = 0;
	virtual bool isInside(vector<double> point) = 0;
};



