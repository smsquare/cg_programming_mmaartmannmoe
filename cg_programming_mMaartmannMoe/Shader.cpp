// Shader.cpp
//////////////////////////////////////////////////////////////////////////

#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

CShader::CShader() {
	m_bLoaded = false;
	m_Result = GL_FALSE;
}

/*************************************************************
Name:	LoadShader
Params:	a_csFilePath - path to file
		a_iType		 - GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
Result: Loads and compiles shader.
**************************************************************/
bool CShader::LoadShader(const char* a_csFilePath, int a_iType) {
	// Create the shader
	m_uiShader = glCreateShader(a_iType);
	// Read the shader code from file
	std::string strShaderCode =	ReadShaderFromFile(a_csFilePath);
	// Compile the shader
	CompileShader(strShaderCode, a_csFilePath);
	// Check the status of the shader
	CheckShader();
	return 1;
}

/****************************************
Name:	DeleteShader
Params:	None...
Result: Deletes shader and frees memory.
****************************************/
void CShader::DeleteShader() {
	if (!IsLoaded()) return;
	this->m_bLoaded = false;
	glDeleteShader(this->m_uiShader);
}

/*************************************************
Name:	ReadShaderFromFile
Params:	a_csFilePath - path to the file
Result: Reads the shader code in from the file and
		returns a string of the file.
**************************************************/
std::string CShader::ReadShaderFromFile(const char* a_csFilePath) {
	std::string strShaderCode;
	std::ifstream shaderStream (a_csFilePath, std::ios::in);
	if (shaderStream.is_open()) {
		std::string Line = "";
		while (std::getline(shaderStream, Line)) {
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	return strShaderCode;
}

/*************************************************************************
Name:	CompileShader
Params:	a_strShaderCode - string of the shader code
		a_csFilePath	- const char* of the file path of the shader code.
Result: Compiles the shader
**************************************************************************/
void CShader::CompileShader(std::string a_strShaderCode, const char* a_csFilePath) {
	printf("Compiling shader: %\n", a_csFilePath);
	const char * csShaderSourcePtr = a_strShaderCode.c_str();
	glShaderSource(m_uiShader, 1, &csShaderSourcePtr, NULL);
	glCompileShader(m_uiShader);
}

/************************************************************************
Name:	CheckShader
Params: None
Result: Checks the status of the shader AFTER attempting to compile.
		Logs any errors.
************************************************************************/
void CShader::CheckShader() {
	glGetShaderiv(m_uiShader, GL_COMPILE_STATUS, &m_Result);
	glGetShaderiv(m_uiShader, GL_INFO_LOG_LENGTH, &m_iInfoLogLength);
	std::vector<char> vcShaderErrorMessage(m_iInfoLogLength);
	glGetShaderInfoLog(m_uiShader, m_iInfoLogLength, NULL, &vcShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &vcShaderErrorMessage[0]);
}
/**********************************************
Name:	IsLoaded
Params:	None
Result: True if shader was loaded and compiled.
***********************************************/
bool CShader::IsLoaded() {
	return this->m_bLoaded;
}

/****************************************
Name:	GetShaderID
Params:	none
Result: Returns ID of a generated shader.
*****************************************/
GLuint CShader::GetShaderID() {
	return this->m_uiShader;
}