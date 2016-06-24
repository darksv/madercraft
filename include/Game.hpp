#pragma once

#include <SFML/Window.hpp>

#include "BlockModel.hpp"
#include "Camera.hpp"
#include "Chunk.hpp"
#include "World.hpp"

namespace mc
{

class Game
{
protected:
	sf::Window* window_;
	camera::Camera camera_;
	World world_;
	sf::Clock clock_;
	GLContext context_;
	std::unique_ptr<GLShaderProgram> shader_;
	std::vector<std::unique_ptr<GLTexture>> textures_;

	bool isRunning_;
	unsigned int framesPerSecond_;

	std::map<BlockKind, BlockModel*> blocks_;

	bool isCursorPositionSet_ = false;
	bool isCursorCenteringEnabled_ = true;
	sf::Event::MouseMoveEvent previousCursorPosition_;

public:
	Game(sf::Window* window);

	void processEvents();
	void update(sf::Time delta);
	void render();
	void loop();

	bool isChunkVisibleByCamera(const Chunk& chunk, const camera::Camera& camera);
	void drawChunk(Chunk &chunk);

	void updateViewport();
	sf::Vector2i getWindowCenterPosition();
	void setCursorAtWindowCenter();
};

}
