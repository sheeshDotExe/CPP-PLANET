#include "camera.hpp"
#include <iostream>
Camera::Camera() {
}

void Camera::init(float x, float y, float z, float movementSpeed, float mouseSensitivityX, float mouseSensitivityY, float zoom) {
	position = glm::vec3(x, y, z);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.0f;
	pitch = 0.0f;
	movementSpeed = movementSpeed;
	mouseSensitivityX = mouseSensitivityX;
	mouseSensitivityY = mouseSensitivityY;
	zoom = zoom;
	updateVectors();
	createProjectionMatrix();
}

void Camera::updateVectors() {
	front = glm::normalize(glm::vec3(glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
		glm::sin(glm::radians(pitch))
		,glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch))));
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::createProjectionMatrix() {
	projectionMatrix = glm::perspective(glm::radians(zoom), 1440.0f / 1080.0f, 0.1f, 1000.0f);
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
	xoffset *= mouseSensitivityX;
	yoffset *= mouseSensitivityY;

	yaw += xoffset;
	pitch += yoffset;

	if (constrainPitch) {
		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		if (pitch < -89.0f) {
			pitch = -89.0f;
		}
	}

	updateVectors();
}

void Camera::processMouseScroll(float yoffset) {
	zoom -= (float)yoffset;
	if (zoom < 1.0f) {
		zoom = 1.0f;
	}
	if (zoom > 90.0f) {
		zoom = 90.0f;
	}
	createProjectionMatrix();
}

void Camera::processKeyboardInput(enum CameraMovement direction, float deltaTime) {
	float velocity = movementSpeed * deltaTime;

	if (direction == FORWARD)
		position += glm::vec3( 1, 0, 1 ) * front * velocity;
	if (direction == BACKWARD)
		position -= glm::vec3( 1, 0, 1 ) * front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
	if (direction == UP)
		position += glm::vec3( 0, 1, 0 ) * velocity;
	if (direction == DOWN)
		position -= glm::vec3( 0, 1, 0 ) * velocity;

}

/*
void setProjectionMatrix(Shader shader) {
	setMat4(shader, (char*)"projection", camera->projectionMatrix);
}

void setViewMatrix(Shader shader) {
	setMat4(shader, (char*)"view", getViewMatrix(camera));
}
*/