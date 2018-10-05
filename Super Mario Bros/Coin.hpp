#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "Game.hpp"
#include "Item.hpp"
#include "DEFINITIONS.hpp"
#include "Score.hpp"
#include "CollisionGrid.hpp"


namespace engine {


	class Coin : public Item
	{
	public:
		Coin(const int x, const int y, int& coins, std::vector<Score>& scores, gameDataRef data);
	
		void draw();

		void animate();

		void update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario);

		bool shouldBeDeleted();

	private:
		gameDataRef _data;

		sf::Sprite _coin;

		unsigned short int _coinAnimationIterator = 0;

		std::array<sf::IntRect, 4> _coinAnimationFrames = { COIN_ITEM1, COIN_ITEM2, COIN_ITEM3, COIN_ITEM4 };
														   
		sf::Clock _clock;

		float _startingY;

		bool _delete = false;

		bool _turn = true;
														   
		float _speed = -700;

		float _animationHeight = -200;

		std::vector<Score>& _scores;

	};



}

