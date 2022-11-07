#include "mesh.hpp"
#include <iostream>
Mesh::Mesh() {
}

std::vector<Vertex> createVertexVector(float*values, int size) {
	std::vector<Vertex> outArr;
	for (int i = 0; i < size; i += sizeof(Vertex) / sizeof(float)) {
		struct Vertex z = { glm::vec3(values[i], values[i+1], values[i+2]), glm::vec3(values[i+3], values[i+4], values[i+5]), glm::vec2(values[i+6], values[i+7]) };
		outArr.push_back(z);
	}
	return outArr;
};

void Mesh::setupMesh(std::vector<Vertex> vertices) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	this->vertices = vertices;
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	glBindVertexArray(0);
}

void Mesh::draw() {
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}