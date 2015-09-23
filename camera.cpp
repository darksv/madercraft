#include "camera.hpp"

Camera::Camera()
{
	mCameraSpeed = 0.65f;
	mCameraPos = glm::vec3(0.0f, 0.0f, -30.0f);
	mCameraFront = glm::vec3(0.0f, -1.0f, -1.0f);
	mCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::moveForward()
{
	mCameraPos += mCameraSpeed * mCameraFront;
}

void Camera::moveBackward()
{
	mCameraPos -= mCameraSpeed * mCameraFront;
}

void Camera::moveLeft()
{
	mCameraPos -= glm::normalize(glm::cross(mCameraFront, mCameraUp)) * mCameraSpeed;
}

void Camera::moveRight()
{
	mCameraPos += glm::normalize(glm::cross(mCameraFront, mCameraUp)) * mCameraSpeed;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
}

void Camera::rotate(GLfloat offsetX, GLfloat offsetY)
{
	mYaw += offsetX;
	mPitch += offsetY;

	if (mPitch > 89.0f)
		mPitch = 89.0f;
	if (mPitch < -89.0f)
		mPitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	front.y = sin(glm::radians(mPitch));
	front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	mCameraFront = glm::normalize(front);
}