#pragma once

#define CHUNK_SIZE 32

#include <map>
#include <vector>

#include <glm\vec3.hpp>

#include "BlockKind.hpp"

typedef BlockKind Blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

class Chunk
{
public:
	static const size_t SIZE = CHUNK_SIZE;

private:
	Blocks blocks_;
	glm::ivec3 position_;
	bool needsCacheUpdate_;
	std::map<BlockKind, std::vector<glm::vec3>> cachedPositions_;

public:
	Chunk(glm::ivec3 position);

	Blocks& getBlocks();
	BlockKind getBlockKindAt(glm::uvec3 relativePosition);
	std::map<BlockKind, std::vector<glm::vec3>> getCalculatedPositions();
	glm::ivec3 getPosition() const;
	std::vector<glm::vec3> getVertices() const;
	void putBlockAt(BlockKind kind, glm::uvec3 relativePosition);
};

