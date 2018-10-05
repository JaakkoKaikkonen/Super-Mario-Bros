#include "Castle.hpp"
#include "DEFINITIONS.hpp"

namespace engine {

	Castle::Castle(gameDataRef data)
		: _data(data), _castle(_data->assets.getTexture("Castle")), _flag(_data->assets.getTexture("Items"))
	{
		_castle.setScale(4.0f, 4.0f);
		_flag.setScale(4.0f, 4.0f);
	}


	void Castle::draw() {
		_data->window.draw(_flag);
		_data->window.draw(_castle);
	}

	void Castle::setPosition(const int x, const int y, sf::IntRect castle, sf::IntRect flag) {
		_castle.setTextureRect(castle);
		_castle.setPosition(x, y);
		_flag.setTextureRect(flag);
		_flag.setPosition(x + TILE_SIZE * 2, y + _flag.getGlobalBounds().height);
	}

	bool Castle::insideCastle(Mario& mario) {
		return mario.mario.getPosition().x > _castle.getPosition().x + TILE_SIZE * 1.9f && mario.mario.getPosition().x < _castle.getPosition().x + _castle.getGlobalBounds().width;
	}

	void Castle::raiseFlag(const float& dt) {
		if (_flag.getPosition().y > _castle.getPosition().y - _flag.getGlobalBounds().height) {
			_flag.move(0, -_flagSpeed * dt);
		}
	}

}
