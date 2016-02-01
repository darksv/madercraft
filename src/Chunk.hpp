#pragma once

#include "BlockKind.hpp"

const size_t CHUNK_SIZE = 32;

struct Chunk
{
	BlockKind blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	glm::ivec3 position;
};