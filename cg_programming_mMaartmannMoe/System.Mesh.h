// System.Mesh.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include "Application.h"
#include "System.Transform.h"
#include "System.Camera.h"
#include "System.Render.h"
#include "ShaderProgram.h"

class CVertex {
public:
	CVertex(const CVertex& a_vertex);
	CVertex(float a_x, float a_y, float a_z);	// TODO: Add texture UV's
	float x, y, z, w;
};

class CMesh {
public:
	CMesh();
	~CMesh();
	
	CTransform transform;
	vector<CVertex*> vertices;

	void AddVertex(const CVertex& a_vertex);
	void Scale(float a_amount);
	void Build();
	void Render(Camera* a_camera);
	GLuint m_vertexArrayObjectID;
	GLuint m_vertexBufferObjectID;
private:

	CShaderProgram* m_material;
	int* m_numQuads;
};

