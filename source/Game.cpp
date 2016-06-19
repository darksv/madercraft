#include <iostream>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <json11.hpp>
#include <Camera.hpp>

#include "BlockModel.hpp"
#include "helpers.hpp"
#include "Game.hpp"
#include "GLShaderProgram.hpp"
#include "GLContext.hpp"

namespace mc
{

Game::Game(sf::Window* window) :
	window_(window)
{
	window_->setMouseCursorVisible(false);

	isRunning_ = true;

	glewExperimental = GL_TRUE;
	glewInit();

	context_.depthTestEnabled(true);
	context_.faceCullingEnabled(true);
	context_.setCullingMode(GL_BACK, GL_CW);

	updateViewport();

	shader_ = context_.getShaderProgram();
	shader_->addShaderFromFile(ShaderType::Vertex, "resources/shaders/cube.vs");
	shader_->addShaderFromFile(ShaderType::Fragment, "resources/shaders/cube.frag");
	shader_->compile();

	std::vector<Vertice> cubeVertices;
	cubeVertices.reserve(180);

	// Bottom face
	cubeVertices.push_back({ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f } }); // BL
	cubeVertices.push_back({ { 0.5f, -0.5f, -0.5f },{ 1.0f, 0.0f } }); // BR
	cubeVertices.push_back({ { 0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f } }); // TR
	cubeVertices.push_back({ { 0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f } }); // TR
	cubeVertices.push_back({ { -0.5f,  0.5f, -0.5f },{ 0.0f, 1.0f } }); // TL
	cubeVertices.push_back({ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f } }); // BL

	// Top face
	cubeVertices.push_back({ { -0.5f, -0.5f,  0.5f },{ 0.0f, 0.0f } }); // BL
	cubeVertices.push_back({ { 0.5f,  0.5f,  0.5f },{ 1.0f, 1.0f } }); // TR
	cubeVertices.push_back({ { 0.5f, -0.5f,  0.5f },{ 1.0f, 0.0f } }); // BR
	cubeVertices.push_back({ { 0.5f,  0.5f,  0.5f },{ 1.0f, 1.0f } }); // TR
	cubeVertices.push_back({ { -0.5f, -0.5f,  0.5f },{ 0.0f, 0.0f } }); // BL
	cubeVertices.push_back({ { -0.5f,  0.5f,  0.5f },{ 0.0f, 1.0f } }); // TL

	// Front face
	cubeVertices.push_back({ { -0.5f,  0.5f,  0.5f },{ 1.0f, 0.0f } }); // TR
	cubeVertices.push_back({ { -0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f } }); // BL
	cubeVertices.push_back({ { -0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f } }); // TL      
	cubeVertices.push_back({ { -0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f } }); // BL
	cubeVertices.push_back({ { -0.5f,  0.5f,  0.5f },{ 1.0f, 0.0f } }); // TR
	cubeVertices.push_back({ { -0.5f, -0.5f,  0.5f },{ 0.0f, 0.0f } }); // BR

	// Back face
	cubeVertices.push_back({ { 0.5f,  0.5f,  0.5f },{ 1.0f, 0.0f } }); // TL
	cubeVertices.push_back({ { 0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f } }); // TR     
	cubeVertices.push_back({ { 0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f } }); // BR
	cubeVertices.push_back({ { 0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f } }); // BR
	cubeVertices.push_back({ { 0.5f, -0.5f,  0.5f },{ 0.0f, 0.0f } }); // BL
	cubeVertices.push_back({ { 0.5f,  0.5f,  0.5f },{ 1.0f, 0.0f } }); // TL

	// Right face
	cubeVertices.push_back({ { -0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f } }); // TR
	cubeVertices.push_back({ { 0.5f, -0.5f,  0.5f },{ 1.0f, 0.0f } }); // BL
	cubeVertices.push_back({ { 0.5f, -0.5f, -0.5f },{ 1.0f, 1.0f } }); // TL
	cubeVertices.push_back({ { 0.5f, -0.5f,  0.5f },{ 1.0f, 0.0f } }); // BL
	cubeVertices.push_back({ { -0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f } }); // TR
	cubeVertices.push_back({ { -0.5f, -0.5f,  0.5f },{ 0.0f, 0.0f } }); // BR

	// Left face
	cubeVertices.push_back({ { -0.5f,  0.5f, -0.5f },{ 0.0f, 1.0f } }); // TL
	cubeVertices.push_back({ { 0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f } }); // TR
	cubeVertices.push_back({ { 0.5f,  0.5f,  0.5f },{ 1.0f, 0.0f } }); // BR
	cubeVertices.push_back({ { 0.5f,  0.5f,  0.5f },{ 1.0f, 0.0f } }); // BR
	cubeVertices.push_back({ { -0.5f,  0.5f,  0.5f },{ 0.0f, 0.0f } }); // BL
	cubeVertices.push_back({ { -0.5f,  0.5f, -0.5f },{ 0.0f, 1.0f } }); // TL

	auto mesh = new Mesh(cubeVertices);

	auto fileContent = getFileContent("resources/blocks.json");
	std::string errorLog;

	auto json = json11::Json::parse(std::string(fileContent.begin(), fileContent.end()), errorLog);
	for (auto& item : json.array_items())
	{
		std::vector<Texture*> textures;
		for (auto& t : item["textures"].array_items())
		{
			auto texture = textureManager_.loadTextureFromFile("resources/textures/" + t.string_value());
			texture->loadToGpu();

			textures.push_back(texture);
		}
		
		auto blockKind = static_cast<BlockKind>(item["id"].int_value());

		blocks_[blockKind] = new BlockModel(mesh, textures[0], textures[1], textures[2], shader_.get());
	}

	world_.createRandomizedChunk(glm::vec3(0, 0, 0));
	//world_.createRandomizedChunk(glm::vec3(0, 1, 0));
	//world_.createRandomizedChunk(glm::vec3(0, 0, 1));
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

		framesPerSecond_ = static_cast<decltype(framesPerSecond_)>(1.0f / elapsed.asSeconds());
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
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			GLfloat xoffset = 0, yoffset = 0;

			if (!isCursorPositionSet_)
			{
				setCursorAtWindowCenter();
				isCursorPositionSet_ = true;
			}

			xoffset = static_cast<float>(event.mouseMove.x - previousCursorPosition_.x);
			yoffset = static_cast<float>(previousCursorPosition_.y - event.mouseMove.y);

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

