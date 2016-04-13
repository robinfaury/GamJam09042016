#include "Mesh.h"

Mesh::Mesh()
	: VAO_(0)
	, verticesSize_(0)
	, indiceSize_(0) {}

Mesh::Mesh(GLuint VAO, unsigned int verticesSize, unsigned int indiceSize)
	: VAO_(VAO)
	, verticesSize_(verticesSize)
	, indiceSize_(indiceSize) {}

void Mesh::draw() {
	glBindVertexArray(VAO_);
	if (indiceSize_ > 0) {
		glDrawElements(GL_TRIANGLES, indiceSize_, GL_UNSIGNED_INT, 0);
	} else {
		glDrawArrays(GL_TRIANGLES, 0, verticesSize_);
	}
}