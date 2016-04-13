#pragma once

#include <map>
#include <vector>

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "ShaderLibrary.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Property {
	unsigned int dim_;
	void* pointer_;
	Property(unsigned int dim, void* pointer) : dim_(dim), pointer_(pointer) {}
};

class Res {
public:
	static GLuint defaultVAO;
	static std::map<std::string, Mesh> mesh;
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

	static void createProgram(std::string name, const char* vertexShader, const char* geometryShader, const char* fragmentShader) {
		programs[name] = compileThreeShaderAndLinkProgram(vertexShader, GL_VERTEX_SHADER, geometryShader, GL_GEOMETRY_SHADER, fragmentShader, GL_FRAGMENT_SHADER);
	}

	static void createGeometry(std::string name, std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Property> property) {
		GLuint vao, vbo, ebo;
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
			for (unsigned int i = 0; i < property.size(); ++i) {
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, property[i].dim_, GL_FLOAT, GL_FALSE, sizeof(Vertex), property[i].pointer_);
			}
		glBindVertexArray(0);

		mesh[name] = Mesh(vao, vertices.size(), indices.size());
	}

	static void loadGeometry(std::string name, char* path) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			printf("ERROR::ASSIMP");
			return;
		}

		aiMesh* mesh = scene->mMeshes[0];
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Property> property;
		property.push_back(Property(3, 0));
		property.push_back(Property(3, (void*)(sizeof(glm::vec3))));
		property.push_back(Property(2, (void*)(2*sizeof(glm::vec3))));

		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 pos;
			pos.x = mesh->mVertices[i].x;
			pos.y = mesh->mVertices[i].y;
			pos.z = mesh->mVertices[i].z;
			vertex.Position = pos;
				
			glm::vec3 nor;
			nor.x = mesh->mNormals[i].x;
			nor.y = mesh->mNormals[i].y;
			nor.z = mesh->mNormals[i].z;
			vertex.Normal = nor;

			glm::vec2 uv;
			uv.x = mesh->mTextureCoords[0][i].x;
			uv.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = uv;

			vertices.push_back(vertex);
		}

		for (GLuint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (GLuint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		createGeometry(name, vertices, indices, property);
	}

private:
	
};
