#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <array>
#include <string>
#include "DEFINITIONS.hpp"

namespace Game {

	class HUD
	{
	public:
		HUD(gameDataRef data);

		void update(const int& score, const int& coins, const int& time, const float& cameraX);

		void updateLevel(const int world, const int level, const int& lifes);

		void draw();

		void loadingScreenDraw();

	private:
		gameDataRef _data;

		sf::Clock _clock;

		unsigned short int _animationIterator = 0;

		std::array<sf::IntRect, 6> _coinAnimationFrames = { COIN01, COIN01, COIN01, COIN02, COIN03, COIN04 };

		std::array<sf::IntRect, 6> _coinAnimationFramesUg = { COIN_UG_01, COIN_UG_01, COIN_UG_01, COIN_UG_02, COIN_UG_03, COIN_UG_04 };

		sf::Sprite _coin;

		sf::Sprite _cross;

		sf::Sprite _marioSprite;

		sf::Text _mario;

		sf::Text _world;

		sf::Text _level;

		sf::Text _time;

		sf::Text _scoreText;

		sf::Text _coinText;

		sf::Text _timeText;

		sf::Text _lifes;

		sf::Text _gameOver;
	};


}