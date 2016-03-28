#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <array>

namespace mc
{

namespace camera
{

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
	float fieldAngle_;
	glm::uvec2 viewportDimensions_;

	glm::vec2 nearPlaneDimensions_;
	glm::vec2 farPlaneDimensions_;
	FrustumVertices frustumVertices_;
	FrustumPlanes frustumPlanes_;

	void calculatePlanes();
	void updateFrustum();

public:
	Camera();

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void rotate(GLfloat offsetX, GLfloat offsetY);
	void changeViewportDimensions(glm::uvec2 newDimensions);

	bool isVerticeInFrustum(glm::vec3 position) const;

	float getAspectRatio() const;
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	glm::vec3 getDirection() const;
	glm::vec3 getPosition() const;
	FrustumVertices getFrustumVertices() const;
	FrustumPlanes getFrustumPlanes() const;
	glm::vec2 getNearPlaneDimensions() const;
	glm::vec2 getFarPlaneDimensions() const;
};

}

}