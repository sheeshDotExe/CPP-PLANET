#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

class Camera {
public:
	Camera();
	void init(float x, float y, float z, float movementSpeed, float mouseSensitivityX, float mouseSensitivityY, float zoom);
	void createProjectionMatrix();
	glm::mat4 getViewMatrix();
	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch);
	void processMouseScroll(float yoffset);
	void processKeyboardInput(CameraMovement direction, float deltaTime);

	float movementSpeed;
	glm::mat4 projectionMatrix;
private:
	void updateVectors();

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	float yaw;
	float pitch;
	float mouseSensitivityX;
	float mouseSensitivityY;
	float zoom;
};