#include "Chunk.hpp"

namespace mc
{

glm::uvec3 convert1dTo3d(size_t i)
{
	const auto z = i / (Chunk::SIZE * Chunk::SIZE);
	i -= (z * Chunk::SIZE * Chunk::SIZE);

	return{ i % Chunk::SIZE, i / Chunk::SIZE, z };
}

size_t convert3dTo1d(glm::uvec3 p)
{
	return (p.z * Chunk::SIZE * Chunk::SIZE) + (p.y * Chunk::SIZE) + p.x;
}

Chunk::Chunk(glm::ivec3 position) :
	position_(position),
	needsCacheUpdate_(true)
{

}

Chunk::Chunk(const Chunk& other) :
	position_(other.getPosition()),
	needsCacheUpdate_(true)
{
	auto& blocks = other.getBlocks();
	std::copy(blocks.begin(), blocks.end(), blocks_.begin());
}

Blocks& Chunk::getBlocks()
{
	return blocks_;
}

const Blocks& Chunk::getBlocks() const
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

	/* TODO: needs optimization */

	for (size_t i = 0; i < blocks_.size(); ++i)
	{
		const auto blockKind = blocks_[i];
		if (blockKind == BlockKind::None)
			continue;

		const auto pos = convert1dTo3d(i);

		/* List all possible neighbours */
		std::vector<glm::uvec3> nearest;
		if (pos.x < Chunk::SIZE - 1) nearest.emplace_back(pos + glm::uvec3(1, 0, 0));
		if (pos.y < Chunk::SIZE - 1) nearest.emplace_back(pos + glm::uvec3(0, 1, 0));
		if (pos.z < Chunk::SIZE - 1) nearest.emplace_back(pos + glm::uvec3(0, 0, 1));
		if (pos.x > 0)               nearest.emplace_back(pos - glm::uvec3(1, 0, 0));
		if (pos.y > 0)               nearest.emplace_back(pos - glm::uvec3(0, 1, 0));
		if (pos.z > 0)               nearest.emplace_back(pos - glm::uvec3(0, 0, 1));

		const auto countCoveredFaces = std::count_if(nearest.begin(), nearest.end(), [this](const glm::vec3& p) {
			return getBlockKindAt(p) != BlockKind::None;
		});

		/* Display current block only if there is at least one face not covered by other block */
		if (countCoveredFaces < 6)
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
	getBlockAt(relativePosition) = kind;
	needsCacheUpdate_ = true;
}

Chunk Chunk::empty(glm::ivec3 position)
{
	Chunk chunk(position);
	auto& blocks = chunk.getBlocks();

	std::fill(blocks.begin(), blocks.end(), BlockKind::None);

	return chunk;
}

Chunk Chunk::randomized(glm::ivec3 position)
{
	Chunk chunk(position);
	auto& blocks = chunk.getBlocks();

	std::generate(blocks.begin(), blocks.end(), []() {
		return static_cast<BlockKind>((rand() % 2) + 1);
	});

	return chunk;
}

}
