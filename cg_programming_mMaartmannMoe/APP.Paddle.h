// APP.Paddle.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Application.h"
#include "System.Camera.h"
#include "System.Render.h"

class CPaddle {
public:
	CPaddle();

	/*** GET ***/
	GLuint GetQuadID();
	vec3 GetPosition();
	vec3 GetVelocity();
	int GetKeyUp();
	int GetKeyDown();

	/*** SET ***/
	void SetQuadID(GLuint a_quadID);
	void SetPosition(vec3 a_position);
	void SetVelocity(vec3 a_velocity);
	void SetKeyUp(int a_upKey);
	void SetKeyDown(int a_downKey);

	/*** Utility ***/
	void Draw(Camera* a_activeCamera);
	void Update(float a_deltaTime);
private:
	GLuint* m_quadID;
	vec3* m_position;
	vec3* m_velocity;
	vec3* m_scale;

	int* m_keyUp;
	int* m_keyDown;
};