#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace mc
{

namespace math
{

glm::vec4 calculatePlane(glm::vec3 a, glm::vec3 b, glm::vec3 point);

}

}