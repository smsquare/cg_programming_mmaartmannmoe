// System.Render.cpp
//////////////////////////////////////////////////////////////////////////

#include "System.Render.h"

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
