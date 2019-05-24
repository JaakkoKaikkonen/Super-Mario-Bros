#include "Score.hpp"

namespace Game {

	Score::Score(const int x, const int y, const int score, gameDataRef data)
		: _data(data), _startY(y)
	{
		_score.setFont(_data->assets.getFont("Font"));
		_score.setCharacterSize(20);
		_score.setString(std::to_string(score));
		_score.setPosition(x, y);
	}


	void Score::update(const float& dt) {
		if (_score.getPosition().y > _startY - 120.0f) {
			_score.move(0.0f, SCORE_SPEED * dt);
		} else {
			_delete = true;
		}
	}

	void Score::draw() {
		_data->window.draw(_score);
	}

	void Score::addScore(int& score) {
		if (!_scoreAdded) {
			score += std::stoi((const std::string&)_score.getString());
			_scoreAdded = true;
		}
	}

	bool Score::shouldBeDeleted() {
		return _delete;
	}



}