// Shader.h
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "Application.h"


/***************************************
Class: CShader
Purpose: Wraps OpenGL shader loading 
		 and compiling
***************************************/
class CShader {
	public:
		CShader();

		bool LoadShader(const char* a_csFilePath, int a_iType);
		void DeleteShader();
		std::string ReadShaderFromFile(const char* a_csFilePath);
		void CompileShader(std::string a_strShaderCode, const char* a_csFilePath);
		void CheckShader();

		bool IsLoaded();
		GLuint GetShaderID();

	private:
		GLuint m_uiShader;		// ID of shader
		int m_iType;			// GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
		bool m_bLoaded;			// Whether shader was loaded and compiled
		int m_iInfoLogLength;	// Length of log used during shader processing
		GLint m_Result;			// Used in checking shader status
};
