#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "CollisionGrid.hpp"
#include "Mario.hpp"
#include <array>
#include <vector>

namespace Game {

	class FireBall
	{
	public:
		FireBall(const int x, const int y, Dir dir, gameDataRef data);

		void draw();
		void update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario);
		void animate();

		bool shouldBeDeleted();

		sf::Sprite& getSprite();

		const Dir& getDirection();

	public:
		bool explode = false;

	private:
		gameDataRef _data;
	
		sf::Sprite _fireBall;

		sf::Clock _clock;

		unsigned short int _animationIterator = 3;

		std::array<sf::IntRect, 4> _animationFrames = { FIREBALL01, FIREBALL02, FIREBALL03, FIREBALL04 };

		unsigned short int _explosionAnimationIterator = 0;

		std::array<sf::IntRect, 4> _explosionAnimationFrames = { FIREBALL_EXPLOSION01, FIREBALL_EXPLOSION01, FIREBALL_EXPLOSION02, FIREBALL_EXPLOSION03 };

		sf::Vector2f _position;
		sf::Vector2f _velocity;

		bool _delete = false;


	};

}

