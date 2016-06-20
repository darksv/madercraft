#pragma once

#include <array>
#include <map>
#include <vector>

#include <glm/vec3.hpp>

#include "BlockKind.hpp"

namespace mc
{

const size_t CHUNK_SIZE = 32;

using Blocks = std::array<BlockKind, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE>;

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
	BlockKind& getBlockAt(glm::uvec3 relativePosition);
	BlockKind getBlockKindAt(glm::uvec3 relativePosition);
	std::map<BlockKind, std::vector<glm::vec3>> getCalculatedPositions();
	glm::ivec3 getPosition() const;
	std::vector<glm::vec3> getVertices() const;
	void putBlockAt(BlockKind kind, glm::uvec3 relativePosition);

	static Chunk empty(glm::ivec3 position);
	static Chunk randomized(glm::ivec3 position);
};

}