#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>

namespace mc
{

enum class TextureType {
	TEXTURE_2D
};

enum class TextureFileFormat {
	TEXTURE_RAW
};

enum class TexturePixelFormat {
	TEXTURE_RGB
};

class Texture
{
protected:
	TextureType type_;
	TexturePixelFormat pixelFormat_;
	size_t width_, height_;
	std::vector<char> data_;

	GLuint textureId_;

	bool loaded_;

public:
	Texture(TextureType type, TexturePixelFormat format, const std::vector<char> &data);
	Texture(TextureType type, TexturePixelFormat format, size_t width, size_t height, const std::vector<char> &data);
	Texture(const Texture& texture) = delete;

	bool loadToGpu();
	GLuint getId();
};

}