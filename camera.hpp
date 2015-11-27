#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#include <iostream>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"

class Camera {
protected:
	GLfloat cameraSpeed_;
	glm::vec3 cameraPosition_;
	glm::vec3 cameraFront_;
	glm::vec3 cameraUp_;

	float pitch_ = 0.0f, yaw_ = 0.0f, roll_ = 0.0f;

public:
	Camera();

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	glm::mat4 getViewMatrix();
	void rotate(GLfloat offsetX, GLfloat offsetY);
};

#endif