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
	return 0;
}

bool Renderer::render(ShapeContainer &shapes, float deltaTime) {
	if (!window.shouldClose()) {

		shader.setVec3("lightPos", glm::vec3(0, 0, 0));

		window.processInput(deltaTime);
		shader.use();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window.setProjectionMatrix(shader);
		window.setViewMatrix(shader);

		for (int i = 0; i < shapes.spheres.size(); i++) {
			Sphere* current = &shapes.spheres[i];
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, current->position);
			shader.setMat4("model", model);
			for (int side = 0; side < current->terrainMeshes.size(); side++) {
				current->terrainMeshes[side].draw();
			}
		}

		for (int i = 0; i < shapes.points.size(); i++) {
			Sphere* current = &shapes.points[i];
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, current->position);
			shader.setMat4("model", model);
			for (int side = 0; side < current->terrainMeshes.size(); side++) {
				current->terrainMeshes[side].draw();
			}
		}


		window.swapBuffer();
		return true;
	}
	glfwTerminate();
	return false;
}