#include "MenuState.hpp"

namespace engine {

	MenuState::MenuState(gameDataRef data)
		: _data(data), _menuBackground(_data->assets.getTexture("Menu")), _menuLogo(_data->assets.getTexture("HUD"), MENU_LOGO), _menuCursor(_data->assets.getTexture("HUD"), MENU_CURSOR),
		  _1PlayerGame("1 PLAYER GAME", _data->assets.getFont("Font"), 35), _2PlayerGame("2 PLAYER GAME", _data->assets.getFont("Font"), 35), _topScore("TOP- 000000", _data->assets.getFont("Font"), 35)
	{
	}


	void MenuState::init() {
		_menuLogo.setScale(4.0f, 4.0f);
		_menuCursor.setScale(4.0f, 4.0f);
		_menuLogo.setPosition(SCREEN_WIDTH / 2 - _menuLogo.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.14f);
		_1PlayerGame.setPosition(SCREEN_WIDTH / 2 - _1PlayerGame.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.57f);
		_2PlayerGame.setPosition(SCREEN_WIDTH / 2 - _2PlayerGame.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.65f);
		_topScore.setPosition(SCREEN_WIDTH / 2 - _topScore.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.75f);

		_cursorPositions[0] = sf::Vector2f(_1PlayerGame.getPosition().x - 55.0f, _1PlayerGame.getPosition().y + 5.0f);
		_cursorPositions[1] = sf::Vector2f(_2PlayerGame.getPosition().x - 55.0f, _2PlayerGame.getPosition().y + 5.0f);

		_menuCursor.setPosition(_cursorPositions[_cursorPosition]);
	}

	void MenuState::handleInput(const float& dt) {
		sf::Event event;
		while (_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			_data->machine.addState(stateRef(new GameState(_data)), true);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (_cursorPosition != _cursorPositions.size() - 1) {
				_cursorPosition++;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (_cursorPosition) {
				_cursorPosition--;
			}
		}


	}

	void MenuState::update(const float& dt) {
		_menuCursor.setPosition(_cursorPositions[_cursorPosition]);
	}

	void MenuState::draw() {
		_data->window.clear();

		_data->window.draw(_menuBackground);
		_data->window.draw(_menuLogo);
		_data->window.draw(_1PlayerGame);
		_data->window.draw(_2PlayerGame);
		_data->window.draw(_topScore);
		_data->window.draw(_menuCursor);

		_data->window.display();
	}




}
