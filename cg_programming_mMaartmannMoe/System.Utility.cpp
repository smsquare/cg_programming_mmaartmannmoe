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