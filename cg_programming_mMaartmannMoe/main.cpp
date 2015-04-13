// main.cpp
//////////////////////////////////////////////////////////////////////////

#include "Application.h"

// For display console messages
#include <stdio.h>
#include <stdlib.h>

// OpenGL includes: glew, glfw, glm
#define GLEW_STATIC
// ALWAYS include glew.h BEFORE bl.h AND glfw3.h
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

int main() {

	/* Initialize the library */
	if (!glfwInit()) {
		fprintf( stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// Define some properties of the window being created...
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x anti-aliasing - AA
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
	
	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "Main Window", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current*/
	// Initialize GLEW
	glfwMakeContextCurrent(window);
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	/* Loop until the user closes the window */
	do {
		/* Render Here */

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	} // Check if the ESC key was pressed OR the window was closed...
	while ( 
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0
	);

	glfwTerminate();
	return 0;
}