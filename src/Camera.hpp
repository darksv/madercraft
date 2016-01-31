#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Camera
{
protected:
	GLfloat cameraSpeed_;
	glm::vec3 cameraPosition_;
	glm::vec3 cameraFront_;
	glm::vec3 cameraUp_;

	float pitch_, yaw_, roll_;

public:
	Camera();

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	glm::mat4 getViewMatrix();
	glm::vec3 getDirection();
	void rotate(GLfloat offsetX, GLfloat offsetY);
};