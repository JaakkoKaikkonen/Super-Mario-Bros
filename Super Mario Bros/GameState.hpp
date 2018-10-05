#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "State.hpp"
#include "MenuState.hpp"
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
#include "Enemy.hpp"
#include "Goomba.hpp"
#include "FireBall.hpp"
#include "Money.hpp"
#include "HUD.hpp"
#include "Score.hpp"


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

		int numberOfCollisionGrids;

		Mario _mario;

		Pole _pole;

		Castle _castle;

		HUD _HUD;

		int _score = 0;

		int _coins = 0;

		sf::Clock _clock;

		unsigned int _time = 400;

		enum Level { Level01 = 1, Level02 };

		enum World { World01 = 1, World02 };

		Level _level = Level01;

		World _world = World01;

		std::vector<Money> _money;

		std::vector<Score> _scores;

		std::vector<FireBall> _fireBalls;

		std::vector<Item*> _items;

		std::vector<Decoration> _levelDecorations;

		std::vector<Tile*> _levelTiles;

		std::vector<Enemy*> _enemies;

		std::vector<CollisionGrid> _collisionGrid;

		float _jumpTimer = 0;

		float _fireBallTimer = 0;

		float _deadTimer;

		float _insideCastleCounter;

		short int _lifes = 3;

		bool _downKeyPressed = false;

		bool _warning = true;

	};

}

