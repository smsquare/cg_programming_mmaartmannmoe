// main.cpp
//////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "LoadShader.h"

GLFWwindow* window = NULL;

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f
};

// Initializes GLFW and the window to be the primary OpenGL context.
// Returns: EXIT_WITH_ERROR if fails; EXIT_WITH_SUCCESS if succeeds.
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

	// Change the background color
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

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

void CreateVAO() {
	GLuint VertexArrayID;																				
	glGenVertexArrays(1, &VertexArrayID);																
	glBindVertexArray(VertexArrayID);		
}

GLuint g_vertexBuffer;	// Global vertex buffer
void CreateVBO() {																		
	// Generate 1 buffer, put the resulting identifier in vertexBuffer									
	glGenBuffers(1, &g_vertexBuffer);																		
																										
	// Bind the vertexBuffer...																			
	glBindBuffer(GL_ARRAY_BUFFER, g_vertexBuffer);														
																										
	// Give vertices to OpenGL...																		
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);	
}

void Render(GLuint vbo, GLuint program) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(
		0, 			// attribute 0. No particular reason for 0, but MUST match layout in shader.
		3,			// size
		GL_FLOAT, 	// type
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)0	// array buffer offset
	);
	
	glUseProgram(program);
	
	// Draw the triangle!
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0
	glDisableVertexAttribArray(0);
	
	/* Swap front and back buffers */
	glfwSwapBuffers(window);
}

int main() {
	// Initialize GLFW, window, GLEW...
	// Compare with bitwise OR. If they all succeed then this step is skipped.
	if (InitWindowFailed() | InitGlewFailed()) {
		return EXIT_WITH_ERROR;
	}

	// Create a Vertex Array Object; Set as current one...
	CreateVAO();

	// Create a Vertex Buffer Object; Set as current one...
	CreateVBO();

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("Shaders/SimpleVertexShader.vertexshader", "Shaders/SimpleFragmentShader.fragmentshader");

	/* MAIN GAME LOOP: Loop until the user closes the window or presses ESC */
	do {
		// Update phase; i.e. Update()...

		// Render phase
		Render(g_vertexBuffer, programID);

		/* Poll for and process events */
		glfwPollEvents();
	} while ( // Check if the ESC key was pressed OR the window was closed...
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0
	);

	glfwTerminate();
	return 0;
}