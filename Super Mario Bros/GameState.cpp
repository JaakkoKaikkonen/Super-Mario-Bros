#include <string>
#include <array>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "Collision.hpp"
#include "functions.hpp"
#include <iostream>

sf::Color backgroundColor;


namespace engine {

	GameState::GameState(gameDataRef data)
		: _data(data), _mario(_data), _pole(_data), _castle(_data), _HUD(_data)
		
	{
		backgroundColor = BACKGROUND_COLOR01;
	}

	void GameState::init() {
		std::cout << "Game state" << std::endl;

		_pole.lowerFlag = false;
		_mario.flagDown = false;
		_deadTimer = 0;
		_insideCastleCounter = 0;
		_mario.reset();

		_data->window.clear();
		
		_HUD.update(_score, _coins, _time, _mario.cameraX);
		_HUD.updateLevel(_world, _level, _lifes);
		_HUD.loadingScreenDraw();

		_data->window.display();

		for (int i = 0; i < _levelTiles.size(); i++) {
			delete _levelTiles[i];
		}
		
		_levelTiles.clear();
		_levelDecorations.clear();
		_items.clear();
		_enemies.clear();
		_collisionGrid.clear();
		_fireBalls.clear();
		_money.clear();


		_levelTiles.reserve(1150);
		_levelDecorations.reserve(40);
		_items.reserve(4);
		_enemies.reserve(12);
		_collisionGrid.reserve(25);
		_fireBalls.reserve(2);
		_scores.reserve(3);
		_money.reserve(20);

		numberOfCollisionGrids = 25;
		int mapLength;

		if (_level == Level01) {
			mapLength = loadLevel("Resources/Levels/Level01.txt", _levelTiles, _enemies, _levelDecorations, _mario, _money, _pole, _castle, _scores, _coins, _data);
			_data->music.openFromFile(OW_THEME_MUSIC_FILEPATH);
		} else if (_level == Level02) {
			mapLength = loadLevel("Resources/Levels/Level02.txt", _levelTiles, _enemies, _levelDecorations, _mario, _money, _pole, _castle, _scores, _coins, _data);
			_data->music.openFromFile(OW_THEME_MUSIC_FILEPATH);
		}

		backgroundColor = BACKGROUND_COLOR01;
		
		//std::cout << mapLength << std::endl;
		int gridWidth = mapLength / numberOfCollisionGrids;

		for (int i = 0; i < numberOfCollisionGrids; i++) {
			_collisionGrid.emplace_back(CollisionGrid(i * gridWidth * TILE_SIZE, -500, gridWidth * TILE_SIZE, SCREEN_HEIGHT + 7000));
			for (int j = 0; j < _levelTiles.size(); j++) {
				if (Collision::checkSpriteCollision(_collisionGrid[i].boundary, _levelTiles[j]->getTile())) {
					_collisionGrid[i].tiles.push_back(_levelTiles[j]);
				}
			}
		}

		_clock.restart();

		while (_clock.getElapsedTime().asSeconds() < LOADINGSCREEN_TIME) {
			sf::Event event;
			while (_data->window.pollEvent(event)) {
				if (sf::Event::Closed == event.type) {
					_data->window.close();
				}
			}
		}

		if (_lifes == 0) {
			_data->machine.addState(stateRef(new MenuState(_data)), true);
			return;
		}

		_data->music.setLoop(true);
		_data->music.play();

		_clock.restart();

		//std::cout << _levelDecorations.size() << std::endl;

	}


	void GameState::handleInput(const float& dt) {
		sf::Event event;
		while (_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			this->init();
		}

		if (!_mario.growingAnimation && !_mario.walk && !_mario.dead && !_mario.climbing && !_mario.dead && !_mario.down && !_mario.up) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				_mario.move(-MARIO_SPEED_X);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				_mario.move(MARIO_SPEED_X);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !_mario.crouch) {
				if (_mario.fireForm && _fireBalls.size() < 2 && _fireBallTimer < 0.0f) {
					_data->assets.getSound("Fireball").play();
					_fireBalls.emplace_back(FireBall(_mario.position.x, _mario.position.y + 10.0f, _mario.dir, _data));
					_mario.throwFireBall = true;
					_fireBallTimer = 0.3f;
				}
			} 
			
