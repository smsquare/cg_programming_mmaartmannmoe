// main.cpp
//////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "Shader.h"
#include "ShaderProgram.h"

GLFWwindow* window = NULL;

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

// TODO: NEED TO MAKE A MORE FLEXIBLE VERSION W/ PARAMS.
/************************************************************************
Name:	CreateVao
Params:	none
Result: Sets up the VAO's for the scene.
************************************************************************/
GLuint uiVAO[2];
void CreateVAO() {																			
	glGenVertexArrays(2, uiVAO);
}

// TODO: NEED TO MAKE A MORE FLEXIBLE VERSION W/ PARAMS.
/************************************************************************
Name:	CreateVBO
Params:	none.
Result: Sets up the VBO's for the scene.
************************************************************************/
GLuint uiVBO[4];
void CreateVBO() {																		
	// Generate 4 buffers, put the resulting identifier in uiVBO									
	glGenBuffers(4, uiVBO);
}

/************************************************************************
Name:	InitScene
Params:	none
Result: Sets up the info needed for the OpenGL scene.
************************************************************************/
// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f
};

float fTriangle[9];		// Triangle verts
float fQuad[12];		// Quad verts
float fTriangleColor[9];
float fQuadColor[12];	

CShader shVertex, shFragment;
CShaderProgram spMain;
void InitScene() {
	// Change the background color
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Setup triangle verts
	fTriangle[0] = -0.4f; fTriangle[1] = 0.1f; fTriangle[2] = 0.0f;
	fTriangle[3] = 0.4f;  fTriangle[4] = 0.1f; fTriangle[5] = 0.0f;
	fTriangle[6] = 0.0f;  fTriangle[7] = 0.7f; fTriangle[8] = 0.0f;

	// Setup triangle color
	fTriangleColor[0] = 1.0f; fTriangleColor[1] = 0.0f; fTriangleColor[2] = 0.0f;
	fTriangleColor[3] = 0.0f; fTriangleColor[4] = 1.0f; fTriangleColor[5] = 0.0f;
	fTriangleColor[6] = 0.0f; fTriangleColor[7] = 0.0f; fTriangleColor[8] = 1.0f;

	// Setup quad verts
	fQuad[0] = -0.2f; fQuad[1] = -0.1f; fQuad[2] = 0.0f;
	fQuad[3] = -0.2f; fQuad[4] = -0.6f; fQuad[5] = 0.0f;
	fQuad[6] = 0.2f; fQuad[7] = -0.1f; fQuad[8] = 0.0f;
	fQuad[9] = 0.2f; fQuad[10] = -0.6f; fQuad[11] = 0.0f;

	// Setup quad color
	fQuadColor[0] = 1.0f; fQuadColor[1] = 0.0f; fQuadColor[2] = 0.0f;
	fQuadColor[3] = 0.0f; fQuadColor[4] = 1.0f; fQuadColor[8] = 0.0f;
	fQuadColor[6] = 0.0f; fQuadColor[7] = 0.0f; fQuadColor[5] = 1.0f;
	fQuadColor[9] = 1.0f; fQuadColor[10] = 1.0f; fQuadColor[11] = 0.0f;

	// Generate two VAO's; one for the triangle and one for the quad.
	CreateVAO();
	// Generate 4 VBO's
	CreateVBO();
	// Setup whole triangle
	glBindVertexArray(uiVAO[0]);	// VAO of tri
	// Bind vert info
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), fTriangle, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0, 			// attribute 0. No particular reason for 0, but MUST match layout in shader.
		3,			// size
		GL_FLOAT, 	// type
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)0	// array buffer offset
		);
	// Bind color info
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), fTriangleColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Setup whole quad
	glBindVertexArray(uiVAO[1]);	// VAO of quad
	// Bind vert info
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), fQuad, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Bind color info
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[3]);
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), fQuadColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Load shaders and create shader program.
	shVertex.LoadShader("Shaders/SimpleVertexShader.vertexshader", GL_VERTEX_SHADER);
	shFragment.LoadShader("Shaders/SimpleFragmentShader.fragmentshader", GL_FRAGMENT_SHADER);

	spMain.CreateProgram();
	spMain.AddShaderToProgram(&shVertex);
	spMain.AddShaderToProgram(&shFragment);

	spMain.LinkProgram();
	spMain.UseProgram();

	shVertex.DeleteShader();
	shFragment.DeleteShader();
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Draw the triangle!
	glBindVertexArray(uiVAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0
	
	glBindVertexArray(uiVAO[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0 ,4);
	/* Swap front and back buffers */
	glfwSwapBuffers(window);
}

int main() {
	// Initialize GLFW, window, GLEW...
	// Compare with bitwise OR. If they all succeed then this step is skipped.
	if (InitWindowFailed() | InitGlewFailed()) {
		return EXIT_WITH_ERROR;
	}

	// Initialize all of the elements that are going to be used for drawing the scene.
	InitScene();

	/* MAIN GAME LOOP: Loop until the user closes the window or presses ESC */
	do {
		// Update phase; i.e. Update()...

		// Render phase
		Render();

		/* Poll for and process events */
		glfwPollEvents();
	} while ( // Check if the ESC key was pressed OR the window was closed...
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0
	);

	glfwTerminate();
	return 0;
}