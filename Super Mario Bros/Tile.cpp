#include "Tile.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Game {

	Tile::Tile(const int& x, const int& y, const sf::IntRect& texture, gameDataRef data) 
		: _data(data), _tile(_data->assets.getTexture("Tiles"), texture)
	{
		_tile.setScale(4.0f, 4.0f);
		_tile.setPosition(x, y);
	}

	void Tile::draw() {
		_data->window.draw(_tile);
	}

	void Tile::update(std::vector<Item*>& items, Mario& mario) {

	}

	void Tile::animate(const float& dt) {

	}

	sf::Sprite& Tile::getTile() {
		return _tile;
	}




}