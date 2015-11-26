#ifndef _GAME_HPP
#define _GAME_HPP

#include <array>
#include <SFML\Window.hpp>
#include "camera.hpp"
#include "block.hpp"

struct Chunk {};

class Game {
protected:
	sf::Window* window_;
	Camera camera_;
	sf::Clock clock_;

	bool isRunning_;

	BlockGrass* blockGrass_;

	bool isCursorPositionSet_ = false;
	bool isCursorCenteringEnabled_ = true;
	sf::Event::MouseMoveEvent previousCursorPosition_;

	glm::mat4 getProjectionMatrix();

public:
	Game(sf::Window* window);

	void processEvents();
	void render();
	void loop();

	void drawChunk(Chunk &chunk, glm::vec3 position);

	sf::Vector2i getWindowCenterPosition();
	void setCursorAtWindowCenter();
};

#endif