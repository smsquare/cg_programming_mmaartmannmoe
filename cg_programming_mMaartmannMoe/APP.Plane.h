// APP.Plane.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Application.h"
#include "System.Object.h"

class Plane : public Object {
	public:
		Plane(GLuint a_width, GLuint a_height);
		virtual ~Plane();

	private:
		GLuint m_width, m_height;
};