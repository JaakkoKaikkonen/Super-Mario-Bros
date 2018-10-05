#pragma once

#include <SFML/Graphics.hpp>

namespace engine {

	class Collision
	{
	public:
		static bool checkSpriteCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
		static bool checkSpriteCollision(const sf::FloatRect& sprite1, const sf::Sprite& sprite2);
		static bool checkSpriteCollision(const sf::Sprite& sprite1, const float& scale1, const sf::Sprite& sprite2, const float& scale2);
		static bool checkSpriteCollision(const sf::Sprite& sprite1, const float& scaleX, const float& scaleY, const sf::Sprite& sprite2);

		static float distanceBetween(const float& x1, const float& y1, const float& x2, const float& y2);
		static float distanceBetween(const sf::Vector2f& vector1, const sf::Vector2f& vector2);

	};

}

