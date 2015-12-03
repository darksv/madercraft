#pragma once

#include <SFML\Window.hpp>

#include "BlockModel.hpp"
#include "Camera.hpp"
#include "Chunk.hpp"
#include "World.hpp"

class Game
{
protected:
	sf::Window* window_;
	Camera camera_;
	World world_;
	Chunk chunk_;
	glm::vec3 chunkPosition_;
	sf::Clock clock_;

	bool isRunning_;

	std::vector<BlockModel*> blocks_;

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