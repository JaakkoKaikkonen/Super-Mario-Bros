#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Item.hpp"
#include "Mario.hpp"
#include <vector>

namespace engine {


	class Tile
	{
	public:

		Tile() = default;
		Tile(const int& x, const int& y, const sf::IntRect& texture, gameDataRef data);

		virtual void draw();
		virtual void update(std::vector<Item*>& items, std::vector<Tile*>& tiles, Mario& mario);
		virtual void animate(const float& dt);
		virtual sf::Sprite& getTile();

	private:
		gameDataRef _data;
		sf::Sprite _tile;
		

	};



}

