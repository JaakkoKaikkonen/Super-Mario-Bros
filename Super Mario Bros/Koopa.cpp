#include "Koopa.hpp"
#include "Collision.hpp"
#include <iostream>

namespace engine {

	Koopa::Koopa(const int x, const int y, Setting setting, std::vector<Score>& scores, gameDataRef data)
		: _data(data), _koopa(_data->assets.getTexture("Enemies")), _name("Koopa"), _position(x, y - _scale * 8.0f), _velocity(-100.0f, 0.0f), _acceleration(0.0f, 0.0f), _scores(scores)
	{
		_koopa.setScale(_scale, _scale);
		_koopa.setPosition(_position);
		if (setting == Setting::OW) {
			_koopaLeftAnimationFrames = { KOOPA1_LEFT, KOOPA2_LEFT };
			_koopaRightAnimationFrames = { KOOPA1_RIGHT, KOOPA2_RIGHT };
			_koopa.setTextureRect(KOOPA1_LEFT);
		} else {
			_koopaLeftAnimationFrames = { KOOPA1_LEFT_UG, KOOPA2_LEFT_UG };
			_koopaRightAnimationFrames = { KOOPA1_RIGHT_UG, KOOPA2_RIGHT_UG };
			_koopa.setTextureRect(KOOPA1_LEFT_UG);
		}
	}


	Koopa::~Koopa()
	{
	}

	void Koopa::draw() {
		_data->window.draw(_koopa);
	}

	bool Koopa::shouldBeUpdated(Mario& mario) {
		if (_koopa.getPosition().y > SCREEN_HEIGHT || _koopa.getPosition().x  < mario.cameraX - _renderDistance) {
			_delete = true;
		}
		return abs(mario.position.x - _position.x) < _renderDistance;
	}

