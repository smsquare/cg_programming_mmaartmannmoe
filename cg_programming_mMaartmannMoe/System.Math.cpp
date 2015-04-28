// System.Math.cpp
//////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "System.Math.h"

float Math::LinearInterpolate(float a_from, float a_to, float a_percentage) {
	return a_from + a_percentage * (a_to - a_from);
}

float Math::UnwindAngle(float a_angle) {
	float TWO_PI = 2 * 3.14159265358989;
	while (a_angle > TWO_PI) a_angle -= TWO_PI;
	while (a_angle < -TWO_PI) a_angle += TWO_PI;
	return a_angle;
}