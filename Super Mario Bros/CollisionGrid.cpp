#include "CollisionGrid.hpp"

namespace engine {

	CollisionGrid::CollisionGrid(const int x, const int y, const int width, const int height)
		: boundary(x, y, width, height)
	{
	}

	CollisionGrid::~CollisionGrid()
	{
	}


}