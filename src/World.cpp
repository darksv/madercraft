#include "World.hpp"

Chunk World::generateEmptyChunk(glm::ivec3 position)
{
	Chunk chunk(position);
	auto& blocks = chunk.getBlocks();

	for (unsigned char x = 0; x < Chunk::SIZE; ++x)
	{
		for (unsigned char y = 0; y < Chunk::SIZE; ++y)
		{
			for (unsigned char z = 0; z < Chunk::SIZE; ++z)
			{
				blocks[x][y][z] = BlockKind::NONE;
			}
		}
	}

	return chunk;
}

Chunk World::generateRandomizedChunk(glm::ivec3 position)
{
	Chunk chunk(position);
	auto& blocks = chunk.getBlocks();

	for (unsigned char x = 0; x < Chunk::SIZE; ++x)
	{
		for (unsigned char y = 0; y < Chunk::SIZE; ++y)
		{
			for (unsigned char z = 0; z < Chunk::SIZE; ++z)
			{
				blocks[x][y][z] = (BlockKind) (rand() % 3);
			}
		}
	}

	return chunk;
}

Chunk* World::createEmptyChunk(glm::ivec3 position)
{
	chunks_.push_back(generateEmptyChunk(position));
	return &chunks_.back();
}

Chunk* World::createRandomizedChunk(glm::ivec3 position)
{
	chunks_.push_back(generateRandomizedChunk(position));
	return &chunks_.back();
}

Chunk* World::getChunk(glm::ivec3 position)
{
	for (Chunk& chunk : chunks_)
	{
		if (chunk.getPosition() == position)
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
	
	chunk->putBlockAt(kind, blockOffsetInChunk);

	return true;
}

static int calculateBlockOffset(int absoluteBlockPosition)
{
	if (absoluteBlockPosition >= 0)
		return absoluteBlockPosition / (int)Chunk::SIZE;
	else
		return (absoluteBlockPosition + 1) / (int)Chunk::SIZE - 1;
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

	offset.x = blockPosition.x - Chunk::SIZE * chunkPosition.x;
	offset.y = blockPosition.y - Chunk::SIZE * chunkPosition.y;
	offset.z = blockPosition.z - Chunk::SIZE * chunkPosition.z;

	return offset;
}

static int calculateBlockIndexByCoord(float absoluteCoord)
{
	return static_cast<int>((absoluteCoord > 0.0f) ? ceil(absoluteCoord) : floor(absoluteCoord));
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
		return chunk->getBlockKindAt(blockOffsetInChunk);
}

float World::getDistanceToChunk(const Chunk& chunk, glm::vec3 position)
{
	auto chunkPosition = chunk.getPosition();
	// TODO use chunk's center point

	return sqrt(pow((float)chunkPosition.x * Chunk::SIZE - position.x, 2) + pow((float)chunkPosition.y * Chunk::SIZE - position.y, 2) + pow((float)chunkPosition.z * Chunk::SIZE - position.z, 2));
}
