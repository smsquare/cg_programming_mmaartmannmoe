// System.Mesh.cpp
//////////////////////////////////////////////////////////////////////////

#include "System.Mesh.h"
#include "System.LoadScene.h"

CVertex::CVertex(const CVertex& a_vertex) {
	this->x = a_vertex.x;
	this->y = a_vertex.y;
	this->z = a_vertex.z;
	this->w = 1.0;
}

CVertex::CVertex(float a_x, float a_y, float a_z) {
	this->x = a_x;
	this->y = a_y;
	this->z = a_z;
	this->w = 1.0;
}

CMesh::CMesh () {

}

CMesh::~CMesh () {
}

void CMesh::AddVertex(const CVertex& a_vertex) {
	CVertex* vert = new CVertex(a_vertex);
	this->vertices.push_back(vert);
}

void CMesh::Scale(float a_amount) {
	for(int n = 0; n < this->vertices.size(); n++) {
		CVertex* p = this->vertices[n];
		p->x *= a_amount;
		p->y *= a_amount;
		p->z *= a_amount;
	}
}

void CMesh::Build() {
	// Generate VertexBufferObjectID
	glGenBuffers(1, &this->m_vertexBufferObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_vertexBufferObjectID);
	// Generate a GLfloat[numVerts * numElemetsPerVertex] to fill with mesh data
	int numVertices = this->vertices.size();
	int numElementsPerVertex = 4;	// (x, y, z, w) TODO: add texture UV's
	
	GLfloat* quads = new GLfloat[numVertices * numElementsPerVertex];
	for (int n = 0, m = 0; n < numVertices; n++, m += numElementsPerVertex) {
		CVertex* v = this->vertices[n];
		quads[m + 0] = v->x;
		quads[m + 1] = v->y;
		quads[m + 2] = v->z;
		quads[m + 3] = v->w;

	}
	// Attach the buffer data
	glBufferData(GL_ARRAY_BUFFER, numVertices * numElementsPerVertex * sizeof(float), quads, GL_STATIC_DRAW);
	
	// Generate VertexArrayObjectID
	glGenVertexArrays(1, &this->m_vertexArrayObjectID);
	glBindVertexArray(this->m_vertexArrayObjectID);
	// Vertex Attrib Pointer
	glVertexAttribPointer(
		0,			//attribute layout
		3,			//Elements in array
		GL_FLOAT,	//Each element is of type float
		GL_FALSE,	//Normalized?
		0,			//Stride...
		(void*)0	//Array buffer offset...
		);
	// Enable Vertex Attrib
	glEnableVertexAttribArray(0);
	delete [] quads;
}

void CMesh::Render(Camera* a_camera) {
	// Get variable from shader
	GLuint MVPMatrixID = glGetUniformLocation(spMain.GetProgramID(), "MVP");

	mat4 MVPMatrix = a_camera->GetProjectionMatrix() * a_camera->GetViewMatrix() * RenderQuad(this->m_vertexBufferObjectID, vec3(this->transform.x, this->transform.y, this->transform.z), vec3(0.05f));
	glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
}