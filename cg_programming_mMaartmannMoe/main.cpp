// main.cpp
//////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "LoadShader.h"

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f
};

int main() {

	/* Initialize the library */
	if (!glfwInit()) {
		fprintf( stderr, "Failed to initialize GLFW\n");
		return -1;
	} else {
		fprintf(stdout, "Initialized GLFW\n");
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
		fprintf(stderr, "ERROR: Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	} else {
		fprintf(stdout, "Created window...\n");
	}

	/* Make the window's context current*/
	// Initialize GLEW
	glfwMakeContextCurrent(window);
	glewExperimental = true; // Needed in core profile
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		/* Problem: glewInit failed!!! */
		fprintf(stderr, "ERROR %s: Failed to initialize GLEW.\n", glewGetErrorString(err));
		return -1;
	} else {
		fprintf(stdout, "Initialized GLEW...\n");
	}

	///////////////////////// WEEK 02 /////////////////////////////////////////////////////////////////////
	// Create a Vertex Array Object; Set as current one...												
	GLuint VertexArrayID;																				
	glGenVertexArrays(1, &VertexArrayID);																
	glBindVertexArray(VertexArrayID);																	
																										
	// This will identify our vertex buffer																
	GLuint vertexBuffer;																				
																										
	// Generate 1 buffer, put the resulting identifier in vertexBuffer									
	glGenBuffers(1, &vertexBuffer);																		
																										
	// Bind the vertexBuffer...																			
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);														
																										
	// Give vertices to OpenGL...																		
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);	
	

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("Shaders/SimpleVertexShader.vertexshader", "Shaders/SimpleFragmentShader.fragmentshader");

	// Change the background color
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// End WEEK 02 ////////////////////////////////////////////////////////////////////////////////////////
	
	/* Loop until the user closes the window or presses ESC */
	do {
		/* Render Here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
			0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0
		);

		glUseProgram(programID);

		// Draw the triangle!
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0
		glDisableVertexAttribArray(0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			fprintf(stdout, "ESC pressed! Exiting program!\n");
		}

	} // Check if the ESC key was pressed OR the window was closed...
	while ( 
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0
	);

	glfwTerminate();
	return 0;
}