	void Koopa::update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario) {
	
		if (!_shell) {
			this->animate();
		}

		if (_moving) {

			_velocity.x += _acceleration.x * dt;
			_position.x += _velocity.x * dt;
			_acceleration.x = 0;


			_koopa.setPosition(_position);

		}
		if (!_dead) {
			bool exit = false;
			for (int i = 0; i < collisionGrid.size(); i++) {
				if (exit) break;
				if (Collision::checkSpriteCollision(collisionGrid[i].boundary, _koopa)) {
					for (int j = 0; j < collisionGrid[i].tiles.size(); j++) {
						if (_shell) {
							if (Collision::checkSpriteCollision(_koopa, 1.0f, 0.5f, collisionGrid[i].tiles[j]->getTile())) {
								if (_velocity.x > 0) {
									_position.x = collisionGrid[i].tiles[j]->getTile().getPosition().x - _koopa.getGlobalBounds().width;
									_velocity.x *= -1.0f;
								} else {
									_position.x = collisionGrid[i].tiles[j]->getTile().getPosition().x + collisionGrid[i].tiles[j]->getTile().getGlobalBounds().width;
									_velocity.x *= -1.0f;
								}
								exit = true;
								break;
							}
						} else {
							if (Collision::checkSpriteCollision(_koopa, 1.0f, 0.9f, collisionGrid[i].tiles[j]->getTile())) {
								if (_velocity.x > 0) {
									_position.x = collisionGrid[i].tiles[j]->getTile().getPosition().x - _koopa.getGlobalBounds().width;
									_velocity.x *= -1.0f;
								} else {
									_position.x = collisionGrid[i].tiles[j]->getTile().getPosition().x + collisionGrid[i].tiles[j]->getTile().getGlobalBounds().width;
									_velocity.x *= -1.0f;
								}
								exit = true;
								break;
							}
						}
					}
				}
			}

			if (!mario.growingAnimation && !mario.takeDamage) {
				if (_moving) {
					if (mario.bigMario) {
						if (Collision::checkSpriteCollision(mario.mario, 0.8f, 0.5f, _koopa) && !mario.dead) {
							mario.takeDamage = true;
						}
					} else {
						if (Collision::checkSpriteCollision(mario.mario, mario.hitBoxScale - 0.2f, 0.5f, _koopa) && !mario.dead) {
							mario.takeDamage = true;
						}
					}
				} else {
					if (mario.bigMario || !mario.isCollidingY) {
						if (Collision::checkSpriteCollision(mario.mario, 1.0f, 0.8f, _koopa) && !mario.dead) {
							if (mario.position.x < _position.x) {
								mario.position.x = _position.x - mario.mario.getGlobalBounds().width;
							} else {
								mario.position.x = _position.x + _koopa.getGlobalBounds().width;
							}
							mario.velocity.x = 0;
						}
					} else {
						if (Collision::checkSpriteCollision(mario.mario, mario.hitBoxScale, 0.8f, _koopa) && !mario.dead) {
							if (mario.position.x < _position.x) {
								mario.position.x = _position.x - mario.mario.getGlobalBounds().width * (mario.hitBoxScale + ((1.0f - mario.hitBoxScale) / 2));
							} else {
								mario.position.x = _position.x + _koopa.getGlobalBounds().width - mario.mario.getGlobalBounds().width * ((1.0f - mario.hitBoxScale) / 2);
							}
							mario.velocity.x = 0;
						}
					}
				}

			}
		}

			this->applyGravity();

			_velocity.y += _acceleration.y * dt;
			_position.y += _velocity.y * dt;
			_acceleration.y = 0;

			_koopa.setPosition(_position);


		if (!_dead) {
			bool exit = false;
			for (int i = 0; i < collisionGrid.size(); i++) {
				if (exit) break;
				if (Collision::checkSpriteCollision(collisionGrid[i].boundary, _koopa)) {
					for (int j = 0; j < collisionGrid[i].tiles.size(); j++) {
						if (_shell) {
							if (Collision::checkSpriteCollision(_koopa, 0.5f, 1.0f, collisionGrid[i].tiles[j]->getTile())) {
								if (_flipped) {
									_moving = false;
									_flipped = false;
								}
								if (collisionGrid[i].tiles[j]->getTile().getPosition().y + 1.0f < _position.y + _koopa.getGlobalBounds().height) {
									_position.y = collisionGrid[i].tiles[j]->getTile().getPosition().y - _koopa.getGlobalBounds().height;
									_velocity.y = 0.0f;
									exit = true;
									break;
								} else {
									_position.y = collisionGrid[i].tiles[j]->getTile().getPosition().y - _koopa.getGlobalBounds().height;
									_velocity.y = 0.0f;
								}
							}
						} else {
							if (Collision::checkSpriteCollision(_koopa, 0.95f, 1.0f, collisionGrid[i].tiles[j]->getTile())) {
								if (collisionGrid[i].tiles[j]->getTile().getPosition().y + 1.0f < _position.y + _koopa.getGlobalBounds().height) {
									_position.y = collisionGrid[i].tiles[j]->getTile().getPosition().y - _koopa.getGlobalBounds().height;
									_velocity.y = 0.0f;
									exit = true;
									break;
								} else {
									_position.y = collisionGrid[i].tiles[j]->getTile().getPosition().y - _koopa.getGlobalBounds().height;
									_velocity.y = 0.0f;
								}
							}
						}
					}
				}
			}



			if (!mario.growingAnimation && !mario.takeDamage && mario.velocity.y > 0) {
				if (Collision::checkSpriteCollision(_koopa, 0.9f, 0.98f, mario.mario) && !mario.dead && !mario.takeDamage) {
					if (mario.position.y < _position.y) {
						if (!_shell) {
							_position.y += _scale * 10.0f;
							_scores.emplace_back(Score(_koopa.getPosition().x, _koopa.getPosition().y, 500, _data));
						}
						if (mario.mario.getPosition().x + mario.mario.getGlobalBounds().width / 2 < _koopa.getPosition().x + _koopa.getGlobalBounds().width / 2) {
							_velocity.x = KOOPA_SLIDING_SPEED;
						} else {
							_velocity.x = -KOOPA_SLIDING_SPEED;
						}
						_shell = true;
						_moving = !_moving;
						if (_koopa.getTextureRect() != KOOPA_SHELL_UPSIDEDOWN && _koopa.getTextureRect() != KOOPA_SHELL_UPSIDEDOWN_UG) {
							_koopa.setTextureRect(_koopaLeftAnimationFrames[0] == KOOPA1_LEFT ? KOOPA_SHELL : KOOPA_SHELL_UG);
						}
						_data->assets.getSound("Kick").play();
						mario.velocity.y = 0;
						mario.jump(-100000.0f);
					}
				}
			}

			if (_posY > _position.y && !_flipped) {
				this->flip(-(PI - PI / 4));
			}

			_posY = _position.y - 1.0f;


			if (_moving && _shell) {
				_sliding = true;
			} else {
				_sliding = false;
			}


			_koopa.setPosition(_position);

		}	

	}



	void Koopa::animate() {
		if (_velocity.x > 0) {
			if (_clock.getElapsedTime().asSeconds() > KOOPA_ANIMATION_TIME / _koopaRightAnimationFrames.size()) {
				if (_animationIterator < _koopaRightAnimationFrames.size() - 1) {
					_animationIterator++;
				} else {
					_animationIterator = 0;
				}
				_koopa.setTextureRect(_koopaRightAnimationFrames[_animationIterator]);
				_clock.restart();
			}
		} else {
			if (_clock.getElapsedTime().asSeconds() > KOOPA_ANIMATION_TIME / _koopaLeftAnimationFrames.size()) {
				if (_animationIterator < _koopaLeftAnimationFrames.size() - 1) {
					_animationIterator++;
				} else {
					_animationIterator = 0;
				}
				_koopa.setTextureRect(_koopaLeftAnimationFrames[_animationIterator]);
				_clock.restart();
			}
		}
	}

	void Koopa::flip(const float angle) {
		_koopa.setTextureRect(_koopaLeftAnimationFrames[0] == KOOPA1_LEFT ? KOOPA_SHELL_UPSIDEDOWN : KOOPA_SHELL_UPSIDEDOWN_UG);
		if (_shell) {
			_position.y -= 10.0f;
		} else {
			_shell = true;
			_scores.emplace_back(Score(_koopa.getPosition().x, _koopa.getPosition().y, 200, _data));
		}
		_flipped = true;
		_moving = true;
		_acceleration += sf::Vector2f(cos(angle) * 100000.0f, sin(angle) * 100000.0f);
		_velocity.x = 0;
		_velocity.y = 0;
	}

	void Koopa::applyGravity() {
		_acceleration.y += 1200.0f;
	}


	sf::Sprite& Koopa::getSprite() {
		return _koopa;
	}

	void Koopa::setPosition(sf::Vector2f position) {
		_position = position;
	}

	bool Koopa::sliding() {
		return _sliding;
	}

	bool Koopa::shell() {
		return _shell;
	}

	std::string& Koopa::getName() {
		return _name;
	}

	bool Koopa::shouldBeDeleted() {
		return _delete;
	}

	void Koopa::turn() {
		_velocity.x *= -1;
	}

	void Koopa::kill() {
		_dead = true;
	}

	bool Koopa::checkIfDead() {
		return _dead;
	}

}