// System.Object.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Application.h"
#include "System.Camera.h"

class Object {
	public:
		Object();

		virtual ~Object();
		virtual void Update(const float& a_delatTime);
		virtual void Render(Camera* a_camera);

		void SetPosition(vec3 a_position);
		void SetScale(vec3 a_scale);

		vec3 GetPosition();
		float GetLeftX();
		float GetRightX();
		float GetTopY();
		float GetBottomY();
		GLuint LoadBMP(const char* a_imagePath);
		void LoadTriangles(const GLuint& a_numRows, const GLuint& a_numColoumns, const GLenum& a_renderMode);
	protected:
		vec3 position, scale;
	private:
		float m_leftX, m_rightX, m_topY, m_bottomY;
		mat4 Render();
		GLuint m_numIndices;
		GLuint m_vertexBufferID;
		GLenum m_renderMode;
};