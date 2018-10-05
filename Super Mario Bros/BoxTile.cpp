#include "BoxTile.hpp"
#include "Mushroom.hpp"
#include "FireFlower.hpp"
#include "DEFINITIONS.hpp"
#include "Score.hpp"
#include <iostream>

namespace engine {


	BoxTile::BoxTile(const int& x, const int& y, Items item, Setting setting, int& coins, std::vector<Score>& scores, gameDataRef data)
		: _data(data), _tile(_data->assets.getTexture("Tiles")), _item(item), _coins(coins), _scores(scores)
	{
		_tile.setScale(4.0f, 4.0f);
		_tile.setPosition(x, y);

		if (setting == Setting::OW) {
			_boxAnimationFrames = { BOX_TILE1, BOX_TILE1, BOX_TILE1, BOX_TILE2, BOX_TILE3 };
			_tile.setTextureRect(BOX_TILE1);
		} else {
			_boxAnimationFrames = { BOX_TILE1_UG, BOX_TILE1_UG, BOX_TILE1_UG, BOX_TILE2_UG, BOX_TILE3_UG };
			_tile.setTextureRect(BOX_TILE1_UG);
		}
	}

	void BoxTile::draw() {
		_data->window.draw(_tile);
	}

	void BoxTile::update(std::vector<Item*>& items, Mario& mario) {
		_data->assets.getSound("Bump").play();
		if (!_opened) {
			if (_item == Items::coin) {
				_data->assets.getSound("Coin").play();
				items.emplace_back(new Coin(_tile.getPosition().x + _tile.getGlobalBounds().width / 2, _tile.getPosition().y, _coins, _scores, _data));
			} else if (_item == Items::powerUp) {
				_data->assets.getSound("Powerup_appear").play();
				if (mario.bigMario) {
					items.emplace_back(new FireFlower(_tile.getPosition().x, _tile.getPosition().y, _boxAnimationFrames[0] == BOX_TILE1 ? Setting::OW : Setting::UG, _scores, _data));
				} else {
					items.emplace_back(new Mushroom(_tile.getPosition().x, _tile.getPosition().y, _scores, _data));
				}
			}
			_opened = true;
		}
	}

	void BoxTile::animate(const float& dt) {
		if (_opened && _tileY <= 0 && !_animationDone) {
			_tile.setTextureRect(_boxAnimationFrames[0] == BOX_TILE1 ? BOX_TILE_OPENED : BOX_TILE_OPENED_UG);
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
