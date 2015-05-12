// System.LoadScene.cpp
//////////////////////////////////////////////////////////////////////////

#include "System.LoadScene.h"

CShader shVertex;
CShader shFragment;
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

GLuint MVPMatrixID;
Camera* camMain = new Camera();
GLuint quadID;

void LoadScene() {
	GLuint vertexArrayID = 0;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Create and compile GLSL program from shaders...
	LoadShaders();

	// Get variable from shader
	MVPMatrixID = glGetUniformLocation(spMain.GetProgramID(), "MVP");
			
	spMain.UseProgram();
	// Setup main camera
	camMain->SetAspectRatio(SCREEN_WIDTH, SCREEN_HEIGHT);
	camMain->SetProjectionMatrix(FIELD_OF_VIEW, camMain->GetAspectRaio(), Z_NEAR, Z_FAR);
	camMain->SetPosition(vec3(0, 0, 3));
	camMain->SetViewMatrix();
	camMain->MVPMatrixID = glGetUniformLocation(spMain.GetProgramID(), "MVP");
	// Load quad info
	quadID = LoadQuad();
}