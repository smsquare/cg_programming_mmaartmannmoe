// Application.h
//////////////////////////////////////////////////////////////////////////
#pragma once

// Standard headers...
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <stdexcpt.h>
#include <cmath>

// OpenGL includes: glew, glfw, glm
#define GLEW_STATIC
// ALWAYS include glew.h BEFORE bl.h AND glfw3.h
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// GLM provides OpenGL mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Namespaces...
using namespace std;
using namespace glm;

// Defines...
#define APP_NAME "My First Window"
#define EXIT_WITH_ERROR -1
#define EXIT_WITH_SUCCESS 0
#define OPEN_GL_VERSION_MAJOR 3		// Specifies OpenGL 3.3
#define OPEN_GL_VERSION_MINOR 3
#define ANTIALIASING 4				// Nx anti-aliasing
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define GLFW_FAIL 0

// Camera defines
#define FIELD_OF_VIEW 45.0f
#define Z_NEAR 0.1f
#define Z_FAR 100.0f

#define _DEBUG

// External Globals...
extern GLFWwindow* window;
extern GLint shaderStatus;
extern bool activeRef;
