#include "camera.hpp"

Camera::Camera()
{
	cameraSpeed_    = 0.65f;
	cameraPosition_ = glm::vec3(0.0f, 0.0f, 30.0f);
	cameraFront_    = glm::vec3(0.0f, 0.0f, 1.0f);
	cameraUp_       = glm::vec3(0.0f, 0.0f, 1.0f);
}

void Camera::moveForward()
{
	cameraPosition_ += glm::normalize(glm::vec3(cameraFront_.x, cameraFront_.y, 0.0f)) * cameraSpeed_;
}

void Camera::moveBackward()
{
	cameraPosition_ -= glm::normalize(glm::vec3(cameraFront_.x, cameraFront_.y, 0.0f)) * cameraSpeed_;
}

void Camera::moveLeft()
{
	cameraPosition_ -= glm::normalize(glm::cross(cameraFront_, cameraUp_)) * cameraSpeed_;
}

void Camera::moveRight()
{
	cameraPosition_ += glm::normalize(glm::cross(cameraFront_, cameraUp_)) * cameraSpeed_;
}

void Camera::moveUp()
{
	cameraPosition_ += glm::vec3(0.0f, 0.0f, 1.0f) * cameraSpeed_;
}

void Camera::moveDown()
{
	cameraPosition_ += glm::vec3(0.0f, 0.0f, -1.0f) * cameraSpeed_;
}


glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPosition_, cameraPosition_ + cameraFront_, cameraUp_);
}

void Camera::rotate(GLfloat offsetX, GLfloat offsetY)
{
	yaw_ -= offsetX;
	pitch_ += offsetY;

	if (pitch_ > 89.0f)
		pitch_ = 89.0f;
	if (pitch_ < -89.0f)
		pitch_ = -89.0f;

	glm::vec3 front;

	front.z = sin(glm::radians(pitch_));
	front.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
	front.y = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));

	cameraFront_ = glm::normalize(front);

	std::cout << "cameraDirection: " << cameraFront_.x << ", " << cameraFront_.y << ", " << cameraFront_.z << std::endl;
}