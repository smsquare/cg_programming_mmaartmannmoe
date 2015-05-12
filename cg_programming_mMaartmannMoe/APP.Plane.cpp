// APP.Plane.cpp
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "APP.Plane.h"

Plane::Plane(GLuint a_width, GLuint a_height) : Object() {
	LoadTriangles(this->m_width = a_width, this->m_height = a_height, GL_TRIANGLE_STRIP);
}

Plane::~Plane() {

}