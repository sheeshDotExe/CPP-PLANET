#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera/camera.hpp"
#include "shader/shader.hpp"
class Window {
public:
	Window();
	int initWindow(int width, int height);
	bool shouldClose();
	void swapBuffer();
	void processInput(float deltaTime);
	void setViewMatrix(Shader &shader);
	void setProjectionMatrix(Shader &shader);
private:
	int width, height;
	GLFWwindow* windowHandle;
};
