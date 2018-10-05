#include "Money.hpp"
#include "Collision.hpp"

namespace engine {

	Money::Money(const int x, const int y, Setting setting, gameDataRef data)
		: _data(data), _money(_data->assets.getTexture("Items"), COIN01)
	{
		if (setting == Setting::OW) {
			_animationFrames = { COIN01, COIN01, COIN01, COIN02, COIN03, COIN04 };
		} else {
			_animationFrames = { COIN_UG_01, COIN_UG_01, COIN_UG_01, COIN_UG_02, COIN_UG_03, COIN_UG_04 };
		}
		_money.setScale(4.0f, 4.0f);
		_money.setPosition(x, y);
	}


	void Money::animate() {
		if (_clock.getElapsedTime().asSeconds() > COIN_ANIMATION_TIME / _animationFrames.size()) {
			if (_animationIterator < _animationFrames.size() - 1) {
				_animationIterator++;
			} else {
				_animationIterator = 0;
			}
			_money.setTextureRect(_animationFrames[_animationIterator]);
			_clock.restart();
		}
	}

	void Money::update(Mario& mario, int& coins) {
		if (Collision::checkSpriteCollision(_money, mario.mario)) {
			_data->assets.getSound("Coin").play();
			coins++;
			_delete = true;
		}
	}

	void Money::draw() {
		_data->window.draw(_money);
	}

	bool Money::shouldBeDeleted() {
		return _delete;
	}

}