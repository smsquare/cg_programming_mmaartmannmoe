// ShaderProgram.h
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "Application.h"
#include "Shader.h"

/***********************************
Class:	CShaderProgram
Purpose: Wraps OpenGL shader program
		 and make its usage easy.
***********************************/
class CShaderProgram {
	public:
		CShaderProgram();

		void CreateProgram();
		void DeleteProgram();

		bool AddShaderToProgram(CShader* a_pShader);
		bool LinkProgram();
		void UseProgram();

	private:
		GLuint m_uiProgram;	// ID of Program
		bool m_bLinked;		// Whether program is linked and ready to use. 
};