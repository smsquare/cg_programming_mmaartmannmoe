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