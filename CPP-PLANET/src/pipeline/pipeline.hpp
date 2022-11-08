#pragma once
#include <windows.h>
#include <winUser.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <io.h>
#include <stdio.h>
#include <direct.h>
#include "components/window.hpp"
#include "components/shader/shader.hpp"
#include "components/camera/camera.hpp"
#include "components/mesh/mesh.hpp"
#include "components/shapes/sphere.hpp"
namespace Pipeline {

#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1080
	
	struct PipelineOptions {
		int width, height, fps;
		char* vertexShaderPath;
		char* fragmentShaderPath;
		char* spritemapPath;
	};

	class Renderer {
	public:
		Renderer(int width, int height, int fps);
		Renderer();
		bool render();

		Sphere test;
	private:
		struct PipelineOptions options;
		Shader shader;
		Window window;
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		int init();
	};
}