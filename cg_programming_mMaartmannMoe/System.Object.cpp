// System.Object.cpp
//////////////////////////////////////////////////////////////////////////

#include "System.Object.h"
#include "System.Mesh.h"

Object::Object() {
	m_renderMode = GL_TRIANGLES;
	m_vertexBufferID = 0;
	SetPosition(vec3(0));
	SetScale(vec3(1));
	m_numIndices = 0;
}

Object::~Object() {

}

/********************************* SET *********************************/
void Object::SetPosition(vec3 a_position) {
	this->position = a_position;
}

void Object::SetScale(vec3 a_scale) {
	this->scale = a_scale;
}

/******************************* Utility *******************************/
/*
GLuint Object::LoadBMP(const char* a_imagePath) {
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(a_imagePath, "rb");
	if (!file) {
	#ifdef _DEBUG
		fprintf(stderr, "Image could not be opened.\n");
	#endif 
		return 0; // i.e. return that it failed
	}

	if (fread(header, 1, 54, file) != 54) {
	#ifdef _DEBUG
		fprintf(stderr, "Not a correct BMP file.\n");
	#endif 
		return 0; // i.e. return that it failed
	}


} */

void Object::LoadTriangles(const GLuint& a_numColoumns, const GLuint& a_numRows, const GLenum& a_renderMode) { 
	vec3* vertexBuffer = CMesh::BuildMesh(a_numColoumns, a_numRows);
	
	this->m_numIndices = ((((2*a_numColoumns) + 3) * a_numRows) + (a_numRows-1));
	fprintf(stdout, "x,y: %u, %u\n", a_numColoumns, a_numRows);
	fprintf(stdout, "test numIndices form: %u\n", m_numIndices);

	for (int i = 0; i < m_numIndices; i++) {
		fprintf(stdout, "index[%d]: %f, %f, %f\n", i, vertexBuffer[i].x, vertexBuffer[i].y, vertexBuffer[i].z);
	}

	this->m_renderMode = a_renderMode;
	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_numIndices, vertexBuffer, GL_STATIC_DRAW);
}

void Object::Update(const float& a_deltaTime) {
	m_leftX = position.x - scale.x;
	m_rightX = position.x + scale.x;
}

void Object::Render(Camera* a_camera) {
	mat4 modelMatrix = Render();
	mat4 MVPMatrix = a_camera->GetProjectionMatrix() * a_camera->GetViewMatrix() * modelMatrix;
	glUniformMatrix4fv(a_camera->MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
}

mat4 Object::Render() {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);

	glVertexAttribPointer(
		0,			//attribute layout
		3,			//Elements in array
		GL_FLOAT,	//Each element is of type float
		GL_FALSE,	//Normalized?
		0,			//Stride...
		(void*)0	//Array buffer offset...
	);

	glDrawArrays(m_renderMode, 0, m_numIndices); // GL_TRIANGLE_STRIP or GL_TRIANGLES
	glDisableVertexAttribArray(0);

	mat4 identityMatrix = mat4(1.0f);
	mat4 translateMatrix = translate(identityMatrix, position);
	mat4 modelMatrix = glm::scale(translateMatrix, scale);

	return modelMatrix;
}