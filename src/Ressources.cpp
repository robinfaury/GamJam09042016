#include "Ressources.h"

std::map<std::string, Texture> Ressources::textures = {
	{ "", Texture() }
};

std::map<std::string, GLuint> Ressources::programs = {
	{ "", 0 }
};
