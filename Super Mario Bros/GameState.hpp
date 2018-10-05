#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "State.hpp"
#include "Game.hpp"
#include "Mario.hpp"
#include "Tile.hpp"
#include "BrickTile.hpp"
#include "BoxTile.hpp"
#include "Pipe.hpp"
#include "Decoration.hpp"
#include "Item.hpp"
#include "Pole.hpp"
#include "Castle.hpp"
#include "CollisionGrid.hpp"

namespace engine {

	class GameState : public State
	{
	public:
		GameState(gameDataRef data);

		void init();

		void handleInput(const float& dt);
		void update(const float& dt);
		void draw();

	private:
		gameDataRef _data;

		Mario _mario;

		Pole _pole;

		Castle _castle;

		enum Level { Level01, Level02 };

		Level _level = Level01;

		std::vector<Item*> _items;

		std::vector<Decoration> _levelDecorations;

		std::vector<Tile*> _levelTiles;

		std::vector<CollisionGrid> _collisionGrid;

		float _jumpTimer = 0;

	};

}

