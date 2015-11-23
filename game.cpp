#include <GL\glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "game.hpp"

Game::Game(sf::Window* window)
	: window_(window)
{
	cubeVertices_ = {{
		// top
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

		// bottom
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

		// sides
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f
	}};

	window_->setMouseCursorVisible(false);

	isRunning_ = true;

	glewExperimental = GL_TRUE;
	glewInit();

	cubeTextures_.push_back(Texture("textures\\cube_side.raw"));
	cubeTextures_.push_back(Texture("textures\\cube_top.raw"));
	cubeTextures_.push_back(Texture("textures\\cube_bottom.raw"));

	shaders_.push_back(Shader("shaders\\cube.vs", "shaders\\cube.frag"));


	auto windowSize = window_->getSize();

	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
}

void Game::loop()
{
	while (isRunning_)
	{
		processEvents();
		draw();
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
}

void Game::drawChunk(Chunk& chunk, glm::vec3 position)
{
	GLuint modelUniform = glGetUniformLocation(shaders_[0].getProgram(), "model");

	for (int x = 0; x < 32; ++x)
	{
		for (int y = 0; y < 32; ++y)
		{
			for (int z = 0; z < 32; ++z)
			{
				if (x > 0 && x < 31 && y > 0 && y < 31 && z > 0 && z < 31)
					continue;

				glm::mat4 model;
				model = glm::translate(model, glm::vec3(x, y, z));
				model = glm::translate(model, position);

				glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(model));

				cubeTextures_[1].bind();
				glDrawArrays(GL_TRIANGLES, 6 * 0, 6 * 1);
				cubeTextures_[0].bind();
				glDrawArrays(GL_TRIANGLES, 6 * 2, 6 * 4);
				cubeTextures_[2].bind();
				glDrawArrays(GL_TRIANGLES, 6 * 1, 6 * 1);

				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}
	}
}

void Game::draw()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * cubeVertices_.size(), cubeVertices_.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	shaders_[0].use();

	GLint timeUniform = glGetUniformLocation(shaders_[0].getProgram(), "time");
	glUniform1f(timeUniform, clock_.getElapsedTime().asSeconds());

	GLuint viewUniform = glGetUniformLocation(shaders_[0].getProgram(), "view");
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(camera_.getViewMatrix()));

	sf::Vector2u windowSize = window_->getSize();

	glm::mat4 projection;
	projection = glm::perspective(45.0f, (float)windowSize.x / (float)windowSize.y, 0.1f, 100.0f);
	GLuint projectionUniform = glGetUniformLocation(shaders_[0].getProgram(), "projection");
	glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(vao_);

	//for (int i = 0; i < 4; ++i)
	//{
	//	drawChunk(Chunk(), glm::vec3(0.0f, 0.0f, 0.0f));
	//}

	drawChunk(Chunk(), glm::vec3(0.0f, 0.0f, 0.0f));

	glBindVertexArray(0);

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