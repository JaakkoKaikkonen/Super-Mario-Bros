#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Game.hpp"
#include "Tile.hpp"
#include "Item.hpp"
#include "Score.hpp"

namespace engine {

	class BrickTile : public Tile
	{
	public:
		BrickTile() = default;
		BrickTile(const int& x, const int& y, Items item, Setting setting, int& coins, std::vector<Score>& scores, gameDataRef data);

		void draw();
		void update(std::vector<Item*>& items, Mario& mario);
		void animate(const float& dt);
		sf::Sprite& getTile();

	private:
		gameDataRef _data;

		sf::Sprite _tile;

		Items _item;

		sf::Clock _clock;

		sf::Clock _clock2;

		std::array<sf::IntRect, 2> _particleAnimationFrames = { };

		char _particleAnimationIterator = 0;

		sf::Sprite _particles[4];

		sf::Vector2f _rightParticlesVector;

		sf::Vector2f _leftParticlesVector;

		char _coinCounter = 10;

		float particleAnimationSpeed = 475.0f;

		float _animationHeight = -17.0f;

		float _animationSpeedY = -300;

		float _tileY = 0;

		bool _opened = false;

		bool _bounce = false;
		
		bool _explode = false;

		bool _destroyed = false;

		int& _coins;

		std::vector<Score>& _scores;

	};

}

