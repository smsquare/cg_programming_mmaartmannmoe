// System.Matrix.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "System.Geometry.h"
#include "System.List.h";
using namespace System::List;

class Matrix {
public:
	float m[4][4];
public:
	Matrix();
	Matrix(float m[16]);
	Matrix(float m[4][4]);
	Matrix(Matrix& matrix);

	static Matrix Identity();
	static Matrix Translate(float a_x, float a_y, float a_z);
	static Matrix Scale(float a_amount);
	// Rotation functions
	static Matrix RotateX(float a_amount);
	static Matrix RotateY(float a_amount);
	static Matrix RotateZ(float a_amount);
	static Matrix Rotate(float a_g, float a_b, float a_a);

	static Matrix Perspective(float a_fov, float a_w, float a_h, float a_near, float a_far);
	static Matrix Frustum(float a_left, float a_right, float a_bottom, float a_top, float a_n, float a_f);
	static Matrix Projection(float a_fovy, float a_aspect, float a_n, float a_f);
	
	static Matrix Multiply(Matrix& a_m, Matrix& a_n);
	static Matrix Transpose(Matrix& a_m);

	static Point TransformPoint(Matrix& m, Point& p);
	Point TransformPoint(Point& p);

	// Axis extraction functions dig into the matrix and extract the
	// coordinate system axes that it represents.
	static Point ExtractXAxis(Matrix& m);
	static Point ExtractYAxis(Matrix& m);
	static Point ExtractZAxis(Matrix& m);
	static Point ExtractPosition(Matrix& m);
	
	// This is an implementation of the assignment operator, which allows
	// the matrix to be used on the left-hand side of an assignment statement
	// and have the code within the implementation of this function run.
	void operator=(const Matrix& matrix);

	// This is an implementation of the (const float*) typecast operator.
	// It is what allows the Matrix to be supplied to OpenGL functions which
	// expect (const float*) as the matrix datatype.
	inline operator const float* () const { return &m[0][0]; }

	// This is an implementation of the function call operator.
	// This is what allows you to access members of the matrix as though
	// the matrix were a function, e.g. M(1, 2); // Row 1 Column 2.
	float& operator ()(int row, int column);
};