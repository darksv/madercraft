#pragma once

#include <cstdint>

namespace mc
{

enum class BlockKind : std::uint8_t
{
	None = 0x00,
	Grass = 0x01,
	Dirt = 0x02
};

}