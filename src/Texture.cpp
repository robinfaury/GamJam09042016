#include "Texture.h"

Texture::Texture()
	: id_(0)
	, width_(0)
	, height_(0) {}

Texture::Texture(GLuint id, GLsizei width, GLsizei height)
	: id_(id)
	, width_(width)
	, height_(height) {}

