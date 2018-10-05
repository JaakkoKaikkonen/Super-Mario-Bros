#include "Pipe.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace engine {

	Pipe::Pipe(const int& x, const int& y, const sf::IntRect& texture, gameDataRef data)
		: _data(data), _pipe(_data->assets.getTexture("Tiles"), texture)
	{
		if (_pipe.getTextureRect() == PIPE_BOTTOM) {
			_pipe.setPosition(x + 8, y);
		} else {
			_pipe.setPosition(x, y);
		}

		_pipe.setScale(4.0f, 4.0f);
	}

	void Pipe::draw() {
		_data->window.draw(_pipe);
	}


	void Pipe::update() {
		
	}

	void Pipe::animate() {

	}

	sf::Sprite& Pipe::getTile() {
		return _pipe;
	}

}