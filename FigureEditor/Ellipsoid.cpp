#include "stdafx.h"
#include "Ellipsoid.h"
#include "Matrix.h"

Ellipsoid::Ellipsoid()
: quadricObj(NULL)
{
	a = 0.0;
	b = 0.0;
	c = 0.0;
	for (int i = 0; i < 3; i++)
		color[i] = 0.0;
	quadricObj = gluNewQuadric();
	gluQuadricNormals(quadricObj, GLU_SMOOTH);
}


Ellipsoid::~Ellipsoid()
{
	gluDeleteQuadric(quadricObj);
}

void Ellipsoid::changeColor(double red, double green, double blue)
{
	this->color[0] = red;
	this->color[1] = green;
	this->color[2] = blue;
}

bool Ellipsoid::intersectsFigure(Figure* figure)
{
	const double incr(0.51), pi2(2 * M_PI);

	vector<double> point(3);
	Matrix rotation(3);
	rotation.getRotation(rotateX / 180.0 * M_PI, rotateY / 180.0 * M_PI, rotateZ / 180.0 * M_PI);

	for (double phi = -M_PI_2; phi <= M_PI_2; phi += incr)
	for (double theta = 0.05; theta < pi2; theta += incr)
	{
		point[0] = a * zoom * sin(theta) * cos(phi);
		point[1] = b * zoom * sin(theta) * sin(phi);
		point[2] = c * zoom * cos(theta);

		point = rotation * point;

		point[0] += moveX;
		point[1] += moveY;
		point[2] += moveZ;

		if (figure->isInside(point))
			return true;
	}
	return false;
}

bool Ellipsoid::isInside(vector<double> point)
{
	point[0] -= moveX;
	point[1] -= moveY;
	point[2] -= moveZ;

	Matrix rotation(3);
	rotation.getRotation(-rotateX / 180.0 * M_PI, -rotateY / 180.0 * M_PI, -rotateZ / 180.0 * M_PI);

	if ((point[0] * point[0]) / (a * a * zoom * zoom) + 
		(point[1] * point[1]) / (b * b * zoom * zoom) + 
		(point[2] * point[2]) / (c * c * zoom * zoom) <= 1.0)
		return true;
	return false;
}