#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Mario.hpp"

namespace engine {

	class Castle
	{
	public:
		Castle(gameDataRef data);

		void draw();

		void setPosition(const int x, const int y, sf::IntRect castle, sf::IntRect flag);
		
		bool insideCastle(Mario& mario);

		void raiseFlag(const float& dt);

	private:
		gameDataRef _data;

		sf::Sprite _castle;

		sf::Sprite _flag;

		float _flagSpeed = 175.0f;
	};


}

