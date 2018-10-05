#include "Pole.hpp"
#include "DEFINITIONS.hpp"

namespace engine {

	Pole::Pole(gameDataRef data)
		: _data(data), _flag(_data->assets.getTexture("Items"), POLE_FLAG)
	{
		_flag.setScale(_scale, _scale);
		poleSprites[0].setTexture(_data->assets.getTexture("Tiles"));
		poleSprites[0].setTextureRect(POLE_TOP);
		poleSprites[0].setScale(_scale, _scale);
		for (int i = 1; i < poleSprites.size(); i++) {
			poleSprites[i].setTexture(_data->assets.getTexture("Tiles"));
			poleSprites[i].setTextureRect(POLE);
			poleSprites[i].setScale(_scale, _scale);
		}
	}


	void Pole::draw() {
		for (int i = 0; i < poleSprites.size(); i++) {
			_data->window.draw(poleSprites[i]);
		}
		_data->window.draw(_flag);
	}

	void Pole::setPosition(const int x, const int y) {
		_flag.setPosition(x - 8 * _scale, y + TILE_SIZE + 2);
		poleSprites[0].setPosition(x + _scale * 4, y + _scale * 8);
		for (int i = 1; i < poleSprites.size(); i++) {
			poleSprites[i].setPosition(x + _scale * 7, y + i * TILE_SIZE);
		}
	}

	bool Pole::updateFlag(const float& dt) {
		if (_flag.getPosition().y < SCREEN_HEIGHT - TILE_SIZE * 2.5 - _flag.getGlobalBounds().height - 12) {
			_flag.move(0, _flagSpeed * dt);
			return false;
		} else {
			return true;
		}
	}


}