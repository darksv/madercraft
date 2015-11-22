#ifndef _GAME_HPP
#define _GAME_HPP

#include <array>
#include <SFML\Window.hpp>
#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"

struct Chunk {
	char blocks[32][32][32];
};

class Game {
protected:
	sf::Window* window_;

	bool isRunning_;

	Camera camera_;

	sf::Clock clock_;

	std::array<GLfloat, 180> cubeVertices_;
	std::vector<Texture> cubeTextures_;
	std::vector<Shader> shaders_;

	GLuint vao_, vbo_;

	bool isCursorPositionSet_ = false;
	bool isCursorCenteringEnabled_ = true;
	sf::Event::MouseMoveEvent previousCursorPosition_;

public:
	Game(sf::Window* window);

	void processEvents();
	void draw();
	void loop();

	void drawChunk(Chunk &chunk, glm::vec3 position);

	sf::Vector2i getWindowCenterPosition();
	void setCursorAtWindowCenter();
};

#endif