#include "Mushroom.hpp"
#include "Collision.hpp"
#include "DEFINITIONS.hpp"
#include "Tile.hpp"
#include <iostream>

namespace engine {

	Mushroom::Mushroom(const int x, const int y, gameDataRef data)
		: _data(data), _mushroom(_data->assets.getTexture("Items"), MUSHROOM_ITEM), _velocity(200.0f, 0.0f), _acceleration(0.0f, 0.0f), _startY(y)
	{
		_mushroom.setScale(4.0f, 4.0f);
		_position = sf::Vector2f(x, y - _mushroom.getGlobalBounds().height / 3.5);
		_mushroom.setPosition(_position);
	}


	void Mushroom::draw() {
		_data->window.draw(_mushroom);
	}

	void Mushroom::animate() {
		
	}

	void Mushroom::update(const float& dt, std::vector<CollisionGrid>& collisionGrid, Mario& mario) {


		if (!_animationDone) {
			_position.y += _animationSpeed * dt;
			if (_startY - _position.y > _mushroom.getGlobalBounds().height) {
				_position.y = _startY - _mushroom.getGlobalBounds().height - 0.001f;
				_animationDone = true;
			}

		} else {

			this->applyGravity();

			_position.x += _velocity.x * dt;

			for (int i = 0; i < collisionGrid.size(); i++) {
				if (Collision::checkSpriteCollision(collisionGrid[i].boundary, _mushroom)) {
					for (int j = 0; j < collisionGrid[i].tiles.size(); j++) {
						if (Collision::checkSpriteCollision(_mushroom, 1.0f, 0.8f, collisionGrid[i].tiles[j]->getTile())) {
							if (_velocity.x > 0) {
								_position.x = collisionGrid[i].tiles[j]->getTile().getPosition().x - _mushroom.getGlobalBounds().width;
								_velocity.x *= -1.0f;
							} else {
								_position.x = collisionGrid[i].tiles[j]->getTile().getPosition().x + collisionGrid[i].tiles[j]->getTile().getGlobalBounds().width;
								_velocity.x *= -1.0f;
							}
						}
					}
				}
			}


			_velocity.y += _acceleration.y * dt;
			_position.y += _velocity.y * dt;
			_acceleration.y = 0;

			bool exit = false;
			for (int i = 0; i < collisionGrid.size(); i++) {
				if (exit) break;
				if (Collision::checkSpriteCollision(collisionGrid[i].boundary, _mushroom)) {
					for (int j = 0; j < collisionGrid[i].tiles.size(); j++) {
						if (Collision::checkSpriteCollision(_mushroom, 0.90f, 1.0f, collisionGrid[i].tiles[j]->getTile())) {
							_position.y = collisionGrid[i].tiles[j]->getTile().getPosition().y - _mushroom.getGlobalBounds().height;
							_velocity.y = 0;
							exit = true;
							break;
						}
					}
				}
			}

			if (Collision::checkSpriteCollision(_mushroom, 0.75f, 0.75f, mario.mario)) {
				mario.bigMario = true;
				mario.growingAnimation = true;
				_delete = true;
			} else if (_position.x < mario.cameraX - _mushroom.getGlobalBounds().width) {
				_delete = true;
			}
		}

		_mushroom.setPosition(_position);

	}

	bool Mushroom::shouldBeDeleted() {
		return _delete;
	}


	void Mushroom::applyGravity() {
		_acceleration.y += 900.0f;
	}


}