// System.Mesh.cpp
//////////////////////////////////////////////////////////////////////////

#include "System.Mesh.h"
/************************************************************************
Name:	BuildMesh
Params:	a_sizeX: number of squares in x dir
		a_sizeY: number of squares in y dir
Result: Creates an array of vec3's containing vertex position information
		Used to generate data for the VBO.
************************************************************************/
vec3* CMesh::BuildMesh(int a_sizeX, int a_sizeY) {
	int numIndex = ((((2*a_sizeX) + 3) * a_sizeY) + (a_sizeY-1));
	vec3 *squares = new vec3[numIndex];

	int y = a_sizeY;
	for (int row = 0; row < a_sizeY; row++) {
		for (int sqInd = 0; sqInd < a_sizeX; sqInd++) {
			// 0 index:
			if (sqInd == 0) {
				// row offset: (row * ((2*a_sizeX)+4)) 
				squares[(row * ((2*a_sizeX)+4)) + 0] = vec3(0.0f, (GLfloat)y, 0.0f);
				squares[(row * ((2*a_sizeX)+4)) + 1] = vec3(0.0f, (GLfloat)(y-1), 0.0f);
			}
			squares[(row * ((2*a_sizeX)+4)) +(2*sqInd) + 2] = vec3(1.0f+sqInd, (GLfloat)y, 0.0f);
			squares[(row * ((2*a_sizeX)+4)) +(2*sqInd) + 3] = vec3(1.0f+sqInd, (GLfloat)(y-1), 0.0f);
		} 
		// DoubleTap
		squares[(row * ((2*a_sizeX)+4)) +(2*a_sizeX)+2] = vec3(1.0f+(a_sizeX-1), (GLfloat)(y-1), 0.0f);

		if (y > 1) {
			// Double tap front before starting over
			squares[(row * ((2*a_sizeX)+4)) +(2*a_sizeX)+3] = vec3(0.0f, (GLfloat)(y-1), 0.0f);
		}
		y--;		
	}

	return squares;
}

