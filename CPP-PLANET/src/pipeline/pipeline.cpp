#include "pipeline.hpp"
using namespace Pipeline;

static void _getInfo(struct PipelineOptions* options) {
	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	if (width == 0) {
		options->width = DEFAULT_WIDTH;
	}
	else {
		options->width = width;
	}

	int height = GetSystemMetrics(SM_CYFULLSCREEN);
	if (height == 0) {
		options->height = DEFAULT_HEIGHT;
	}
	else {
		options->height = height;
	}

	return;
}

Renderer::Renderer(int width, int height, int fps) {
	options.width = width;
	options.height = height;
	options.fps = fps;
	init();
}

Renderer::Renderer() {
	_getInfo(&options);
	init();
}

int Renderer::init() {
	std::cout << options.width << " : " << options.height << "\n";
	window.initWindow(options.width, options.height);
	return 0;
}

bool Renderer::render() {
	if (!window.shouldClose()) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window.swapBuffer();
		return true;
	}
	glfwTerminate();
	return false;
}