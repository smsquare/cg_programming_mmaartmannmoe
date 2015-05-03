// APP.Ball.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Application.h"
#include "System.Camera.h"
#include "System.Render.h"


void DrawBall(const GLuint& a_quadID, const vec3& a_position, const mat4& a_projectionMatrix, const mat4& a_viewMatrix, const GLuint& a_MVPMatrixID);

class Ball {
public:
	Ball();

	/*** GET ***/
	GLuint GetQuadID();
	vec3 GetPosition();
	vec3 GetVelocity();

	/*** SET ***/
	void SetQuadID(GLuint a_quadID);
	void SetPosition(vec3 a_position);
	void SetVelocity(vec3 a_velocity);

	/*** Utility ***/
	void Draw(Camera* a_activeCamera);
	void Update(float a_deltaTime);
private:
	GLuint* m_quadID;
	vec3* m_position;
	vec3* m_velocity;
};