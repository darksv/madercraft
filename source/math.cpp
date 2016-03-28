#include <glm/gtc/matrix_transform.hpp>

#include "math.hpp"

namespace mc
{

namespace math
{

glm::vec4 calculatePlane(glm::vec3 a, glm::vec3 b, glm::vec3 point)
{
	auto normal = glm::normalize(glm::cross(a, b));

	return glm::vec4(normal, -glm::dot(normal, point));
}

}

}