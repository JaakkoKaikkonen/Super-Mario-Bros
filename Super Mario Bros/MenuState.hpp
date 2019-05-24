#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include <iostream>
#include "DEFINITIONS.hpp"
#include <array>

namespace Game {

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

		sf::Text _1PlayerGame;

		sf::Text _pressEnter;

		sf::Text _topScore;

	};

}