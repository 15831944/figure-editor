#include "stdafx.h"
#include "Matrix.h"
using namespace std;

Matrix::Matrix(int newSize)
	{
		size = newSize;
		A = new double*[size];
		for (int i = 0; i < size; i++)
			A[i] = new double[size];
		for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			A[i][j] = 0.0;
	}

Matrix::Matrix(const Matrix& m)
	{
		size = m.size;
		A = new double*[size];
		for (int i = 0; i < size; i++)
			A[i] = new double[size];
		for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			A[i][j] = m.A[i][j];
	}

Matrix::~Matrix()
	{
		for (int i = 0; i < size; i++)
			delete[] A[i];
		delete[] A;
		size = 0;
	}

Matrix& Matrix::operator=(const Matrix& m)
	{
		for (int i = 0; i < size; i++)
			delete[] A[i];
		delete[] A;
		size = m.size;
		A = new double*[size];
		for (int i = 0; i < size; i++)
			A[i] = new double[size];
		for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			A[i][j] = m.A[i][j];
		return *this;
	}

void Matrix::getIdentity()
	{
		for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		if (i == j)
			A[i][j] = 1.0;
		else
			A[i][j] = 0.0;
	}
	
Matrix Matrix::getTransposed()
	{
		Matrix T = *this;
		for (int i = 0; i < size; i++)
		for (int j = i + 1; j < size; j++)
		{
			double v = T.A[i][j];
			T.A[i][j] = T.A[j][i];
			T.A[j][i] = v;
		}
		return T;
	}

void Matrix::getOneRotationMatrix(int i, int j, double angle)
	{
		getIdentity();
		A[i][i] = A[j][j] = cos(angle);
		A[i][j] = -sin(angle);
		A[j][i] = sin(angle);
	}

void Matrix::getRotation(double angleX, double angleY, double angleZ)
{
	Matrix M1(3), M2(3), M3(3);
	M1.getIdentity();
	M2.getIdentity();
	M3.getIdentity();
	if (angleX) M1.getOneRotationMatrix(1, 2, angleX);
	if (angleY) M2.getOneRotationMatrix(0, 2, angleY);
	if (angleZ) M3.getOneRotationMatrix(0, 1, angleZ);
	M1.getTransposed();
	M2.getTransposed();
	M3.getTransposed();
	*this = M1 * M2 * M3;
}

Matrix Matrix::operator*(const Matrix& m2)
{
	if (size != m2.size)
		throw "Multiplication error: size1 != size2";
	Matrix result(size);
	for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++)
	for (int k = 0; k < size; k++)
		result.A[i][j] += A[i][k] * m2.A[k][j];
	return result;

}

vector<double> Matrix::operator*(const vector<double>& x)
{
	vector<double> result(size);
	for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++)
		result[i] += A[i][j] * x[j];
	return result;
}

void Matrix::operator*(double x[3])
{
	vector<double> result(3);
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
		result[i] += A[i][j] * x[j];
	for (int i = 0; i < 3; i++)
		x[i] = result[i];
}