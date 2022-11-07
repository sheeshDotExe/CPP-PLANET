#pragma once
#include "../mesh/mesh.hpp"

class Sphere {
public:
	Sphere();
	void createSphere(float radius, float mass, glm::vec3 initialVelocity);
private:
	float radius, mass;
	glm::vec3 velocity;
	Mesh mesh();
};