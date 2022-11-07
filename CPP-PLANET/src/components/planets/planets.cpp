#include "planets.hpp"

Simulation::Simulation() {
	std::cout << "sheesh\n";
	planet.createSphere(5.0f, 1.0f, glm::vec3(1,1,1));
}

int Simulation::run() {
	std::cout << "ok\n";
	bool running = true;
	while (running) {
		running = pipeline.render();
	}
	return 0;
}