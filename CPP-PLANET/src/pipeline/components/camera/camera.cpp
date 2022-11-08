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
	this->movementSpeed = movementSpeed;
	this->mouseSensitivityX = mouseSensitivityX;
	this->mouseSensitivityY = mouseSensitivityY;
	this->zoom = zoom;
	updateVectors();
	createProjectionMatrix();
}

void Camera::updateVectors() {
	// calculate the new Front vector
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);
	// also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, worldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}

void Camera::createProjectionMatrix() {
	projectionMatrix = glm::perspective(glm::radians(zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
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

void Camera::processKeyboardInput(CameraMovement direction, float deltaTime) {
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
