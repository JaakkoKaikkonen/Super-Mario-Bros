#include "Decoration.hpp"
#include "DEFINITIONS.hpp"
#include <string>

namespace engine {

	Decoration::Decoration(const int& x, const int& y, const std::string textureName, const sf::IntRect intRect, gameDataRef data)
		: _data(data), _decoration(_data->assets.getTexture(textureName), intRect)
	{
		if (intRect == BUMP_TILE_SMALL || intRect == BUMP_TILE_BIG) {
			_decoration.setPosition(x, y - 12);
		} else {
			_decoration.setPosition(x, y);
		}
		_decoration.setScale(4.0f, 4.0f);
	}

	void Decoration::draw() {
		_data->window.draw(_decoration);
	}



}
