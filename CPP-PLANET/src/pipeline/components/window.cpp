#include "window.hpp"

int firstMouse = true;
float lastX, lastY;

static void _size_callback(GLFWwindow* windowW, int width, int height) {
	glViewport(0, 0, width, height);
}

static void _mouse_callback(GLFWwindow* windowW, double xposIn, double yposIn) {
	float xpos = (float)xposIn;
	float ypos = (float)yposIn;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	//processMouseMovement(&window.camera, xoffset, yoffset, true);
	//camera.ProcessMouseMovement(xoffset, yoffset);
}

static void _scroll_callback(GLFWwindow* windowW, double xoffset, double yoffset) {
	//processMouseScroll(&window.camera, (float)yoffset);
	//camera.ProcessMouseScroll((float)yoffset);
}

static void _key_callback(GLFWwindow* window, int button, int action, int mods) {
}

Window::Window() {

}

int Window::initWindow(int width, int height) {
	width = width;
	height = height;
	if (glfwInit() == GLFW_FALSE) {
		return 1;
	};
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	windowHandle = glfwCreateWindow(width, height, "OpenGL application", glfwGetPrimaryMonitor(), NULL);
	glfwMakeContextCurrent(windowHandle);
	glfwSwapInterval(0);

	glfwSetFramebufferSizeCallback(windowHandle, _size_callback);
	glfwSetCursorPosCallback(windowHandle, _mouse_callback);
	glfwSetScrollCallback(windowHandle, _scroll_callback);
	glfwSetMouseButtonCallback(windowHandle, _key_callback);

	glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return 1;
	}
	glEnable(GL_DEPTH_TEST);

	return 0;
}

bool Window::shouldClose() {
	if (glfwWindowShouldClose(windowHandle)) {
		return true;
	}
	return false;
}

void Window::swapBuffer() {
	glfwSwapBuffers(windowHandle);
	glfwPollEvents();
}