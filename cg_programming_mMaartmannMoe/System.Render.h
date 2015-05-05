// System.Render.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Application.h"

mat4 RenderVertex(GLuint a_vertexBuffer, const vec3& a_position);
mat4 RenderQuad(GLuint a_vertexBuffer, const vec3& a_position, const vec3& a_scale);