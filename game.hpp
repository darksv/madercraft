#ifndef _GAME_HPP
#define _GAME_HPP

#include <array>
#include <SFML\Window.hpp>
#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"

class Game {
protected:
	sf::Window* mWindow;
	sf::VideoMode mVideoMode;
	sf::ContextSettings mSettings;
	bool mRunning;

	Camera* mCamera;

	sf::Clock mClock;

	std::array<GLfloat, 180> mCubeVertices;
	std::vector<Texture> mCubeTextures;
	std::vector<Shader> mShaders;

	GLuint mVAO, mVBO;

	bool mFirstMouse = true;
	int mLastX, mLastY;

public:
	Game();

	void processEvents();
	void draw();
	void loop();

	void centerMouseCursor();
};

#endif