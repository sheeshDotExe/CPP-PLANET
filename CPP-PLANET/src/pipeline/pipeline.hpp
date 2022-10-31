#pragma once
#include "components/window.hpp"
#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Pipeline {

#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1080
	
	struct PipelineOptions {
		int width, height, fps;
	};

	class Renderer {
	public:
		Renderer(int width, int height, int fps);
		Renderer();
		bool render();
	private:
		struct PipelineOptions options;
		Window window;
		int init();
	};
}