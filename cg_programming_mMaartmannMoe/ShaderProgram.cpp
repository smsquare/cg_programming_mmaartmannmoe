// ShaderProgram.cpp
//////////////////////////////////////////////////////////////////////////

#include "ShaderProgram.h"

CShaderProgram::CShaderProgram() {
	this->m_bLinked = false;
}
/*------------------------------
Name:	CreateProgram
Params:	none
Result:	Creates a new program.
/*----------------------------*/
void CShaderProgram::CreateProgram() {
	this->m_uiProgram = glCreateProgram();
}

/*-----------------------------------------
Name:	DeleteProgram		  
Params:	none				  
Result:	Deletes program and frees memory.
/*---------------------------------------*/
void CShaderProgram::DeleteProgram() {
	if (!this->m_bLinked) return;
	this->m_bLinked = false;
	glDeleteProgram(this->m_uiProgram);
}	

/************************************************************************
Name:	AddShaderToProgram
Params: a_pShader: pointer to a shader object that you would like to add
Result: Adds the shader to the program.
************************************************************************/
bool CShaderProgram::AddShaderToProgram(CShader* a_pShader) {
	if (!a_pShader->IsLoaded()) return false;
	glAttachShader(m_uiProgram, a_pShader->GetShaderID());
	return true;
}

/*************************************************
Name:	LinkProgram
Params:	none
Result: Performs final linkage of OpenGL program.
*************************************************/
bool CShaderProgram::LinkProgram() {
	fprintf(stdout, "Linking program\n");
	glLinkProgram(m_uiProgram);
	int iLinkStatus;
	// Check the program
	glGetProgramiv(m_uiProgram, GL_LINK_STATUS, &iLinkStatus);
	m_bLinked = iLinkStatus == GL_TRUE;
	return m_bLinked;
}

/***********************************
Name:	UseProgram
Params: none
Result: If linked, use the program.
***********************************/
void CShaderProgram::UseProgram() {
	if (m_bLinked) glUseProgram(m_uiProgram);
}

/*************************************************
Name:	GetProgramID
Params:	none
Result: Returns the program ID.
*************************************************/
GLuint CShaderProgram::GetProgramID() {
	return this->m_uiProgram;
}