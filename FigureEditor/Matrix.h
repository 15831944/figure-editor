#pragma once
using namespace std;

class Matrix
{
	int size;
	double **A;
	void getOneRotationMatrix(int i, int j, double angle);
public:
	Matrix(int newSize);
	Matrix(const Matrix& m);
	~Matrix();
	vector<double> operator*(const vector<double>& x);
	void operator*(double x[3]);
	Matrix operator*(const Matrix& m2);
	Matrix& operator=(const Matrix& m);
	void getIdentity();
	Matrix getTransposed();
	void getRotation(double angleX, double angleY, double angleZ);
	
};


