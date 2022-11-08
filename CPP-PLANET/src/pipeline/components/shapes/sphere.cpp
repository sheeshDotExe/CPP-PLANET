#include "sphere.hpp"

TerrainFace::TerrainFace(glm::vec3 localUp) {
	this->localUp = localUp;
	this->axisA = glm::vec3(localUp.y, localUp.z, localUp.x);
	this->axisB = glm::cross(localUp, this->axisA);
}

void TerrainFace::constructMesh(Mesh &mesh, float radius) {
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> triangles;

	for (int y = 0; y < resolution; y++) {
		for (int x = 0; x < resolution; x++) {
			int i = x + y * resolution;
			glm::vec2 percent = glm::vec2(x, y) / glm::vec2((resolution - 1), (resolution - 1));
			glm::vec3 pointOnCube = localUp + (percent.x - 0.5f) * 2 * axisA + (percent.y - 0.5f) * 2 * axisB;
			glm::vec3 pointOnSphere = glm::normalize(pointOnCube) * radius;

			vertices.push_back(pointOnSphere);

			if (x != resolution - 1 && y != resolution - 1) {
				triangles.push_back(i);
				triangles.push_back(i + resolution + 1);
				triangles.push_back(i + resolution);
				triangles.push_back(i);
				triangles.push_back(i + 1);
				triangles.push_back(i + resolution + 1);
			}
		}
	}

	mesh.setupMesh(cmpVertices(vertices), triangles);
}

void Sphere::createSphere(float radius, float mass, glm::vec3 initialVelocity) {
	this->radius = radius;
	this->mass = mass;
	this->velocity = initialVelocity;

	std::vector<glm::vec3> directions = { glm::vec3(0,1,0),glm::vec3(0,-1,0) ,glm::vec3(1,0,0) ,glm::vec3(-1,0,0) ,glm::vec3(0,0,1) ,glm::vec3(0,0,-1) };

	std::cout << directions.size();

	for (int i = 0; i < directions.size(); i++) {
		terrainFaces.push_back(TerrainFace(directions[i]));
		terrainMeshes.push_back(Mesh());
		terrainFaces[i].constructMesh(terrainMeshes[i], this->radius);
	}

}

