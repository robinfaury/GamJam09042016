#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

class Mesh {
public:
	GLuint VAO_;
	unsigned int verticesSize_;
	unsigned int indiceSize_;

	Mesh();
	Mesh(GLuint VAO, unsigned int verticesSize, unsigned int indiceSize);

	void draw();
};