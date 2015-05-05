// APP.Ball.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Application.h"
#include "System.Camera.h"
#include "System.Render.h"
#include "System.Mesh.h"
#include "APP.Paddle.h"

class CBall {
public:
	CBall();

	CMesh mesh;
	enum class PADDLEHIT { NOTHING, TOP, BOTTOM, LEFT, RIGHT};
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
	void Update(float a_deltaTime, CPaddle* leftPaddle, CPaddle* rightPaddle);
	void BuildBall();
	int IsHittingWhatSide(CPaddle* paddle);
	int IsBallHittingPaddle(CPaddle* paddle);
private:
	GLuint* m_quadID;
	vec3* m_position;
	vec3* m_velocity;
	vec3* m_scale;
};