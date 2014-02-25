#include "stdafx.h"
#include "Cuboid.h"
#include "Matrix.h"


Cuboid::Cuboid()
{
	length = 0.0;
	height = 0.0;
	width = 0.0;
	for (int i = 0; i < 6; i++)
	for (int j = 0; j < 3; j++)
		faceColor[i][j] = 0.0f;
}


Cuboid::~Cuboid()
{
}

void Cuboid::changeColor(double red, double green, double blue)
{
	for (int i = 0; i < 6; i++)
	{
		this->faceColor[i][0] = red;
		this->faceColor[i][1] = green;
		this->faceColor[i][2] = blue;
	}
}

void Cuboid::changeFaceColor(unsigned int face, double red, double green, double blue)
{
	if (face < 6)  {
		this->faceColor[face][0] = red;
		this->faceColor[face][1] = green;
		this->faceColor[face][2] = blue;
	}
}

bool Cuboid::intersectsFigure(Figure* figure)
{
	const double incr(0.5);
	double x(0), y(0), z(0);

	vector<double> point(3);
	Matrix rotation(3);
	rotation.getRotation(rotateX / 180.0 * M_PI, rotateY / 180.0 * M_PI, rotateZ / 180.0 * M_PI);

	// front face
	for (x = -length * zoom / 2; x <= length * zoom / 2; x += incr)
	for (y = -height * zoom / 2; y <= height * zoom / 2; y += incr)
	{
		point[0] = x;
		point[1] = y;
		point[2] = width / 2;

		point = rotation * point;

		point[0] += moveX;
		point[1] += moveY;
		point[2] += moveZ;

		if (figure->isInside(point))
			return true;
	}

	// back face
	for (x = -length * zoom / 2; x <= length * zoom / 2; x += incr)
	for (y = -height * zoom / 2; y <= height * zoom / 2; y += incr)
	{
		point[0] = x;
		point[1] = y;
		point[2] = - width / 2;

		point = rotation * point;

		point[0] += moveX;
		point[1] += moveY;
		point[2] += moveZ;

		if (figure->isInside(point))
			return true;
	}

	// right face
	for (y = -height * zoom / 2; y <= height * zoom / 2; y += incr)
	for (z = -width * zoom / 2; z <= width * zoom / 2; z += incr)
	{
		point[0] = -length / 2;
		point[1] = y;
		point[2] = z;

		point = rotation * point;

		point[0] += moveX;
		point[1] += moveY;
		point[2] += moveZ;

		if (figure->isInside(point))
			return true;
	}

	// left face
	for (y = -height * zoom / 2; y <= height * zoom / 2; y += incr)
	for (z = -width * zoom / 2; z <= width * zoom / 2; z += incr)
	{
		point[0] = -length / 2;
		point[1] = y;
		point[2] = z;

		point = rotation * point;

		point[0] += moveX;
		point[1] += moveY;
		point[2] += moveZ;

		if (figure->isInside(point))
			return true;
	}

	// top face
	for (x = -length * zoom / 2; x <= length * zoom / 2; x += incr)
	for (z = -width * zoom / 2; z <= width * zoom / 2; z += incr)
	{
		point[0] = x;
		point[1] = height / 2;
		point[2] = z;

		point = rotation * point;

		point[0] += moveX;
		point[1] += moveY;
		point[2] += moveZ;

		if (figure->isInside(point))
			return true;
	}

	// bottom face
	for (x = -length * zoom / 2; x <= length * zoom / 2; x += incr)
	for (z = -width * zoom / 2; z <= width * zoom / 2; z += incr)
	{
		point[0] = x;
		point[1] = - height / 2;
		point[2] = z;

		point = rotation * point;

		point[0] += moveX;
		point[1] += moveY;
		point[2] += moveZ;

		if (figure->isInside(point))
			return true;
	}

	return false;
}

bool Cuboid::isInside(vector<double> point)
{
	point[0] -= moveX;
	point[1] -= moveY;
	point[2] -= moveZ;

	Matrix rotation(3);
	rotation.getRotation(-rotateX / 180.0 * M_PI, -rotateY / 180.0 * M_PI, -rotateZ / 180.0 * M_PI);
	point = rotation * point;

	if (point[0] >= -length * zoom / 2 && point[0] <= length * zoom / 2 &&
		point[1] >= -height * zoom / 2 && point[1] <= height * zoom / 2 &&
		point[2] >= -width * zoom / 2 && point[2] <= width * zoom / 2)
		return true;
	return false;
}