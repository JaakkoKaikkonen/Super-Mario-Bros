#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Tile.hpp"
#include "DEFINITIONS.hpp"

namespace engine {

	class Platform : public Tile
	{
	public:
		Platform(const int x, const int y, Mario& mario, gameDataRef data);

		void draw();
		void update(std::vector<Item*>& items, Mario& mario);
		void animate(const float& dt);
		sf::Sprite& getTile();


	private:
		gameDataRef _data;

		sf::Sprite _tile;

		Mario& _mario;

	};



}