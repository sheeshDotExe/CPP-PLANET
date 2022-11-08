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

std::vector<Vertex> cmpVertices(std::vector<glm::vec3> &vertices) {
	std::vector<Vertex> outArr;
	for (int i = 0; i < vertices.size(); i++) {
		struct Vertex vertex = { vertices[i], glm::vec3(0,0,0), glm::vec2(0,0) };
		outArr.push_back(vertex);
	}
	return outArr;
}

//calculate normals
std::vector<Vertex> generateTriangles(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
	std::vector<Vertex> outArr;
	for (int i = 0; i < indices.size(); i += 3) {
		glm::vec3 p1 = vertices[indices[i]].position;
		glm::vec3 p2 = vertices[indices[i+1]].position;
		glm::vec3 p3 = vertices[indices[i+2]].position;

		glm::vec3 U = p2 - p3;
		glm::vec3 V = p3 - p1;
		glm::vec3 normal;
		normal.x = U.y * V.z - U.z * V.y;
		normal.y = U.z * V.x - U.x * V.z;
		normal.z = U.x * V.y - U.y * V.x;

		outArr.push_back(Vertex{ p1, normal, glm::vec2(0, 0) });
		outArr.push_back(Vertex{ p2, normal, glm::vec2(0, 0) });
		outArr.push_back(Vertex{ p3, normal, glm::vec2(0, 0) });
	}
	return outArr;
}

void Mesh::setupMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {

	std::vector<Vertex> triangles = generateTriangles(vertices, indices);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	this->vertices = triangles;
	this->indices = indices;
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, triangles.size() * sizeof(Vertex), &triangles[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

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
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	//glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}