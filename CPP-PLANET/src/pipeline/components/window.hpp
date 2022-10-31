#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera/camera.hpp"

class Window {
public:
	Window();
	int initWindow(int width, int height);
	bool shouldClose();
	void swapBuffer();
	Camera camera;
private:
	int width, height;
	GLFWwindow* windowHandle;
};