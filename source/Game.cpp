#include <chrono>
#include <iostream>
#include <map>

#include <Windows.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <json11.hpp>

#include "BlockModel.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "GLShaderProgram.hpp"
#include "GLContext.hpp"
#include "helpers.hpp"
#include <FontManager.hpp>

namespace mc
{

Game::Game()
{
	SDL_Init(SDL_INIT_VIDEO);

	window_ = SDL_CreateWindow("MaderCraft",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480,
		SDL_WINDOW_OPENGL);

	oglContext_ = SDL_GL_CreateContext(window_);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GL_SetSwapInterval(0);


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
	cubeVertices.reserve(36);

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
		for (auto& t : item["textures"].array_items())
		{
			auto textureData = getFileContent("resources/textures/" + t.string_value());

			textures_.push_back(context_.getTexture(GL_TEXTURE_2D, 128, 128, textureData.data()));
		}
		
		auto blockKind = static_cast<BlockKind>(item["id"].int_value());

		blocks_[blockKind] = new BlockModel(mesh, textures_[0].get(), textures_[1].get(), textures_[2].get(), shader_.get());
	}

	for (size_t i = 0; i < 1; i++)
		for (size_t j = 0; j < 1; j++)
			for (size_t k = 0; k < 1; k++)
				world_.createRandomizedChunk(glm::vec3(i, j, k));
}

Game::~Game()
{
	SDL_GL_DeleteContext(oglContext_);
	SDL_DestroyWindow(window_);
}

void Game::run()
{
	using namespace std::chrono;

	while (isRunning_)
	{
		const auto timeStart = steady_clock::now();
		{
			processEvents();
			update(1.0/30.0);
			render();
		}
		const auto timeEnd = steady_clock::now();

		framesPerSecond_ = static_cast<decltype(framesPerSecond_)>(1.0 / duration_cast<duration<float>>(timeEnd - timeStart).count());
	}
}



void Game::processEvents()
{
	GLfloat mouseSensitivity = 0.45f;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT_RESIZED:
			updateViewport();
			break;
		case SDL_WINDOWEVENT_CLOSE:
			isRunning_ = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				isRunning_ = false;
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			camera_.rotate(event.motion.xrel * mouseSensitivity, -event.motion.yrel * mouseSensitivity);
			break;
		}
	}

	const auto scan = SDL_GetKeyboardState(nullptr);

	if (scan[SDL_SCANCODE_W])
		camera_.moveForward();

	if (scan[SDL_SCANCODE_S])
		camera_.moveBackward();

	if (scan[SDL_SCANCODE_A])
		camera_.moveLeft();

	if (scan[SDL_SCANCODE_D])
		camera_.moveRight();

	if (scan[SDL_SCANCODE_LSHIFT])
		camera_.moveDown();

	if (scan[SDL_SCANCODE_SPACE])
		camera_.moveUp();

	const auto pickedBlock = world_.getBlockIntersectedByLine(camera_.getDirection(), camera_.getPosition());

	const auto mouseState = SDL_GetMouseState(NULL, NULL);

	if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
		world_.putBlockAt(BlockKind::Dirt, pickedBlock);

	if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
		world_.putBlockAt(BlockKind::None, pickedBlock);
}

void Game::update(float delta)
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
		shader->setUniform("globalTime_", 0);
		shader->setUniform("viewMatrix", camera_.getViewMatrix());
		shader->setUniform("projectionMatrix", camera_.getProjectionMatrix());
		shader->use();

		textures_[0]->bind();
		blockModel->getMesh()->drawMultiple(context_, blockPositions);
		textures_[0]->unbind();
	}
}

void Game::render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT, GL_LINE);

	for (Chunk& chunk : world_.getAllChunks())
	{
		if (isChunkVisibleByCamera(chunk, camera_))
			drawChunk(chunk);
	}
	
	SDL_GL_SwapWindow(window_);
}

void Game::updateViewport()
{
	glm::ivec2 windowSize;
	SDL_GetWindowSize(window_, &windowSize.x, &windowSize.y);

	glViewport(0, 0, windowSize.x, windowSize.y);
	camera_.changeViewportDimensions(glm::uvec2(windowSize.x, windowSize.y));
}

}
