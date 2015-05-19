// System.Texture.h
//////////////////////////////////////////////////////////////////////////
#pragma once

// EXAMPLE OF ALTERNATE INIT ONCE METHOD
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Application.h"

class CTexture {
	public:
		CTexture();
		~CTexture();

		bool LoadTextureFromPixels32(GLuint* a_pixels, GLuint a_width, GLuint a_height);
		void FreeTexture();
		void Render(GLfloat x, GLfloat y);
		GLuint GetTextureID();
		GLuint GetWidth();
		GLuint GetHeight();
	private:
		// Texture Name
		GLuint m_textureID;

		// Texture dimensions
		GLuint m_textureWidth;
		GLuint m_textureHeight;
};

#endif