#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.hpp"

namespace engine {

	class CollisionGrid
	{
	public:
		CollisionGrid(const int x, const int y, const int width, const int height);

		~CollisionGrid();


	public:
		sf::FloatRect boundary;

		std::vector<Tile*> tiles;


	};


}