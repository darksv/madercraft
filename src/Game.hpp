#pragma once

#include <SDL.h>
#include "BlockModel.hpp"
#include "Camera.hpp"
#include "Chunk.hpp"
#include "World.hpp"

namespace mc
{

class Game
{
protected:
	SDL_Window* window_;
    SDL_GLContext oglContext_;

	camera::Camera camera_;
	World world_;
	GLContext context_;
	std::unique_ptr<GLShaderProgram> shader_;
	std::vector<std::unique_ptr<GLTexture>> textures_;

	bool isRunning_;
	unsigned int framesPerSecond_;

	std::map<BlockKind, BlockModel*> blocks_;

public:
	Game();
    ~Game();

	void processEvents();
	void update(float delta);
	void render();
	void run();

	bool isChunkVisibleByCamera(const Chunk& chunk, const camera::Camera& camera);
	void drawChunk(Chunk &chunk);

	void updateViewport();
};

}
