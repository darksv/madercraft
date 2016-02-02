#include "World.hpp"

Chunk World::generateChunk(glm::ivec3 position)
{
	Chunk chunk;
	chunk.position = position;

	for (unsigned char x = 0; x < CHUNK_SIZE; ++x)
	{
		for (unsigned char y = 0; y < CHUNK_SIZE; ++y)
		{
			for (unsigned char z = 0; z < CHUNK_SIZE; ++z)
			{
				chunk.blocks[x][y][z] = BlockKind::NONE;
			}
		}
	}

	return chunk;
}

std::map<BlockKind, std::vector<glm::vec3>> World::translateChunkBlocks(const Chunk& chunk)
{
	std::map<BlockKind, std::vector<glm::vec3>> blockPositions;
	glm::vec3 chunkPosition((float)chunk.position.x * CHUNK_SIZE, (float)chunk.position.y * CHUNK_SIZE, (float)chunk.position.z * CHUNK_SIZE);

	for (int x = 0; x < CHUNK_SIZE; ++x)
	{
		for (int y = 0; y < CHUNK_SIZE; ++y)
		{
			for (int z = 0; z < CHUNK_SIZE; ++z)
			{
				auto kind = chunk.blocks[x][y][z];

				if (kind == BlockKind::NONE)
					continue;

				blockPositions[kind].push_back(chunkPosition + glm::vec3(x, y, z));
			}
		}
	}

	return blockPositions;
}

Chunk* World::createEmptyChunk(glm::ivec3 position)
{
	chunks_.push_back(generateChunk(position));
	return &chunks_.back();
}

Chunk* World::getChunk(glm::ivec3 position)
{
	for (Chunk& chunk : chunks_)
	{
		if (position == chunk.position)
			return &chunk;
	}

	return nullptr;
}

std::list<Chunk>& World::getAllChunks()
{
	return chunks_;
}

bool World::putBlockAt(BlockKind kind, glm::ivec3 position)
{
	auto chunkPosition = getChunkPositionByBlock(position);
	auto blockOffsetInChunk = getBlockPositionInChunk(position);
	auto chunk = getChunk(chunkPosition);

	if (chunk == nullptr)
		chunk = createEmptyChunk(chunkPosition);
	
	chunk->blocks[blockOffsetInChunk.x][blockOffsetInChunk.y][blockOffsetInChunk.z] = kind;

	return true;
}

static int calculateBlockOffset(int absoluteBlockPosition)
{
	if (absoluteBlockPosition >= 0)
		return absoluteBlockPosition / (int)CHUNK_SIZE;
	else
		return (absoluteBlockPosition + 1) / (int)CHUNK_SIZE - 1;
}

glm::ivec3 World::getChunkPositionByBlock(glm::ivec3 blockPosition)
{
	glm::ivec3 chunkPosition;

	chunkPosition.x = calculateBlockOffset(blockPosition.x);
	chunkPosition.y = calculateBlockOffset(blockPosition.y);
	chunkPosition.z = calculateBlockOffset(blockPosition.z);

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

static int calculateBlockIndexByCoord(float absoluteCoord)
{
	return (absoluteCoord > 0.0f) ? ceil(absoluteCoord) : floor(absoluteCoord);
}

glm::ivec3 World::getBlockByPosition(glm::vec3 blockPosition)
{
	glm::ivec3 blockPositionConverted;

	blockPositionConverted.x = calculateBlockIndexByCoord(blockPosition.x);
	blockPositionConverted.y = calculateBlockIndexByCoord(blockPosition.y);
	blockPositionConverted.z = calculateBlockIndexByCoord(blockPosition.z);

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
	auto chunkPosition = getChunkPositionByBlock(position);
	auto blockOffsetInChunk = getBlockPositionInChunk(position);
	auto chunk = getChunk(chunkPosition);

	if (chunk == nullptr)
		return BlockKind::NONE;
	else
		return chunk->blocks[blockOffsetInChunk.x][blockOffsetInChunk.y][blockOffsetInChunk.z];
}

float World::getDistanceToChunk(const Chunk& chunk, glm::vec3 position)
{
	// TODO use chunk's center point

	return sqrt(pow((float)chunk.position.x * CHUNK_SIZE - position.x, 2) + pow((float)chunk.position.y * CHUNK_SIZE - position.y, 2) + pow((float)chunk.position.z * CHUNK_SIZE - position.z, 2));
}
