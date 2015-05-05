// System.LoadScene.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "System.Camera.h"
#include "Shader.h"
#include "ShaderProgram.h"

extern CShader shVertex;
extern CShader shFragment;
extern CShaderProgram spMain;

extern GLuint MVPMatrixID;

extern Camera* camMain;

extern GLuint quadID;

void LoadShaders();
GLuint& LoadQuad();

void LoadScene();