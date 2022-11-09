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
#include "components/shapes/shapeContainer.hpp"
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
		bool render(ShapeContainer &shapes, float deltaTime);
	private:
		struct PipelineOptions options;
		Shader shader;
		Window window;
		int init();
	};
}