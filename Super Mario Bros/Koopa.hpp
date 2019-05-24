#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Enemy.hpp"
#include "CollisionGrid.hpp"
#include "Mario.hpp"
#include "DEFINITIONS.hpp"
#include "Score.hpp"
#include <array>
#include <vector>

namespace Game {

	class Koopa : public Enemy
	{
	public:
		Koopa(const int x, const int y, Setting setting, std::vector<Score>& scores, gameDataRef data);
		~Koopa();

		void draw();

		bool shouldBeUpdated(Mario& mario);

		void update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario);

		void animate();

		sf::Sprite& getSprite();

		void setPosition(sf::Vector2f position);

		void turn();

		bool shell();

		bool sliding();

		std::string& getName();

		bool shouldBeDeleted();

		void flip(const float angle);

		void kill();

		bool checkIfDead();

	private:
		void applyGravity();



	private:
		gameDataRef _data;

		sf::Sprite _koopa;

		std::string _name;

		float _scale = 4.0f;

		float _renderDistance = SCREEN_WIDTH * 1.5f;

		sf::Vector2f _position;
		sf::Vector2f _velocity;
		sf::Vector2f _acceleration;


		sf::Clock _clock;

		unsigned short int _animationIterator;

		std::array<sf::IntRect, 2> _koopaLeftAnimationFrames;

		std::array<sf::IntRect, 2> _koopaRightAnimationFrames;


		float _posY = 0;

		bool _dead = false;

		bool _moving = true;

		bool _shell = false;

		bool _sliding = false;

		bool _flipped = false;

		bool _delete = false;

		std::vector<Score>& _scores;

	};




}