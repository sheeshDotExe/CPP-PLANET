#include "planets.hpp"
#include <Windows.h>

float GravitationalConstant = 6.67430;

float Acc = 0.000001;
int Points = 10000000;

float sqrMagnitude(glm::vec3 in){
	return in.x * in.x + in.y * in.y + in.z * in.z;
}

void Simulation::rayTrack(Sphere& sphere, int steps, float speed) {
	std::vector<glm::vec3> coords;

	glm::vec3 pos = sphere.position;
	glm::vec3 velo = sphere.velocity;

	std::vector<Sphere> sim;
	for (int i = 0; i < shapes.spheres.size(); i++) {
		Sphere other = shapes.spheres[i];
		if (other.position != sphere.position) {
			sim.push_back(other);
		}
	}

	for (int i = 0; i < steps; i++) {
		for (int i = 0; i < sim.size(); i++) {
			Sphere* current = &sim[i];
			for (int otherI = 0; otherI < sim.size(); otherI++) {
				if (otherI != i) {
					Sphere* other = &sim[otherI];
					glm::vec3 distance = (other->position - current->position);
					glm::vec3 forceDirection = glm::normalize(other->position - current->position);
					glm::vec3 force = forceDirection * GravitationalConstant * other->mass / sqrMagnitude(distance);
					current->velocity += force * deltaTime;
				}
			}
		}
		for (int i = 0; i < sim.size(); i++) {
			Sphere* current = &sim[i];
			current->position += current->velocity * deltaTime;
		}

		for (int otherI = 0; otherI < sim.size(); otherI++) {
			Sphere* other = &sim[otherI];
			glm::vec3 distance = (other->position - pos);
			glm::vec3 forceDirection = glm::normalize(other->position - pos);
			glm::vec3 force = forceDirection * GravitationalConstant * other->mass / sqrMagnitude(distance);
			velo += force * speed;
		}
		pos += velo * speed;
		if (i % (Points / 1000) == 0) {
			std::cout << i << "\n";
			Sphere point = Sphere();
			point.createSphere(0.5, 0, 4, glm::vec3(0, 0, 0), coords[i]);
			shapes.points.push_back(point);
		}
	}
}

void Simulation::physicsCalculations() {
	for (int i = 0; i < shapes.spheres.size(); i++) {
		Sphere* current = &shapes.spheres[i];
		for (int otherI = 0; otherI < shapes.spheres.size(); otherI++) {
			if (otherI != i) {
				Sphere* other = &shapes.spheres[otherI];
				glm::vec3 distance = (other->position - current->position);
				glm::vec3 forceDirection = glm::normalize(other->position - current->position);
				glm::vec3 force = forceDirection * GravitationalConstant * other->mass / sqrMagnitude(distance);
				current->velocity += force *deltaTime;
			}
		}
	}
	for (int i = 0; i < shapes.spheres.size(); i++) {
		Sphere* current = &shapes.spheres[i];
		current->position += current->velocity * deltaTime;
	}
}

Simulation::Simulation() {
	std::cout << "sheesh\n";
	Sphere moon;
	Sphere earth;
	Sphere sun;
	moon.createSphere(3.0f, 0.1, 100, glm::vec3(0,0,sqrt(GravitationalConstant * 100 / 150) + sqrt(GravitationalConstant * 10 / 30)), glm::vec3(160,0,0));
	earth.createSphere(10.0f, 10, 100, glm::vec3(0, 0, sqrt(GravitationalConstant * 100 / 150)), glm::vec3(140,0,0));
	sun.createSphere(20.0f, 100, 100, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

	shapes.spheres.push_back(moon);
	shapes.spheres.push_back(earth);
	shapes.spheres.push_back(sun);

	rayTrack(earth, Points, Acc);
	rayTrack(moon, Points, Acc);
}

int Simulation::run() {
	std::cout << "ok\n";
	bool running = true;
	bool physics = false;
	while (running) {
		Sleep(10);

		if (GetAsyncKeyState(0x46) & 1){
			shapes.spheres[0].velocity.z += 1;
			shapes.points.clear();
			rayTrack(shapes.spheres[0], Points, Acc);
			rayTrack(shapes.spheres[1], Points, Acc);
		}
		if (GetAsyncKeyState(0x47) & 1) {
			shapes.spheres[0].velocity.z -= 1;
			shapes.points.clear();
			rayTrack(shapes.spheres[0], Points, Acc);
			rayTrack(shapes.spheres[1], Points, Acc);
		}

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (GetAsyncKeyState(0x48) & 1) {
			physics = !physics;
		}

		if (physics) {
			physicsCalculations();
		}

		running = pipeline.render(shapes, this->deltaTime);
	}
	return 0;
}