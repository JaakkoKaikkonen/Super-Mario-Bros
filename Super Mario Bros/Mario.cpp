#include "Mario.hpp"
#include <iostream>

namespace engine {

	Mario::Mario(gameDataRef data)
		: position(0.0f, 0.0f), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), _data(data), camera(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		mario.setTexture(_data->assets.getTexture("Mario"));
		mario.setScale(4.2f, 3.5f);
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

		mario.setPosition(position);
	}


	void Mario::checkCameraCollision() {
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
				dir = Dir::Right;
			} else {
				dir = Dir::Left;
			}
			if ((dir == Dir::Right && velocity.x < 0) || (dir == Dir::Left && velocity.x > 0)) {
				acceleration.x = speed / 12;
			} else {
				acceleration.x = speed;
			}
		}

	}

	void Mario::jump(const float speed) {
		acceleration.y = speed;
	}


	//Call animate() before update()!!!!!!!!
	void Mario::animate(const float& dt) {
		if (!dead) {
			if (down) {
				if (bigMario) {
					mario.move(0.0f, 100.0f * dt);
				} else {
					mario.move(0.0f, 75.0f * dt);
				}
			} else if (up) {
				if (bigMario) {
					position.y += -40.0f * dt;
					mario.move(0.0f, -40.0f * dt);
				} else {
					position.y += -24.0f * dt;
					mario.move(0.0f, -24.0f * dt);
				}
			}
			if (growingAnimation) {
				if (dir == Dir::Right) {
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
					if (fireForm) {
						//Fire mario animations

						if (throwFireBall) {
							if (dir == Dir::Right) {
								if (!isCollidingY) {
									mario.setTextureRect(FIRE_MARIO_JUMP_THROW_RIGHT);
								} else if (velocity.x > 80.0f) {
									if (_clock.getElapsedTime().asSeconds() > MARIO_RUN_ANIMATION_TIME / _fireMarioThrowRunRightAnimationFrames.size()) {
										if (_runLeftAnimationIterator < _fireMarioThrowRunRightAnimationFrames.size() - 1) {
											_runLeftAnimationIterator++;
										} else {
											_runLeftAnimationIterator = 0;
										}
										mario.setTextureRect(_fireMarioThrowRunRightAnimationFrames[_runLeftAnimationIterator]);
										_clock.restart();
									}
								} else {
									mario.setTextureRect(FIRE_MARIO_THROW_RIGHT01);
								}
							} else {
								if (!isCollidingY) {
									mario.setTextureRect(FIRE_MARIO_JUMP_THROW_LEFT);
								} else if (velocity.x < -80.0f) {
									if (_clock.getElapsedTime().asSeconds() > MARIO_RUN_ANIMATION_TIME / _fireMarioThrowRunLeftAnimationFrames.size()) {
										if (_runLeftAnimationIterator < _fireMarioThrowRunLeftAnimationFrames.size() - 1) {
											_runLeftAnimationIterator++;
										} else {
											_runLeftAnimationIterator = 0;
										}
										mario.setTextureRect(_fireMarioThrowRunLeftAnimationFrames[_runLeftAnimationIterator]);
										_clock.restart();
									}
								} else {
									mario.setTextureRect(FIRE_MARIO_THROW_LEFT01);
								}
							}
						} else if (climbing) {
							if (mario.getPosition().y < SCREEN_HEIGHT - TILE_SIZE * 2.5 - mario.getGlobalBounds().height - 5 && !_hasClimbedDown) {
								mario.move(0, POLE_CLIMBING_SPEED * dt);
								if (_clock.getElapsedTime().asSeconds() > MARIO_CLIMB_POLE_ANIMATION_TIME / _fireMarioClimbingAnimationFrames.size()) {
									if (_climbAnimationIterator < _fireMarioClimbingAnimationFrames.size() - 1) {
										_climbAnimationIterator++;
									} else {
										_climbAnimationIterator = 0;
									}
									mario.setTextureRect(_fireMarioClimbingAnimationFrames[_climbAnimationIterator]);
									_clock.restart();
								}
							} else if (!_hasClimbedDown) {
								mario.setTextureRect(FIRE_MARIO_CLIMB_POLE_LEFT);
								mario.move(mario.getGlobalBounds().width, 0);
								_hasClimbedDown = true;
								_clock.restart();
							} else if (flagDown && _clock.getElapsedTime().asSeconds() > 0.5f) {
								_data->assets.getSound("Stage_clear").play();
								velocity.x = 100.0f;
								dir = Dir::Right;
								crouch = false;
								climbing = false;
								walk = true;
								mario.move(20.0f, 0.0f);
							}
						} else if (takeDamage) {
						
							if (dir == Dir::Right) {
								if (_clock.getElapsedTime().asSeconds() > MARIO_SHRINKING_ANIMATION_TIME / _shrinkingRightAnimatinFrames.size()) {
									if (_shrinkingAnimationIterator == -1) {
										_shrinkingAnimationIterator = 18;
										bigMario = false;
										fireForm = false;
										takeDamage = false;

									} else {
										position.y += _shrinkingAnimationPositions[_shrinkingAnimationIterator];
										mario.setPosition(position.x, position.y);
										mario.setTextureRect(_shrinkingRightAnimatinFrames[_shrinkingAnimationIterator]);
										_shrinkingAnimationIterator--;
										_clock.restart();
									}
								}
							} else {
								if (_clock.getElapsedTime().asSeconds() > MARIO_SHRINKING_ANIMATION_TIME / _shrinkingLeftAnimatinFrames.size()) {
									if (_shrinkingAnimationIterator == -1) {
										_shrinkingAnimationIterator = 18;
										bigMario = false;
										takeDamage = false;
										fireForm = false;
									} else {
										position.y += _shrinkingAnimationPositions[_shrinkingAnimationIterator];
										mario.setPosition(position.x, position.y);
										mario.setTextureRect(_shrinkingLeftAnimatinFrames[_shrinkingAnimationIterator]);
										_shrinkingAnimationIterator--;
										_clock.restart();
									}
								}
							}


						} else if (crouch) {
							if (dir == Dir::Right) {
								mario.setTextureRect(FIRE_MARIO_CROUCH_RIGHT);
							} else {
								mario.setTextureRect(FIRE_MARIO_CROUCH_LEFT);
							}
						} else if (!isCollidingY) {
							if (dir == Dir::Right) {
								mario.setTextureRect(FIRE_MARIO_JUMP_RIGHT);
							} else {
								mario.setTextureRect(FIRE_MARIO_JUMP_LEFT);
							}
						} else if (acceleration.x != 0 && dir == Dir::Left && velocity.x > 0) {
							mario.setTextureRect(FIRE_MARIO_TURN_LEFT);
						} else if (acceleration.x != 0 && dir == Dir::Right && velocity.x < 0) {
							mario.setTextureRect(FIRE_MARIO_TURN_RIGHT);
						} else if (velocity.x > 80.0f) {
							if (_clock.getElapsedTime().asSeconds() > MARIO_RUN_ANIMATION_TIME / _fireMarioRunRightAnimationFrames.size()) {
								if (_runRightAnimationIterator < _fireMarioRunRightAnimationFrames.size() - 1) {
									_runRightAnimationIterator++;
								} else {
									_runRightAnimationIterator = 0;
								}
								mario.setTextureRect(_fireMarioRunRightAnimationFrames[_runRightAnimationIterator]);
								_clock.restart();
							}
						} else if (velocity.x < -80.0f) {
							if (_clock.getElapsedTime().asSeconds() > MARIO_RUN_ANIMATION_TIME / _fireMarioRunLeftAnimationFrames.size()) {
								if (_runLeftAnimationIterator < _fireMarioRunLeftAnimationFrames.size() - 1) {
									_runLeftAnimationIterator++;
								} else {
									_runLeftAnimationIterator = 0;
								}
								mario.setTextureRect(_fireMarioRunLeftAnimationFrames[_runLeftAnimationIterator]);
								_clock.restart();
							}
						} else {
							if (dir == Dir::Right) {
								mario.setTextureRect(FIRE_MARIO_IDLE_RIGHT);
							} else {
								mario.setTextureRect(FIRE_MARIO_IDLE_LEFT);
							}
						}
						if (walk) {
							if (mario.getPosition().y < SCREEN_HEIGHT - TILE_SIZE * 1.5 - mario.getGlobalBounds().height) {
								mario.move(250.0f * dt, 250.0f * dt);
								cameraX += 210.0f * dt;
								camera.move(210.0f * dt, 0.0f);
							} else if (!insideCastle) {
								isCollidingY = true;
								mario.move(180.0f * dt, 0.0f);
								cameraX += 175.0f * dt;
								camera.move(175.0f * dt, 0.0f);
							}
							_data->window.setView(camera);
						}


					} else {
						//Big mario animations
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
							} else if (flagDown && _clock.getElapsedTime().asSeconds() > 0.5f) {
								_data->assets.getSound("Stage_clear").play();
								velocity.x = 100.0f;
								dir = Dir::Right;
								crouch = false;
								climbing = false;
								walk = true;
								mario.move(20.0f, 0.0f);
							}
						} else if (takeDamage) {
			
							if (dir == Dir::Right) {
								if (_clock.getElapsedTime().asSeconds() > MARIO_SHRINKING_ANIMATION_TIME / _shrinkingRightAnimatinFrames.size()) {
									if (_shrinkingAnimationIterator == -1) {
										_shrinkingAnimationIterator = 18;
										bigMario = false;
										takeDamage = false;

									} else {
										position.y += _shrinkingAnimationPositions[_shrinkingAnimationIterator];
										mario.setPosition(position.x, position.y);
										mario.setTextureRect(_shrinkingRightAnimatinFrames[_shrinkingAnimationIterator]);
										_shrinkingAnimationIterator--;
										_clock.restart();
									}
								}
							} else {
								if (_clock.getElapsedTime().asSeconds() > MARIO_SHRINKING_ANIMATION_TIME / _shrinkingLeftAnimatinFrames.size()) {
									if (_shrinkingAnimationIterator == -1) {
										_shrinkingAnimationIterator = 18;
										bigMario = false;
										takeDamage = false;
									} else {
										position.y += _shrinkingAnimationPositions[_shrinkingAnimationIterator];
										mario.setPosition(position.x, position.y);
										mario.setTextureRect(_shrinkingLeftAnimatinFrames[_shrinkingAnimationIterator]);
										_shrinkingAnimationIterator--;
										_clock.restart();
									}
								}
							}


						} else if (crouch) {
							if (dir == Dir::Right) {
								mario.setTextureRect(BIG_MARIO_CROUCH_RIGHT);
							} else {
								mario.setTextureRect(BIG_MARIO_CROUCH_LEFT);
							}
						} else if (!isCollidingY) {
							if (dir == Dir::Right) {
								mario.setTextureRect(BIG_MARIO_JUMP_RIGHT);
							} else {
								mario.setTextureRect(BIG_MARIO_JUMP_LEFT);
							}
						} else if (acceleration.x != 0 && dir == Dir::Left && velocity.x > 0) {
							mario.setTextureRect(BIG_MARIO_TURN_LEFT);
						} else if (acceleration.x != 0 && dir == Dir::Right && velocity.x < 0) {
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
							if (dir == Dir::Right) {
								mario.setTextureRect(BIG_MARIO_IDLE_RIGHT);
							} else {
								mario.setTextureRect(BIG_MARIO_IDLE_LEFT);
							}
						}
						if (walk) {
							if (mario.getPosition().y < SCREEN_HEIGHT - TILE_SIZE * 1.5 - mario.getGlobalBounds().height) {
								mario.move(250.0f * dt, 250.0f * dt);
								cameraX += 210.0f * dt;
								camera.move(210.0f * dt, 0.0f);
							} else if (!insideCastle) {
								isCollidingY = true;
								mario.move(180.0f * dt, 0.0f);
								cameraX += 175.0f * dt;
								camera.move(175.0f * dt, 0.0f);
							}
							_data->window.setView(camera);
						}
					}
				} else {
				//Small mario animations
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
						} else if (flagDown && _clock.getElapsedTime().asSeconds() > 0.5f) {
							_data->assets.getSound("Stage_clear").play();
							velocity.x = 100.0f;
							dir = Dir::Right;
							climbing = false;
							walk = true;
							mario.move(15.0f, 0.0f);
						}
					} else if (takeDamage) {
						_data->music.stop();
						_data->assets.getSound("Mario_die").play();
						mario.setTextureRect(SMALL_MARIO_DEAD);
						dead = true;
						velocity.y = 0;
						velocity.x = 0;
						this->jump(-200000.0f);
					} else if (!isCollidingY) {
						if (dir == Dir::Right) {
							mario.setTextureRect(SMALL_MARIO_JUMP_RIGHT);
						} else {
							mario.setTextureRect(SMALL_MARIO_JUMP_LEFT);
						}
					} else if (acceleration.x != 0 && dir == Dir::Left && velocity.x > 0) {
						mario.setTextureRect(SMALL_MARIO_TURN_LEFT);
					} else if (acceleration.x != 0 && dir == Dir::Right && velocity.x < 0) {
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
						if (dir == Dir::Right) {
							mario.setTextureRect(SMALL_MARIO_IDLE_RIGHT);
						} else {
							mario.setTextureRect(SMALL_MARIO_IDLE_LEFT);
						}
					}
					if (walk) {
						if (mario.getPosition().y < SCREEN_HEIGHT - TILE_SIZE * 1.5 - mario.getGlobalBounds().height) {
							mario.move(250.0f * dt, 250.0f * dt);
							cameraX += 210.0f * dt;
							camera.move(210.0f * dt, 0.0f);
						} else if (!insideCastle) {
							isCollidingY = true;
							mario.move(180.0f * dt, 0.0f);
							cameraX += 175.0f * dt;
							camera.move(175.0f * dt, 0.0f);
						}
						_data->window.setView(camera);
					}
				}
			}
		}

	}

	void Mario::updateCamera(const float& dt) {

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

	void Mario::reset() {
		camera.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		cameraX = 0;
		cameraSpeed = 0;
		_data->window.setView(camera);
		dir = Dir::Right;
		velocity.x = 0;
		velocity.y = 0;
		_hasClimbedDown = false;
		climbing = false;
		dead = false;
		flagDown = false;
		walk = false;
		insideCastle = false;
		takeDamage = false;
	}

	void Mario::applyGravity() {
		acceleration.y += 1600.0f;
	}


	void Mario::draw() {
		_data->window.draw(mario);
	}



}