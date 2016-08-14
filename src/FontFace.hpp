#pragma once

#include <cstdint>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Glyph
{
	uint32_t charCode;
	glm::uvec2 advance;
	glm::uvec2 size;
	glm::vec2 coords[4];
};

class FontFace
{
public:
	FontFace(FT_Face face, size_t size);
	~FontFace();

	const std::vector<uint8_t>& getBitmap() const noexcept;
	glm::uvec2 getBitmapSize() const noexcept;
	const std::vector<Glyph>& getGlyphs() const noexcept;
	const Glyph& getGlyphByChar(uint32_t charCode) const noexcept;

private:
	FT_Face face_;
	size_t size_;
	std::vector<uint8_t> bitmap_;
	glm::uvec2 bitmapSize_;
	std::vector<Glyph> glyphs_;
};
