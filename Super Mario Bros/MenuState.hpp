#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include <array>

namespace engine {

	class MenuState : public State
	{
	public:
		MenuState(gameDataRef data);

		void init();

		void handleInput(const float& dt);
		void update(const float& dt);
		void draw();


	private:
		gameDataRef _data;

		sf::Sprite _menuBackground;

		sf::Sprite _menuLogo;

		sf::Sprite _menuCursor;

		sf::Text _1PlayerGame;

		sf::Text _2PlayerGame;

		sf::Text _topScore;

		unsigned short int _cursorPosition = 0;

		std::array<sf::Vector2f, 2> _cursorPositions = { };

	};

}