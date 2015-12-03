#pragma once

#include <map>
#include <vector>

#include <glm/glm.hpp>

#include "Chunk.hpp"

class World
{
public:
	Chunk generateChunk();
	std::map<size_t, std::vector<glm::vec3>> calculateBlocks(const Chunk& chunk, glm::vec3 position);
};