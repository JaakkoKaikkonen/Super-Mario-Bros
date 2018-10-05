#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace engine {


	class Score
	{
	public:
		Score(const int x, const int y, const int score, gameDataRef data);
		~Score();

		void update(const float& dt);

		void draw();

		void addScore(int& score);

		bool shouldBeDeleted();
	
	private:
		gameDataRef _data;

		sf::Text _score;

		float _startY;

		bool _scoreAdded = false;

		bool _delete = false;

	};



}
