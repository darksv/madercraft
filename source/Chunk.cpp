#include "Chunk.hpp"
#include <string>

namespace mc
{

glm::uvec3 convert1dTo3d(size_t i)
{
	const auto z = i / (Chunk::SIZE * Chunk::SIZE);
	i -= (z * Chunk::SIZE * Chunk::SIZE);

	return{ i % Chunk::SIZE, i / Chunk::SIZE, z };
}

size_t convert3dTo1d(glm::vec3 p)
{
	return (p.z * Chunk::SIZE * Chunk::SIZE) + (p.y * Chunk::SIZE) + p.x;
}

Chunk::Chunk(glm::ivec3 position) :
	position_(position),
	needsCacheUpdate_(true)
{

}

Blocks& Chunk::getBlocks()
{
	return blocks_;
}

BlockKind& Chunk::getBlockAt(glm::uvec3 relativePosition)
{
	return blocks_[convert3dTo1d(relativePosition)];
}

BlockKind Chunk::getBlockKindAt(glm::uvec3 relativePosition)
{
	return getBlockAt(relativePosition);
}

std::map<BlockKind, std::vector<glm::vec3>> Chunk::getCalculatedPositions()
{
	if (!needsCacheUpdate_)
		return cachedPositions_;

	std::map<BlockKind, std::vector<glm::vec3>> blockPositions;
	glm::vec3 chunkPosition(static_cast<float>(position_.x) * Chunk::SIZE, static_cast<float>(position_.y) * Chunk::SIZE, static_cast<float>(position_.z) * Chunk::SIZE);

	for (size_t i = 0; i < Chunk::SIZE * Chunk::SIZE * Chunk::SIZE; ++i)
	{
		const auto blockKind = blocks_[i];
		if (blockKind == BlockKind::NONE)
			continue;

		const auto pos = convert1dTo3d(i);

		blockPositions[blockKind].push_back(chunkPosition + glm::vec3(pos.x, pos.y, pos.z));
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
	blocks_[convert3dTo1d(relativePosition)] = kind;
	needsCacheUpdate_ = true;
}

Chunk Chunk::empty(glm::ivec3 position)
{
	Chunk chunk(position);
	auto& blocks = chunk.getBlocks();

	std::fill(blocks.begin(), blocks.end(), BlockKind::NONE);

	return chunk;
}

Chunk Chunk::randomized(glm::ivec3 position)
{
	Chunk chunk(position);
	auto& blocks = chunk.getBlocks();

	std::generate(blocks.begin(), blocks.end(), []() {
		return static_cast<BlockKind>(rand() % 3);
	});

	return chunk;
}

}
