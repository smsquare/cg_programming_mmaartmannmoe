// APP.Initialize.cpp
//////////////////////////////////////////////////////////////////////////

#include "APP.Initialize.h"
// Initializes GLFW and the window to be the primary OpenGL context.
// Returns: EXIT_WITH_ERROR if fails; EXIT_WITH_SUCCESS if succeeds
//			since InitWindowFailed && InitGlewFailed are being compared 
//			bitwise in an if statement.
int InitWindowFailed() {
	/* Initialize the library */
	if (glfwInit() == GLFW_FAIL) {
		fprintf( stderr, "Failed to initialize GLFW\n");
		return EXIT_WITH_ERROR;
	}
	fprintf(stdout, "Initialized GLFW...\n");

	// Define some properties of the window being created...
	glfwWindowHint(GLFW_SAMPLES, 4);								// 4x anti-aliasing - AA
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					// Want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);			// Make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// We don't want the old OpenGL

	/* Create a windowed mode window and its OpenGL context */

	window = glfwCreateWindow(1024, 768, "Main Window", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "ERROR: Failed to open GLFW window.\n");
		glfwTerminate();
		return EXIT_WITH_ERROR;
	} 

	// Make context current
	glfwMakeContextCurrent(window);

	// Ensure we can capture the escape key being pressed below.
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	fprintf(stdout, "Created window...\n");

	return EXIT_WITH_SUCCESS;
}

int InitGlewFailed() {
	glewExperimental = true; // Needed in core profile...
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "ERROR %s: Failed to initialize GLEW.\n", glewGetErrorString(err));
		return EXIT_WITH_ERROR;
	} else {
		fprintf(stdout, "Initialized GLEW...\n");
		return EXIT_WITH_SUCCESS;
	}
}
