#include "camera.hpp"

Camera::Camera(float x, float y, float z, float movementSpeed, float mouseSensitivityX, float mouseSensitivityY, float zoom) {
	position = glm::vec3(x, y, z);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.0f;
	pitch = 0.0f;
	movementSpeed = movementSpeed;
	mouseSensitivityX = mouseSensitivityX;
	mouseSensitivityY = mouseSensitivityY;
	zoom = zoom;
}

void Camera::updateVectors() {

}