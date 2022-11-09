#pragma once
#include <iostream>
#include "sphere.hpp"

struct ShapeContainer {
	std::vector<Sphere> spheres;
	std::vector<Sphere> points;
};