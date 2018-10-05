#pragma once

#include <vector>
#include <string>
#include "Mario.hpp"
#include "CollisionGrid.hpp"

namespace engine {

	class Enemy {
	public: 

		virtual void draw() = 0;

		virtual bool shouldBeUpdated(Mario& mario) = 0;

		virtual void update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario) = 0;

		virtual void animate() = 0;

		virtual sf::Sprite& getSprite() = 0;

		virtual void setPosition(sf::Vector2f position) = 0;

		virtual bool shell() = 0;

		virtual bool sliding() = 0;

		virtual void turn() = 0;

		virtual void flip(const float angle) = 0;

		virtual std::string& getName() = 0;

		virtual bool shouldBeDeleted() = 0;

		virtual void kill() = 0;

		virtual bool checkIfDead() = 0;

	};




}
