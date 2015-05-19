// System.Texture.cpp
//////////////////////////////////////////////////////////////////////////

#include "System.Texture.h"

CTexture::CTexture() {
	// Initialize texture ID
	this->m_textureID = 0;

	// Initialize texture dimensions
	this->m_textureWidth = 0;
	this->m_textureHeight = 0;
}
CTexture::~CTexture() {
	// Free texture data if needed
	FreeTexture();
}

/*  Pre Condition:
		-A valid OpenGL context
	Post Condition:
		-Creates a texture from the given pixels
		-Reports error to console if texture could not be created
	Side Effects:
		-Binds a NULL texture
*/
bool CTexture::LoadTextureFromPixels32(GLuint* a_pixels, GLuint a_width, GLuint a_height) {
	// Free texture if it exists
	FreeTexture();

	// Get texture dimensions
	this->m_textureWidth = a_width;
	this->m_textureHeight = a_height;

	// Generate texture ID
	glGenTextures(1, &this->m_textureID);

	// Bind texture ID
	glBindTexture(GL_TEXTURE_2D, this->m_textureID);

	// Generate Texture: assign pixels to our texture ID.
	glTexImage2D(
		GL_TEXTURE_2D,		// the texture target or the type of texture we're assigning the pixels to
		0,					// the mipmap level.
		GL_RGBA,			// the pixel format of how the texture is stored. OpenGL takes this as a suggestion, not an order
		a_width,			// texture width
		a_height,			// texture height
		0,					// texture border width
		GL_RGBA,			// the format of the pixel data you're assigning
		GL_UNSIGNED_BYTE,	// the data type for the pixel data you're assigning
		a_pixels			// the pointer address of the pixel data you're assigning
	);

	// Set texture parameters
	// GL_TEXTURE_MAG_FILTER && GL_TEXTURE_MIN_FILTER control how the texture is shown when it is magnified and minified respectively.
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	


	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, NULL);

	// Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		#ifdef _DEBUG
			fprintf(stderr, "Error loading texture from %p pixels!\n", a_pixels);
		#endif 
		return false;
	}
	return true;
}

void CTexture::FreeTexture() {
	// Delete texture
	if ( this->m_textureID != 0) {
		glDeleteTextures(1, &this->m_textureID);
		this->m_textureID = 0;
	}

	this->m_textureWidth = 0;
	this->m_textureHeight = 0;
}

void CTexture::Render(GLfloat a_x, GLfloat a_y) {
	// If the texture exists
	if (this->m_textureID != 0) {	
		// Remove any previous transformations
		glLoadIdentity();

		// Move to rendering point
		glTranslatef(a_x, a_y, 0.f);

		// Set texture ID
		glBindTexture(GL_TEXTURE_2D, this->m_textureID);

	}
}

//class CTexture {

//		
//		GLuint GetTextureID();
//		GLuint GetWidth();
//		GLuint GetHeight();
//	private:
//		// Texture Name
//		GLuint m_textureID;
//
//		// Texture dimensions
//		GLuint m_textureWidth;
//		GLuint m_textureHeight;
//};