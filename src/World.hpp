#pragma once

#include <list>
#include <map>
#include <vector>

#include <glm/glm.hpp>

#include "Chunk.hpp"

class World
{
protected:
	std::list<Chunk> chunks_;

public:
	Chunk generateChunk();
	std::map<BlockKind, std::vector<glm::vec3>> translateChunkBlocks(const Chunk& chunk, glm::vec3 offset);
};