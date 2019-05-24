#include "Piranha.hpp"
#include "Collision.hpp"

namespace Game {

	Piranha::Piranha(const int x, const int y, Setting setting, std::vector<Score>& scores, gameDataRef data)
		: _data(data), _piranha(_data->assets.getTexture("Enemies")), _name("Piranha"), _startY(y + TILE_SIZE), _scores(scores)
	{
	
		if (setting == Setting::OW) {
			_animationFrames = { PIRANHA1, PIRANHA2 };
			_piranha.setTextureRect(PIRANHA1);
		} else {
			_animationFrames = { PIRANHA1_UG, PIRANHA2_UG };
			_piranha.setTextureRect(PIRANHA1_UG);
		}

		_piranha.setPosition(x + (PIPE_TOP.width / 2 - _piranha.getGlobalBounds().width / 2) * 4.0f, y + TILE_SIZE);
		_piranha.setScale(4.0f, 4.0f);

	}

	void Piranha::draw() {
		_data->window.draw(_piranha);
	}

	bool Piranha::shouldBeUpdated(Mario& mario) {
		if (_piranha.getPosition().x + _piranha.getGlobalBounds().width < mario.cameraX) {
			_delete = true;
		}
		return abs(mario.position.x - _piranha.getPosition().x) < _renderDistance;
	}

	void Piranha::update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario) {

			this->animate();

			if (!_move && _clock2.getElapsedTime().asSeconds() > 1.2f) {
				if (Collision::distanceBetween(mario.mario.getPosition(), sf::Vector2f(_piranha.getPosition().x + _piranha.getGlobalBounds().width / 2, _piranha.getPosition().y)) > 230) {
					_move = true;
				}
			} else if (Collision::checkSpriteCollision(_piranha, 0.6f, 0.7f, mario.mario)) {
				mario.takeDamage = true;
			}
		
			if (_move && _clock2.getElapsedTime().asSeconds() > 1.2f) {

				if (_piranha.getPosition().y < _startY - _piranha.getGlobalBounds().height + 4.0f) {
					dir = down;
					_clock2.restart();
				} else if (_piranha.getPosition().y > _startY) {
					dir = up;
					_clock2.restart();
					_move = false;
				}

				if (dir == up) {
					_piranha.move(0, -125 * dt);
				} else {
					_piranha.move(0, 125 * dt);
				}

			}

	}

	void Piranha::animate() {
		if (_clock.getElapsedTime().asSeconds() > PIRANHA_ANIMATON_TIME / _animationFrames.size()) {
			if (_animationIterator < _animationFrames.size() - 1) {
				_animationIterator++;
			} else {
				_animationIterator = 0;
			}
			_piranha.setTextureRect(_animationFrames[_animationIterator]);
			_clock.restart();
		}
	}

	sf::Sprite& Piranha::getSprite() {
		return _piranha;
	}

	void Piranha::setPosition(sf::Vector2f position) {

	}

	bool Piranha::shell() {
		return false;
	}

	bool Piranha::sliding() {
		return false;
	}

	void Piranha::turn() {

	}

	void Piranha::flip(const float angle) {

	}

	std::string& Piranha::getName() {
		return _name;
	}

	bool Piranha::shouldBeDeleted() {
		return _delete;
	}

	void Piranha::kill() {
		_scores.emplace_back(Score(_piranha.getPosition().x, _piranha.getPosition().y, 200, _data));
		_delete = true;
	}

	bool Piranha::checkIfDead() {
		return false;
	}



}