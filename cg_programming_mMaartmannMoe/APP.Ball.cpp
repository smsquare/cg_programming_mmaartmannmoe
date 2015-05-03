// APP.Ball.cpp
//////////////////////////////////////////////////////////////////////////

#include "APP.Ball.h"
#include "System.LoadScene.h"


Ball::Ball() {
	this->m_quadID = new GLuint();
	this->m_position = new vec3(0.0f, 0.0f, 0.0f);
	this->m_velocity = new vec3(0.0f, 0.0f, 0.0f);
}

/********************************* GET *********************************/
GLuint Ball::GetQuadID() {
	return *this->m_quadID;
}

vec3 Ball::GetPosition() {
	return *this->m_position;
}

vec3 Ball::GetVelocity() {
	return *this->m_velocity;
}

/********************************* SET *********************************/
void Ball::SetQuadID(GLuint a_quadID) {
	*this->m_quadID = a_quadID;
}

void Ball::SetPosition(vec3 a_position) {
	*this->m_position = a_position;
}

void Ball::SetVelocity(vec3 a_velocity) {
	*this->m_velocity = a_velocity;
}

/******************************* Utility *******************************/
void Ball::Draw(Camera* a_activeCamera) {
	mat4 MVPMatrix = a_activeCamera->GetProjectionMatrix() * a_activeCamera->GetViewMatrix() * RenderQuad(GetQuadID(), GetPosition(), vec3(0.05f));
	glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
}

void Ball::Update(float a_deltaTime) {
	vec3 pos = GetPosition();
	vec3 velocity = GetVelocity();

	pos += velocity * a_deltaTime;

	if (pos.x > 1.4f) {
		pos.x = 1.4f;
		velocity.x = - velocity.x;
	} else if (pos.x < -1.4f) {
		pos.x = -1.4f;
		velocity.x = -velocity.x;
	}

	SetPosition(pos);
	SetVelocity(velocity);
}