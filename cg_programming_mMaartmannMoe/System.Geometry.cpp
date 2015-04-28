// System.Geometry.cpp
//////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "System.Geometry.h"


Point::Point() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}

Point::Point(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1.0;
}

Point::Point(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Point::Point(const Point& pt) {
	this->x = pt.x;
	this->y = pt.y;
	this->z = pt.z;
	this->w = pt.w;
}

float Point::Magnitude() {
	return sqrt(x*x+y*y+z*z);
}

Point Point::Normalize(Point& pt) {
	Point result;
	float length = pt.Magnitude();
	result.x = pt.x / length;
	result.y = pt.y / length;
	result.z = pt.z / length;
	result.w = pt.w;
	return result;
}

float Point::DotProduct(Point& a, Point& b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}