#include "mesh.hpp"
#include <iostream>
Mesh::Mesh() {
}

std::vector<float> verticesW = {
		-0.5f, -0.5f, -0.5f, 0, 0, 0,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,0, 0, 0,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,0, 0, 0,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,0, 0, 0,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,0, 0, 0,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,0, 0, 0,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,0, 0, 0,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,0, 0, 0,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,0, 0, 0,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,0, 0, 0,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,0, 0, 0,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,0, 0, 0,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,0, 0, 0,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,0, 0, 0,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,0, 0, 0,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,0, 0, 0,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,0, 0, 0,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,0, 0, 0,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,0, 0, 0,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,0, 0, 0,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,0, 0, 0,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,0, 0, 0,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,0, 0, 0,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,0, 0, 0,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,0, 0, 0,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,0, 0, 0,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,0, 0, 0,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,0, 0, 0,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,0, 0, 0,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,0, 0, 0,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,0, 0, 0,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,0, 0, 0,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,0, 0, 0,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,0, 0, 0,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,0, 0, 0,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,0, 0, 0,  0.0f, 1.0f
};


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

	//this->vertices = vertices;
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	std::cout << this->VAO << "\n";

	glBufferData(GL_ARRAY_BUFFER, verticesW.size() * sizeof(float), &verticesW[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));

	glBindVertexArray(0);
}

void Mesh::draw() {
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}