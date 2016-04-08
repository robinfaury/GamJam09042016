#pragma once

#include <GLFW/glfw3.h>

#include "stb_image.h"

class Texture
{
public:
	GLuint id_;
	GLsizei width_;
	GLsizei height_;

public:
	Texture();
	Texture(GLuint id, GLsizei width, GLsizei height);
};
