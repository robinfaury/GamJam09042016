#include "Texture.h"

Texture::Texture()
	: id_(0)
	, width_(0)
	, height_(0) {}

Texture::Texture(GLuint id, GLsizei width, GLsizei height)
	: id_(id)
	, width_(width)
	, height_(height) {}

void Texture::SetId(GLuint id)
{
	id_ = id;
}

void Texture::SetWidth(unsigned int width)
{
	width_ = width;
}

void Texture::SetHeight(unsigned int height)
{
	height_ = height;
}

GLuint Texture::GetId()
{
	return id_;
}

unsigned int Texture::GetWidth()
{
	return width_;
}

unsigned int Texture::GetHeight()
{
	return height_;
}
