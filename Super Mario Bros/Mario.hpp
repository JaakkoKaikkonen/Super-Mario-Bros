#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include <array>

namespace engine {

	class Mario
	{
	public:
		Mario(gameDataRef data);

		void updateX(const float& dt);
		void updateY(const float& dt);

		void checkCameraCollision();

		void move(const float& speed);

		void jump(const float speed);

		void animate(const float& dt);

		void updateCamera(const float& dt);

		void reset();

		void applyGravity();

		void draw();


	public:
		sf::Sprite mario;

		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Vector2f acceleration;

		Dir dir = Dir::Right;

		sf::View camera;

		bool bigMario = false;

		bool fireForm = false;

		bool throwFireBall = false;

		float cameraX = 0;

		float cameraDistance;

		float cameraSpeed;

		float hitBoxScale = 0.75f;

		bool isCollidingY = true;

		bool growingAnimation = false;

		bool crouch = false;

		bool climbing = false;

		bool flagDown = false;

		bool walk = false;

		bool insideCastle = false;

		bool takeDamage = false;

		bool dead = false;

		bool dontStandUp = false;

		bool down = false;

		bool up = false;

		float marioScaleX = 4.2f;

		float marioScaleY = 3.5f;

	private:
		gameDataRef _data;

		sf::Clock _clock;

		const float _smallMarioHeight = SMALL_MARIO_IDLE_RIGHT.height * marioScaleY;

		unsigned short int _growingAnimationIterator = 0;

		short int _shrinkingAnimationIterator = 18;

		std::array<float, 19> _shrinkingAnimationPositions = { _smallMarioHeight, 0.0f,  0.0f, -_smallMarioHeight,  _smallMarioHeight, 0.0f, 0.0f, -_smallMarioHeight,  _smallMarioHeight, 0.0f,   0.0f, 0.0f,  0.0f, -_smallMarioHeight, _smallMarioHeight , 0.0f, 0.0f , 0.0f ,0.0f };

		std::array<float, 10> _growingAnimationPositions = { 0.0f, -_smallMarioHeight, _smallMarioHeight, -_smallMarioHeight, _smallMarioHeight, -_smallMarioHeight, 0.0f, _smallMarioHeight, -_smallMarioHeight, 0.0f};

		std::array<sf::IntRect, 19> _shrinkingRightAnimatinFrames = { SMALL_MARIO_IDLE_RIGHT , EMPTY, SMALL_BIG_MARIO_RIGHT, EMPTY, SMALL_MARIO_IDLE_RIGHT, EMPTY,  SMALL_BIG_MARIO_RIGHT, EMPTY, SMALL_MARIO_IDLE_RIGHT, EMPTY,
																	SMALL_BIG_MARIO_RIGHT, EMPTY, BIG_MARIO_IDLE_RIGHT, EMPTY, SMALL_MARIO_IDLE_RIGHT, EMPTY, SMALL_BIG_MARIO_RIGHT, EMPTY, BIG_MARIO_IDLE_RIGHT };

		std::array<sf::IntRect, 19> _shrinkingLeftAnimatinFrames = { SMALL_MARIO_IDLE_LEFT , EMPTY ,  SMALL_BIG_MARIO_LEFT, EMPTY, SMALL_MARIO_IDLE_LEFT, EMPTY, SMALL_BIG_MARIO_LEFT, EMPTY, SMALL_MARIO_IDLE_LEFT, EMPTY,
																	SMALL_BIG_MARIO_LEFT, EMPTY, BIG_MARIO_IDLE_LEFT, EMPTY, SMALL_MARIO_IDLE_LEFT, EMPTY, SMALL_BIG_MARIO_LEFT, EMPTY, BIG_MARIO_IDLE_LEFT };

