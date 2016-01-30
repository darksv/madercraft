#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>

enum class TextureType {
	TEXTURE_2D
};

enum class TextureFormat {
	TEXTURE_RGB
};

class Texture
{
protected:
	TextureType type_;
	TextureFormat format_;
	size_t width_, height_;
	std::vector<char> data_;

	GLuint textureId_;

	bool loaded_;

public:
	Texture(TextureType type, TextureFormat format, const std::vector<char> &data);
	Texture(TextureType type, TextureFormat format, size_t width, size_t height, const std::vector<char> &data);
	Texture(const Texture& texture) = delete;

	bool loadToGpu();
	GLuint getId();
};