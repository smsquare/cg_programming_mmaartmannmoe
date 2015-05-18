// System.Camera.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Application.h"

class Camera {
public:
	Camera ();
	~Camera ();

	void SetAspectRatio(const int& a_screenWidth, const int& a_screenHeight);
	void SetProjectionMatrix(float a_fov, float a_aspectRatio, float a_near, float a_far);
	void SetPosition(vec3 a_position);
	void SetViewMatrix();	// Explict declaration
	void SetViewMatrix(vec3 a_cameraPos, vec3 a_worldOrigin, vec3 a_upVector);
	void SetWorldOrigin(vec3 a_worldOrigin);

	float GetAspectRaio();
	mat4 GetProjectionMatrix();
	vec3 GetPosition();
	mat4 GetViewMatrix();
	vec3 GetWorldOrigin();

	GLuint MVPMatrixID;

private:
	float* m_aspectRatio;
	mat4* m_projectionMatrix;
	vec3* m_position;
	vec3* m_worldOrigin;
	vec3* m_upVector;
	mat4* m_viewMatrix;
};
