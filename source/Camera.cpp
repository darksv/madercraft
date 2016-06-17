#include <algorithm>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <Camera.hpp>

#include "Camera.hpp"
#include "math.hpp"

namespace mc
{

namespace camera
{

void Camera::updateFrustum()
{
	std::array<glm::vec3, 8> vertices;

	// algorithm based on http://www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-extracting-the-planes/

	const glm::vec3 leftVector = glm::normalize(glm::cross(cameraUp_, cameraFront_));
	const glm::vec3 upVector = glm::normalize(glm::cross(cameraFront_, leftVector));

	const glm::vec3 nearPlaneCenter = cameraPosition_ + cameraFront_ * nearDistance_;
	const glm::vec3 nearPlaneUp = upVector * (nearPlaneDimensions_.y / 2.0f);
	const glm::vec3 nearPlaneLeft = leftVector * (nearPlaneDimensions_.x / 2.0f);

	const glm::vec3 farPlaneCenter = cameraPosition_ + cameraFront_ * farDistance_;
	const glm::vec3 farPlaneUp = upVector * (farPlaneDimensions_.y / 2.0f);
	const glm::vec3 farPlaneLeft = leftVector * (farPlaneDimensions_.x / 2.0f);

	vertices[0] = nearPlaneCenter + nearPlaneUp + nearPlaneLeft; // NTL
	vertices[1] = nearPlaneCenter + nearPlaneUp - nearPlaneLeft; // NTR
	vertices[2] = nearPlaneCenter - nearPlaneUp + nearPlaneLeft; // NBL
	vertices[3] = nearPlaneCenter - nearPlaneUp - nearPlaneLeft; // NBR
	vertices[4] = farPlaneCenter + farPlaneUp + farPlaneLeft;    // FTL
	vertices[5] = farPlaneCenter + farPlaneUp - farPlaneLeft;    // FTR
	vertices[6] = farPlaneCenter - farPlaneUp + farPlaneLeft;    // FBL
	vertices[7] = farPlaneCenter - farPlaneUp - farPlaneLeft;    // FBR

	// calculate planes with normal vectors directed to the inside of frustum
	frustumPlanes_[0] = math::calculatePlane(vertices[4] - vertices[5], vertices[7] - vertices[5], vertices[5]); // far
	frustumPlanes_[1] = math::calculatePlane(vertices[1] - vertices[0], vertices[2] - vertices[0], vertices[0]); // near
	frustumPlanes_[2] = math::calculatePlane(vertices[1] - vertices[5], vertices[4] - vertices[5], vertices[5]); // top
	frustumPlanes_[3] = math::calculatePlane(vertices[6] - vertices[7], vertices[3] - vertices[7], vertices[7]); // bottom
	frustumPlanes_[4] = math::calculatePlane(vertices[0] - vertices[4], vertices[6] - vertices[4], vertices[4]); // left
	frustumPlanes_[5] = math::calculatePlane(vertices[7] - vertices[5], vertices[1] - vertices[5], vertices[5]); // right
}

void Camera::calculatePlanes()
{
	const double dft = 2.0 * tan(glm::radians(fieldAngle_) / 2.0);

	nearPlaneDimensions_.x = static_cast<float>(dft * nearDistance_ * getAspectRatio());
	nearPlaneDimensions_.y = static_cast<float>(dft * nearDistance_);

	farPlaneDimensions_.x = static_cast<float>(dft * farDistance_ * getAspectRatio());
	farPlaneDimensions_.y = static_cast<float>(dft * farDistance_);
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
	viewportDimensions_(0, 0)
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

void Camera::changeViewportDimensions(glm::uvec2 newDimensions)
{
	viewportDimensions_ = newDimensions;

	calculatePlanes();
}

bool Camera::isVerticeInFrustum(glm::vec3 position) const
{
	auto vertice = glm::vec4(position, 1.0);

	for (auto& plane : frustumPlanes_)
		if (glm::dot(vertice, plane) < 0)
			return false;

	return true;
}

float Camera::getAspectRatio() const
{
	return (float)viewportDimensions_.x / (float)viewportDimensions_.y;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(cameraPosition_, cameraPosition_ + cameraFront_, cameraUp_);
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return glm::perspective(fieldAngle_, getAspectRatio(), nearDistance_, farDistance_);
}

glm::vec3 Camera::getDirection() const
{
	return cameraFront_;
}

glm::vec3 Camera::getPosition() const
{
	return cameraPosition_;
}

const FrustumPlanes& Camera::getFrustumPlanes() const
{
	return frustumPlanes_;
}

glm::vec2 Camera::getNearPlaneDimensions() const
{
	return nearPlaneDimensions_;
}

glm::vec2 Camera::getFarPlaneDimensions() const
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

}

}