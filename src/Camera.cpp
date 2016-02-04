#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"

Camera::Camera() :
	pitch_(0.0f),
	roll_(0.0f),
	yaw_(0.0f),
	cameraSpeed_(0.65f),
	cameraPosition_(0.0f, 0.0f, 30.0f),
	cameraFront_(0.0f, 0.0f, 1.0f),
	cameraUp_(0.0f, 0.0f, 1.0f),
	farDistance_(100.0f),
	nearDistance_(0.1f),
	fieldAngle_(45.0f),
	aspectRatio_(1.0f)
{

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

void Camera::updateAspectRatio(float aspectRatio)
{
	aspectRatio_ = aspectRatio;

	const float dft = 2.0 * tan(glm::radians(fieldAngle_) / 2.0);

	nearPlaneDimensions_.x = dft * nearDistance_ * aspectRatio_;
	nearPlaneDimensions_.y = dft * nearDistance_;

	farPlaneDimensions_.x = dft * farDistance_ * aspectRatio_;
	farPlaneDimensions_.y = dft * farDistance_;

	// TODO calculate frustum vertices and then planes
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPosition_, cameraPosition_ + cameraFront_, cameraUp_);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio)
{
	return glm::perspective(fieldAngle_, aspectRatio, nearDistance_, farDistance_);
}

glm::vec3 Camera::getDirection()
{
	return cameraFront_;
}

glm::vec3 Camera::getPosition()
{
	return cameraPosition_;
}

FrustumVertices Camera::getFrustumVertices()
{
	return frustumVertices_;
}

glm::vec2 Camera::getNearPlaneDimensions()
{
	return nearPlaneDimensions_;
}

glm::vec2 Camera::getFarPlaneDimensions()
{
	return farPlaneDimensions_;
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
}