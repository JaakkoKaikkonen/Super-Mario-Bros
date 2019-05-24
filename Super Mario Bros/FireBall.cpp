#include "FireBall.hpp"
#include "Collision.hpp"
#include <iostream>

namespace Game {

	FireBall::FireBall(const int x, const int y, Dir dir, gameDataRef data)
		: _data(data), _fireBall(_data->assets.getTexture("Items"), FIREBALL04), _position(0.0f, y), _velocity(0.0f, 0.0f)
	{
		_fireBall.setScale(4.0f, 4.0f);
		_fireBall.setPosition(_position);
		if (dir == Dir::Right) {
			_velocity.x = FIREBALL_SPEED;
			_position.x = x + 30.0f;
		} else {
			_velocity.x = -FIREBALL_SPEED;
			_position.x = x;
		}
	}


	void FireBall::draw() {
		_data->window.draw(_fireBall);
	}

	void FireBall::update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario) {

		if (!explode) {

			_velocity.y += 4300.0f * dt;
			

			_position.x += _velocity.x * dt;

			for (int i = 0; i < collisionGrid.size(); i++) {
				if (Collision::checkSpriteCollision(collisionGrid[i].boundary, _fireBall)) {
					for (int j = 0; j < collisionGrid[i].tiles.size(); j++) {
						if (Collision::checkSpriteCollision(collisionGrid[i].tiles[j]->getTile(), 1.0f, 0.6f, _fireBall)) {
							explode = true;
						}
					}
				}
			}
			_fireBall.setPosition(_position);

			_position.y += _velocity.y * dt;

			for (int i = 0; i < collisionGrid.size(); i++) {
				if (Collision::checkSpriteCollision(collisionGrid[i].boundary, _fireBall)) {
					for (int j = 0; j < collisionGrid[i].tiles.size(); j++) {
						if (Collision::checkSpriteCollision(collisionGrid[i].tiles[j]->getTile(), 0.6f, 1.0f, _fireBall)) {
							if (collisionGrid[i].tiles[j]->getTile().getPosition().y < _fireBall.getPosition().y) {
								_position.y = collisionGrid[i].tiles[j]->getTile().getPosition().y + collisionGrid[i].tiles[j]->getTile().getGlobalBounds().height + 0.01f;
								_velocity.y = 500.0f;
							} else {
								_position.y = collisionGrid[i].tiles[j]->getTile().getPosition().y - _fireBall.getGlobalBounds().height - 0.01f;
								_velocity.y = -775.0f;
							}
						}
					}
				}
			}
			_fireBall.setPosition(_position);
		
			if (_position.y > SCREEN_HEIGHT || _position.x + _fireBall.getGlobalBounds().width < mario.cameraX || _position.x > mario.cameraX + SCREEN_WIDTH) {
				_delete = true;
			}
		
		}

	}

	void FireBall::animate() {
		if (explode) {
			if (_clock.getElapsedTime().asSeconds() > FIREBALL_EXPLOSION_TIME / _explosionAnimationFrames.size()) {
				if (_explosionAnimationIterator < _explosionAnimationFrames.size() - 1) {
					_explosionAnimationIterator++;
				} else {
					_delete = true;
				}
				_fireBall.setTextureRect(_explosionAnimationFrames[_explosionAnimationIterator]);
				_clock.restart();
			}
		} else {

			if (_clock.getElapsedTime().asSeconds() > FIREBALL_ANIMATION_TIME / _animationFrames.size()) {
				if (_animationIterator < _animationFrames.size() - 1) {
					_animationIterator++;
				} else {
					_animationIterator = 0;
				}
				_fireBall.setTextureRect(_animationFrames[_animationIterator]);
				_clock.restart();
			}
		}
	}


	bool FireBall::shouldBeDeleted() {
		return _delete;
	}

	sf::Sprite& FireBall::getSprite() {
		return _fireBall;
	}

	const Dir& FireBall::getDirection() {
		if (_velocity.x > 0) {
			return Dir::Right;
		} else {
			return Dir::Left;
		}
	}

}