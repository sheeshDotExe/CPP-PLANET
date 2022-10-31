#include "planets.hpp"

Simulation::Simulation() {
	std::cout << "sheesh\n";
}

int Simulation::run() {
	std::cout << "ok\n";
	bool running = true;
	while (running) {
		running = pipeline.render();
	}
	return 0;
}