#include "Ressources.h"

GLuint Res::defaultVAO = 0;

std::map<std::string, Mesh> Res::mesh = {
	{ "", Mesh() }
};

std::map<std::string, Texture> Res::textures = {
	{ "", Texture() }
};

std::map<std::string, GLuint> Res::programs = {
	{ "", 0 }
};
