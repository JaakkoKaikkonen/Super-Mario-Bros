#include "Pipe.hpp"
#include "DEFINITIONS.hpp"
#include "Collision.hpp"

namespace engine {

	Pipe::Pipe(const int& x, const int& y, const sf::IntRect& texture, Mario& mario, const bool isPortal, gameDataRef data)
		: _data(data), _pipe(_data->assets.getTexture("Tiles"), texture), _isPortal(isPortal), _mario(mario)
	{
		
		if (_pipe.getTextureRect() == PIPE_BOTTOM || _pipe.getTextureRect() == PIPE_BOTTOM_UG) {
			_pipe.setPosition(x + 8, y);
			_pipe.setColor(sf::Color(254, 255, 255));
		} else {
			_pipe.setPosition(x, y);
			_pipe.setColor(sf::Color(254, 255, 255));
			if (_isPortal) {
				_pipe.setColor(sf::Color(254, 254, 255));
			}
		}

		_pipe.setScale(4.0f, 4.0f);
	}

	void Pipe::draw() {
		_data->window.draw(_pipe);
	}


	void Pipe::update() {
		
	}

	void Pipe::animate(const float& dt) {
		if (_isPortal && _pipe.getColor() == sf::Color(254, 254, 255)) {
			if (teleport) {
				_mario.position.x = _pipe.getPosition().x + _pipe.getGlobalBounds().width / 2 - _mario.mario.getGlobalBounds().width / 2;
				_mario.position.y = _pipe.getPosition().y - 0.1f;
				_mario.down = false;
				_mario.dir = Dir::Right;
				_mario.updateX(dt);
				_mario.updateY(dt);
				_mario.camera.setCenter(_mario.position.x + 380.0f, SCREEN_HEIGHT / 2);
				_mario.cameraX = _mario.position.x - (SCREEN_WIDTH / 2 - 380.0f);
				_data->window.setView(_mario.camera);
				_mario.updateCamera(dt);
				_mario.up = true;
				if (backgroundColor == BACKGROUND_COLOR01) {
					backgroundColor = BACKGROUND_COLOR02;
					_data->music.openFromFile(UG_THEME_MUSIC_FILEPATH);
					_data->music.play();
				} else {
					backgroundColor = BACKGROUND_COLOR01;
					_data->music.openFromFile(OW_THEME_MUSIC_FILEPATH);
					_data->music.play();
				}
				teleport = false;
			} else if (_mario.mario.getPosition().y > _pipe.getPosition().y  && _mario.mario.getPosition().x > _pipe.getPosition().x && _mario.mario.getPosition().x + _mario.mario.getGlobalBounds().width < _pipe.getPosition().x + _pipe.getGlobalBounds().width) {
				teleport = true;
				_pipe.setColor(sf::Color(254, 255, 254));
			} else if (_mario.up) {
				if (Collision::checkSpriteCollision(_pipe, _mario.mario)) {
					_mario.animate(dt);
					if (!Collision::checkSpriteCollision(_pipe, _mario.mario)) {
						_mario.up = false;
						_pipe.setColor(sf::Color(254, 255, 254));
						_mario.velocity.x = 0.0f;
						_mario.velocity.y = 0.0f;
						_mario.position.y = _pipe.getPosition().y - _mario.mario.getGlobalBounds().height;
					}
				}
			}
		}
		
	}

	sf::Sprite& Pipe::getTile() {
		return _pipe;
	}


	bool Pipe::teleport = false;

}