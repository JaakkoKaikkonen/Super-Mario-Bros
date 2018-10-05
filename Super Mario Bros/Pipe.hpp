#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Tile.hpp"
#include "Mario.hpp"

namespace engine {

	class Pipe : public Tile
	{
	public:
		Pipe(const int& x, const int& y, const sf::IntRect& texture, Mario& mario, const bool isPortal, gameDataRef data);
		
		void draw();
		void update();
		void animate(const float& dt);
		sf::Sprite& getTile();

	public:
		static bool teleport;

	private:
		gameDataRef _data;

		sf::Sprite _pipe;

		bool _isPortal;

		bool _teleported = false;

		Mario& _mario;

	};


}

