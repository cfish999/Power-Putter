#pragma once

#include <SFML/Graphics.hpp>

namespace Fish {

	class Collision {
	public:
		Collision();

		bool CheckTargetAndBallCollision(sf::Sprite sprite1, sf::Sprite sprite2);
		bool CheckBoundAreaAndBallCollision(sf::Sprite sprite1, sf::Vector2f window);
		int CheckBallAndSquareCollision(sf::Sprite sprite1, sf::Sprite sprite2);
		bool CheckBallAndWindCollision(sf::Sprite sprite1, sf::Sprite sprite2);
		int CheckBallAndRectangleCollision(sf::Sprite sprite1, sf::Sprite sprite2);
		bool CheckBallAndSpringSideCollision(sf::Sprite sprite1, sf::Sprite sprite2);
		float CheckDistanceFromFan(sf::Sprite sprite1, sf::Sprite sprite2, bool upOrDown);

	private:
		int _formatting = 0;
	};
}