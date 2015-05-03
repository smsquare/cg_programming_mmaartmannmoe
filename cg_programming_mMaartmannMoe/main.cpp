// main.cpp
//////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "APP.Initialize.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "System.Utility.h"

GLFWwindow* window = NULL;

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

void DrawBall(const GLuint& a_quadID, const vec3& a_position, const mat4& a_projectionMatrix, const mat4& a_viewMatrix, const GLuint& a_MVPMatrixID) {
	mat4 MVPMatrix = a_projectionMatrix * a_viewMatrix * RenderQuad(a_quadID, a_position, vec3(0.05f));
	glUniformMatrix4fv(a_MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
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
		#ifdef _DEBUG
			fprintf(stdout, "Delta Time: %f\n", fDeltaTime);
		#endif	
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
		//mat4 MVPMatrix = projectionMatrix * viewMatrix * RenderQuad(quadID, ballPosition, vec3(0.05f));
		//glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
		DrawBall(quadID, ballPosition, projectionMatrix, viewMatrix, MVPMatrixID);

		// Render the paddle
		mat4 MVPMatrix = projectionMatrix * viewMatrix * RenderQuad(quadID, vec3(-1.0f,0.0f,0.0f), vec3(0.05f, 0.7f,0.0f));
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