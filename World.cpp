#include "World.hpp"

Chunk World::generateChunk()
{
	Chunk chunk;
	for (unsigned char x = 0; x < 32; ++x)
	{
		for (unsigned char y = 0; y < 32; ++y)
		{
			for (unsigned char z = 0; z < 32; ++z)
			{
				chunk.blocks[x][y][z] = (x + y + z) % 3;
			}
		}
	}

	return chunk;
}

std::map<size_t, std::vector<glm::vec3>> World::calculateBlocks(const Chunk& chunk, glm::vec3 position)
{
	std::map<size_t, std::vector<glm::vec3>> blockPositions;

	for (int x = 0; x < 32; ++x)
	{
		for (int y = 0; y < 32; ++y)
		{
			for (int z = 0; z < 32; ++z)
			{
				unsigned char kind = chunk.blocks[x][y][z];

				if (kind == 0)
					continue;

				blockPositions[kind-1].push_back(position + glm::vec3(x, y, z));
			}
		}
	}

	return blockPositions;
}