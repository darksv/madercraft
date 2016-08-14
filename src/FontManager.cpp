#include "FontManager.hpp"

FontManager::FontManager()
{
	FT_Init_FreeType(&ftHandle_);
}

FontManager::~FontManager()
{
	//FT_Done_FreeType(ftHandle_);
}

std::unique_ptr<FontFace> FontManager::getFace(std::string filePath, size_t size) noexcept
{
	FT_Face face;
	FT_New_Face(ftHandle_, filePath.c_str(), 0, &face);
	
	return std::make_unique<FontFace>(face, size);
}
