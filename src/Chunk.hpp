#pragma once

#include "BlockKind.hpp"

struct Chunk
{
public:
	BlockKind blocks[32][32][32];
};