#pragma once

#include <vector>
#include "Mario.hpp"

namespace engine {

	class Item 
	{
	public:
		virtual void draw() = 0;

		virtual void animate() = 0;

		virtual void update(const float& dt, std::vector<class CollisionGrid>& collisionGrid, Mario& mario) = 0;

		virtual bool shouldBeDeleted() = 0;

	};


}
