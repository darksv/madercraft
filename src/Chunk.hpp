#pragma once

#include <map>
#include <vector>

#include "BlockKind.hpp"

const size_t CHUNK_SIZE = 32;

struct Chunk
{
	BlockKind blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	glm::ivec3 position;

	bool needsCacheUpdate;
	std::map<BlockKind, std::vector<glm::vec3>> cachedPositions;
};