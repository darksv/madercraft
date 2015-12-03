#pragma once

#include <cstdint>

struct Chunk
{
public:
	std::uint8_t blocks[32][32][32];
};