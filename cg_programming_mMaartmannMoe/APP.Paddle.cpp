// APP.Paddle.cpp
//////////////////////////////////////////////////////////////////////////

#include "APP.Paddle.h"
#include "System.LoadScene.h"

CPaddle::CPaddle() {
	this->m_quadID = new GLuint();
	this->m_position = new vec3(0.0f, 0.0f, 0.0f);
	this->m_velocity = new vec3(0.0f, 0.0f, 0.0f);
	this->m_scale = new vec3(0.06f, 0.6f,0.0f);
	this->m_keyUp = new int();
	this->m_keyDown = new int();
}

/********************************* GET *********************************/
GLuint CPaddle::GetQuadID() {
	return *this->m_quadID;
}

vec3 CPaddle::GetPosition() {
	return *this->m_position;
}

vec3 CPaddle::GetVelocity() {
	return *this->m_velocity;
}

int CPaddle::GetKeyUp() {
	return *this->m_keyUp;
}

int CPaddle::GetKeyDown() {
	return *this->m_keyDown;
}

/********************************* SET *********************************/
void CPaddle::SetQuadID(GLuint a_quadID) {
	*this->m_quadID = a_quadID;
}

void CPaddle::SetPosition(vec3 a_position) {
	*this->m_position = a_position;
}

void CPaddle::SetVelocity(vec3 a_velocity) {
	*this->m_velocity = a_velocity;
}

void CPaddle::SetKeyUp(int a_upKey) {
	*this->m_keyUp = a_upKey;
}

void CPaddle::SetKeyDown(int a_downKey) {
	*this->m_keyDown = a_downKey;
}

/******************************* Utility *******************************/
void CPaddle::Draw(Camera* a_activeCamera) {
	mat4 MVPMatrix = a_activeCamera->GetProjectionMatrix() * a_activeCamera->GetViewMatrix() * RenderQuad(GetQuadID(), GetPosition(), vec3(0.05f, 0.7f,0.0f));
	glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
}

void CPaddle::Update(float a_deltaTime) {
	vec3 pos = this->GetPosition();
	vec3 velocity = this->GetVelocity();
	// KEY PRESSES
	if (glfwGetKey(window, GetKeyUp()) == GLFW_PRESS) {
		pos.y += 2.0f * a_deltaTime;
		velocity.y = 0.5f;

	}
	if (glfwGetKey(window, GetKeyDown()) == GLFW_PRESS) {
		pos.y -= 2.0f * a_deltaTime;
		velocity.y = -0.5f;
	}

	if (glfwGetKey(window, GetKeyDown()) != GLFW_PRESS && glfwGetKey(window, GetKeyUp()) != GLFW_PRESS) {
		velocity.y = 0.0f;
	}

	// STAY ON SCREEN
	if (pos.y > 1.3f) {
		pos.y = 1.3f;
	}
	if (pos.y < -1.3f) {
		pos.y = -1.3f;
	}

	SetPosition(pos);
	SetVelocity(velocity);
}

