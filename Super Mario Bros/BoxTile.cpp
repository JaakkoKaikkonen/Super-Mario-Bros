#include "BoxTile.hpp"
#include "Mushroom.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace engine {


	BoxTile::BoxTile(const int& x, const int& y, Items item, gameDataRef data)
		: _data(data), _tile(_data->assets.getTexture("Tiles"), BOX_TILE1), _item(item)
	{
		_tile.setScale(4.0f, 4.0f);
		_tile.setPosition(x, y);
	}

	void BoxTile::draw() {
		_data->window.draw(_tile);
	}

	void BoxTile::update(std::vector<Item*>& items, std::vector<Tile*>& tiles, Mario& mario) {
		if (!_opened) {
			if (_item == Items::coin) {
				items.emplace_back(new Coin(_tile.getPosition().x + _tile.getGlobalBounds().width / 2, _tile.getPosition().y, _data));
			} else if (_item == Items::mushroom) {
				items.emplace_back(new Mushroom(_tile.getPosition().x, _tile.getPosition().y, _data));
			}
			_opened = true;
		}
	}

	void BoxTile::animate(const float& dt) {
		if (_opened && _tileY <= 0 && !_animationDone) {
			_tile.setTextureRect(BOX_TILE_OPENED);
			_tileY += _animationSpeedY * dt;
			_tile.move(0, _animationSpeedY * dt);
			if (_tileY < _animationHeight) {
				_tile.move(0, (_animationHeight + abs(_tileY)));
				_tileY = _animationHeight;
				_animationSpeedY *= -1;
			}
		} else if(_tileY > 0 && !_animationDone) {
			_tile.move(0, -(_tileY));
			_animationDone = true;
		} else if (_clock.getElapsedTime().asSeconds() > BOX_ANIMATION_TIME / _boxAnimationFrames.size() && !_opened) {
			if (_boxAnimationIterator < _boxAnimationFrames.size() - 1) {
				_boxAnimationIterator++;
			} else {
				_boxAnimationIterator = 0;
			}
			_tile.setTextureRect(_boxAnimationFrames[_boxAnimationIterator]);
			_clock.restart();
		} 

	}

	sf::Sprite& BoxTile::getTile() {
		return _tile;
	}
}