			if (_fireBallTimer < 0.1){
				_mario.throwFireBall = false;
			}

			_fireBallTimer -= dt;


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				_downKeyPressed = true;
				if (_mario.bigMario && !_mario.crouch) {
					_mario.throwFireBall = false;
					_mario.crouch = true;
					_mario.position.y += 10.0f * _mario.marioScaleY;
					_mario.mario.setPosition(_mario.position.x, _mario.position.y);
				}
			} 

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				_downKeyPressed = false;
				if (_mario.crouch && !_mario.dontStandUp) {
					_mario.crouch = false;
					_mario.position.y -= 10.0f * _mario.marioScaleY;
				}
			}
				

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && !_mario.crouch) {
				if (_jumpTimer < 0.105f) {
					if (_jumpTimer == 0.0f) {
						if (_mario.bigMario) {
							_data->assets.getSound("Jump_big").play();
						} else {
							_data->assets.getSound("Jump_small").play();
						}
					} 
					_mario.jump(-9600.0f);
					_jumpTimer += dt;
				}
			} else if (_mario.isCollidingY) {
				_jumpTimer = 0;
			} else {
				_jumpTimer = 0.105f;
			}

		}

		
	}




	void GameState::update(const float& dt) {

		std::array<Tile*, 3> boxesCollidedWith;

		int iterator = -1;

		_mario.animate(dt);


		for (int i = 0; i < _levelTiles.size(); i++) {
			_levelTiles[i]->animate(dt);
		}
		
		if (!_mario.growingAnimation && !_mario.climbing && !_mario.walk && !_mario.down && !_mario.up) {

			_mario.updateCamera(dt);


			_mario.updateX(dt);
			_mario.checkCameraCollision();
			
			if (!_mario.dead) {
				if (_mario.isCollidingY && !_mario.bigMario) {
					bool exit = false;
					for (int i = 0; i < _collisionGrid.size(); i++) {
						if (exit) break;
						if (Collision::checkSpriteCollision(_collisionGrid[i].boundary, _mario.mario)) {
							for (int j = 0; j < _collisionGrid[i].tiles.size(); j++) {
								if (Collision::checkSpriteCollision(_mario.mario, _mario.hitBoxScale, 0.98f, _collisionGrid[i].tiles[j]->getTile())) {
									if (_mario.mario.getPosition().x < _collisionGrid[i].tiles[j]->getTile().getPosition().x && _mario.velocity.x > -1.0f) {
										_mario.position.x = _collisionGrid[i].tiles[j]->getTile().getPosition().x - 0.01f - _mario.mario.getGlobalBounds().width * (_mario.hitBoxScale + ((1.0f - _mario.hitBoxScale) / 2));
										_mario.velocity.x = 0;
									} else if (_mario.mario.getPosition().x > _collisionGrid[i].tiles[j]->getTile().getPosition().x && _mario.velocity.x < 1.0f) {
										_mario.position.x = _collisionGrid[i].tiles[j]->getTile().getPosition().x + _collisionGrid[i].tiles[j]->getTile().getGlobalBounds().width - _mario.mario.getGlobalBounds().width * ((1.0f - _mario.hitBoxScale) / 2);
										_mario.velocity.x = 0;
									}
									exit = true;
									break;
								}
							}
						}
					}
				} else {
					bool exit = false;
					for (int i = 0; i < _collisionGrid.size(); i++) {
						if (exit) break;
						if (Collision::checkSpriteCollision(_collisionGrid[i].boundary, _mario.mario)) {
							for (int j = 0; j < _collisionGrid[i].tiles.size(); j++) {
								if (Collision::checkSpriteCollision(_mario.mario, 1.0f, 0.98f, _collisionGrid[i].tiles[j]->getTile())) {
									if (_mario.mario.getPosition().x <_collisionGrid[i].tiles[j]->getTile().getPosition().x && _mario.velocity.x > -1.0f) {
										_mario.position.x = _collisionGrid[i].tiles[j]->getTile().getPosition().x - _mario.mario.getGlobalBounds().width;
										_mario.velocity.x = 0;
									} else if (_mario.mario.getPosition().x > _collisionGrid[i].tiles[j]->getTile().getPosition().x && _mario.velocity.x < 1.0f) {
										_mario.position.x = _collisionGrid[i].tiles[j]->getTile().getPosition().x + _collisionGrid[i].tiles[j]->getTile().getGlobalBounds().width;
										_mario.velocity.x = 0;
									}
									exit = true;
									break;
								}
							}
						}
					}
				}
			}

			_mario.updateY(dt);

			if (!_mario.dead) {
				if (_mario.bigMario) {
					if (_mario.crouch) {
						sf::FloatRect mario(_mario.position.x, _mario.position.y - 10.0f * _mario.marioScaleY, BIG_MARIO_IDLE_RIGHT.width * _mario.marioScaleX, BIG_MARIO_IDLE_RIGHT.height * _mario.marioScaleY - 22.0f * _mario.marioScaleY);
						bool exit = false;
						for (int i = 0; i < _collisionGrid.size(); i++) {
							if (exit) break;
							if (Collision::checkSpriteCollision(_collisionGrid[i].boundary, _mario.mario)) {
								for (int j = 0; j < _collisionGrid[i].tiles.size(); j++) {
									if (Collision::checkSpriteCollision(mario, _collisionGrid[i].tiles[j]->getTile())) {
										_mario.dontStandUp = true;
										exit = true;
										break;
									} else {
										_mario.dontStandUp = false;
									}
								}
							}
						}
					}
					bool exit = false;
					for (int i = 0; i < _collisionGrid.size(); i++) {
						if (exit) break;
						if (Collision::checkSpriteCollision(_collisionGrid[i].boundary, _mario.mario)) {
							for (int j = 0; j < _collisionGrid[i].tiles.size(); j++) {
								if (Collision::checkSpriteCollision(_mario.mario, _collisionGrid[i].tiles[j]->getTile())) {
									if (_mario.mario.getPosition().y < _collisionGrid[i].tiles[j]->getTile().getPosition().y + _collisionGrid[i].tiles[j]->getTile().getGlobalBounds().height / 2) {
										if (_collisionGrid[i].tiles[j]->getTile().getColor() == sf::Color(254, 254, 255)) {
											if (_downKeyPressed && _mario.position.y + _mario.mario.getGlobalBounds().height + 0.1f > _collisionGrid[i].tiles[j]->getTile().getPosition().y && 
												_mario.position.x > _collisionGrid[i].tiles[j]->getTile().getPosition().x + 8.0f && 
												_mario.position.x + _mario.mario.getGlobalBounds().width < _collisionGrid[i].tiles[j]->getTile().getPosition().x + _collisionGrid[i].tiles[j]->getTile().getGlobalBounds().width - 8.0f) {
												_data->assets.getSound("Pipe").play();
												_mario.mario.setPosition(_mario.position.x, _mario.position.y - 10.0f * _mario.marioScaleY);
												_downKeyPressed = false;
												_mario.down = true;
												_mario.crouch = false;
											}
										} 
										_mario.position.y = _collisionGrid[i].tiles[j]->getTile().getPosition().y - _mario.mario.getGlobalBounds().height;
										_mario.isCollidingY = true;
										_mario.velocity.y = 0;
										exit = true;
										break;
									} else {
										iterator++;
										boxesCollidedWith[iterator] = _collisionGrid[i].tiles[j];
									}
								} else {
									_mario.isCollidingY = false;
								}
							}
						}
					}
				} else if (!_mario.dead) {
					bool exit = false;
					for (int i = 0; i < _collisionGrid.size(); i++) {
						if (exit) break;
						if (Collision::checkSpriteCollision(_collisionGrid[i].boundary, _mario.mario)) {
							for (int j = 0; j < _collisionGrid[i].tiles.size(); j++) {
								if (Collision::checkSpriteCollision(_mario.mario, _mario.hitBoxScale, 1.0f, _collisionGrid[i].tiles[j]->getTile())) {
									if (_collisionGrid[i].tiles[j]->getTile().getColor() == sf::Color(254, 254, 255)) {
										if (_downKeyPressed && _mario.position.y + _mario.mario.getGlobalBounds().height + 0.1f > _collisionGrid[i].tiles[j]->getTile().getPosition().y &&
											_mario.position.x > _collisionGrid[i].tiles[j]->getTile().getPosition().x + 8.0f &&
											_mario.position.x + _mario.mario.getGlobalBounds().width < _collisionGrid[i].tiles[j]->getTile().getPosition().x + _collisionGrid[i].tiles[j]->getTile().getGlobalBounds().width - 8.0f) {
											_data->assets.getSound("Pipe").play();
											_downKeyPressed = false;
											_mario.down = true;
										}
									}
									if (_mario.mario.getPosition().y < _collisionGrid[i].tiles[j]->getTile().getPosition().y + _collisionGrid[i].tiles[j]->getTile().getGlobalBounds().height / 2) {
										_mario.position.y = _collisionGrid[i].tiles[j]->getTile().getPosition().y - _mario.mario.getGlobalBounds().height;
										_mario.isCollidingY = true;
										_mario.velocity.y = 0;
										exit = true;
										break;
									} else {
										iterator++;
										boxesCollidedWith[iterator] = _collisionGrid[i].tiles[j];
									}
								} else {
									_mario.isCollidingY = false;
								}
							}
						}
					}
				}
			}

			if(iterator != -1) {
				if (iterator == 0) {
					_mario.position.y = boxesCollidedWith[iterator]->getTile().getPosition().y + boxesCollidedWith[iterator]->getTile().getGlobalBounds().height;
					boxesCollidedWith[iterator]->update(_items, _mario);
					_mario.velocity.y = 0;
				} else if (abs((_mario.position.x + _mario.mario.getGlobalBounds().width / 2) - 
					(boxesCollidedWith[0]->getTile().getPosition().x + boxesCollidedWith[0]->getTile().getGlobalBounds().width / 2)) < 
					abs((_mario.position.x + _mario.mario.getGlobalBounds().width / 2) - 
					(boxesCollidedWith[1]->getTile().getPosition().x + boxesCollidedWith[1]->getTile().getGlobalBounds().width / 2))) {

					_mario.position.y = boxesCollidedWith[0]->getTile().getPosition().y + boxesCollidedWith[0]->getTile().getGlobalBounds().height;
					boxesCollidedWith[0]->update(_items, _mario);
					_mario.velocity.y = 0;
				} else {
					_mario.position.y = boxesCollidedWith[1]->getTile().getPosition().y + boxesCollidedWith[1]->getTile().getGlobalBounds().height;
					boxesCollidedWith[1]->update(_items, _mario);
					_mario.velocity.y = 0;
				}
			}

		} else if (!_mario.walk) {
			_mario.velocity.y = 0;
			_mario.velocity.x = 0;
		}

		for (int i = 0; i < _money.size(); i++) {
			_money[i].animate();
			_money[i].update(_mario, _coins);
			if (_money[i].shouldBeDeleted()) {
				_money[i] = _money[_money.size() - 1];
				_money.pop_back();
			}
		}

		for (int i = _items.size() - 1; i >= 0; i--) {
			_items[i]->animate();
			_items[i]->update(dt, _collisionGrid, _mario);
			if (_items[i]->shouldBeDeleted()) {
				delete _items[i];
				_items[i] = _items[_items.size() - 1];
				_items.pop_back();
			}
		}

		for (int i = _fireBalls.size() - 1; i >= 0; i--) {
			_fireBalls[i].animate();
			_fireBalls[i].update(dt, _collisionGrid, _mario);
			if (_fireBalls[i].shouldBeDeleted()) {
				_fireBalls[i] = _fireBalls[_fireBalls.size() - 1];
				_fireBalls.pop_back();
			}
		}


		for (int i = _enemies.size() - 1; i >= 0; i--) {
			if (_enemies[i]->shouldBeUpdated(_mario)) {
				_enemies[i]->update(dt, _collisionGrid, _mario);
				if (!_enemies[i]->checkIfDead()) {
					for (int j = 0; j < _fireBalls.size(); j++) {
						if (Collision::checkSpriteCollision(_fireBalls[j].getSprite(), _enemies[i]->getSprite())) {
							if (!_enemies[i]->shell() && !_fireBalls[j].explode) {
								_enemies[i]->kill();
								if (_fireBalls[j].getDirection() == Dir::Right) {
									_enemies[i]->flip(-PI / 4);
								} else {
									_enemies[i]->flip(-(PI - PI / 4));
								}
							}
							_fireBalls[j].explode = true;
							break;
						}
					}
				}
			}
			if (_enemies[i]->shouldBeDeleted()) {
				delete _enemies[i];
				_enemies[i] = _enemies[_enemies.size() - 1];
				_enemies.pop_back();
			}
		}


		for (int i = 0; i < _enemies.size(); i++) {
			if(_enemies[i]->shouldBeUpdated(_mario) && !_enemies[i]->checkIfDead()) {
				for (int j = 0; j < _enemies.size(); j++) {
					if (_enemies[i] == _enemies[j] || !_enemies[j]->shouldBeUpdated(_mario) || _enemies[j]->checkIfDead()) {
						continue;
					}
					if (Collision::checkSpriteCollision(_enemies[i]->getSprite(), _enemies[j]->getSprite())) {
						if (_enemies[i]->getName() == "Goomba") {
							if (_enemies[j]->getName() == "Koopa") {
								if (_enemies[j]->sliding()) {
									_enemies[i]->flip(-PI / 3);
								} else {
									if (_enemies[i]->getSprite().getPosition().x < _enemies[j]->getSprite().getPosition().x) {
										_enemies[i]->setPosition(sf::Vector2f(_enemies[j]->getSprite().getPosition().x - _enemies[i]->getSprite().getGlobalBounds().width, _enemies[i]->getSprite().getPosition().y));
										_enemies[i]->turn();
									} else {
										_enemies[i]->setPosition(sf::Vector2f(_enemies[j]->getSprite().getPosition().x + _enemies[j]->getSprite().getGlobalBounds().width, _enemies[i]->getSprite().getPosition().y));
										_enemies[i]->turn();
									}
								}
							} else {
								if (_enemies[i]->getSprite().getPosition().x < _enemies[j]->getSprite().getPosition().x) {
									_enemies[i]->setPosition(sf::Vector2f(_enemies[j]->getSprite().getPosition().x - _enemies[i]->getSprite().getGlobalBounds().width, _enemies[i]->getSprite().getPosition().y));
									_enemies[i]->turn();
								} else {
									_enemies[i]->setPosition(sf::Vector2f(_enemies[j]->getSprite().getPosition().x + _enemies[j]->getSprite().getGlobalBounds().width, _enemies[i]->getSprite().getPosition().y));
									_enemies[i]->turn();
								}
							}

						} else if (_enemies[i]->getName() == "Koopa") {
							if (_enemies[j]->getName() == "Goomba") {
								if (!_enemies[i]->sliding() && !_enemies[i]->shell()) {
									if (_enemies[i]->getSprite().getPosition().x < _enemies[j]->getSprite().getPosition().x) {
										_enemies[i]->setPosition(sf::Vector2f(_enemies[j]->getSprite().getPosition().x - _enemies[i]->getSprite().getGlobalBounds().width, _enemies[i]->getSprite().getPosition().y));
										_enemies[i]->turn();
									} else {
										_enemies[i]->setPosition(sf::Vector2f(_enemies[j]->getSprite().getPosition().x + _enemies[j]->getSprite().getGlobalBounds().width, _enemies[i]->getSprite().getPosition().y));
										_enemies[i]->turn();
									}
								}
							} else if (_enemies[j]->getName() == "Koopa") {
								if (_enemies[j]->sliding()) {
									if (_enemies[i]->sliding()) {
										if (_enemies[i]->getSprite().getPosition().x < _enemies[j]->getSprite().getPosition().x) {
											_enemies[i]->setPosition(sf::Vector2f(_enemies[j]->getSprite().getPosition().x - _enemies[i]->getSprite().getGlobalBounds().width, _enemies[i]->getSprite().getPosition().y));
											_enemies[i]->turn();
										} else {
											_enemies[i]->setPosition(sf::Vector2f(_enemies[j]->getSprite().getPosition().x + _enemies[j]->getSprite().getGlobalBounds().width, _enemies[i]->getSprite().getPosition().y));
											_enemies[i]->turn();
										}
									} else if (!_enemies[i]->shell()) {
										if (_enemies[i]->getSprite().getPosition().x < _enemies[j]->getSprite().getPosition().x) {
											_enemies[i]->flip(-(PI - PI / 4));
										} else {
											_enemies[i]->flip(-PI / 4);
										}
									}
								} else {
									if (_enemies[i]->getSprite().getPosition().x < _enemies[j]->getSprite().getPosition().x) {
										_enemies[i]->setPosition(sf::Vector2f(_enemies[j]->getSprite().getPosition().x - _enemies[i]->getSprite().getGlobalBounds().width, _enemies[i]->getSprite().getPosition().y));
										_enemies[i]->turn();
									} else {
										_enemies[i]->setPosition(sf::Vector2f(_enemies[j]->getSprite().getPosition().x + _enemies[j]->getSprite().getGlobalBounds().width, _enemies[i]->getSprite().getPosition().y));
										_enemies[i]->turn();
									}
								}
							}
						}
					}
				}
			}
		}


		//std::cout << _enemies.size() << std::endl;

		if (_mario.climbing) {
			if (_pole.updateFlag(dt)) {
				_mario.flagDown = true;
			}
		} else if (!_mario.walk) {
			for (int i = 0; i < _pole.poleSprites.size(); i++) {
				if (Collision::checkSpriteCollision(_mario.mario, _pole.poleSprites[i])) {
					_data->music.stop();
					_data->assets.getSound("Flagpole").play();
					_scores.emplace_back(Score(_pole.poleSprites[i].getPosition().x, _pole.poleSprites[i].getPosition().y, (i - _pole.poleSprites.size()) * -100, _data));
					if (_mario.bigMario) {
						_mario.mario.setPosition(_pole.poleSprites[1].getPosition().x - _mario.mario.getGlobalBounds().width + 4, _mario.position.y);
					} else {
						_mario.mario.setPosition(_pole.poleSprites[1].getPosition().x - _mario.mario.getGlobalBounds().width + 22, _mario.position.y);
					}
					_pole.lowerFlag = true;
					_mario.climbing = true;
					_mario.throwFireBall = false;
					break;
				}
			}
		}

		if (_castle.insideCastle(_mario)) {
			_mario.insideCastle = true;
			_castle.raiseFlag(dt);
			if (_insideCastleCounter > 3.6f) {
				_level = Level02;
				this->init();
				return;
			}
			_insideCastleCounter += dt;
		}

		_time = (int)_clock.getElapsedTime().asSeconds();

		_HUD.update(_score, _coins, _time, _mario.cameraX);


		for (int i = 0; i < _scores.size(); i++) {
			_scores[i].update(dt);
			_scores[i].addScore(_score);
			if (_scores[i].shouldBeDeleted()) {
				_scores[i] = _scores[_scores.size() - 1];
				_scores.pop_back();
			}
		}


		if (_time >= LEVEL_TIME) {
			_mario.takeDamage = true;
		}
		if (_time >= LEVEL_TIME - 30 && _warning) {
			_data->assets.getSound("Warning").play();
			_warning = false;
		}
	
		if (_mario.position.y > SCREEN_HEIGHT && !_mario.dead) {
			_mario.dead = true;
			_data->music.stop();
			_data->assets.getSound("Mario_die").play();
		}

		if (_mario.dead) {
			if (_deadTimer > 2.0f) {
				_coins = 0;
				_score = 0;
				_lifes--;
				_mario.bigMario = false;
				_mario.fireForm = false;
				this->init();
				return;
			}
			_deadTimer += dt;
		}

	}



	void GameState::draw() {


		_data->window.clear(backgroundColor);

		for (int i = 0; i < _levelDecorations.size(); i++) {
			_levelDecorations[i].draw();
		}


		for (int i = 0; i < _items.size(); i++) {
			_items[i]->draw();
		}

		for (int i = 0; i < _collisionGrid.size(); i++) {
			if (Collision::checkSpriteCollision(_collisionGrid[i].boundary, _mario.mario)) {
				for (int j = 0; j < _collisionGrid[i].tiles.size(); j++) {
					_collisionGrid[i].tiles[j]->draw();
				}
				if (i != 0) {
					for (int j = 0; j < _collisionGrid[i - 1].tiles.size(); j++) {
						_collisionGrid[i - 1].tiles[j]->draw();
					}
				}
				if (i != numberOfCollisionGrids - 1) {
					for (int j = 0; j < _collisionGrid[i + 1].tiles.size(); j++) {
						_collisionGrid[i + 1].tiles[j]->draw();
					}
				}
				if (i < numberOfCollisionGrids - 2) {
					for (int j = 0; j < _collisionGrid[i + 2].tiles.size(); j++) {
						_collisionGrid[i + 2].tiles[j]->draw();
					}
				}
			}
		}



		_castle.draw();

		for (int i = 0; i < _pole.poleSprites.size(); i++) {
			_pole.draw();
		}


		for (int i = 0; i < _money.size(); i++) {
			_money[i].draw();
		}

		_HUD.draw();

		for (int i = 0; i < _enemies.size(); i++) {
			_enemies[i]->draw();
		}

		for (int i = 0; i < _fireBalls.size(); i++) {
			_fireBalls[i].draw();
		}

		for (int i = 0; i < _scores.size(); i++) {
			_scores[i].draw();
		}

		if (!_mario.insideCastle) {
			_mario.draw();
		}


		for (int i = 0; i < _collisionGrid.size(); i++) {
			if (Collision::checkSpriteCollision(_collisionGrid[i].boundary, _mario.mario)) {
				for (int j = 0; j < _collisionGrid[i].tiles.size(); j++) {
					if (_collisionGrid[i].tiles[j]->getTile().getColor().r == 254) {
						_collisionGrid[i].tiles[j]->draw();
					}
				}
				if (i != 0) {
					for (int j = 0; j < _collisionGrid[i - 1].tiles.size(); j++) {
						if (_collisionGrid[i - 1].tiles[j]->getTile().getColor().r == 254) {
							_collisionGrid[i - 1].tiles[j]->draw();
						}
					}
				}
				if (i != numberOfCollisionGrids - 1) {
					for (int j = 0; j < _collisionGrid[i + 1].tiles.size(); j++) {
						if (_collisionGrid[i + 1].tiles[j]->getTile().getColor().r == 254) {
							_collisionGrid[i + 1].tiles[j]->draw();
						}
					}
				}
				if (i < numberOfCollisionGrids - 2) {
					for (int j = 0; j < _collisionGrid[i + 2].tiles.size(); j++) {
						if (_collisionGrid[i + 2].tiles[j]->getTile().getColor().r == 254) {
							_collisionGrid[i + 2].tiles[j]->draw();
						}
					}
				}
			}
		}

		if (_mario.dead) {
			_mario.draw();
		}

		_data->window.display();

		
	}

}
