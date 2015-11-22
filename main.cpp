#include <iostream>

#include "game.hpp"
#include "shader.hpp"

int main()
{
	sf::ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.antialiasingLevel = 16;
	settings.depthBits = 24;

	sf::VideoMode videoMode = sf::VideoMode::getFullscreenModes().at(0);
	videoMode.width /= 2;
	videoMode.height /= 2;
	

	sf::Window window = sf::Window(videoMode, "Madercraft", sf::Style::Default, settings);
	
	Game game(&window);
	game.loop();

	return 0;
}