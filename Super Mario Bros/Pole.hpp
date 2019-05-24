#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "Game.hpp"

namespace Game {

	class Pole
	{
	public:
		Pole(gameDataRef data);

		void draw();

		void setPosition(const int x, const int y);

		bool updateFlag(const float& dt);

	public:
		std::array<sf::Sprite, 10> poleSprites = {};

		bool lowerFlag = false;

	private:
		gameDataRef _data;

		sf::Sprite _flag;

		float _scale = 4.0f;

		float _flagSpeed = 300.0f;

	};

}

