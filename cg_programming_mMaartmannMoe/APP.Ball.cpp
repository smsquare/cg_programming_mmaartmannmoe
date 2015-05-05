// APP.Ball.cpp
//////////////////////////////////////////////////////////////////////////

#include "APP.Ball.h"
#include "System.LoadScene.h"
#include "System.Utility.h"

CBall::CBall() {
	this->m_quadID = new GLuint();
	this->m_position = new vec3(0.0f, 0.0f, 0.0f);
	this->m_velocity = new vec3(0.0f, 0.0f, 0.0f);
	this->m_scale = new vec3(0.05f);
}

/********************************* GET *********************************/
GLuint CBall::GetQuadID() {
	return *this->m_quadID;
}

vec3 CBall::GetPosition() {
	return *this->m_position;
}

vec3 CBall::GetVelocity() {
	return *this->m_velocity;
}

/********************************* SET *********************************/
void CBall::SetQuadID(GLuint a_quadID) {
	*this->m_quadID = a_quadID;
}

void CBall::SetPosition(vec3 a_position) {
	*this->m_position = a_position;
}

void CBall::SetVelocity(vec3 a_velocity) {
	*this->m_velocity = a_velocity;
}

/******************************* Utility *******************************/
void CBall::Draw(Camera* a_activeCamera) {
	mat4 MVPMatrix = a_activeCamera->GetProjectionMatrix() * a_activeCamera->GetViewMatrix() * RenderQuad(GetQuadID(), GetPosition(), vec3(0.05f));
	glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
}

void CBall::Update(float a_deltaTime, CPaddle* leftPaddle, CPaddle* rightPaddle) {
	vec3 pos = GetPosition();
	vec3 velocity = GetVelocity();

	pos += velocity * a_deltaTime;

	// Right wall
	if (pos.x > 2.225f) {
		pos.x = 2.225f;
		velocity = CalculateReflectionVector(velocity, vec3(-1.0f,0.0f,0.0));
	}
	// Left wall
	if (pos.x < -2.225f) {
		pos.x = -2.225f;
		velocity = CalculateReflectionVector(velocity, vec3(1.0f,0.0f,0.0));
	}

	// Top wall
	if (pos.y > 1.662f) {
		pos.y = 1.662f;
		velocity = CalculateReflectionVector(velocity, vec3(0.0f,-1.0f,0.0));
	}

	// Bottom wall
	if (pos.y < -1.662f) {
		pos.y = -1.662f;
		velocity = CalculateReflectionVector(velocity, vec3(0.0f,1.0f,0.0));
	}

	// TEST INPUT /////////////////////////////
	//if (glfwGetKey(window, GLFW_KEY_LEFT)) {
	//	pos.x -= 0.002;
	//}
	//if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
	//	pos.x += 0.002;
	//}
	//if (glfwGetKey(window, GLFW_KEY_UP)) {
	//	pos.y += 0.01;
	//}
	//if (glfwGetKey(window, GLFW_KEY_DOWN)) {
	//	pos.y -= 0.01;
	//}

	// Hits paddles
	int rightPaddleHit = IsBallHittingPaddle(rightPaddle);
	float rightDiffX = rightPaddle->GetPosition().x - pos.x;
	float rightLftCorrect = 0.051 - rightDiffX;
	float rightRtCorrect = 0.051 + rightDiffX;
	switch (rightPaddleHit)	{
		case (int)PADDLEHIT::LEFT:
			pos.x -= rightLftCorrect;
			velocity = CalculateReflectionVector(velocity, vec3(-1.0f,0.0f,0.0f));
			velocity += rightPaddle->GetVelocity();
			break;
		case (int)PADDLEHIT::RIGHT:
			pos.x += rightRtCorrect;
			velocity = CalculateReflectionVector(velocity, vec3(1.0f,0.0f,0.0f));
			velocity += rightPaddle->GetVelocity();
			break;
		case (int)PADDLEHIT::TOP:
			velocity = CalculateReflectionVector(velocity, vec3(0.0f,1.0f,0.0f));
			break;
		case (int)PADDLEHIT::BOTTOM:
			velocity = CalculateReflectionVector(velocity, vec3(0.0f,-1.0f,0.0f));
			break;
		case (int)PADDLEHIT::NOTHING:
			// No collision, do nothing
			break;
		default:
			break;
	}

	int leftPaddleHit = IsBallHittingPaddle(leftPaddle);
	float leftDiffY = leftPaddle->GetPosition().y - pos.y;
	float leftTopCorrect = 0.376 + leftDiffY;
	float leftBottomCorrect = 0.376 - leftDiffY;
	float leftDiffX = leftPaddle->GetPosition().x - pos.x;
	float leftLftCorrect = 0.051 - leftDiffX;
	float leftRtCorrect = 0.051 + leftDiffX;
	switch (leftPaddleHit) {
		case (int)PADDLEHIT::LEFT:
			pos.x -= leftLftCorrect;
			velocity = CalculateReflectionVector(velocity, vec3(-1.0f,0.0f,0.0f));
			velocity += leftPaddle->GetVelocity();
			break;
		case (int)PADDLEHIT::RIGHT:
			pos.x += leftRtCorrect;
			velocity = CalculateReflectionVector(velocity, vec3(1.0f,0.0f,0.0f));
			velocity += leftPaddle->GetVelocity();
			break;
		case (int)PADDLEHIT::TOP:
			velocity = CalculateReflectionVector(velocity, vec3(0.0f,1.0f,0.0f));
			break;
		case (int)PADDLEHIT::BOTTOM:
			velocity = CalculateReflectionVector(velocity, vec3(0.0f,-1.0f,0.0f));
			break;
		case (int)PADDLEHIT::NOTHING:

			break;
		default:
			break;
	}
	SetPosition(pos);
	SetVelocity(velocity);
}



