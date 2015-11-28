#include "helpers.hpp"

std::vector<char> getFileContent(std::string filePath)
{
	std::ifstream fileStream(filePath, std::ios::binary);
	return std::vector<char>(
		(std::istreambuf_iterator<char>(fileStream)),
		(std::istreambuf_iterator<char>())
	);
}