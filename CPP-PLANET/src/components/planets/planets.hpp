#pragma once // include guard
#include <iostream>
#include "../../pipeline/pipeline.hpp"

class Simulation {
public:
	Simulation();
	int run();
private:
	Pipeline::Renderer pipeline;
};
