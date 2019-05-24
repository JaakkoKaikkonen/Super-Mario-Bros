#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Score.hpp"
#include "Game.hpp"
#include "Item.hpp"
#include "CollisionGrid.hpp"

namespace Game {


	class Mushroom : public Item
	{
	public:
		Mushroom(const int x, const int y, std::vector<Score>& scores, gameDataRef data);
		
		void draw();

		void animate();

		void update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario);

		bool shouldBeDeleted();

	private:
		void applyGravity();

	private:
		gameDataRef _data;

		sf::Sprite _mushroom;

		sf::Vector2f _position;
		sf::Vector2f _velocity;
		sf::Vector2f _acceleration;

		float _startY;

		float _animationSpeed = -100.0f;

		bool _animationDone;

		bool _delete;

		std::vector<Score>& _scores;

	};



}