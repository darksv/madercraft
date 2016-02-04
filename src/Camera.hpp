#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

struct FrustumVertices
{
	glm::vec3 ftl, ftr, fbl, fbr, ntl, ntr, nbl, nbr;
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

public:
	Camera();

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix(float aspectRatio);
	glm::vec3 getDirection();
	glm::vec3 getPosition();
	FrustumVertices getFrustumVertices();
	void rotate(GLfloat offsetX, GLfloat offsetY);
};