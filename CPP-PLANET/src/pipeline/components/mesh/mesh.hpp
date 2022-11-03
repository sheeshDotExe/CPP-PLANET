#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class Mesh {
public:
	Mesh();
	void setupMesh(std::vector<Vertex> vertices);
	void draw();
	GLuint VAO;
	GLuint VBO;
private:
	GLsizei size;
	std::vector<Vertex> vertices;

};

std::vector<Vertex> createVertexVector(float* values, int size);