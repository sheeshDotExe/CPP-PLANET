#include "window.hpp"

int firstMouse = true;
float lastX, lastY;
Camera camera;

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

	camera.processMouseMovement(xoffset, yoffset, true);
}

static void _scroll_callback(GLFWwindow* windowW, double xoffset, double yoffset) {
	camera.processMouseScroll((float)yoffset);
}

static void _key_callback(GLFWwindow* window, int button, int action, int mods) {
}

void Window::processInput(float deltaTime) {
	if (glfwGetKey(windowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(windowHandle, true);
	}

	if (glfwGetKey(windowHandle, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera.movementSpeed = 45.0f * 2;
	}
	else {
		camera.movementSpeed = 45.0f;
	}

	if (glfwGetKey(windowHandle, GLFW_KEY_W) == GLFW_PRESS) {
		camera.processKeyboardInput(FORWARD, deltaTime);
	}
	if (glfwGetKey(windowHandle, GLFW_KEY_S) == GLFW_PRESS) {
		camera.processKeyboardInput(BACKWARD, deltaTime);
	}
	if (glfwGetKey(windowHandle, GLFW_KEY_A) == GLFW_PRESS) {
		camera.processKeyboardInput(LEFT, deltaTime);
	}
	if (glfwGetKey(windowHandle, GLFW_KEY_D) == GLFW_PRESS) {
		camera.processKeyboardInput(RIGHT, deltaTime);
	}
	if (glfwGetKey(windowHandle, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.processKeyboardInput(UP, deltaTime);
	}
	if (glfwGetKey(windowHandle, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		camera.processKeyboardInput(DOWN, deltaTime);
	}
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

	camera.init(0.0f, 0.0f, 3.0f, 4.5f, 0.1f, 0.1f, 45.0f);

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


void Window::setViewMatrix(Shader shader) {
	shader.setMat4("view", camera.getViewMatrix());
}

void Window::setProjectionMatrix(Shader shader) {
	shader.setMat4("projection", camera.projectionMatrix);
}