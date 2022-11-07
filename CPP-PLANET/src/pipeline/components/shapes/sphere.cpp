#include "sphere.hpp"

void Sphere::createSphere(float radius, float mass, glm::vec3 initialVelocity) {
	this->radius = radius;
	this->mass = mass;
	this->velocity = initialVelocity;
}