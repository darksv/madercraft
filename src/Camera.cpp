#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"

static glm::vec4 calculatePlane(glm::vec3 a, glm::vec3 b, glm::vec3 point)
{
	auto normal = glm::normalize(glm::cross(a, b));

	return glm::vec4(normal, -glm::dot(normal, point));
}

void Camera::updateFrustum()
{
	FrustumVertices& fv = frustumVertices_;

	// algorithm based on http://www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-extracting-the-planes/

	// near plane

	glm::vec3 nearPlaneCenter = cameraPosition_ + cameraFront_ * nearDistance_;
	glm::vec3 nearPlaneUp = cameraUp_ * (nearPlaneDimensions_.y / 2.0f);
	glm::vec3 nearPlaneLeft = glm::cross(cameraFront_, cameraUp_) * (nearPlaneDimensions_.x / 2.0f);

	fv.ntl = nearPlaneCenter + nearPlaneUp + nearPlaneLeft;
	fv.ntr = nearPlaneCenter + nearPlaneUp - nearPlaneLeft;
	fv.nbl = nearPlaneCenter - nearPlaneUp + nearPlaneLeft;
	fv.nbr = nearPlaneCenter - nearPlaneUp - nearPlaneLeft;

	// far plane

	glm::vec3 farPlaneCenter = cameraPosition_ + cameraFront_ * farDistance_;
	glm::vec3 farPlaneUp = cameraUp_ * (farPlaneDimensions_.y / 2.0f);
	glm::vec3 farPlaneLeft = glm::cross(cameraFront_, cameraUp_) * (farPlaneDimensions_.x / 2.0f);

	fv.ftl = farPlaneCenter + farPlaneUp + farPlaneLeft;
	fv.ftr = farPlaneCenter + farPlaneUp - farPlaneLeft;
	fv.fbl = farPlaneCenter - farPlaneUp + farPlaneLeft;
	fv.fbr = farPlaneCenter - farPlaneUp - farPlaneLeft;


	FrustumPlanes& fp = frustumPlanes_;

	// calculate planes with normal vectors directed to the inside of frustum
	fp.far = calculatePlane(fv.ftl - fv.ftr, fv.fbr - fv.ftr, fv.ftr);
	fp.near = calculatePlane(fv.nbr - fv.ntr, fv.ntl - fv.ntr, fv.ntr);
	fp.top = calculatePlane(fv.ntl - fv.ftl, fv.ftr - fv.ftl, fv.ftl);
	fp.bottom = calculatePlane(fv.nbl - fv.nbr, fv.fbr - fv.nbr, fv.nbr);
	fp.left = calculatePlane(fv.ftl - fv.fbl, fv.nbl - fv.fbl, fv.fbl);
	fp.right = calculatePlane(fv.ftr - fv.fbr, fv.nbr - fv.fbr, fv.fbr);
}

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
	updateFrustum();
}

void Camera::moveBackward()
{
	cameraPosition_ -= glm::normalize(glm::vec3(cameraFront_.x, cameraFront_.y, 0.0f)) * cameraSpeed_;
	updateFrustum();
}

void Camera::moveLeft()
{
	cameraPosition_ -= glm::normalize(glm::cross(cameraFront_, cameraUp_)) * cameraSpeed_;
	updateFrustum();
}

void Camera::moveRight()
{
	cameraPosition_ += glm::normalize(glm::cross(cameraFront_, cameraUp_)) * cameraSpeed_;
	updateFrustum();
}

void Camera::moveUp()
{
	cameraPosition_ += glm::vec3(0.0f, 0.0f, 1.0f) * cameraSpeed_;
	updateFrustum();
}

void Camera::moveDown()
{
	cameraPosition_ += glm::vec3(0.0f, 0.0f, -1.0f) * cameraSpeed_;
	updateFrustum();
}

void Camera::updateAspectRatio(float aspectRatio)
{
	aspectRatio_ = aspectRatio;

	const float dft = 2.0 * tan(glm::radians(fieldAngle_) / 2.0);

	nearPlaneDimensions_.x = dft * nearDistance_ * aspectRatio_;
	nearPlaneDimensions_.y = dft * nearDistance_;

	farPlaneDimensions_.x = dft * farDistance_ * aspectRatio_;
	farPlaneDimensions_.y = dft * farDistance_;
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

FrustumPlanes Camera::getFrustumPlanes()
{
	return frustumPlanes_;
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

	updateFrustum();
}