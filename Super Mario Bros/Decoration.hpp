#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace engine {


	class Decoration
	{
	public:
		Decoration(const int& x, const int& y, const std::string textureName, const sf::IntRect intRect, gameDataRef data);
		
		void draw();

	private:
		gameDataRef _data;

		sf::Sprite _decoration;

	};


}
