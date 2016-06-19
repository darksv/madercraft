#include "Chunk.hpp"

namespace mc
{

Chunk::Chunk(glm::ivec3 position) :
	position_(position),
	needsCacheUpdate_(true)
{

}

Blocks& Chunk::getBlocks()
{
	return blocks_;
}

BlockKind Chunk::getBlockKindAt(glm::uvec3 relativePosition)
{
	return blocks_[relativePosition.x][relativePosition.y][relativePosition.z];
}

std::map<BlockKind, std::vector<glm::vec3>> Chunk::getCalculatedPositions()
{
	if (!needsCacheUpdate_)
		return cachedPositions_;

	std::map<BlockKind, std::vector<glm::vec3>> blockPositions;
	glm::vec3 chunkPosition(static_cast<float>(position_.x) * Chunk::SIZE, static_cast<float>(position_.y) * Chunk::SIZE, static_cast<float>(position_.z) * Chunk::SIZE);

	for (int x = 0; x < Chunk::SIZE; ++x)
	{
		for (int y = 0; y < Chunk::SIZE; ++y)
		{
			for (int z = 0; z < Chunk::SIZE; ++z)
			{
				auto kind = blocks_[x][y][z];

				if (kind == BlockKind::NONE)
					continue;

				blockPositions[kind].push_back(chunkPosition + glm::vec3(x, y, z));
			}
		}
	}

	cachedPositions_ = blockPositions;
	needsCacheUpdate_ = false;

	return blockPositions;
}

glm::ivec3 Chunk::getPosition() const
{
	return position_;
}

std::vector<glm::vec3> Chunk::getVertices() const
{
	auto position = getPosition();
	std::vector<glm::vec3> vertices;
	vertices.reserve(8);

	const float x1 = static_cast<float>(position.x) * Chunk::SIZE;
	const float x2 = x1 + Chunk::SIZE;

	const float y1 = static_cast<float>(position.y) * Chunk::SIZE;
	const float y2 = y1 + Chunk::SIZE;

	const float z1 = static_cast<float>(position.z) * Chunk::SIZE;
	const float z2 = z1 + Chunk::SIZE;

	vertices.emplace_back(x1, y1, z1);
	vertices.emplace_back(x1, y1, z2);
	vertices.emplace_back(x1, y2, z1);
	vertices.emplace_back(x1, y2, z2);
	vertices.emplace_back(x2, y1, z1);
	vertices.emplace_back(x2, y1, z2);
	vertices.emplace_back(x2, y2, z1);
	vertices.emplace_back(x2, y2, z2);

	return vertices;
}

void Chunk::putBlockAt(BlockKind kind, glm::uvec3 relativePosition)
{
	blocks_[relativePosition.x][relativePosition.y][relativePosition.z] = kind;
	needsCacheUpdate_ = true;
}

Chunk Chunk::empty(glm::ivec3 position)
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

Chunk Chunk::randomized(glm::ivec3 position)
{
	Chunk chunk(position);
	auto& blocks = chunk.getBlocks();

	for (unsigned char x = 0; x < Chunk::SIZE; ++x)
	{
		for (unsigned char y = 0; y < Chunk::SIZE; ++y)
		{
			for (unsigned char z = 0; z < Chunk::SIZE; ++z)
			{
				blocks[x][y][z] = static_cast<BlockKind>(rand() % 3);
			}
		}
	}

	return chunk;
}

}