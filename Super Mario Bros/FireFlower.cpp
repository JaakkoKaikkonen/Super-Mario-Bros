#include "FireFlower.hpp"
#include "Collision.hpp"

namespace Game {

	FireFlower::FireFlower(const int x, const int y, Setting setting, std::vector<Score>& scores, gameDataRef data)
		: _data(data), _fireFlower(_data->assets.getTexture("Items")), _startY(y), _scores(scores)
	{
		_fireFlower.setScale(4.0f, 4.0f);

		if (setting == Setting::OW) {
			_animationFrames = { FIREFLOWER01, FIREFLOWER02, FIREFLOWER03, FIREFLOWER04 };
			_fireFlower.setTextureRect(FIREFLOWER01);
		} else {
			_animationFrames = { FIREFLOWER01_UG, FIREFLOWER02_UG, FIREFLOWER03_UG, FIREFLOWER04_UG };
			_fireFlower.setTextureRect(FIREFLOWER01_UG);
		}

		_position = sf::Vector2f(x, y - _fireFlower.getGlobalBounds().height / 3.5);
		_fireFlower.setPosition(_position);

	}


	void FireFlower::draw() {
		_data->window.draw(_fireFlower);
	}

	void FireFlower::animate() {
		if (_clock.getElapsedTime().asSeconds() > FIREFLOWER_ANIMATION_TIME / _animationFrames.size()) {
			if (_animationIterator < _animationFrames.size() - 1) {
				_animationIterator++;
			} else {
				_animationIterator = 0;
			}
			_fireFlower.setTextureRect(_animationFrames[_animationIterator]);
			_clock.restart();
		}
	}

	void FireFlower::update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario) {
		if (!_animationDone) {
			_position.y += _animationSpeed * dt;
			_fireFlower.setPosition(_position);
			if (_startY - _position.y > _fireFlower.getGlobalBounds().height) {
				_position.y = _startY - _fireFlower.getGlobalBounds().height - 0.001f;
				_animationDone = true;
			}
		}

		if (Collision::checkSpriteCollision(_fireFlower, 0.8f, 0.8f, mario.mario) && !mario.dead) {
			_data->assets.getSound("Powerup").play();
			if (mario.bigMario) {
				mario.fireForm = true;
				//mario.fireAnimation = true;
			} else {
				mario.bigMario = true;
				mario.growingAnimation = true;
			}
			_scores.emplace_back(Score(_fireFlower.getPosition().x, _fireFlower.getPosition().y, 1000, _data));
			_delete = true;
		} else if (_position.x < mario.cameraX - _fireFlower.getGlobalBounds().width) {
			_delete = true;
		}

	}

	bool FireFlower::shouldBeDeleted() {
		return _delete;
	}


}