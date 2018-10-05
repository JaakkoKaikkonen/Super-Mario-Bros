#include "Platform.hpp"
#include "Collision.hpp"

namespace engine {

	Platform::Platform(const int x, const int y, Mario& mario, gameDataRef data) 
		: _data(data), _tile(_data->assets.getTexture("Tiles"), PLATFORM), _mario(mario)
	{
		_tile.setScale(4.0f, 4.0f);
		_tile.setPosition(x, y);
	}

	void Platform::draw() {
		_data->window.draw(_tile);
	}

	void Platform::update(std::vector<Item*>& items, Mario& mario) {

	}

	void Platform::animate(const float& dt) {

		if (_tile.getPosition().y + _tile.getGlobalBounds().height < 0) {
			_tile.setPosition(_tile.getPosition().x, SCREEN_HEIGHT);
		}

		_tile.move(0.0f, -PLATFORM_SPEED * dt);

		if (Collision::checkSpriteCollision(_mario.mario, _tile)) {
			_mario.position.y += -PLATFORM_SPEED * dt + 0.1f;
			_mario.isCollidingY = true;
		}

	}

	sf::Sprite& Platform::getTile() {
		return _tile;
	}


}