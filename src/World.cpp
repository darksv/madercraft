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

glm::ivec3 World::getChunkPositionByBlock(glm::ivec3 blockPosition)
{
	glm::ivec3 chunkPosition;

	if (blockPosition.x >= 0)
		chunkPosition.x = blockPosition.x / 32;
	else
		chunkPosition.x = (blockPosition.x + 1) / 32 - 1;

	if (blockPosition.y >= 0)
		chunkPosition.y = blockPosition.y / 32;
	else
		chunkPosition.y = (blockPosition.y + 1) / 32 - 1;

	if (blockPosition.z >= 0)
		chunkPosition.z = blockPosition.z / 32;
	else
		chunkPosition.z = (blockPosition.z + 1) / 32 - 1;
	

	return chunkPosition;
}

glm::uvec3 World::getBlockPositionInChunk(glm::ivec3 blockPosition)
{
	auto chunkPosition = getChunkPositionByBlock(blockPosition);
	glm::ivec3 offset;

	offset.x = blockPosition.x - CHUNK_SIZE * chunkPosition.x;
	offset.y = blockPosition.y - CHUNK_SIZE * chunkPosition.y;
	offset.z = blockPosition.z - CHUNK_SIZE * chunkPosition.z;

	return offset;
}

glm::ivec3 World::getBlockByPosition(glm::vec3 blockPosition)
{
	glm::ivec3 blockPositionConverted;

	if (blockPosition.x >= 0)
		blockPositionConverted.x = ceil(blockPosition.x);
	else
		blockPositionConverted.x = floor(blockPosition.x);

	if (blockPosition.y >= 0)
		blockPositionConverted.y = ceil(blockPosition.y);
	else
		blockPositionConverted.y = floor(blockPosition.y);

	if (blockPosition.z >= 0)
		blockPositionConverted.z = ceil(blockPosition.z);
	else
		blockPositionConverted.z = floor(blockPosition.z);

	return blockPositionConverted;
}

glm::ivec3 World::getBlockIntersectedByLine(glm::vec3 direction, glm::vec3 offset)
{
	glm::vec3 v;
	const float epsilon = 0.1f;
	const float maxDistance = 1.0f;

	for (float c = epsilon; c < maxDistance; c += epsilon)
	{
		v = c * direction + offset;

		auto block = getBlockByPosition(v);

		// TODO make it work...
	}

	return v;
}

BlockKind World::getBlockKind(glm::ivec3 position)
{
	glm::ivec3 chunkPosition = getChunkPositionByBlock(position);

	// TODO complete this...

	return BlockKind();
}
