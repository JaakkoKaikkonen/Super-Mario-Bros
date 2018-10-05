#include "Mario.hpp"
#include <iostream>

namespace engine {

	Mario::Mario(gameDataRef data)
		: position(300, 776), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), _data(data), camera(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		mario.setTexture(_data->assets.getTexture("Mario"));
		mario.setScale(4.2f, 3.5f);
		mario.setPosition(position);
		mario.setTextureRect(SMALL_MARIO_IDLE_RIGHT);

		//std::cout << mario.getGlobalBounds().width << std::endl;
	}

	void Mario::updateX(const float& dt) {
		velocity.x += acceleration.x * dt;
		position.x += velocity.x * dt;
		acceleration.x = 0.0f;

		while (_accumulator < dt) {
			velocity.x *= 0.9996f;
			_accumulator += 0.0001f;
		}
		_accumulator = _accumulator - dt;


		//check if colliding with camera
		if (!isCollidingY || bigMario) {
			if (position.x < cameraX) {
				position.x = cameraX;
				velocity.x = 0;
			}
		} else {
			if (position.x < cameraX - mario.getGlobalBounds().width * ((1.0f - hitBoxScale) / 2)) {
				position.x = cameraX - mario.getGlobalBounds().width * ((1.0f - hitBoxScale) / 2);
				velocity.x = 0;
			}
		}

		mario.setPosition(position);

	}


	void Mario::updateY(const float& dt) {
		this->applyGravity();
		velocity.y += acceleration.y * dt;
		position.y += velocity.y * dt;
		acceleration.y = 0.0f;

		mario.setPosition(position);
		
	}


	void Mario::move(const float& speed) {
		if (!crouch || !isCollidingY) {
			if (speed > 0) {
				dir = Right;
			} else {
				dir = Left;
			}
			if ((dir == Right && velocity.x < 0) || (dir == Left && velocity.x > 0)) {
				acceleration.x = speed / 12;
			} else {
				acceleration.x = speed;
			}
		}

	}

	void Mario::jump() {
		acceleration.y += -10000.0f;
	}


	//Call animate() before update()!!!!!!!!
	void Mario::animate(const float& dt) {
		if (growingAnimation) {
			if (dir == Right) {
				if (_clock.getElapsedTime().asSeconds() > MARIO_GROWING_ANIMATION_TIME / _growingRightAnimatinFrames.size()) {
					if (_growingAnimationIterator == _growingRightAnimatinFrames.size()) {
						_growingAnimationIterator = 0;
						growingAnimation = false;
					} else {
						position.y += _growingAnimationPositions[_growingAnimationIterator];
						mario.setPosition(position.x, position.y);
						mario.setTextureRect(_growingRightAnimatinFrames[_growingAnimationIterator]);
						_growingAnimationIterator++;
						_clock.restart();
					}
				}
			} else {
				if (_clock.getElapsedTime().asSeconds() > MARIO_GROWING_ANIMATION_TIME / _growingLeftAnimatinFrames.size()) {
					if (_growingAnimationIterator == _growingLeftAnimatinFrames.size()) {
						_growingAnimationIterator = 0;
						growingAnimation = false;
					} else {
						position.y += _growingAnimationPositions[_growingAnimationIterator];
						mario.setPosition(position.x, position.y);
						mario.setTextureRect(_growingLeftAnimatinFrames[_growingAnimationIterator]);
						_growingAnimationIterator++;
						_clock.restart();
					}
				}
			}

		} else {

			if (bigMario) {

				if (climbing) {
					if (mario.getPosition().y < SCREEN_HEIGHT - TILE_SIZE * 2.5 - mario.getGlobalBounds().height - 5 && !_hasClimbedDown) {
						mario.move(0, POLE_CLIMBING_SPEED * dt);
						if (_clock.getElapsedTime().asSeconds() > MARIO_CLIMB_POLE_ANIMATION_TIME / _bigMarioClimbingAnimationFrames.size()) {
							if (_climbAnimationIterator < _bigMarioClimbingAnimationFrames.size() - 1) {
								_climbAnimationIterator++;
							} else {
								_climbAnimationIterator = 0;
							}
							mario.setTextureRect(_bigMarioClimbingAnimationFrames[_climbAnimationIterator]);
							_clock.restart();
						}
					} else if (!_hasClimbedDown) {
						mario.setTextureRect(BIG_MARIO_CLIMB_POLE_LEFT);
						mario.move(mario.getGlobalBounds().width, 0);
						_hasClimbedDown = true;
						_clock.restart();
					} else if (flagDown && _clock.getElapsedTime().asSeconds() > 0.75f) {
						velocity.x = 100.0f;
						dir = Right;
						climbing = false;
						walk = true;
						mario.move(20.0f, 0.0f);
					}
				} else if (crouch) {
					if (dir == Right) {
						mario.setTextureRect(BIG_MARIO_CROUCH_RIGHT);
					} else {
						mario.setTextureRect(BIG_MARIO_CROUCH_LEFT);
					}
				} else if (!isCollidingY) {
					if (dir == Right) {
						mario.setTextureRect(BIG_MARIO_JUMP_RIGHT);
					} else {
						mario.setTextureRect(BIG_MARIO_JUMP_LEFT);
					}
				} else if (acceleration.x != 0 && dir == Left && velocity.x > 0) {
					mario.setTextureRect(BIG_MARIO_TURN_LEFT);
				} else if (acceleration.x != 0 && dir == Right && velocity.x < 0) {
					mario.setTextureRect(BIG_MARIO_TURN_RIGHT);
				} else if (velocity.x > 80.0f) {
					if (_clock.getElapsedTime().asSeconds() > MARIO_RUN_ANIMATION_TIME / _bigMarioRunRightAnimationFrames.size()) {
						if (_runRightAnimationIterator < _bigMarioRunRightAnimationFrames.size() - 1) {
							_runRightAnimationIterator++;
						} else {
							_runRightAnimationIterator = 0;
						}
						mario.setTextureRect(_bigMarioRunRightAnimationFrames[_runRightAnimationIterator]);
						_clock.restart();
					}
				} else if (velocity.x < -80.0f) {
					if (_clock.getElapsedTime().asSeconds() > MARIO_RUN_ANIMATION_TIME / _bigMarioRunLeftAnimationFrames.size()) {
						if (_runLeftAnimationIterator < _bigMarioRunLeftAnimationFrames.size() - 1) {
							_runLeftAnimationIterator++;
						} else {
							_runLeftAnimationIterator = 0;
						}
						mario.setTextureRect(_bigMarioRunLeftAnimationFrames[_runLeftAnimationIterator]);
						_clock.restart();
					}
				} else {
					if (dir == Right) {
						mario.setTextureRect(BIG_MARIO_IDLE_RIGHT);
					} else {
						mario.setTextureRect(BIG_MARIO_IDLE_LEFT);
					}
				}
				if (walk) {
					if (mario.getPosition().y < SCREEN_HEIGHT - TILE_SIZE * 1.5 - mario.getGlobalBounds().height) {
						mario.move(250.0f * dt, 250.0f * dt);
						camera.move(210.0f * dt, 0.0f);
					} else if (!insideCastle) {
						isCollidingY = true;
						mario.move(180.0f * dt, 0.0f);
						camera.move(175.0f * dt, 0.0f);
					}
					_data->window.setView(camera);
				}
			} else {
				if (climbing) {
					if (mario.getPosition().y < SCREEN_HEIGHT - TILE_SIZE * 2.5 - mario.getGlobalBounds().height - 10 && !_hasClimbedDown) {
						mario.move(0, POLE_CLIMBING_SPEED * dt);
						if (_clock.getElapsedTime().asSeconds() > MARIO_CLIMB_POLE_ANIMATION_TIME / _smallMarioClimbingAnimationFrames.size()) {
							if (_climbAnimationIterator < _smallMarioClimbingAnimationFrames.size() - 1) {
								_climbAnimationIterator++;
							} else {
								_climbAnimationIterator = 0;
							}
							mario.setTextureRect(_smallMarioClimbingAnimationFrames[_climbAnimationIterator]);
							_clock.restart();
						}
					} else if (!_hasClimbedDown) {
						mario.setTextureRect(SMALL_MARIO_CLIMB_POLE_LEFT);
						mario.move(mario.getGlobalBounds().width - 11, 0);
						_hasClimbedDown = true;
						_clock.restart();
					} else if (flagDown && _clock.getElapsedTime().asSeconds() > 0.75f) {
						velocity.x = 100.0f;
						dir = Right;
						climbing = false;
						walk = true;
						mario.move(15.0f, 0.0f);
					}
				} else if (!isCollidingY) {
					if (dir == Right) {
						mario.setTextureRect(SMALL_MARIO_JUMP_RIGHT);
					} else {
						mario.setTextureRect(SMALL_MARIO_JUMP_LEFT);
					}
				} else if (acceleration.x != 0 && dir == Left && velocity.x > 0) {
					mario.setTextureRect(SMALL_MARIO_TURN_LEFT);
				} else if (acceleration.x != 0 && dir == Right && velocity.x < 0) {
					mario.setTextureRect(SMALL_MARIO_TURN_RIGHT);
				} else if (velocity.x > 80.0f) {
					if (_clock.getElapsedTime().asSeconds() > MARIO_RUN_ANIMATION_TIME / _smallMarioRunRightAnimationFrames.size()) {
						if (_runRightAnimationIterator < _smallMarioRunRightAnimationFrames.size() - 1) {
							_runRightAnimationIterator++;
						} else {
							_runRightAnimationIterator = 0;
						}
						mario.setTextureRect(_smallMarioRunRightAnimationFrames[_runRightAnimationIterator]);
						_clock.restart();
					}
				} else if (velocity.x < -80.0f) {
					if (_clock.getElapsedTime().asSeconds() > MARIO_RUN_ANIMATION_TIME / _smallMarioRunLeftAnimationFrames.size()) {
						if (_runLeftAnimationIterator < _smallMarioRunLeftAnimationFrames.size() - 1) {
							_runLeftAnimationIterator++;
						} else {
							_runLeftAnimationIterator = 0;
						}
						mario.setTextureRect(_smallMarioRunLeftAnimationFrames[_runLeftAnimationIterator]);
						_clock.restart();
					}
				} else {
					if (dir == Right) {
						mario.setTextureRect(SMALL_MARIO_IDLE_RIGHT);
					} else {
						mario.setTextureRect(SMALL_MARIO_IDLE_LEFT);
					}
				}
				if (walk) {
					if (mario.getPosition().y < SCREEN_HEIGHT - TILE_SIZE * 1.5 - mario.getGlobalBounds().height) {
						mario.move(250.0f * dt, 250.0f * dt);
						camera.move(210.0f * dt, 0.0f);
					} else if (!insideCastle) {
						isCollidingY = true;
						mario.move(180.0f * dt, 0.0f);
						camera.move(175.0f * dt, 0.0f);
					}
					_data->window.setView(camera);
				}
			}
		}

	}

	void Mario::updateView(const float& dt) {

		cameraDistance = position.x - cameraX;
		if (cameraDistance > 530.0f) {

			cameraSpeed = cameraDistance - 530.0f;
			cameraX += cameraSpeed;
			camera.move(cameraSpeed, 0.0f);
			_data->window.setView(camera);

		} else if (cameraDistance > 350.0f && acceleration.x > 0.0f && velocity.x > 20.0f) {
			
			cameraSpeed = CAMERA_SPEED * dt;
			cameraX += cameraSpeed;
			camera.move(cameraSpeed, 0.0f);
			_data->window.setView(camera);

		}
	
	}

	void Mario::applyGravity() {
		acceleration.y += 1600.0f;
	}


	void Mario::draw() {
		_data->window.draw(mario);
	}


}