		std::array<sf::IntRect, 10> _growingRightAnimatinFrames = { SMALL_MARIO_IDLE_RIGHT , SMALL_BIG_MARIO_RIGHT, SMALL_MARIO_IDLE_RIGHT, SMALL_BIG_MARIO_RIGHT, SMALL_MARIO_IDLE_RIGHT,
																	SMALL_BIG_MARIO_RIGHT, BIG_MARIO_IDLE_RIGHT, SMALL_MARIO_IDLE_RIGHT, SMALL_BIG_MARIO_RIGHT, BIG_MARIO_IDLE_RIGHT };

		std::array<sf::IntRect, 10> _growingLeftAnimatinFrames = { SMALL_MARIO_IDLE_LEFT , SMALL_BIG_MARIO_LEFT, SMALL_MARIO_IDLE_LEFT, SMALL_BIG_MARIO_LEFT, SMALL_MARIO_IDLE_LEFT,
																	SMALL_BIG_MARIO_LEFT, BIG_MARIO_IDLE_LEFT, SMALL_MARIO_IDLE_LEFT, SMALL_BIG_MARIO_LEFT, BIG_MARIO_IDLE_LEFT };

		unsigned short int _runRightAnimationIterator = 0;

		unsigned short int _runLeftAnimationIterator = 0;

		std::array<sf::IntRect, 3> _smallMarioRunRightAnimationFrames = { SMALL_MARIO_RUN_RIGHT_01 , SMALL_MARIO_RUN_RIGHT_02, SMALL_MARIO_RUN_RIGHT_03 };

		std::array<sf::IntRect, 3> _smallMarioRunLeftAnimationFrames = { SMALL_MARIO_RUN_LEFT_01 , SMALL_MARIO_RUN_LEFT_02, SMALL_MARIO_RUN_LEFT_03 };

		std::array<sf::IntRect, 3> _bigMarioRunRightAnimationFrames = { BIG_MARIO_RUN_RIGHT_01 , BIG_MARIO_RUN_RIGHT_02, BIG_MARIO_RUN_RIGHT_03 };

		std::array<sf::IntRect, 3> _bigMarioRunLeftAnimationFrames = { BIG_MARIO_RUN_LEFT_01 , BIG_MARIO_RUN_LEFT_02, BIG_MARIO_RUN_LEFT_03 };

		std::array<sf::IntRect, 3> _fireMarioRunRightAnimationFrames = { FIRE_MARIO_RUN_RIGHT_01 , FIRE_MARIO_RUN_RIGHT_02, FIRE_MARIO_RUN_RIGHT_03 };

		std::array<sf::IntRect, 3> _fireMarioRunLeftAnimationFrames = { FIRE_MARIO_RUN_LEFT_01 , FIRE_MARIO_RUN_LEFT_02, FIRE_MARIO_RUN_LEFT_03 };

		std::array<sf::IntRect, 3> _fireMarioThrowRunRightAnimationFrames = { FIRE_MARIO_THROW_RIGHT01 , FIRE_MARIO_THROW_RIGHT02, FIRE_MARIO_THROW_RIGHT03 };

		std::array<sf::IntRect, 3> _fireMarioThrowRunLeftAnimationFrames = { FIRE_MARIO_THROW_LEFT01 , FIRE_MARIO_THROW_LEFT02, FIRE_MARIO_THROW_LEFT03 };

		unsigned short int _climbAnimationIterator = 0;

		std::array<sf::IntRect, 2> _bigMarioClimbingAnimationFrames = { BIG_MARIO_CLIMB_POLE1, BIG_MARIO_CLIMB_POLE2 };

		std::array<sf::IntRect, 2> _smallMarioClimbingAnimationFrames = { SMALL_MARIO_CLIMB_POLE1, SMALL_MARIO_CLIMB_POLE2 };

		std::array<sf::IntRect, 2> _fireMarioClimbingAnimationFrames = { FIRE_MARIO_CLIMB_POLE1, FIRE_MARIO_CLIMB_POLE2 };

		float _accumulator = 0.0f;

		bool _hasClimbedDown = false;

	};


}

