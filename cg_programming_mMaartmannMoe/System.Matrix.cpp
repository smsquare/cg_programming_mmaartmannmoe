// System.Matrix.cpp
///////////////////////////////////////////////////////////////////

#include <math.h>
#include "System.Matrix.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////

Matrix::Matrix() {
	*this = Matrix::Identity();
}

Matrix::Matrix(float m[16]) {
	for(int row = 0; row < 4; row++) {
		for(int col = 0; col < 4; col++) {
			(*this)(row,col) = m[row*4+col];
		}
	}
}

Matrix::Matrix(float m[4][4]) {
	for(int row = 0; row < 4; row++) {
		for(int col = 0; col < 4; col++) {
			(*this)(row,col) = m[row][col];
		}
	}
}

Matrix::Matrix(Matrix& matrix) {
	// Invoke the implemented assignment operator
	*this = matrix;
}

void Matrix::operator=(const Matrix& matrix) {
	for(int row = 0; row < 4; row++) {
		for(int col = 0; col < 4; col++) {
			(*this)(row,col) = matrix.m[row][col];
		}
	}
}


float& Matrix::operator()(int row, int column) {
	return this->m[row][column];
}

Matrix Matrix::Identity() {
	float identity[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return Matrix(identity);
}

Matrix Matrix::Translate(float x, float y, float z) {
	float translate[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1
	};
	return Matrix(translate);
}

Matrix Matrix::Scale(float fAmt) {
	// The scale matrix consists of scale amounts
	// applied to the diagonals of the matrix.
	Matrix matrix = Matrix::Identity();
	matrix(0,0) *= fAmt;
	matrix(1,1) *= fAmt;
	matrix(2,2) *= fAmt;
	// (but not to the W-component)
	return matrix;
}

Matrix Matrix::RotateY(float fAmt) {
	Matrix result;
	Matrix matrix = Matrix::Identity();
	result(0,0) = cos(fAmt);
	result(0,2) = sin(fAmt);
	result(2,0) = -sin(fAmt);
	result(2,2) = cos(fAmt);
	return result;
}

Matrix Matrix::RotateZ(float fAmt) {
	Matrix result;
	Matrix matrix = Matrix::Identity();
	result(0,0) = cos(fAmt);
	result(0,1) = -sin(fAmt);
	result(1,0) = sin(fAmt);
	result(1,1) = cos(fAmt);
	return result;
}

Matrix Matrix::RotateX(float fAmt) {
	Matrix result;
	Matrix matrix = Matrix::Identity();
	result(1,1) = cos(fAmt);
	result(1,2) = -sin(fAmt);
	result(2,1) = sin(fAmt);
	result(2,2) = cos(fAmt);
	return result;
}

Matrix Matrix::Rotate(float g, float b, float a) {
	float rotate[] = {
		cos(a)*cos(b), sin(a)*cos(b), -sin(b), 0,
		cos(a)*sin(b)*sin(g) - sin(a)*cos(g), sin(a)*sin(b)*sin(g) + cos(a)*cos(g), cos(b)*sin(g), 0,
		cos(a)*sin(b)*cos(g)+sin(a)*sin(g), sin(a)*sin(b)*cos(g)-cos(a)*sin(g), cos(b)*cos(g), 0,
		0, 0, 0, 1
	};
	return Matrix(rotate);
}

Matrix Matrix::Perspective(float fov, float w, float h, float near, float far) {
	float aspect = w / h;
	fov = (fov * 3.14159265358) / 180.0;
	float fovy = fov / aspect;
	float f = 1 / tan(fovy / 2);
	float perspective[] = {
		f/aspect, 0, 0, 0,
		0, f, 0, 0,
		0, 0, (far+near)/(near-far), (2*far*near)/(near-far),
		0, 0, -1, 0
	};
	return Matrix(perspective);
}

Matrix Matrix::Frustum(float left, float right, float bottom, float top, float n, float f)
{
	Matrix result = Matrix::Identity();

	if ((right == left) ||
		(top == bottom) ||
		(n == f) ||
		(n < 0.0) ||
		(f < 0.0))
		return result;

	result(0, 0) = (2.0f * n) / (right - left);
	result(1, 1) = (2.0f * n) / (top - bottom);

	result(2, 0) = (right + left) / (right - left);
	result(2, 1) = (top + bottom) / (top - bottom);
	result(2, 2) = -(f + n) / (f - n);
	result(2, 3)= -1.0f;

	result(3, 2) = -(2.0f * f * n) / (f - n);
	result(3, 3) =  0.0f;

	return result;
}

Matrix Matrix::Projection(float fovy, float aspect, float n, float f)
{
	fovy = (fovy * 3.14159265358) / 180.0;
	float  top = n * tan(0.5f*fovy); // bottom = -top
	float  right = top * aspect; // left = -right
	return Matrix::Frustum(-right, right, -top, top, n, f);
}

Matrix Matrix::Multiply(Matrix& m, Matrix& n) {
	Matrix r = Matrix::Identity();
	r(0,0) = m(0,0) * n(0,0) + m(0,1) * n(1,0) + m(0,2) * n(2,0) + m(0,3) * n(3,0);
	r(0,1) = m(0,0) * n(0,1) + m(0,1) * n(1,1) + m(0,2) * n(2,1) + m(0,3) * n(3,1);
	r(0,2) = m(0,0) * n(0,2) + m(0,1) * n(1,2) + m(0,2) * n(2,2) + m(0,3) * n(3,2);
	r(0,3) = m(0,0) * n(0,3) + m(0,1) * n(1,3) + m(0,2) * n(2,3) + m(0,3) * n(3,3);
	r(1,0) = m(1,0) * n(0,0) + m(1,1) * n(1,0) + m(1,2) * n(2,0) + m(1,3) * n(3,0);
	r(1,1) = m(1,0) * n(0,1) + m(1,1) * n(1,1) + m(1,2) * n(2,1) + m(1,3) * n(3,1);
	r(1,2) = m(1,0) * n(0,2) + m(1,1) * n(1,2) + m(1,2) * n(2,2) + m(1,3) * n(3,2);
	r(1,3) = m(1,0) * n(0,3) + m(1,1) * n(1,3) + m(1,2) * n(2,3) + m(1,3) * n(3,3);
	r(2,0) = m(2,0) * n(0,0) + m(2,1) * n(1,0) + m(2,2) * n(2,0) + m(2,3) * n(3,0);
	r(2,1) = m(2,0) * n(0,1) + m(2,1) * n(1,1) + m(2,2) * n(2,1) + m(2,3) * n(3,1);
	r(2,2) = m(2,0) * n(0,2) + m(2,1) * n(1,2) + m(2,2) * n(2,2) + m(2,3) * n(3,2);
	r(2,3) = m(2,0) * n(0,3) + m(2,1) * n(1,3) + m(2,2) * n(2,3) + m(2,3) * n(3,3);
	r(3,0) = m(3,0) * n(0,0) + m(3,1) * n(1,0) + m(3,2) * n(2,0) + m(3,3) * n(3,0);
	r(3,1) = m(3,0) * n(0,1) + m(3,1) * n(1,1) + m(3,2) * n(2,1) + m(3,3) * n(3,1);
	r(3,2) = m(3,0) * n(0,2) + m(3,1) * n(1,2) + m(3,2) * n(2,2) + m(3,3) * n(3,2);
	r(3,3) = m(3,0) * n(0,3) + m(3,1) * n(1,3) + m(3,2) * n(2,3) + m(3,3) * n(3,3);
	return r;
}

Matrix Matrix::Transpose(Matrix& m) {
	Matrix result;
	for(int row = 0; row < 4; row++) {
		for(int col = 0; col < 4; col++) {
			result(col,row) = m(row,col);
		}
	}
	return result;
}

Point Matrix::TransformPoint(Point& p) {
	return Matrix::TransformPoint(*this, p);
}

Point Matrix::TransformPoint(Matrix& m, Point& p) {
	Point Q = Point(0, 0, 0, 1);
	Q.x = p.x * m(0,0) + p.y * m(0,1) + p.z * m(0,2) + p.w * m(0,3);
	Q.y = p.x * m(1,0) + p.y * m(1,1) + p.z * m(1,2) + p.w * m(1,3);
	Q.z = p.x * m(2,0) + p.y * m(2,1) + p.z * m(2,2) + p.w * m(2,3);
	Q.w = p.x * m(3,0) + p.y * m(3,1) + p.z * m(3,2) + p.w * m(3,3);
	if(Q.w != 0.0) {
		Q.x /= Q.w;
		Q.y /= Q.w;
		Q.z /= Q.w;
		Q.w /= Q.w;
	}
	return Q;
}

Point Matrix::ExtractXAxis(Matrix& m) {
	return Point(
		m(0, 0), 
		m(0, 1), 
		m(0, 2), 
		m(0, 3)
		);
}

Point Matrix::ExtractYAxis(Matrix& m) {
	return Point(
		m(1, 0), 
		m(1, 1), 
		m(1, 2), 
		m(1, 3)
		);
}

Point Matrix::ExtractZAxis(Matrix& m) {
	return Point(
		m(2, 0), 
		m(2, 1), 
		m(2, 2), 
		m(2, 3)
		);
}

Point Matrix::ExtractPosition(Matrix& m) {
	return Point(
		m(3, 0), 
		m(3, 1), 
		m(3, 2), 
		m(3, 3)
		);
}