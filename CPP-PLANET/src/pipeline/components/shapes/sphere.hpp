#pragma once
#include "../mesh/mesh.hpp"
#include <iostream>

class TerrainFace {
public:
	TerrainFace(glm::vec3 localUp);
	void constructMesh(Mesh &mesh, float radius);
	int resolution = 10;
	glm::vec3 localUp;
	glm::vec3 axisA;
	glm::vec3 axisB;

};

class Sphere {
public:
	Sphere() {
	};
	void createSphere(float radius, float mass, glm::vec3 initialVelocity);
	float radius, mass;
	glm::vec3 velocity;
	std::vector<TerrainFace> terrainFaces;
	std::vector<Mesh> terrainMeshes;
private:
};