#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Mario.hpp"
#include <array>


namespace engine {

	class Money
	{
	public:
		Money(const int x, const int y, Setting setting, gameDataRef data);

		void animate();

		void update(Mario& mario, int& coins);

		void draw();

		bool shouldBeDeleted();

	private:
		gameDataRef _data;

		sf::Sprite _money;

		sf::Clock _clock;

		unsigned short int _animationIterator = 0;

		std::array<sf::IntRect, 6> _animationFrames = {  };

		bool _delete = false;
	};



}
