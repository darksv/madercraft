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

BlockKind Chunk::getBlockKindAt(glm::uvec3 relativePosition)
{
	return blocks_[relativePosition.x][relativePosition.y][relativePosition.z];
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

std::vector<glm::vec3> Chunk::getVertices() const
{
	auto position = getPosition();
	float x1, x2, y1, y2, z1, z2;
	std::vector<glm::vec3> vertices;
	vertices.resize(8);

	x1 = position.x * Chunk::SIZE;
	x2 = x1 + Chunk::SIZE;

	y1 = position.y * Chunk::SIZE;
	y2 = y1 + Chunk::SIZE;

	z1 = position.z * Chunk::SIZE;
	z2 = z1 + Chunk::SIZE;

	vertices[0] = glm::vec3(x1, y1, z1);
	vertices[1] = glm::vec3(x1, y1, z2);
	vertices[2] = glm::vec3(x1, y2, z1);
	vertices[3] = glm::vec3(x1, y2, z2);
	vertices[4] = glm::vec3(x2, y1, z1);
	vertices[5] = glm::vec3(x2, y1, z2);
	vertices[6] = glm::vec3(x2, y2, z1);
	vertices[7] = glm::vec3(x2, y2, z2);

	return vertices;
}

void Chunk::putBlockAt(BlockKind kind, glm::uvec3 relativePosition)
{
	blocks_[relativePosition.x][relativePosition.y][relativePosition.z] = kind;
	needsCacheUpdate_ = true;
}
