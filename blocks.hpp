#ifndef _BLOCKS_H
#define _BLOCKS_H

#include <array>
#include <string>

namespace Blocks
{

enum class Kind : char {
	BK_GRASS,
	BK_DIRT
};

struct Block {
	Kind kind;
	std::string name;
};

const std::array<Block, 2> BLOCKS = { {
	{ BK_GRASS, "trowa" },
	{ BK_DIRT, "ziymia" }
} };

};

#endif