int CBall::IsHittingWhatSide(CPaddle* paddle) {
	vec3 paddlePos = paddle->GetPosition(); 
	vec3 ballPos = this->GetPosition();
	if (ballPos.x > (paddlePos.x - 0.035) && ballPos.x < (paddlePos.x + 0.035)) {
		if (ballPos.y > 0.345 + paddlePos.y) {
			fprintf(stdout, "hitting top");
			return (int)PADDLEHIT::TOP;
		} else if (ballPos.y < -0.345 + paddlePos.y) {
			fprintf(stdout, "hitting bottom");
			return (int)PADDLEHIT::BOTTOM;
		}
	} 
	else if (ballPos.x > paddlePos.x) {
		fprintf(stdout, "hitting right");
		return (int)PADDLEHIT::RIGHT;
	} else {
		fprintf(stdout, "hitting left");
		return (int)PADDLEHIT::LEFT;
	}
}

int CBall::IsBallHittingPaddle(CPaddle* paddle) {
	vec3 ballPos = this->GetPosition();
	vec3 paddlePos = paddle->GetPosition();

	// Less than the top
	if (ballPos.y < (paddlePos.y + 0.375)) {
		// Greater than the bottom
		if (ballPos.y > (paddlePos.y - 0.375)) {
			// Greater than the left
			if (ballPos.x > (paddlePos.x - 0.05)) {
				// Less than the right
				if (ballPos.x < paddlePos.x + 0.05) {
					return IsHittingWhatSide(paddle);
				}
			}
		}		
	}

	return (int)PADDLEHIT::NOTHING;
}

void CBall::BuildBall() {
	//GLfloat g_vertex_buffer_data[] = {
	//	0.0f, 0.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f,
	//	1.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f,
	//	1.0f, 1.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f
	//};

	//// Center square
	//for (int i = 0, size = 18; i < size; ++i) {
	//	g_vertex_buffer_data[i] -= 0.5f;
	//}
	//for (int n = 0; n < 18;n += 3) {
	//	CVertex* v = new CVertex(g_vertex_buffer_data[n+0], g_vertex_buffer_data[n+1], g_vertex_buffer_data[n+2]);
	//	this->mesh.AddVertex(*v);
	//}
}