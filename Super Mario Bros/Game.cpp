#include "Game.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace engine {

	Game::Game(int width, int height, std::string title) {

		sf::Image icon;
		icon.loadFromFile(TOP_ICON_FILEPATH);

		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		_data->window.setVerticalSyncEnabled(true);
		//_data->window.setFramerateLimit(60);

		_data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		//Load textures
		_data->assets.loadFont("Font", FONT_FILE_PATH);
		_data->assets.loadTexture("Mario", MARIO_TEXTURES_FILEPATH);
		_data->assets.loadTexture("Blocks", BLOCK_TEXTURES_FILEPATH);
		_data->assets.loadTexture("Tiles", TILE_TEXTURES_FILEPATH);
		_data->assets.loadTexture("Items", ITEM_TEXTURES_FILEPATH);
		_data->assets.loadTexture("Castle", CASTLE_TEXTURES_FILEPATH);
		_data->assets.loadTexture("Enemies", ENEMY_TEXTURES_FILEPATH);
		_data->assets.loadTexture("HUD", HUD_TECTURES_FILEPATH);
		_data->assets.loadTexture("Menu", MENU_BACKGROUND_FILEPATH);
		_data->assets.loadSound("Jump_small", JUMP_SMALL_SOUND_FILEPATH);
		_data->assets.loadSound("Jump_big", JUMP_BIG_SOUND_FILEPATH);
		_data->assets.loadSound("Coin", COIN_SOUND_FILEPATH);
		_data->assets.loadSound("Powerup_appear", POWERUP_APPEARS_SOUND_FILEPATH);
		_data->assets.loadSound("Powerup", POWERUP_SOUND_FILEPATH);
		_data->assets.loadSound("Break_block", BREAK_BLOCK_SOUND_FILEPATH);
		_data->assets.loadSound("Fireball", FIREBALL_SOUND_FILEPATH);
		_data->assets.loadSound("Kick", KICK_SOUND_FILEPATH);
		_data->assets.loadSound("Stomp", STOMP_SOUND_FILEPATH);
		_data->assets.loadSound("Bump", BUMP_SOUND_FILEPATH);
		_data->assets.loadSound("Mario_die", MARIO_DIE_SOUND_FILEPATH);
		_data->assets.loadSound("Pipe", PIPE_SOUND_FILEPATH);
		_data->assets.loadSound("Flagpole", FLAGPOLE_SOUND_FILEPATH);
		_data->assets.loadSound("Stage_clear", STAGE_CLEAR_SOUND_FILEPATH);
		_data->assets.loadSound("Warning", WARNING_SOUND_FILEPATH);
		_data->assets.loadSound("GameOver", GAMEOVER_SOUND_FILEPATH);
		

		_data->machine.addState(stateRef(new MenuState(_data)), true);

		this->run();
	}

	void Game::run() {
		float newTime, frameTime;

		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;


		while (this->_data->window.isOpen()) {
			this->_data->machine.processStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();

			frameTime = newTime - currentTime;

			currentTime = newTime;

			if (frameTime > 0.15f) {
				frameTime = 0.15f;
			}

			accumulator += frameTime;

			//std::cout << frameTime << std::endl;

			while (accumulator >= dt)
			{
				this->_data->machine.getActiveState()->handleInput(dt);
				this->_data->machine.getActiveState()->update(dt);

				accumulator -= dt;
			}

		
			this->_data->machine.getActiveState()->draw();

			//std::cout << 1 / frameTime << std::endl;
		}


	}


}