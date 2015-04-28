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

CShader shVertex, shFragment;
CShaderProgram spMain;
void LoadShaders() {
	// Load shaders and create shader program.
	shVertex.LoadShader("Shaders/SimpleVertexShader.vertexshader", GL_VERTEX_SHADER);
	shFragment.LoadShader("Shaders/SimpleFragmentShader.fragmentshader", GL_FRAGMENT_SHADER);

	spMain.CreateProgram();
	spMain.AddShaderToProgram(&shVertex);
	spMain.AddShaderToProgram(&shFragment);

	spMain.LinkProgram();


	shVertex.DeleteShader();
	shFragment.DeleteShader();
}

GLuint& LoadQuad() {
	static GLfloat g_vertex_buffer_data[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	// Center square
	for (int i = 0, size = 18; i < size; ++i) {
		g_vertex_buffer_data[i] -= 0.5f;
	}

	GLuint vertexBuffer = 0;

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	return vertexBuffer;
}

mat4 RenderVertex(GLuint a_vertexBuffer, const vec3& a_position) {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, a_vertexBuffer);

	glVertexAttribPointer(
		0,			//attribute layout
		3,			//Elements in array
		GL_FLOAT,	//Each element is of type float
		GL_FALSE,	//Normalized?
		0,			//Stride...
		(void*)0	//Array buffer offset...
	);

	mat4 identityMatrix = mat4(1.0f);
	mat4 positionMatrix = translate(identityMatrix, a_position);
	return positionMatrix;
}

mat4 RenderQuad(GLuint a_vertexBuffer, const vec3& a_position, const vec3& a_scale) {

	mat4 scaleMatrix = mat4(
		a_scale.x, 0, 0, 0,
		0, a_scale.y, 0, 0,
		0, 0, a_scale.z, 0,
		0, 0, 0, 1
	);

	mat4 positionMatrix = RenderVertex(a_vertexBuffer, a_position);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);

	return positionMatrix * scaleMatrix;
}

float& GetDeltaTime() {
	static float fLastTime = glfwGetTime();

	float fNow = glfwGetTime();
	float fDeltaTime = fNow - fLastTime;

	fLastTime = fNow;
	return fDeltaTime;
}

int main() {
	// Initialize GLFW, window, GLEW...
	// Compare with bitwise OR. If they all succeed then this step is skipped.
	if (InitWindowFailed() | InitGlewFailed()) {
		return EXIT_WITH_ERROR;
	}

	GLuint vertexArrayID = 0;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Create and compile GLSL program from shaders...
	LoadShaders();

	// Get variable from shader
	GLuint MVPMatrixID = glGetUniformLocation(spMain.GetProgramID(), "MVP");

	// Setup camera
	float aspectRatio = SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	mat4 projectionMatrix = perspective(FIELD_OF_VIEW, aspectRatio, Z_NEAR, Z_FAR);

	// Load quad info

	GLuint quadID = LoadQuad();

	/* MAIN GAME LOOP: Loop until the user closes the window or presses ESC */
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Get delta time...
		float fDeltaTime = GetDeltaTime();
		fprintf(stdout, "Delta Time: %f\n", fDeltaTime);

		spMain.UseProgram();
		// Update phase; i.e. Update()...

		// Initialize position data...
		static vec3 ballPosition = vec3(0);
		static vec3 ballVelocity = vec3(1.0f, 0.0f, 0.0f);
		ballPosition += ballVelocity * fDeltaTime;

		if (ballPosition.x > 1.4f) {
			ballPosition.x = 1.4f;
			ballVelocity.x = -ballVelocity.x;
		}
		else if (ballPosition.x < -1.4f) {
			ballPosition.x = -1.4f;
			ballVelocity.x = -ballVelocity.x;
		}

		// Camera
		vec3 cameraPos = vec3(0,0,3);
		vec3 worldOrigin = vec3(0,0,0);
		vec3 upVector = vec3(0,1,0);
		mat4 viewMatrix = lookAt(
			cameraPos,		// Camera is at (0,0,3) in world space
			worldOrigin,	// and looks at the origin
			upVector		// Head is up (set to 0,-1,0 to look upside down)
		);

		// Render the ball...
		mat4 MVPMatrix = projectionMatrix * viewMatrix * RenderQuad(quadID, ballPosition, vec3(0.05f));
		glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
		// Render the paddle
		MVPMatrix = projectionMatrix * viewMatrix * RenderQuad(quadID, vec3(-1.0f,0.0f,0.0f), vec3(0.05f, 0.7f,0.0f));
		glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
		// Render the paddle
		MVPMatrix = projectionMatrix * viewMatrix * RenderQuad(quadID, vec3(1.0f,0.0f,0.0f), vec3(0.05f, 0.7f,0.0f));
		glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	} while ( // Check if the ESC key was pressed OR the window was closed...
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0
	);

	glfwTerminate();
	return 0;
}