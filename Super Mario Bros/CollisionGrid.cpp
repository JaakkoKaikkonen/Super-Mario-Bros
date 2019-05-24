#include "CollisionGrid.hpp"

namespace Game {

	CollisionGrid::CollisionGrid(const int x, const int y, const int width, const int height)
		: boundary(x, y, width, height)
	{
	}

}