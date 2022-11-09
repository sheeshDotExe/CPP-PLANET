#pragma once // include guard
#include <iostream>
#include "../../pipeline/pipeline.hpp"
#include "../../pipeline/components/shapes/sphere.hpp"
#include "../../pipeline/components/shapes/shapeContainer.hpp"

class Simulation {
public:
	Simulation();
	int run();
	ShapeContainer shapes;
private:
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	Pipeline::Renderer pipeline;
	void physicsCalculations();
	void rayTrack(Sphere& sphere, int steps, float speed);
};
