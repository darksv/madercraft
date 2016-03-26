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
	return camera_.getProjectionMatrix((float)windowSize.x / (float)windowSize.y);
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

	updateViewport();

	Texture* t1 = textureManager_.loadTextureFromFile("textures\\cube_top.raw");
	Texture* t2 = textureManager_.loadTextureFromFile("textures\\cube_bottom.raw");
	Texture* t3 = textureManager_.loadTextureFromFile("textures\\cube_side.raw");

	ShaderProgram* s = new ShaderProgram();
	s->addShaderFromFile(ShaderType::VERTEX_SHADER, "shaders\\cube.vs");
	s->addShaderFromFile(ShaderType::FRAGMENT_SHADER, "shaders\\cube.frag");
	s->compile();

	blocks_[BlockKind::DIRT]  = (BlockModel*)new BlockGrass(t1, t2, t3, s);
	blocks_[BlockKind::GRASS] = (BlockModel*)new BlockGrass(t2, t2, t3, s);

	world_.createRandomizedChunk(glm::vec3(0, 0, 0));
	world_.createRandomizedChunk(glm::vec3(0, 1, 0));
	world_.createRandomizedChunk(glm::vec3(0, 0, 1));
}

void Game::loop()
{
	sf::Clock gameClock;

	sf::Time lastTime = gameClock.getElapsedTime();
	while (isRunning_)
	{
		auto currentTime = gameClock.getElapsedTime();
		auto elapsed = currentTime - lastTime;
		{
			processEvents();
			update(elapsed);
			render();
		}
		lastTime = currentTime;

		framesPerSecond_ = (unsigned int)(1.0 / elapsed.asSeconds());		
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window_->pollEvent(event))
	{
		if (event.type == sf::Event::Resized)
		{
			updateViewport();
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
			else if (event.key.code == sf::Keyboard::F)
			{
				auto fv = camera_.getFrustumVertices();
				auto fp = camera_.getFrustumPlanes();

				std::cout << std::endl;
				std::cout << "ftl=(" << fv.ftl.x << ", " << fv.ftl.y << ", " << fv.ftl.z << ")" << std::endl;
				std::cout << "ftr=(" << fv.ftr.x << ", " << fv.ftr.y << ", " << fv.ftr.z << ")" << std::endl;
				std::cout << "fbl=(" << fv.fbl.x << ", " << fv.fbl.y << ", " << fv.fbl.z << ")" << std::endl;
				std::cout << "fbr=(" << fv.fbr.x << ", " << fv.fbr.y << ", " << fv.fbr.z << ")" << std::endl;
				std::cout << "ntl=(" << fv.ntl.x << ", " << fv.ntl.y << ", " << fv.ntl.z << ")" << std::endl;
				std::cout << "ntr=(" << fv.ntr.x << ", " << fv.ntr.y << ", " << fv.ntr.z << ")" << std::endl;
				std::cout << "nbl=(" << fv.nbl.x << ", " << fv.nbl.y << ", " << fv.nbl.z << ")" << std::endl;
				std::cout << "nbr=(" << fv.nbr.x << ", " << fv.nbr.y << ", " << fv.nbr.z << ")" << std::endl;
				std::cout << std::endl;
				std::cout << "far=(" << fp.far.x << ", " << fp.far.y << ", " << fp.far.z << ", " << fp.far.w << ")" << std::endl;
				std::cout << "near=(" << fp.near.x << ", " << fp.near.y << ", " << fp.near.z << ", " << fp.near.w << ")" << std::endl;
				std::cout << "top=(" << fp.top.x << ", " << fp.top.y << ", " << fp.top.z << ", " << fp.top.w << ")" << std::endl;
				std::cout << "bottom=(" << fp.bottom.x << ", " << fp.bottom.y << ", " << fp.bottom.z << ", " << fp.bottom.w << ")" << std::endl;
				std::cout << "left=(" << fp.left.x << ", " << fp.left.y << ", " << fp.left.z << ", " << fp.left.w << ")" << std::endl;
				std::cout << "right=(" << fp.right.x << ", " << fp.right.y << ", " << fp.right.z << ", " << fp.right.w << ")" << std::endl;
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

	auto pickedBlock = world_.getBlockIntersectedByLine(camera_.getDirection(), camera_.getPosition());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		world_.putBlockAt(BlockKind::DIRT, pickedBlock);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		world_.putBlockAt(BlockKind::NONE, pickedBlock);
	}
}

void Game::update(sf::Time delta)
{
	auto cameraDirection = camera_.getDirection();
	auto cameraPosition = camera_.getPosition();
	auto currentBlockPosition = world_.getBlockByPosition(camera_.getPosition());
	auto currentChunkPosition = world_.getChunkPositionByBlock(currentBlockPosition);

	std::cout << "\r";
	std::cout << framesPerSecond_ << "fps";
	std::cout << " ";
	std::cout << "(" << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << ")";
	std::cout << " ";
	std::cout << "(" << currentBlockPosition.x << ", " << currentBlockPosition.y << ", " << currentBlockPosition.z << ")";
	std::cout << " ";
	std::cout << "(" << currentChunkPosition.x << ", " << currentChunkPosition.y << ", " << currentChunkPosition.z << ")";
	std::cout << " ";
	std::cout << "(" << cameraDirection.x << ", " << cameraDirection.y << ", " << cameraDirection.z << ")";
}

void Game::drawChunk(Chunk& chunk)
{
	auto positions = chunk.getCalculatedPositions();
	
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

	for (Chunk& chunk : world_.getAllChunks())
	{
		const auto vertices = chunk.getVertices();
		
		// find mins and maxes for each axis
		auto x = std::minmax_element(vertices.begin(), vertices.end(), [](glm::vec3 const& left, glm::vec3 const& right) {
			return left.x < right.x;
		});
		auto y = std::minmax_element(vertices.begin(), vertices.end(), [](glm::vec3 const& left, glm::vec3 const& right) {
			return left.y < right.y;
		});
		auto z = std::minmax_element(vertices.begin(), vertices.end(), [](glm::vec3 const& left, glm::vec3 const& right) {
			return left.z < right.z;
		});

		bool isInFrustum = true;

		for (auto& plane : camera_.getFrustumPlanes().planes)
		{
			const glm::vec3 min(x.first->x, y.first->y, z.first->z);
			const glm::vec3 max(x.second->x, y.second->y, z.second->z);

			glm::vec3 p(min), n(max);

			// finding P and N vertices (based on http://www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-testing-boxes-ii/)

			if (plane.x >= 0)
			{
				p.x = max.x;
				n.x = min.x;
			}
				
			if (plane.y >= 0)
			{
				p.y = max.y;
				n.y = min.y;
			}
				
			if (plane.z >= 0)
			{
				p.z = max.z;
				n.z = min.z;
			}
				
			if (glm::dot(plane, glm::vec4(p, 1.0)) < 0) // outside frustum
			{
				isInFrustum = false;
				break;
			}
			else if (glm::dot(plane, glm::vec4(n, 1.0)) < 0) // intersects
				break;
			
		}

		if (isInFrustum)
			drawChunk(chunk);
	}
	
	window_->display();
}

void Game::updateViewport()
{
	auto windowSize = window_->getSize();

	glViewport(0, 0, windowSize.x, windowSize.y);
	camera_.updateAspectRatio((float)windowSize.x / (float)windowSize.y);
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