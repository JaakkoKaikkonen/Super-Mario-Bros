#include "BrickTile.hpp"
#include "DEFINITIONS.hpp"
#include "Coin.hpp"
#include "Mushroom.hpp"
#include "FireFlower.hpp"
#include <iostream>

namespace Game {

	BrickTile::BrickTile(const int& x, const int& y, Items item, Setting setting, int& coins, std::vector<Score>& scores, gameDataRef data)
		: _data(data), _tile(_data->assets.getTexture("Tiles")), _rightParticlesVector(cos(-PI / 4), sin(-PI / 4)),
		_leftParticlesVector(cos(-(PI - PI / 4)), sin(-(PI - PI / 4))), _item(item), _coins(coins), _scores(scores)
	{
		if (setting == Setting::OW) {
			_tile.setTextureRect(BRICK_TILE);
			_particleAnimationFrames[0] = BRICK_PARTICLE1;
			_particleAnimationFrames[1] = BRICK_PARTICLE2;
		} else {
			_tile.setTextureRect(BRICK_TILE_UG);
			_particleAnimationFrames[0] = BRICK_PARTICLE1_UG;
			_particleAnimationFrames[1] = BRICK_PARTICLE1_UG;
		}
		_tile.setScale(4.0f, 4.0f);
		_tile.setPosition(x, y);
		char j = 0;
		for (char i = 0; i < 4; i++) {
			_particles[i] = sf::Sprite(_data->assets.getTexture("Tiles"), _particleAnimationFrames[0]);
			_particles[i].setScale(4.0f, 4.0f);
			if (i < 2) {
				_particles[i].setPosition(x + BRICK_PARTICLE1.width * 4.0f * i, y);
			} else {
				_particles[i].setPosition(x + BRICK_PARTICLE1.width * 4.0f * j, y - BRICK_PARTICLE1.height * 4.0f);
				j++;
			}
		}
	}

	void BrickTile::draw() {
		if (!_destroyed || _opened) {
			if (_explode) {
				for (char i = 0; i < 4; i++) {
					_data->window.draw(_particles[i]);
				}
			} else {
				_data->window.draw(_tile);
			}
		}
	}

	void BrickTile::update(std::vector<Item*>& items, Mario& mario) {
		_data->assets.getSound("Bump").play();
		if (!_opened) {
			if (_item != Items::empty) {
				if (_item == Items::coin) {
					_data->assets.getSound("Coin").play();
					items.emplace_back(new Coin(_tile.getPosition().x + _tile.getGlobalBounds().width / 2, _tile.getPosition().y, _coins, _scores, _data));
					_bounce = true;
					_coinCounter--;
				} else if (_item == Items::powerUp) {
					_data->assets.getSound("Powerup_appear").play();
					if (mario.bigMario) {
						items.emplace_back(new FireFlower(_tile.getPosition().x, _tile.getPosition().y, _tile.getTextureRect() == BRICK_TILE ? Setting::OW : Setting::UG, _scores, _data));
					} else {
						items.emplace_back(new Mushroom(_tile.getPosition().x, _tile.getPosition().y, _scores, _data));
					}
					_tile.setTextureRect(_tile.getTextureRect() == BRICK_TILE ? BOX_TILE_OPENED : BRICK_TILE_OPENED_UG);
					_opened = true;
				}	
				if (_coinCounter == 0) {
					_tile.setTextureRect(_tile.getTextureRect() == BRICK_TILE ? BOX_TILE_OPENED : BRICK_TILE_OPENED_UG);
					_opened = true;
				}
			} else if (mario.bigMario) {
				_data->assets.getSound("Break_block").play();
				_explode = true;
				_tile.setColor(sf::Color(254, 255, 255));
				_bounce = true;
				_clock2.restart();
			} else {
				_bounce = true;
			}
		}
	}

	void BrickTile::animate(const float& dt) {
		if (!_destroyed) {

			if (_tileY <= 0 && _bounce) {
				_tileY += _animationSpeedY * dt;
				_tile.move(0, _animationSpeedY * dt);
				if (_tileY < _animationHeight) {
					_tile.move(0, (_animationHeight + abs(_tileY)));
					_tileY = _animationHeight;
					_animationSpeedY *= -1;
					if (_explode) {
						_tile.setPosition(0, -100);
						_bounce = false;
					}
				}
			} else if (_tileY > 0 && _bounce) {
				_tile.move(0, -(_tileY));
				_tileY = 0;
				_animationSpeedY = -300;
				_bounce = false;
			}


			if (_explode) {
		
				for (char i = 0; i < 4; i++) {
					if (i % 2 == 0) {
						_particles[i].move(_leftParticlesVector * particleAnimationSpeed * dt);
					} else {
						_particles[i].move(_rightParticlesVector * particleAnimationSpeed * dt);
					}
					if (i > 1) {
						_particles[i].move(0, -particleAnimationSpeed * 1.15f * dt);
					} else {
						_particles[i].move(0, -particleAnimationSpeed * 0.1f * dt);
					}
				}
				_leftParticlesVector.y += 6 * dt;
				_rightParticlesVector.y += 6 * dt;
				if (_leftParticlesVector.x < -0.35f) {
					_leftParticlesVector.x += 1 * dt;
					_rightParticlesVector.x += -1 * dt;
				}

				if (_clock.getElapsedTime().asSeconds() > BRICK_PARTICLE_ANIMATION_TIME / _particleAnimationFrames.size()) {
					if (_particleAnimationIterator < _particleAnimationFrames.size() - 1) {
						_particleAnimationIterator++;
					} else {
						_particleAnimationIterator = 0;
					}
					for (char i = 0; i < 4; i++) {
						_particles[i].setTextureRect(_particleAnimationFrames[_particleAnimationIterator]);
					}
					_clock.restart();
				}

				if (_particles[3].getPosition().y > SCREEN_HEIGHT) {
					_destroyed = true;
				}

			}
		}

	}

	sf::Sprite& BrickTile::getTile() {
		return _tile;
	}



}