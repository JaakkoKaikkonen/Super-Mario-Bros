#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Tile.hpp"

namespace engine {

	class Pipe : public Tile
	{
	public:
		Pipe(const int& x, const int& y, const sf::IntRect& texture, gameDataRef data);
		
		void draw();
		void update();
		void animate();
		sf::Sprite& getTile();

	private:
		gameDataRef _data;

		sf::Sprite _pipe;


	};

}

