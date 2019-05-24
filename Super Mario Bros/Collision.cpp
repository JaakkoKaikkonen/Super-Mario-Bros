#include "Collision.hpp"

namespace Game {

	bool Collision::checkSpriteCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
	
		return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
	}

	bool Collision::checkSpriteCollision(const sf::FloatRect& sprite1, const sf::Sprite& sprite2) {
		return sprite1.intersects(sprite2.getGlobalBounds());
	}

	bool Collision::checkSpriteCollision(const sf::Sprite& sprite1, const float& scale1, const sf::Sprite& sprite2, const float& scale2) {

		sf::FloatRect rect1 = sprite1.getGlobalBounds();
		sf::FloatRect rect2 = sprite2.getGlobalBounds();

		rect1.left += (rect1.width - rect1.width * scale1) / 2;
		rect1.top += (rect1.height - rect1.height * scale1) / 2;
		rect2.left += (rect2.width - rect2.width * scale2) / 2;
		rect2.top += (rect2.height - rect2.height * scale2) / 2;

		rect1.width *= scale1;
		rect1.height *= scale1;
		rect2.width *= scale2;
		rect2.height *= scale2;

		return rect1.intersects(rect2);
	}


	bool Collision::checkSpriteCollision(const sf::Sprite& sprite1, const float& scaleX, const float& scaleY, const sf::Sprite& sprite2) {

		sf::FloatRect rect1 = sprite1.getGlobalBounds();
		sf::FloatRect rect2 = sprite2.getGlobalBounds();

		rect1.left += (rect1.width - rect1.width * scaleX) / 2;
		rect1.top += (rect1.height - rect1.height * scaleY) / 2;

		rect1.width *= scaleX;
		rect1.height *= scaleY;

		return rect1.intersects(rect2);
	}


	float Collision::distanceBetween(const float& x1, const float& y1, const float& x2, const float& y2) {
		float x = x1 - x2;
		float y = y1 - y2;
		return sqrt(x * x + y * y);
	}

	float Collision::distanceBetween(const sf::Vector2f& vector1, const sf::Vector2f& vector2) {
		sf::Vector2f vector = vector1 - vector2;
		return sqrt(vector.x * vector.x + vector.y * vector.y);
	}

}
