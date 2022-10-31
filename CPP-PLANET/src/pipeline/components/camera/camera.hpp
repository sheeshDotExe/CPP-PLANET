#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	Camera(float x, float y, float z, float movementSpeed, float mouseSensitivityX, float mouseSensitivityY, float zoom);
private:
	void updateVectors();

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	glm::mat4 projectionMatrix;
	float yaw;
	float pitch;
	float movementSpeed;
	float mouseSensitivityX;
	float mouseSensitivityY;
	float zoom;
};