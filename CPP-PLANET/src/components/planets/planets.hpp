#pragma once // include guard
#include <iostream>
#include "../../pipeline/pipeline.hpp"
#include "../../pipeline/components/shapes/sphere.hpp"

class Simulation {
public:
	Simulation();
	int run();
	Sphere planet;
private:
	Pipeline::Renderer pipeline;
};
