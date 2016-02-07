#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <array>

struct FrustumVertices
{
	union
	{
		glm::vec3 vertices[8];
		struct
		{
			glm::vec3 ftl, ftr, fbl, fbr, ntl, ntr, nbl, nbr;
		};
	};

	FrustumVertices() {};
};

struct FrustumPlanes
{
	union
	{
		glm::vec4 planes[6];
		struct
		{
			glm::vec4 bottom, top, left, right, near, far;
		};
	};

	FrustumPlanes() {};
};

class Camera
{
protected:
	GLfloat cameraSpeed_;
	glm::vec3 cameraPosition_;
	glm::vec3 cameraFront_;
	glm::vec3 cameraUp_;

	float pitch_, yaw_, roll_;
	float nearDistance_, farDistance_;
	float aspectRatio_, fieldAngle_;

	glm::vec2 nearPlaneDimensions_, farPlaneDimensions_;
	FrustumVertices frustumVertices_;
	FrustumPlanes frustumPlanes_;

	void updateFrustum();
public:
	Camera();

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void updateAspectRatio(float aspectRatio);

	bool isVerticeInFrustum(glm::vec3 position);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix(float aspectRatio);
	glm::vec3 getDirection();
	glm::vec3 getPosition();
	FrustumVertices getFrustumVertices() const;
	FrustumPlanes getFrustumPlanes() const;
	glm::vec2 getNearPlaneDimensions();
	glm::vec2 getFarPlaneDimensions();
	void rotate(GLfloat offsetX, GLfloat offsetY);
};