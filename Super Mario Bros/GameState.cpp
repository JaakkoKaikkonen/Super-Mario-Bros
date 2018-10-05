#include <string>
#include <array>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "Collision.hpp"
#include "functions.hpp"
#include <iostream>


namespace engine {

	GameState::GameState(gameDataRef data)
		: _data(data), _mario(_data), _pole(_data), _castle(_data)
	{
		_levelTiles.reserve(600);
		_levelDecorations.reserve(40);
		_items.reserve(4);

	}

	void GameState::init() {
		std::cout << "Game state" << std::endl;
		_collisionGrid.clear();
		_collisionGrid.reserve(25);
		int numberOfCollisionGrids = 25;
		int mapLength;

		if (_level == Level01) {
			mapLength = loadLevel(_levelTiles, _levelDecorations, _pole, _castle, "Level01.txt", _data);

		}

		std::cout << mapLength << std::endl;
		int gridWidth = mapLength / numberOfCollisionGrids;

		for (int i = 0; i < numberOfCollisionGrids; i++) {
			_collisionGrid.emplace_back(CollisionGrid(i * gridWidth * TILE_SIZE, 0, gridWidth * TILE_SIZE, SCREEN_HEIGHT));
			for (int j = 0; j < _levelTiles.size(); j++) {
				if (Collision::checkSpriteCollision(_collisionGrid[i].boundary, _levelTiles[j]->getTile())) {
					_collisionGrid[i].tiles.push_back(_levelTiles[j]);
				}
			}
		}



		//std::cout << _levelTiles.size() << std::endl;
		//std::cout << _levelDecorations.size() << std::endl;

	}


	void GameState::handleInput(const float& dt) {
		sf::Event event;
		while (_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}
		}


		if (!_mario.growingAnimation && !_mario.walk) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				_mario.move(-MARIO_SPEED_X);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				_mario.move(MARIO_SPEED_X);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _mario.bigMario && !_mario.crouch) {
				_mario.crouch = true;
				_mario.position.y += 11.0f * _mario.marioScaleY;
				_mario.mario.setPosition(_mario.position.x, _mario.position.y);
			} 

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _mario.crouch && !_mario.dontStandUp) {
				_mario.crouch = false;
				_mario.position.y -= 11.0f * _mario.marioScaleY;
			}
				

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && !_mario.crouch) {
				if (_jumpTimer < 0.105f) {
					_mario.jump();
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
		
		if (!_mario.growingAnimation && !_mario.climbing && !_mario.walk) {

			_mario.updateView(dt);


			_mario.updateX(dt);
			
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
								} else if (_mario.mario.getPosition().x >  _collisionGrid[i].tiles[j]->getTile().getPosition().x && _mario.velocity.x < 1.0f) {
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
								} else if (_mario.mario.getPosition().x >_collisionGrid[i].tiles[j]->getTile().getPosition().x && _mario.velocity.x < 1.0f) {
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

			_mario.updateY(dt);

			if (_mario.bigMario) {
				if (_mario.crouch) {
					sf::FloatRect mario(_mario.position.x, _mario.position.y - 11.0f * _mario.marioScaleY, BIG_MARIO_IDLE_RIGHT.width * _mario.marioScaleX, BIG_MARIO_IDLE_RIGHT.height * _mario.marioScaleY - 21.0f * _mario.marioScaleY);
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
			} else {
				bool exit = false;
				for (int i = 0; i < _collisionGrid.size(); i++) {
					if (exit) break;
					if (Collision::checkSpriteCollision(_collisionGrid[i].boundary, _mario.mario)) {
						for (int j = 0; j < _collisionGrid[i].tiles.size(); j++) {
							if (Collision::checkSpriteCollision(_mario.mario, _mario.hitBoxScale, 1.0f, _collisionGrid[i].tiles[j]->getTile())) {
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

			if(iterator != -1) {
				if (iterator == 0) {
					_mario.position.y = boxesCollidedWith[iterator]->getTile().getPosition().y + boxesCollidedWith[iterator]->getTile().getGlobalBounds().height;
					boxesCollidedWith[iterator]->update(_items, _levelTiles, _mario);
					_mario.velocity.y = 0;
				} else if (abs((_mario.position.x + _mario.mario.getGlobalBounds().width / 2) - 
					(boxesCollidedWith[0]->getTile().getPosition().x + boxesCollidedWith[0]->getTile().getGlobalBounds().width / 2)) < 
					abs((_mario.position.x + _mario.mario.getGlobalBounds().width / 2) - 
					(boxesCollidedWith[1]->getTile().getPosition().x + boxesCollidedWith[1]->getTile().getGlobalBounds().width / 2))) {

					_mario.position.y = boxesCollidedWith[0]->getTile().getPosition().y + boxesCollidedWith[0]->getTile().getGlobalBounds().height;
					boxesCollidedWith[0]->update(_items, _levelTiles, _mario);
					_mario.velocity.y = 0;
				} else {
					_mario.position.y = boxesCollidedWith[1]->getTile().getPosition().y + boxesCollidedWith[1]->getTile().getGlobalBounds().height;
					boxesCollidedWith[1]->update(_items, _levelTiles, _mario);
					_mario.velocity.y = 0;
				}
			}

		} else if (!_mario.walk) {
			_mario.velocity.y = 0;
			_mario.velocity.x = 0;
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

		if (_mario.climbing) {
			if (_pole.updateFlag(dt)) {
				_mario.flagDown = true;
			}
		} else if (!_mario.walk) {
			for (int i = 0; i < _pole.poleSprites.size(); i++) {
				if (Collision::checkSpriteCollision(_mario.mario, _pole.poleSprites[i])) {
					if (_mario.bigMario) {
						_mario.mario.setPosition(_pole.poleSprites[1].getPosition().x - _mario.mario.getGlobalBounds().width + 4, _mario.position.y);
					} else {
						_mario.mario.setPosition(_pole.poleSprites[1].getPosition().x - _mario.mario.getGlobalBounds().width + 22, _mario.position.y);
					}
					_pole.lowerFlag = true;
					_mario.climbing = true;
				}
			}
		}

		if (_castle.insideCastle(_mario)) {
			_mario.insideCastle = true;
			_castle.raiseFlag(dt);
		}

	
	}



	void GameState::draw() {
		_data->window.clear(BACKGROUND_COLOR);

		for (int i = 0; i < _levelDecorations.size(); i++) {
			_levelDecorations[i].draw();
		}

		_castle.draw();

		for (int i = 0; i < _pole.poleSprites.size(); i++) {
			_pole.draw();
		}

		for (int i = 0; i < _items.size(); i++) {
			_items[i]->draw();
		}

		if (!_mario.insideCastle) {
			_mario.draw();
		}
		
		for (int i = 0; i < _levelTiles.size(); i++) {
			_levelTiles[i]->draw();
		}
		

		_data->window.display();
	}

}
