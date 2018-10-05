#include "Game.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace engine {

	Game::Game(int width, int height, std::string title) {

		sf::Image icon;
		icon.loadFromFile(TOP_ICON_FILEPATH);

		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		_data->window.setFramerateLimit(240);

		_data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		//Load textures
		_data->assets.loadTexture("Mario", MARIO_TEXTURES_FILEPATH);
		_data->assets.loadTexture("Blocks", BLOCK_TEXTURES_FILEPATH);
		_data->assets.loadTexture("Tiles", TILE_TEXTURES_FILEPATH);
		_data->assets.loadTexture("Items", ITEM_TEXTURES_FILEPATH);
		_data->assets.loadTexture("Castle", CASTLE_TEXTURES_FILEPATH);


		_data->machine.addState(stateRef(new GameState(_data)), true);

		this->run();
	}

	void Game::run() {
		float newTime, frameTime;

		float currentTime = this->_clock.getElapsedTime().asSeconds();


		while (this->_data->window.isOpen()) {
			this->_data->machine.processStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();

			frameTime = newTime - currentTime;

			currentTime = newTime;

			if (frameTime > 0.15f) {
				frameTime = 0.15f;
			}

			this->_data->machine.getActiveState()->handleInput(frameTime);
			this->_data->machine.getActiveState()->update(frameTime);
			this->_data->machine.getActiveState()->draw();

			std::cout << 1 / frameTime << std::endl;
		}


	}


}