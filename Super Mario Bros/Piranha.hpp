#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Enemy.hpp"
#include "Score.hpp"
#include "DEFINITIONS.hpp"
#include <array>
#include <string>

namespace engine {

	class Piranha : public Enemy
	{
	public:
		Piranha(const int x, const int y, Setting setting, std::vector<Score>& scores, gameDataRef data);
		
		void draw();

		bool shouldBeUpdated(Mario& mario);

		void update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario);

		void animate();

		sf::Sprite& getSprite();

		void setPosition(sf::Vector2f position);

		bool shell();

		bool sliding();

		void turn();

		void flip(const float angle);

		std::string& getName();

		bool shouldBeDeleted();

		void kill();

		bool checkIfDead();



	private:
		gameDataRef _data;

		sf::Sprite _piranha;

		std::string _name;

		int _startY;

		float _renderDistance = SCREEN_WIDTH * 0.9f;

		enum Dir { up, down };

		Dir dir = up;

		sf::Clock _clock;

		sf::Clock _clock2;

		unsigned short int _animationIterator = 0;

		std::array<sf::IntRect, 2> _animationFrames = { };

		bool _move = false;

		bool _delete = false;

		std::vector<Score>& _scores;

	};



}