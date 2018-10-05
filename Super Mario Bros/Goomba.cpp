#include "Goomba.hpp"
#include "Collision.hpp"
#include <iostream>


namespace engine {

	Goomba::Goomba(const int x, const int y, Setting setting, std::vector<Score>& scores, gameDataRef data)
		: _data(data), _goomba(_data->assets.getTexture("Enemies")), _name("Goomba"), _position(x, y), _velocity(-90.0f, 0.0f), _acceleration(0.0f, 0.0f), _scores(scores)
	{
		_goomba.setScale(4.0f, 4.0f);
		_goomba.setPosition(_position);
		if (setting == Setting::OW) {
			_goombaAnimationFrames = { GOOMBA1, GOOMBA2 };
			_goomba.setTextureRect(GOOMBA1);
		} else {
			_goombaAnimationFrames = { GOOMBA1_UG, GOOMBA2_UG };
			_goomba.setTextureRect(GOOMBA1_UG);
		}
	}


	Goomba::~Goomba()
	{
	}

	void Goomba::draw() {
		if (_clock2.getElapsedTime().asSeconds() < 0.7f) {
			_data->window.draw(_goomba);
		}
	}

	bool Goomba::shouldBeUpdated(Mario& mario) {
		if (_goomba.getPosition().y > SCREEN_HEIGHT || _goomba.getPosition().x + _goomba.getGlobalBounds().width < mario.cameraX || (_stomped && _clock2.getElapsedTime().asSeconds() > 0.7f)) {
			_delete = true;
		}
		return !_stomped && abs(mario.position.x - _position.x) < _renderDistance;
	}

	void Goomba::update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario) {
		
		if (!_flipped) {
			this->animate();
		}

		_clock2.restart();

		this->applyGravity();

		_velocity.x += _acceleration.x * dt;
		_position.x += _velocity.x * dt;
		_acceleration.x = 0;
	

		_goomba.setPosition(_position);

		//std::cout << _velocity.y << std::endl;


		if (!_flipped) {
			bool exit = false;
			for (int i = 0; i < collisionGrid.size(); i++) {
				if (exit) break;
				if (Collision::checkSpriteCollision(collisionGrid[i].boundary, _goomba)) {
					for (int j = 0; j < collisionGrid[i].tiles.size(); j++) {
						if (Collision::checkSpriteCollision(_goomba, 1.0f, 0.9f, collisionGrid[i].tiles[j]->getTile())) {
							if (_velocity.x > 0) {
								_position.x = collisionGrid[i].tiles[j]->getTile().getPosition().x - _goomba.getGlobalBounds().width;
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

			if (!mario.growingAnimation && !mario.takeDamage) {
				if (mario.bigMario) {
					if (Collision::checkSpriteCollision(mario.mario, 0.9f, 0.8f, _goomba) && !mario.dead) {
						mario.takeDamage = true;
					}
				} else {
					if (Collision::checkSpriteCollision(mario.mario, mario.hitBoxScale - 0.1f, 0.8f, _goomba) && !mario.dead) {
						mario.takeDamage = true;
					}
				}

			}
		}

		_velocity.y += _acceleration.y * dt;
		_position.y += _velocity.y * dt;
		//std::cout << _acceleration.x << "\t" << _acceleration.y << std::endl;
		_acceleration.y = 0;
			

		_goomba.setPosition(_position);

		if (!_flipped) {
			bool exit = false;
			for (int i = 0; i < collisionGrid.size(); i++) {
				if (exit) break;
				if (Collision::checkSpriteCollision(collisionGrid[i].boundary, _goomba)) {
					for (int j = 0; j < collisionGrid[i].tiles.size(); j++) {
						if (Collision::checkSpriteCollision(_goomba, 0.95f, 1.0f, collisionGrid[i].tiles[j]->getTile())) {
							if(collisionGrid[i].tiles[j]->getTile().getPosition().y + 1.0f < _position.y + _goomba.getGlobalBounds().height) {
								_position.y = collisionGrid[i].tiles[j]->getTile().getPosition().y - _goomba.getGlobalBounds().height;
								_velocity.y = 0.0f;
								exit = true;
								break;
							} else {
								_position.y = collisionGrid[i].tiles[j]->getTile().getPosition().y - _goomba.getGlobalBounds().height;
								_velocity.y = 0.0f;
							}
						}
					}
				}
			}

			if (!mario.growingAnimation && !mario.takeDamage && mario.velocity.y > 0) {
				if (Collision::checkSpriteCollision(_goomba, 0.95f, 0.98f, mario.mario) && !mario.dead && !mario.takeDamage) {
					if (mario.position.y < _position.y) {
						_goomba.setTextureRect(_goombaAnimationFrames[0] == GOOMBA1 ? GOOMBA_DEAD : GOOMBA_DEAD_UG);
						_scores.emplace_back(Score(_goomba.getPosition().x, _goomba.getPosition().y, 100, _data));
						_stomped = true;
						_clock.restart();
						_data->assets.getSound("Stomp").play();
						mario.velocity.y = 0;
						mario.jump(-110000.0f);
					}
				}
			}

			if (_posY > _position.y) {
				this->flip(-PI / 3);
			}

			_posY = _position.y - 1.0f;


			_goomba.setPosition(_position);

		}

		
	}



	void Goomba::animate() {
		if (_clock.getElapsedTime().asSeconds() > GOOMBA_ANIMATION_TIME / _goombaAnimationFrames.size()) {
			if (_animationIterator < _goombaAnimationFrames.size() - 1) {
				_animationIterator++;
			} else {
				_animationIterator = 0;
			}
			_goomba.setTextureRect(_goombaAnimationFrames[_animationIterator]);
			_clock.restart();
		}

	}

	void Goomba::applyGravity() {
		_acceleration.y += 1500.0f;
	}
 
	void Goomba::flip(const float angle) {
		if (!_flipped) {
			_goomba.setTextureRect(_goombaAnimationFrames[0] == GOOMBA1 ? GOOMBA_UPSIDEDOWN : GOOMBA_UPSIDEDOWN_UG);
			_scores.emplace_back(Score(_goomba.getPosition().x, _goomba.getPosition().y, 100, _data));
			_flipped = true;
			_dead = true;
			_acceleration += sf::Vector2f(cos(angle) * 100000, sin(angle) * 100000);
			_velocity.x = 0;
			_velocity.y = 0;
		}
	}


	sf::Sprite& Goomba::getSprite() {
		return _goomba;
	}

	void Goomba::setPosition(sf::Vector2f position) {
		_position = position;
	}

	bool Goomba::shell() {
		return 0;
	}

	bool Goomba::sliding() {
		return 0;
	}

	std::string& Goomba::getName() {
		return _name;
	}

	bool Goomba::shouldBeDeleted() {
		return _delete;
	}

	void Goomba::turn() {
		_velocity.x *= -1;
	}

	void Goomba::kill() {
		_dead = true;
	}

	bool Goomba::checkIfDead() {
		return _dead;
	}

}