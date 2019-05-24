#include "HUD.hpp"
#include <string>
#include <iostream>

namespace Game {

	HUD::HUD(gameDataRef data)
		: _data(data), _coin(_data->assets.getTexture("Items"), COIN01), _cross(_data->assets.getTexture("HUD"), HUD_CROSS), _marioSprite(_data->assets.getTexture("Mario"), SMALL_MARIO_IDLE_RIGHT)
	{

		_mario.setFont(_data->assets.getFont("Font"));
		_time.setFont(_data->assets.getFont("Font"));
		_scoreText.setFont(_data->assets.getFont("Font"));
		_coinText.setFont(_data->assets.getFont("Font"));
		_world.setFont(_data->assets.getFont("Font"));
		_level.setFont(_data->assets.getFont("Font"));
		_timeText.setFont(_data->assets.getFont("Font"));
		_lifes.setFont(_data->assets.getFont("Font"));
		_gameOver.setFont(_data->assets.getFont("Font"));
		
		_coin.setScale(2.8f, 2.8f);
		_cross.setScale(4.5f, 4.5f);
		_marioSprite.setScale(4.2f, 3.5f);

		_world.setCharacterSize(35);
		_mario.setCharacterSize(35);
		_time.setCharacterSize(35);
		_scoreText.setCharacterSize(35);
		_coinText.setCharacterSize(35);
		_level.setCharacterSize(35);
		_timeText.setCharacterSize(35);
		_lifes.setCharacterSize(35);
		_gameOver.setCharacterSize(35);
	
		_mario.setString("MARIO");
		_time.setString("TIME");
		_world.setString("WORLD");
		_gameOver.setString("GAME OVER");
		//_scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);

	}


	void HUD::draw() {
		_data->window.draw(_mario);
		_data->window.draw(_time);
		_data->window.draw(_scoreText);
		_data->window.draw(_coin);
		_data->window.draw(_cross);
		_data->window.draw(_coinText);
		_data->window.draw(_world);
		_data->window.draw(_level);
		_data->window.draw(_timeText);
	}


	void HUD::loadingScreenDraw() {
		_data->window.draw(_mario);
		_data->window.draw(_time);
		_data->window.draw(_scoreText);
		_coin.setTextureRect(_coinAnimationFramesUg[0]);
		_animationIterator = 0;
		_data->window.draw(_coin);
		_data->window.draw(_cross);
		_data->window.draw(_coinText);
		_data->window.draw(_world);
		_data->window.draw(_level);

		if (std::stoi((const std::string&)_lifes.getString())) {

			_world.setPosition(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.4f);
			_level.setPosition(SCREEN_WIDTH * 0.52f, SCREEN_HEIGHT * 0.4f);
			_cross.setPosition(SCREEN_WIDTH * 0.46f, SCREEN_HEIGHT / 2 + _cross.getGlobalBounds().height);

			_data->window.draw(_world);
			_data->window.draw(_level);
			_data->window.draw(_cross);

			_lifes.setPosition(SCREEN_WIDTH * 0.53f, SCREEN_HEIGHT / 2 + _lifes.getGlobalBounds().height / 3);
			_data->window.draw(_lifes);

			_marioSprite.setPosition(SCREEN_WIDTH * 0.38f, SCREEN_HEIGHT / 2);
			_data->window.draw(_marioSprite);

		} else {

			_gameOver.setPosition(SCREEN_WIDTH / 2 - _gameOver.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - _gameOver.getGlobalBounds().height / 2);
			_data->window.draw(_gameOver);
			_data->assets.getSound("GameOver").play();

		}
	}


	void HUD::update(const int& score, const int& coins, const int& time, const float& cameraX) {
		_mario.setPosition(cameraX + SCREEN_WIDTH * 0.075f, SCREEN_HEIGHT * 0.03f);
		_time.setPosition(cameraX + SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.03f);
		_scoreText.setPosition(cameraX + SCREEN_WIDTH * 0.075f, SCREEN_HEIGHT * 0.075f);
		_coin.setPosition(cameraX + SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.075f);
		_cross.setPosition(cameraX + SCREEN_WIDTH * 0.38f, SCREEN_HEIGHT * 0.085f);
		_coinText.setPosition(cameraX + SCREEN_WIDTH * 0.405f, SCREEN_HEIGHT * 0.075f);
		_world.setPosition(cameraX + SCREEN_WIDTH * 0.57f, SCREEN_HEIGHT * 0.03f);
		_level.setPosition(cameraX + SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.075f);
		_timeText.setPosition(cameraX + SCREEN_WIDTH * 0.83f, SCREEN_HEIGHT * 0.075f);
		
		_scoreText.setString(std::string("000000").erase(0, std::to_string(score).length()) + std::to_string(score));
		_coinText.setString(std::string("00").erase(0, std::to_string(coins).length()) + std::to_string(coins));
		_timeText.setString(std::to_string(LEVEL_TIME - time));

		//std::cout << std::to_string(coins).length() << std::endl;


		if (_clock.getElapsedTime().asSeconds() > COIN_ANIMATION_TIME / _coinAnimationFrames.size()) {
			if (_animationIterator < _coinAnimationFrames.size() - 1) {
				_animationIterator++;
			} else {
				_animationIterator = 0;
			}
			_coin.setTextureRect(backgroundColor == BACKGROUND_COLOR01 ? _coinAnimationFrames[_animationIterator] : _coinAnimationFramesUg[_animationIterator]);
			_clock.restart();
		}

	}


	void HUD::updateLevel(const int world, const int level, const int& lifes) {
		_level.setString(std::to_string(world) + "-" + std::to_string(level));
		_lifes.setString(std::to_string(lifes));
	}



}