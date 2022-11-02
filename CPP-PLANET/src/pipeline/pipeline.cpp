#include "pipeline.hpp"
#include <direct.h>
#pragma warning(disable : 4996)
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

	const char* resourcesPath = "/src/pipeline/components/";

	const char* vertexShaderExtension = "shader/glsl/vertexShader.glsl";
	const char* fragmentShaderExtension = "shader/glsl/fragmentShader.glsl";

	//const char* spritemapExtension = "sprites/spritemap.png";

	DWORD folderPathSize = GetCurrentDirectory(0, NULL) + strlen(resourcesPath) + 1;
	char* baseDir = (char*)malloc(folderPathSize * sizeof(char));
	char* vertexShaderPath = (char*)malloc((folderPathSize + strlen(vertexShaderExtension)) * sizeof(char));
	char* fragmentShaderPath = (char*)malloc((folderPathSize + strlen(fragmentShaderExtension)) * sizeof(char));
	//char* spritemapPath = (char*)malloc((folderPathSize + strlen(spritemapExtension)) * sizeof(char));

	_getcwd(baseDir, folderPathSize);
	strcat(baseDir, resourcesPath);

	strcpy(vertexShaderPath, baseDir);
	strcpy(fragmentShaderPath, baseDir);
	//strcpy(spritemapPath, baseDir);

	strcat(vertexShaderPath, vertexShaderExtension);
	strcat(fragmentShaderPath, fragmentShaderExtension);
	//strcat(spritemapPath, spritemapExtension);

	options->vertexShaderPath = vertexShaderPath;
	options->fragmentShaderPath = fragmentShaderPath;
	//options->spritemapPath = spritemapPath;

	free(baseDir);

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
	shader.initShader(options.vertexShaderPath, options.fragmentShaderPath);
	window.setProjectionMatrix(shader);
	return 0;
}

float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

Mesh test();

bool Renderer::render() {
	if (!window.shouldClose()) {
		window.processInput(1);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window.setViewMatrix(this->shader);

		window.swapBuffer();
		return true;
	}
	glfwTerminate();
	return false;
}