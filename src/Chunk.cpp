#include "Chunk.hpp"

Chunk::Chunk(glm::ivec3 position) :
	position_(position),
	needsCacheUpdate_(true)
{

}

Blocks& Chunk::getBlocks()
{
	return blocks_;
}

BlockKind Chunk::getBlockKindAt(glm::ivec3 position)
{
	return blocks_[position.x][position.y][position.z];
}

std::map<BlockKind, std::vector<glm::vec3>> Chunk::getCalculatedPositions()
{
	if (!needsCacheUpdate_)
		return cachedPositions_;

	std::map<BlockKind, std::vector<glm::vec3>> blockPositions;
	glm::vec3 chunkPosition((float)position_.x * Chunk::SIZE, (float)position_.y * Chunk::SIZE, (float)position_.z * Chunk::SIZE);

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

void Chunk::putBlockAt(BlockKind kind, glm::ivec3 position)
{
	blocks_[position.x][position.y][position.z] = kind;
}
