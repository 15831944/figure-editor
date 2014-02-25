#include "stdafx.h"
#include "Figure.h"
#include "Matrix.h"


Figure::Figure()
{
	moveX = 0.0f;
	moveY = 0.0f;
	moveZ = 0.0f;
	rotateX = 0.0f;
	rotateY = 0.0f;
	rotateZ = 0.0f;
	zoom = 1.0f;
	visibility = 1.0f;
	picked = false;
	intersected = false;
	projectedXOY = false;
	projectedYOZ = false;
	projectedXOZ = false;
}

Figure::~Figure() 
{
}

void Figure::scale(double zoom)
{
	this->zoom *= zoom;
}

void Figure::move(double x, double y, double z)
{
	moveX += x;
	moveY += y;
	moveZ += z;
}

void Figure::rotate(double angle, bool x, bool y, bool z)
{
	Matrix M(3);
	if (x)
	{
		M.getRotation(angle / 180.0 * M_PI, 0.0, 0.0);
		vector<double> center(3);
		center[0] = moveX;
		center[1] = moveY;
		center[2] = moveZ;
		vector<double> newCenter = M * center;
		moveX = newCenter[0];
		moveY = newCenter[1];
		moveZ = newCenter[2];
		rotateX += angle;
	}
	if (y)
	{
		M.getRotation(0.0, -angle / 180.0 * M_PI, 0.0);
		vector<double> center(3);
		center[0] = moveX;
		center[1] = moveY;
		center[2] = moveZ;
		vector<double> newCenter = M * center;
		moveX = newCenter[0];
		moveY = newCenter[1];
		moveZ = newCenter[2];
		rotateY += angle;
	}
	if (z)
	{
		M.getRotation(0.0, 0.0, angle / 180.0 * M_PI);
		vector<double> center(3);
		center[0] = moveX;
		center[1] = moveY;
		center[2] = moveZ;
		vector<double> newCenter = M * center;
		moveX = newCenter[0];
		moveY = newCenter[1];
		moveZ = newCenter[2];
		rotateZ += angle;
	}
}

void Figure::pick()
{
	picked = true;
	visibility = 0.5f;
}


void Figure::unpick()
{
	picked = false;
	visibility = 1.0f;
	intersected = false;
	projectedXOY = projectedYOZ = projectedXOZ = false;
}
