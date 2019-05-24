#include "MenuState.hpp"
#include <fstream>
#include <string>

namespace Game {

	MenuState::MenuState(gameDataRef data)
		: _data(data), _menuBackground(_data->assets.getTexture("Menu")), _menuLogo(_data->assets.getTexture("HUD"), MENU_LOGO),
		  _1PlayerGame("1 PLAYER GAME", _data->assets.getFont("Font"), 35), _pressEnter("PRESS ENTER TO PLAY", _data->assets.getFont("Font"), 35),
		  _topScore("TOP- 000000", _data->assets.getFont("Font"), 35)
	{
	}


	void MenuState::init() {
		//Read highscore
		std::ifstream highScoreFile;
		highScoreFile.open(HIGH_SCORE_FILEPATH);

		if (highScoreFile.is_open()) {
			int highScore;
			highScoreFile >> highScore;
			_topScore.setString(std::string("TOP- ") + std::string("000000").erase(0, std::to_string(highScore).length()) + std::to_string(highScore));
		} else {
			std::cout << "Highscore file not found" << std::endl;
		}


		_menuLogo.setScale(4.0f, 4.0f);
		_menuLogo.setPosition(SCREEN_WIDTH / 2 - _menuLogo.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.14f);
		_1PlayerGame.setPosition(SCREEN_WIDTH / 2 - _1PlayerGame.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.57f);
		_pressEnter.setPosition(SCREEN_WIDTH / 2 - _pressEnter.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.66f);
		_topScore.setPosition(SCREEN_WIDTH / 2 - _topScore.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.75f);
	}

	void MenuState::handleInput(const float& dt) {
		sf::Event event;
		while (_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			_data->machine.addState(stateRef(new GameState(_data)), true);
		}

	}

	void MenuState::update(const float& dt) {
		
	}

	void MenuState::draw() {
		_data->window.clear();

		_data->window.draw(_menuBackground);
		_data->window.draw(_menuLogo);
		_data->window.draw(_1PlayerGame);
		_data->window.draw(_pressEnter);
		_data->window.draw(_topScore);

		_data->window.display();
	}




}
