#pragma once

#include <cstdint>

namespace mc
{

enum class BlockKind : std::uint8_t
{
	NONE = 0x00,
	GRASS = 0x01,
	DIRT = 0x02
};

}