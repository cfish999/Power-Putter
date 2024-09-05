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

	};
}