#pragma once

#include <memory>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H
#include "FontFace.hpp"

class FontManager
{
public:
	FontManager();
	~FontManager();

	std::unique_ptr<FontFace> getFace(std::string filePath, size_t size) noexcept;

private:
	FT_Library ftHandle_;
};