bool Game::isChunkVisibleByCamera(const Chunk& chunk, const camera::Camera& camera)
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

	for (auto& plane : camera.getFrustumPlanes())
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

	return isInFrustum;
}

void Game::drawChunk(Chunk& chunk)
{
	auto positions = chunk.getCalculatedPositions();

	for (auto item : positions)
	{
		auto blockKind = item.first;
		auto blockPositions = item.second;

		BlockModel* blockModel = blocks_[blockKind];

		auto shader = blockModel->getShaderProgram();
		shader->setUniform("globalTime_", clock_.getElapsedTime().asSeconds());
		shader->setUniform("viewMatrix", camera_.getViewMatrix());
		shader->setUniform("projectionMatrix", camera_.getProjectionMatrix());
		shader->use();

		glBindTexture(GL_TEXTURE_2D, 1);
		blockModel->getMesh()->drawMultiple(context_, blockPositions);
	}
}

void Game::render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (Chunk& chunk : world_.getAllChunks())
	{
		if (isChunkVisibleByCamera(chunk, camera_))
			drawChunk(chunk);
	}

	window_->display();
}

void Game::updateViewport()
{
	auto windowSize = window_->getSize();

	glViewport(0, 0, windowSize.x, windowSize.y);
	camera_.changeViewportDimensions(glm::uvec2(windowSize.x, windowSize.y));
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

}
