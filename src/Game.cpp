#include <iostream>
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Dirt.hpp"
#include "Game.hpp"
#include "Grass.hpp"
#include "ShaderProgram.hpp"

glm::mat4 Game::getProjectionMatrix()
{
	sf::Vector2u windowSize = window_->getSize();
	return glm::perspective(45.0f, (float)windowSize.x / (float)windowSize.y, 0.1f, 100.0f);
}

Game::Game(sf::Window* window) :
	window_(window)
{
	window_->setMouseCursorVisible(false);

	isRunning_ = true;

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	Texture* t1 = textureManager_.loadTextureFromFile("textures\\cube_top.raw");
	Texture* t2 = textureManager_.loadTextureFromFile("textures\\cube_bottom.raw");
	Texture* t3 = textureManager_.loadTextureFromFile("textures\\cube_side.raw");

	ShaderProgram* s = new ShaderProgram();
	s->addShaderFromFile(ShaderType::VERTEX_SHADER, "shaders\\cube.vs");
	s->addShaderFromFile(ShaderType::FRAGMENT_SHADER, "shaders\\cube.frag");
	s->compile();

	blocks_[BlockKind::DIRT] = (BlockModel*)new BlockGrass(t1, t2, t3, s);
	blocks_[BlockKind::GRASS] = (BlockModel*)new BlockGrass(t2, t2, t3, s);

	for (size_t i = 0; i < 4; ++i)
		chunks_[i] = world_.generateChunk(glm::vec3(i * 32, 0.0f, 0.0f));
}

void Game::loop()
{
	sf::Clock renderClock;

	while (isRunning_)
	{
		sf::Time timeStart = renderClock.getElapsedTime();
		{
			processEvents();
			render();
		}
		sf::Time timeEnd = renderClock.restart();

		unsigned int fps = (unsigned int)(1.0 / (timeEnd - timeStart).asSeconds());

		auto cameraDirection = camera_.getDirection();
		auto cameraPosition = camera_.getPosition();
		auto currentBlockPosition = world_.getBlockByPosition(camera_.getPosition());
		auto currentChunkPosition = world_.getChunkPositionByBlock(currentBlockPosition);

		std::cout << "\r";
		std::cout << fps << "fps";
		std::cout << " ";
		std::cout << "(" << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << ")";
		std::cout << " ";
		std::cout << "(" << currentBlockPosition.x << ", " << currentBlockPosition.y << ", " << currentBlockPosition.z << ")";
		std::cout << " ";
		std::cout << "(" << currentChunkPosition.x << ", " << currentChunkPosition.y << ", " << currentChunkPosition.z << ")";
		std::cout << " ";
		std::cout << "(" << cameraDirection.x << ", " << cameraDirection.y << ", " << cameraDirection.z << ")";
		
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window_->pollEvent(event))
	{
		if (event.type == sf::Event::Resized)
		{
			glViewport(0, 0, event.size.width, event.size.height);
		}
		else if (event.type == sf::Event::Closed)
		{
			isRunning_ = false;
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				isRunning_ = false;
			}
			else if (event.key.code == sf::Keyboard::Tab)
			{
				isCursorCenteringEnabled_ = false;
				window_->setVisible(false);;
			}
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			GLfloat xoffset = 0, yoffset = 0;

			if (! isCursorPositionSet_)
			{
				setCursorAtWindowCenter();
				isCursorPositionSet_ = true;
			}
			
			xoffset = (float)(event.mouseMove.x - previousCursorPosition_.x);
			yoffset = (float)(previousCursorPosition_.y - event.mouseMove.y);
			
			previousCursorPosition_ = event.mouseMove;

			GLfloat sensitivity = 0.45f;

			camera_.rotate(xoffset * sensitivity, yoffset * sensitivity);
		}
	}

	if (isCursorCenteringEnabled_)
	{
		auto centerPosition = getWindowCenterPosition();

		sf::Mouse::setPosition(centerPosition, *window_);
		previousCursorPosition_.x = centerPosition.x;
		previousCursorPosition_.y = centerPosition.y;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		camera_.moveForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		camera_.moveBackward();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		camera_.moveLeft();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		camera_.moveRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		camera_.moveDown();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		camera_.moveUp();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		auto v = world_.getBlockIntersectedByLine(camera_.getDirection(), camera_.getPosition());

		std::cout << std::endl << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
	}
}

void Game::drawChunk(Chunk& chunk)
{
	auto positions = world_.translateChunkBlocks(chunk);

	for (auto item : positions)
	{
		BlockKind blockKind = item.first;
		auto blockPositions = item.second;
		BlockModel* blockModel = blocks_[blockKind];
		ShaderProgram* shader = blockModel->getShaderProgram();

		GLint timeUniform = shader->getUniform("globalTime_");
		glUniform1f(timeUniform, clock_.getElapsedTime().asSeconds());

		GLuint viewUniform = shader->getUniform("viewMatrix");
		glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(camera_.getViewMatrix()));

		GLuint projectionUniform = shader->getUniform("projectionMatrix");
		glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(getProjectionMatrix()));

		blockModel->draw(blockPositions);
	}
}

void Game::render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (size_t i = 0; i < 4; ++i)
		drawChunk(chunks_[i]);
	
	window_->display();
}

sf::Vector2i Game::getWindowCenterPosition()
{
	sf::Vector2u windowSize = window_->getSize();
	
	return sf::Vector2i(windowSize.x / 2, windowSize.y / 2);
}

void Game::setCursorAtWindowCenter()
{
	sf::Mouse::setPosition(getWindowCenterPosition());
}