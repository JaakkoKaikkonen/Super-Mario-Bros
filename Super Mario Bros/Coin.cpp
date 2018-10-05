#include "Coin.hpp"
#include "DEFINITIONS.hpp"
#include "Tile.hpp"

namespace engine {

	Coin::Coin(const int x, const int y, int& coins, std::vector<Score>& scores, gameDataRef data)
		: _data(data), _coin(_data->assets.getTexture("Items"), COIN_ITEM1), _startingY(y), _scores(scores)
	{
		_coin.setScale(3.0f, 3.0f);
		_coin.setPosition(x - _coin.getGlobalBounds().width / 2, y);
		coins++;
	}


	void Coin::draw() {
		_data->window.draw(_coin);
	}

	void Coin::animate() {
		if (_clock.getElapsedTime().asSeconds() > COIN_ITEM_ANIMATION_TIME / _coinAnimationFrames.size()) {
			if (_coinAnimationIterator < _coinAnimationFrames.size() - 1) {
				_coinAnimationIterator++;
			} else {
				_coinAnimationIterator = 0;
			}
			_coin.setTextureRect(_coinAnimationFrames[_coinAnimationIterator]);
			_clock.restart();
		}
	}

	void Coin::update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario) {
		_coin.move(0, _speed * dt);
		if (_coin.getPosition().y < _startingY + _animationHeight && _turn) {
			_speed *= -1;
			_turn = false;
		} else if (_coin.getPosition().y > _startingY - _coin.getGlobalBounds().height && !_turn) {
			_scores.emplace_back(Score(_coin.getPosition().x, _coin.getPosition().y, 200, _data));
			_delete = true;
		}
	}

	bool Coin::shouldBeDeleted() {
		return _delete;
	}


}