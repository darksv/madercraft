#pragma once

#include <list>
#include <map>
#include <vector>

#include <glm/glm.hpp>

#include "Chunk.hpp"

class World
{
	friend class Game;

protected:
	std::list<Chunk> chunks_;

public:
	Chunk generateChunk(glm::ivec3 position);
	std::map<BlockKind, std::vector<glm::vec3>> translateChunkBlocks(const Chunk& chunk);

	Chunk* createEmptyChunk(glm::ivec3 position);
	Chunk* getChunk(glm::ivec3 position);

	bool putBlockAt(BlockKind kind, glm::ivec3 position);

	glm::ivec3 getChunkPositionByBlock(glm::ivec3 blockPosition);
	glm::uvec3 getBlockPositionInChunk(glm::ivec3 blockPosition);
	glm::ivec3 getBlockByPosition(glm::vec3 blockPosition);
	glm::ivec3 getBlockIntersectedByLine(glm::vec3 direction, glm::vec3 offset);
	BlockKind getBlockKind(glm::ivec3 position);
};