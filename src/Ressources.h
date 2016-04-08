#pragma once

#include <map>

#include "Shader.h"
#include "Texture.h"
#include "ShaderLibrary.h"

class Ressources {
public:
	static std::map<std::string, Texture> textures;
	static std::map<std::string, GLuint> programs;

	static void loadTexture(std::string name, char* path) {
		GLsizei width, height, channels;
		GLubyte* data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
		createTexture(name, width, height, data);
	}

	static void createTexture(std::string name, GLsizei width, GLsizei height, GLubyte* data) {
		GLuint idTexture;
		glGenTextures(1, &idTexture);
		glBindTexture(GL_TEXTURE_2D, idTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		textures[name] = Texture(idTexture, width, height);
	}

	static void createProgram(std::string name, const char* vertexShader, const char* fragmentShader) {
		programs[name] = compileTwoShaderAndLinkProgram(vertexShader, GL_VERTEX_SHADER, fragmentShader, GL_FRAGMENT_SHADER);
	}

private:
	
};
