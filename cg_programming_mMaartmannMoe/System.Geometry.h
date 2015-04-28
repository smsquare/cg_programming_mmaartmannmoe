// System.Geometry.h
//////////////////////////////////////////////////////////////////////////
#pragma once

class Point {
public:
	float x, y, z, w;
public:
	Point();
	Point(float x, float y, float z);
	Point(float x, float y, float z, float w);
	Point(const Point& pt);
	float Magnitude();
	static Point Normalize(Point& pt);
	static float DotProduct(Point& a, Point& b);
};