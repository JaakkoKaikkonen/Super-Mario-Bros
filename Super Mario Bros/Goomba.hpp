#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include <array>
#include <vector>
#include "Score.hpp"

namespace engine {

	class Goomba : public Enemy
	{
	public:
		Goomba(const int x, const int y, Setting setting, std::vector<Score>& scores, gameDataRef data);

		~Goomba();
	
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

		sf::Sprite _goomba;

		std::string _name;
		
		sf::Clock _clock;

		sf::Clock _clock2;

		unsigned short int _animationIterator = 0;

		std::array<sf::IntRect, 2> _goombaAnimationFrames;

		sf::Vector2f _position;
		sf::Vector2f _velocity;
		sf::Vector2f _acceleration;

		float _posY = 0;

		float _renderDistance = SCREEN_WIDTH;

		bool _dead = false;

		bool _stomped = false;

		bool _flipped = false;

		bool _delete = false;

		std::vector<Score>& _scores;

	};



}
