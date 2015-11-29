#include <map>
#include <GL\glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "game.hpp"
#include "grass.hpp"
#include "dirt.hpp"

glm::mat4 Game::getProjectionMatrix()
{
	sf::Vector2u windowSize = window_->getSize();
	return glm::perspective(45.0f, (float)windowSize.x / (float)windowSize.y, 0.1f, 100.0f);
}

Game::Game(sf::Window* window)
	: window_(window)
{
	window_->setMouseCursorVisible(false);

	isRunning_ = true;

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	Texture *t1 = new Texture("textures\\cube_top.raw");
	Texture *t2 = new Texture("textures\\cube_bottom.raw");
	Texture *t3 = new Texture("textures\\cube_side.raw");
	Shader *s1 = new Shader("shaders\\cube.vs", "shaders\\cube.frag");

	blocks_.push_back((BlockModel*)new BlockGrass(t1, t2, t3, s1));
	blocks_.push_back((BlockModel*)new BlockDirt(t2, t2, t3, s1));
}

void Game::loop()
{
	while (isRunning_)
	{
		processEvents();
		render();
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

	GLfloat cameraSpeed = 0.65f;

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
}

void Game::drawChunk(Chunk& chunk, glm::vec3 position)
{
	std::map<size_t, std::vector<glm::vec3>> positions;

	for (int x = 0; x < 32; ++x)
	{
		for (int y = 0; y < 32; ++y)
		{
			for (int z = 0; z < 32; ++z)
			{
				if (x > 0 && x < 31 && y > 0 && y < 31 && z > 0 && z < 31)
					continue;

				bool kind = sqrt(pow(x - 15.5, 2) + pow(y - 15.5, 2)) > 16 ? 0 : 1;

				positions[kind].push_back(position + glm::vec3(x, y, z + kind));
			}
		}
	}

	

	for (size_t i = 0; i < blocks_.size(); ++i)
	{
		Shader* shader = blocks_[i]->getShader();

		GLint timeUniform = shader->getUniform("globalTime_");
		glUniform1f(timeUniform, clock_.getElapsedTime().asSeconds());

		GLuint viewUniform = shader->getUniform("viewMatrix");
		glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(camera_.getViewMatrix()));

		GLuint projectionUniform = shader->getUniform("projectionMatrix");
		glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(getProjectionMatrix()));

		blocks_[i]->draw(positions[i]);
	}
}

void Game::render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawChunk(Chunk(), glm::vec3(0.0f, 0.0f, 0.0f));

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