// System.Utility.cpp
//////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "System.Utility.h"

float& GetDeltaTime() {
	static float fLastTime = glfwGetTime();

	float fNow = glfwGetTime();
	float fDeltaTime = fNow - fLastTime;

	fLastTime = fNow;
	return fDeltaTime;
}

vec3 CalculateReflectionVector(vec3 a_velocity, vec3 a_normal) {
	vec3 result;

	result.x = a_velocity.x - (2.0f*a_normal.x * dot(a_velocity, a_normal));
	result.y = a_velocity.y - (2.0f*a_normal.y * dot(a_velocity, a_normal));
	result.z = 0.0f;

	return result;
}