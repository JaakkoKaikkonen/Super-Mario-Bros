#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Item.hpp"
#include "DEFINITIONS.hpp"
#include "CollisionGrid.hpp"
#include "Score.hpp"
#include <array>
#include <vector>

namespace engine {

	class FireFlower : public Item
	{
	public:
		FireFlower(const int x, const int y, Setting setting, std::vector<Score>& scores, gameDataRef data);
		~FireFlower();

		void draw();

		void animate();

		void update(const float& dt, std::vector<class CollisionGrid>& collisionGrid, Mario& mario);

		bool shouldBeDeleted();


	private:
		gameDataRef _data;

		sf::Sprite _fireFlower;

		sf::Clock _clock;

		unsigned short int _animationIterator = 0;

		std::array<sf::IntRect, 4> _animationFrames;

		sf::Vector2f _position;

		float _startY;

		float _animationSpeed = -100;

		bool _animationDone = false;

		bool _delete = false;

		std::vector<Score>& _scores;

	};




}
