#pragma once

#include <GLFW/glfw3.h>

#include "stb_image.h"

class Texture
{
private:
	GLuint id_;
	GLsizei width_;
	GLsizei height_;

public:
	Texture();
	Texture(GLuint id, GLsizei width, GLsizei height);

	void SetId(GLuint id);
	void SetWidth(unsigned int width);
	void SetHeight(unsigned int height);

	GLuint GetId();
	unsigned int GetWidth();
	unsigned int GetHeight();
};
