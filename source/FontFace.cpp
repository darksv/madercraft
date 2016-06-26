#include "FontFace.hpp"
#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

FontFace::FontFace(FT_Face face, size_t size) :
	face_(face),
	size_(size),
	bitmapSize_{512, 512}
{
	bitmap_.resize(bitmapSize_.x * bitmapSize_.y * 3, 0x00);

	FT_Set_Pixel_Sizes(face, 0, size);

	FT_UInt glyphIndex;
	FT_ULong charCode = FT_Get_First_Char(face_, &glyphIndex);

	auto coordToIndex = [](size_t x, size_t y, size_t width)
	{
		return y * width + x;
	};

	/* Position of the glyph in the font texture */
	glm::uvec2 glyphPosition{0, size_};

	while (glyphIndex != 0)
	{
		if (FT_Load_Glyph(face_, glyphIndex, FT_LOAD_RENDER) == 0)
		{
			auto slot = face_->glyph;
			auto bitmap = slot->bitmap;
			
			/* Wrap to next line if needed */
			if (glyphPosition.x + bitmap.width > bitmapSize_.x)
			{
				glyphPosition.x = 0;
				glyphPosition.y += size_;
			}

			const glm::uvec2 bitmapPosition{ glyphPosition.x + slot->bitmap_left, glyphPosition.y - slot->bitmap_top };

			/* Check if new bitmap would not fit into the font texture bitmap */
			if (bitmapPosition.x + bitmap.width >= bitmapSize_.x - 1 || bitmapPosition.y + bitmap.rows >= bitmapSize_.y - 1)
				break;
			
			/* Copy glyph bitmap into a font texture bitmap */
			for (size_t x = 0; x < bitmap.width; ++x)
			{
				for (size_t y = 0; y < bitmap.rows; ++y)
				{
					auto offset = 3 * coordToIndex(bitmapPosition.x + x, bitmapPosition.y + y, bitmapSize_.x);
					auto color = bitmap.buffer[coordToIndex(x, y, bitmap.width)];

					bitmap_[offset + 0] = color;
					bitmap_[offset + 1] = color;
					bitmap_[offset + 2] = color;
				}
			}

			Glyph glyph;
			glyph.charCode = charCode;
			glyph.size = { bitmap.width, bitmap.rows };
			glyph.advance = { face_->glyph->advance.x >> 6, 0 };

			const auto x1 = static_cast<float>(bitmapPosition.x) / static_cast<float>(bitmapSize_.x);                // LEFT
			const auto y1 = static_cast<float>(bitmapPosition.y) / static_cast<float>(bitmapSize_.y);                // TOP
			const auto x2 = static_cast<float>(bitmapPosition.x + glyph.size.x) / static_cast<float>(bitmapSize_.x); // RIGHT
			const auto y2 = static_cast<float>(bitmapPosition.y + glyph.size.y) / static_cast<float>(bitmapSize_.y); // BOTTOM
			
			// TL
			glyph.coords[0].x = x1;
			glyph.coords[0].y = 1.0f - y1;
			// TR
			glyph.coords[1].x = x2;
			glyph.coords[1].y = 1.0f - y1;
			// BR
			glyph.coords[2].x = x1;
			glyph.coords[2].y = 1.0f - y2;
			// BL
			glyph.coords[3].x = x2;
			glyph.coords[3].y = 1.0f - y2;

			glyphs_.push_back(glyph);

			glyphPosition.x += glyph.advance.x;
		}

		charCode = FT_Get_Next_Char(face_, charCode, &glyphIndex);
	}

	//std::ofstream ofs("font_bitmap_" + std::to_string(size_) + ".raw", std::ios::out | std::ios::binary);
	//ofs.write(reinterpret_cast<char*>(bitmap_.data()), bitmap_.size());
}

FontFace::~FontFace()
{
	delete face_;
}

const std::vector<uint8_t>& FontFace::getBitmap() const noexcept
{
	return bitmap_;
}

glm::uvec2 FontFace::getBitmapSize() const noexcept
{
	return bitmapSize_;
}

const std::vector<Glyph>& FontFace::getGlyphs() const noexcept
{
	return glyphs_;
}

const Glyph& FontFace::getGlyphByChar(uint32_t charCode) const noexcept
{
	auto it = std::find_if(glyphs_.begin(), glyphs_.end(), [charCode](const Glyph& glyph)
	{
		return glyph.charCode == charCode;
	});

	return *it;
}
