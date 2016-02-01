#include "World.hpp"

Chunk World::generateChunk()
{
	Chunk chunk;
	for (unsigned char x = 0; x < CHUNK_SIZE; ++x)
	{
		for (unsigned char y = 0; y < CHUNK_SIZE; ++y)
		{
			for (unsigned char z = 0; z < CHUNK_SIZE; ++z)
			{
				chunk.blocks[x][y][z] = (rand() % 10) < 3 ? BlockKind::GRASS : BlockKind::DIRT;
			}
		}
	}

	return chunk;
}

std::map<BlockKind, std::vector<glm::vec3>> World::translateChunkBlocks(const Chunk& chunk, glm::vec3 offset)
{
	std::map<BlockKind, std::vector<glm::vec3>> blockPositions;

	for (int x = 0; x < CHUNK_SIZE; ++x)
	{
		for (int y = 0; y < CHUNK_SIZE; ++y)
		{
			for (int z = 0; z < CHUNK_SIZE; ++z)
			{
				auto kind = chunk.blocks[x][y][z];

				if (kind == BlockKind::NONE)
					continue;

				blockPositions[kind].push_back(offset + glm::vec3(x, y, z));
			}
		}
	}

	return blockPositions;
}

glm::uvec3 World::getChunkPositionByBlock(glm::uvec3 blockPosition)
{
	// TODO make it work...
	return glm::uvec3(0, 0, 0);
}
