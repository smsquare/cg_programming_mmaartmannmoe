// System.Camera.cpp
//////////////////////////////////////////////////////////////////////////

#include "System.Camera.h"

Camera::Camera () {
	this->m_aspectRatio = new float();
	this->m_projectionMatrix = new mat4();
	this->m_position = new vec3(0, 0, 0);		// Initizlize to 0, 0, 0
	this->m_worldOrigin = new vec3(0, 0, 0);	// Initialize to 0, 0, 0
	this->m_upVector = new vec3(0, 1, 0);		// Initialize to 0, 1, 0
	this->m_viewMatrix = new mat4();
	this->MVPMatrixID = NULL;
}

Camera::~Camera ()
{
}

void Camera::SetAspectRatio(const int& a_screenWidth, const int& a_screenHeight) {
	*this->m_aspectRatio = (a_screenWidth / (float)a_screenHeight);
#ifdef _DEBUG
	fprintf(stdout, "Aspect Ratio set to: %f\n", *m_aspectRatio);
#endif
}

/************************************************************************
Name:	SetProjectionMatrix
Params: a_fov = field of view; a_aspectRatio = aspect ratio;
		a_near = near clip plane; a_far = far clip plane.
Result: Sets the projection matrix of the camera.
************************************************************************/
void Camera::SetProjectionMatrix(float a_fov, float a_aspectRatio, float a_near, float a_far) {
	*this->m_projectionMatrix = perspective(a_fov, a_aspectRatio, a_near, a_far);
}

void Camera::SetPosition(vec3 a_position) {
	*this->m_position = a_position;
}
/************************************************************************
Name:	SetViewMatrix
Params:	none
Result:	Takes the current camera pos, world origin, and up vector, runs 
		through Lookat(), establishing a view matrix.
************************************************************************/
void Camera::SetViewMatrix() {
	*this->m_viewMatrix = lookAt(
		*this->m_position,		// Camera is at (0,0,3) in world space
		*this->m_worldOrigin,	// and looks at the origin
		*this->m_upVector		// Head is up (set to 0,-1,0 to look upside down)
	);
}

float Camera::GetAspectRaio() {
	return *this->m_aspectRatio;
}

mat4 Camera::GetProjectionMatrix() {
	return *this->m_projectionMatrix;
}

mat4 Camera::GetViewMatrix() {
	return *this->m_viewMatrix;
}
